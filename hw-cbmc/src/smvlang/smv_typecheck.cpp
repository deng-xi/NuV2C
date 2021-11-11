/*******************************************************************\

Module: SMV Language Type Checking

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <cassert>
#include <set>
#include <algorithm>

#include <util/expr_util.h>
#include <util/location.h>
#include <util/typecheck.h>
#include <util/arith_tools.h>
#include <util/i2string.h>
#include <util/std_expr.h>

#include "smv_typecheck.h"
#include "expr2smv.h"

class smv_typecheckt:public typecheckt
{
public:
  smv_typecheckt(
    smv_parse_treet &_smv_parse_tree,
    symbol_tablet &_symbol_table,
    const std::string &_module,
    bool _do_spec,
    message_handlert &_message_handler):
    typecheckt(_message_handler),
    smv_parse_tree(_smv_parse_tree),
    symbol_table(_symbol_table),
    module(_module),
    do_spec(_do_spec)
  {
    nondet_count=0;
  }

  virtual ~smv_typecheckt() { }

  typedef enum { INIT, TRANS, OTHER } modet;

  void convert(smv_parse_treet::modulet &smv_module);
  void convert(smv_parse_treet::mc_varst &vars);

  void collect_define(const exprt &expr);
  void convert_defines(exprt::operandst &invar);
  void convert_define(const irep_idt &identifier);

  typedef enum { NORMAL, NEXT } expr_modet;
  virtual void convert(exprt &exprt, expr_modet expr_mode);

  virtual void typecheck(exprt &exprt, const typet &type, modet mode);
  virtual void typecheck_op(exprt &exprt, const typet &type, modet mode);

  virtual void typecheck();

  // overload to use SMV syntax
  
  virtual std::string to_string(const typet &type);
  virtual std::string to_string(const exprt &expr);

protected:
  smv_parse_treet &smv_parse_tree;
  symbol_tablet &symbol_table;
  const std::string &module;
  bool do_spec;

  class smv_ranget
  {
  public:
    smv_ranget():from(0), to(0)
    {
    }
  
    mp_integer from, to;
    
    bool is_contained_in(const smv_ranget &other) const
    {
      if(other.from>from) return false;
      if(other.to<to) return false;
      return true;
    }
    
    void make_union(const smv_ranget &other)
    {
      mp_min(from, other.from);
      mp_max(to, other.to);
    }
    
    void to_type(typet &dest) const
    {
      dest=typet(ID_range);
      dest.set(ID_from, integer2string(from));
      dest.set(ID_to, integer2string(to));
    }
    
    bool is_bool() const
    {
      return from==0 && to==1;
    }
    
    bool is_singleton() const
    {
      return from==to;
    }
  };
  
  void convert_type(const typet &type, smv_ranget &dest);
  void convert(smv_parse_treet::modulet::itemt &item);
  void typecheck(smv_parse_treet::modulet::itemt &item);

  smv_parse_treet::modulet *modulep;

  unsigned nondet_count;

  void flatten_hierarchy(smv_parse_treet::modulet &module);

  void instantiate(
    smv_parse_treet::modulet &smv_module,
    const irep_idt &identifier,
    const irep_idt &instance,
    const exprt::operandst &operands,
    const irept &location);
    
  void type_union(
    const typet &type1,
    const typet &type2,
    typet &dest);

  typedef std::map<irep_idt, exprt> rename_mapt;

  void instantiate_rename(exprt &expr,
                          const rename_mapt &rename_map);

  void convert_ports(smv_parse_treet::modulet &smv_module,
                     typet &dest);

  // for defines
  class definet
  {
  public:
    exprt value;
    bool typechecked, in_progress;
    
    explicit definet(const exprt &_v):value(_v), typechecked(false), in_progress(false)
    {
    }

    definet():typechecked(false), in_progress(false)
    {
    }
  };
  
  typedef hash_map_cont<irep_idt, definet, irep_id_hash> define_mapt;
  define_mapt define_map;
};

/*******************************************************************\

Function: smv_typecheckt::convert_ports

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::convert_ports(
  smv_parse_treet::modulet &smv_module,
  typet &dest)
{
  irept::subt &ports=dest.add(ID_ports).get_sub();

  ports.reserve(smv_module.ports.size());

  for(std::list<irep_idt>::const_iterator
      it=smv_module.ports.begin();
      it!=smv_module.ports.end();
      it++)
  {
    ports.push_back(exprt(ID_symbol));
    ports.back().set(ID_identifier,
      id2string(smv_module.name)+"::var::"+id2string(*it));
  }
}

/*******************************************************************\

Function: smv_typecheckt::flatten_hierarchy

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::flatten_hierarchy(smv_parse_treet::modulet &smv_module)
{
  for(smv_parse_treet::mc_varst::iterator
      it=smv_module.vars.begin();
      it!=smv_module.vars.end();
      it++)
  {
    smv_parse_treet::mc_vart &var=it->second;

    if(var.type.id()=="submodule")
    {
      exprt &inst=static_cast<exprt &>(static_cast<irept &>(var.type));

      Forall_operands(o_it, inst)
        convert(*o_it, NORMAL);

      instantiate(smv_module,
                  inst.get(ID_identifier),
                  it->first,
                  inst.operands(),
                  inst.find_location());
    }
  }
}

/*******************************************************************\

Function: smv_typecheckt::instantiate

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::instantiate(
  smv_parse_treet::modulet &smv_module,
  const irep_idt &identifier,
  const irep_idt &instance,
  const exprt::operandst &operands,
  const irept &location)
{
  symbol_tablet::symbolst::const_iterator s_it=
    symbol_table.symbols.find(identifier);

  if(s_it==symbol_table.symbols.end())
  {
    err_location(location);
    str << "submodule `"
        << identifier
        << "' not found";
    throw 0;
  }

  if(s_it->second.type.id()!=ID_module)
  {
    err_location(location);
    str << "submodule `"
        << identifier
        << "' not a module";
  }

  const irept::subt &ports=s_it->second.type.find(ID_ports).get_sub();

  // do the arguments/ports

  if(ports.size()!=operands.size())
  {
    err_location(location);
    str << "submodule `" << identifier
        << "' has wrong number of arguments";
    throw 0;
  }

  std::set<irep_idt> port_identifiers;
  rename_mapt rename_map;

  for(unsigned i=0; i<ports.size(); i++)
  {
    const irep_idt &identifier=ports[i].get(ID_identifier);
    rename_map.insert(std::pair<irep_idt, exprt>(identifier, operands[i]));
    port_identifiers.insert(identifier);
  }

  // do the variables

  std::string new_prefix=
    id2string(smv_module.name)+"::var::"+id2string(instance)+".";

  std::set<irep_idt> var_identifiers;

  forall_symbol_module_map(v_it, symbol_table.symbol_module_map, identifier)
  {
    symbol_tablet::symbolst::const_iterator s_it2=
      symbol_table.symbols.find(v_it->second);

    if(s_it2==symbol_table.symbols.end())
    {
      str << "symbol `" << v_it->second << "' not found";
      throw 0;
    }

    if(port_identifiers.find(s_it2->second.name)!=
       port_identifiers.end())
    {
    }
    else if(s_it2->second.type.id()==ID_module)
    {
    }
    else
    {
      symbolt symbol(s_it2->second);

      symbol.name=new_prefix+id2string(symbol.base_name);
      symbol.module=smv_module.name;

      rename_map.insert(std::pair<irep_idt, exprt>
                        (s_it2->second.name, symbol.symbol_expr()));

      var_identifiers.insert(symbol.name);

      symbol_table.move(symbol);
    }
  }

  // fix values (macros)

  for(std::set<irep_idt>::const_iterator
      v_it=var_identifiers.begin();
      v_it!=var_identifiers.end();
      v_it++)
  {
    symbol_tablet::symbolst::iterator s_it2=
      symbol_table.symbols.find(*v_it);

    if(s_it2==symbol_table.symbols.end())
    {
      str << "symbol `" << *v_it << "' not found";
      throw 0;
    }

    symbolt &symbol=s_it2->second;

    if(!symbol.value.is_nil())
    {
      instantiate_rename(symbol.value, rename_map);
      typecheck(symbol.value, symbol.type, OTHER);
    }
  }

  // get the transition system

  const transt &trans=to_trans_expr(s_it->second.value);

  std::string old_prefix=id2string(s_it->first)+"::var::";

  // do the transition system

  if(!trans.invar().is_true())
  {
    exprt tmp(trans.invar());
    instantiate_rename(tmp, rename_map);
    smv_module.add_invar(tmp);
  }
    
  if(!trans.init().is_true())
  {
    exprt tmp(trans.init());
    instantiate_rename(tmp, rename_map);
    smv_module.add_init(tmp);
  }
    
  if(!trans.trans().is_true())
  {
    exprt tmp(trans.trans());
    instantiate_rename(tmp, rename_map);
    smv_module.add_trans(tmp);
  }

}

/*******************************************************************\

Function: smv_typecheckt::instantiate_rename

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::instantiate_rename(
  exprt &expr,
  const rename_mapt &rename_map)
{
  Forall_operands(it, expr)
    instantiate_rename(*it, rename_map);

  if(expr.id()==ID_symbol || expr.id()==ID_next_symbol)
  {
    const irep_idt &old_identifier=expr.get(ID_identifier);
    bool next=expr.id()==ID_next_symbol;

    rename_mapt::const_iterator it=
      rename_map.find(old_identifier);

    if(it!=rename_map.end())
    {
      expr=it->second;

      if(next)
      {
        if(expr.id()==ID_symbol)
        {
          expr=it->second;
          expr.id(ID_next_symbol);
        }
        else
        {
          err_location(expr);
          str << "expected symbol expression here, but got "
              << to_string(it->second);
          throw 0;
        }
      }
      else
        expr=it->second;
    }
  }
}

/*******************************************************************\

Function: smv_typecheckt::typecheck_op

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::typecheck_op(
  exprt &expr,
  const typet &type,
  modet mode)
{
  if(expr.operands().size()==0)
  {
    err_location(expr);
    str << "Expected operands for " << expr.id_string()
        << " operator";
    throw 0;
  }

  Forall_operands(it, expr)
    typecheck(*it, type, mode);

  expr.type()=type;

  // type fixed?

  if(type.is_nil())
  {
    // figure out types

    forall_operands(it, expr)
      if(!it->type().is_nil())
      {
        expr.type()=it->type();
        break;
      }
  }
}

/*******************************************************************\

Function: smv_typecheckt::convert_type

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::convert_type(const typet &src, smv_ranget &dest)
{
  if(src.id()==ID_bool)
  {
    dest.from=0;
    dest.to=1;
  }
  else if(src.id()==ID_range)
  {
    dest.from=string2integer(src.get_string(ID_from));
    dest.to=string2integer(src.get_string(ID_to));
  }
  else
  {
    err_location(src);
    str << "Unexpected type: `" << to_string(src) << "'";
    throw 0;
  }
}

/*******************************************************************\

Function: smv_typecheckt::type_union

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::type_union(
  const typet &type1,
  const typet &type2,
  typet &dest)
{
  if(type1.is_nil())
  {
    dest=type2;
    return;
  }

  if(type2.is_nil())
  {
    dest=type1;
    return;
  }

  smv_ranget range1, range2;
  convert_type(type1, range1);
  convert_type(type2, range2);

  range1.make_union(range2);
  
  if((type1.id()==ID_bool || type2.id()==ID_bool) &&
     range1.is_bool())
  {
    dest=typet(ID_bool);
  }
  else
    range1.to_type(dest);
}

/*******************************************************************\

Function: smv_typecheckt::typecheck

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::typecheck(
  exprt &expr,
  const typet &type,
  modet mode)
{
  if(expr.id()==ID_symbol || 
     expr.id()==ID_next_symbol)
  {
    const irep_idt &identifier=expr.get(ID_identifier);
    bool next=expr.id()==ID_next_symbol;
    
    if(define_map.find(identifier)!=define_map.end())
      convert_define(identifier);

    symbol_tablet::symbolst::iterator s_it=symbol_table.symbols.find(identifier);

    if(s_it==symbol_table.symbols.end())
    {
      err_location(expr);
      str << "variable `" << identifier << "' not found";
      throw 0;
    }

    symbolt &symbol=s_it->second;
    
    assert(symbol.type.is_not_nil());
    expr.type()=symbol.type;

    if(mode==INIT || (mode==TRANS && next))
    {
      if(symbol.module==module)
      {
        symbol.is_input=false;
        symbol.is_state_var=true;
      }
    }
  }
  else if(expr.id()==ID_and ||
          expr.id()==ID_or ||
          expr.id()==ID_xor ||
          expr.id()==ID_not)
  {
    typecheck_op(expr, typet(ID_bool), mode);
  }
  else if(expr.id()==ID_nondet_symbol)
  {
    if(!type.is_nil())
      expr.type()=type;
  }
  else if(expr.id()==ID_constraint_select_one)
  {
    typecheck_op(expr, type, mode);

    typet op_type;
    op_type.make_nil();

    forall_operands(it, expr)
    {
      typet tmp;
      type_union(it->type(), op_type, tmp);
      op_type=tmp;
    }
    
    Forall_operands(it, expr)
      typecheck(*it, op_type, mode);
      
    expr.type()=op_type;
  }
  else if(expr.id()==ID_implies)
  {
    if(expr.operands().size()!=2)
    {
      err_location(expr);
      str << "Expected two operands for -> operator";
      throw 0;
    }

    typecheck_op(expr, typet(ID_bool), mode);
  }
  else if(expr.id()==ID_equal || expr.id()==ID_notequal ||
          expr.id()==ID_lt || expr.id()==ID_le ||
          expr.id()==ID_gt || expr.id()==ID_ge)
  {
    Forall_operands(it, expr)
      typecheck(*it, static_cast<const typet &>(get_nil_irep()), mode);

    if(expr.operands().size()!=2)
    {
      err_location(expr);
      str << "Expected two operands for " << expr;
      throw 0;
    }

    expr.type()=typet(ID_bool);

    exprt &op0=expr.op0(),
          &op1=expr.op1();
          
    typet op_type;

    type_union(op0.type(), op1.type(), op_type);
    
    typecheck(op0, op_type, mode);
    typecheck(op1, op_type, mode);

    if(expr.id()==ID_lt || expr.id()==ID_le ||
       expr.id()==ID_gt || expr.id()==ID_ge)
    {
      if(op0.type().id()!=ID_range)
      {
        err_location(expr);
        str << "Expected number type for " << to_string(expr);
        throw 0;
      }
    }
  }
  else if(expr.id()==ID_plus || expr.id()==ID_minus)
  {
    bool minus=expr.id()==ID_minus;

    typecheck_op(expr, type, mode);
    
    if(type.is_nil())
    {
      if(expr.type().id()==ID_range ||
         expr.type().id()==ID_bool)
      {
        // find proper type for precise arithmetic
        smv_ranget new_range;
        bool first=true;

        forall_operands(it, expr)
        {
          smv_ranget smv_range;
          convert_type(it->type(), smv_range);

          if(minus && !first)
          {
            smv_range.from.negate();
            smv_range.to.negate();
          }

          if(smv_range.to<smv_range.from)
            std::swap(smv_range.to, smv_range.from);

          new_range.to+=smv_range.to;
          new_range.from+=smv_range.from;

          if(first) first=false;
        }

        new_range.to_type(expr.type());
      }
    }
    else if(type.id()!=ID_range)
    {
      err_location(expr);
      str << "Expected number type for "
          << to_string(expr);
      throw 0;
    }
  }
  else if(expr.id()==ID_constant)
  {
    // already done, but maybe need to change the type
    if(type.is_not_nil() && type!=expr.type())
    {
      mp_integer int_value;
      bool have_int_value=false;
      
      if(expr.type().id()==ID_bool)
      {
        int_value=expr.is_true()?1:0;
        have_int_value=true;
      }
      else if(expr.type().id()==ID_range)
      {
        int_value=string2integer(id2string(expr.get(ID_value)));
        have_int_value=true;
      }

      if(have_int_value)
      {
        if(type.id()==ID_bool)
        {
          if(int_value==0)
            expr=false_exprt();
          else if(int_value==1)
            expr=true_exprt();
        }
        else if(type.id()==ID_range)
        {
          mp_integer from=string2integer(type.get_string(ID_from)),
                     to=string2integer(type.get_string(ID_to));

          if(int_value>=from && int_value<=to)
          {
            expr=exprt(ID_constant, type);
            expr.set(ID_value, integer2string(int_value));
          }
        }
      }
    }
  }
  else if(expr.id()=="number_constant")
  {
    const std::string &value=expr.get_string(ID_value);

    mp_integer int_value=string2integer(value);

    if(type.is_nil())
    {
      expr.type()=typet(ID_range);
      expr.type().set(ID_from, integer2string(int_value));
      expr.type().set(ID_to, integer2string(int_value));
      expr.id(ID_constant);
    }
    else
    {
      expr.type()=type;

      if(type.id()==ID_bool)
      {
        if(int_value==0)
          expr=false_exprt();
        else if(int_value==1)
          expr=true_exprt();
        else
        {
          err_location(expr);
          str << "expected 0 or 1 here, but got " << value;
          throw 0;
        }
      }
      else if(type.id()==ID_range)
      {
        smv_ranget smv_range;
        convert_type(type, smv_range);

        if(int_value<smv_range.from || int_value>smv_range.to)
        {
          err_location(expr);
          str << "expected " << smv_range.from << ".." << smv_range.to 
              << " here, but got " << value;
          throw 0;
        }

        expr.id(ID_constant);
      }
      else
      {
        err_location(expr);
        str << "Unexpected constant: " << value;
        throw 0;
      }
    }
  }
  else if(expr.id()==ID_cond)
  {
    if(type.is_nil())
    {
      bool condition=true;
      
      expr.type().make_nil();

      Forall_operands(it, expr)
      {
        if(condition)
          typecheck(*it, typet(ID_bool), mode);
        else
        {
          typecheck(*it, static_cast<const typet &>(get_nil_irep()), mode);
          type_union(expr.type(), it->type(), expr.type());
        }

        condition=!condition;
      }
    }
    else
    {
      expr.type()=type;

      bool condition=true;

      Forall_operands(it, expr)
      {
        if(condition)
          typecheck(*it, typet(ID_bool), mode);
        else
          typecheck(*it, expr.type(), mode);

        condition=!condition;
      }
    }
  } 
  else if(expr.id()==ID_AG || expr.id()==ID_AX || expr.id()==ID_AF || 
          expr.id()==ID_EG || expr.id()==ID_EX || expr.id()==ID_EF)
  {
    if(expr.operands().size()!=1)
    {
      err_location(expr);
      str << "Expected one operand for " << expr.id_string()
          << " operator";
      throw 0;
    }

    expr.type()=typet(ID_bool);

    typecheck(expr.op0(), expr.type(), mode);
  }
  else if(expr.id()==ID_typecast)
  {
  }
  else
  {
    err_location(expr);
    str << "No type checking for " << expr;
    throw 0;
  }

  if(!type.is_nil() && expr.type()!=type)
  {
    smv_ranget e, t;
    convert_type(expr.type(), e);
    convert_type(type, t);

    if(e.is_contained_in(t))
    {
      if(e.is_singleton())
      {
        if(type.id()==ID_bool)
        {
          if(e.from==0)
            expr=false_exprt();
          else
            expr=true_exprt();
        }
        else
        {
          expr=exprt(ID_constant, type);
          expr.set(ID_value, integer2string(e.from));
        }
      }
      else
        expr.make_typecast(type);

      return;      
    }

    err_location(expr);
    str << "Expected expression of type `" << to_string(type)
        << "', but got expression `" << to_string(expr)
        << "', which is of type `" << to_string(expr.type()) << "'";
    throw 0;
  }
}

/*******************************************************************\

Function: smv_typecheckt::convert

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::convert(exprt &expr, expr_modet expr_mode)
{
  if(expr.id()=="smv_next")
  {
    if(expr_mode!=NORMAL)
    {
      err_location(expr);
      str << "next(next(...)) encountered";
      throw 0;
    }
    
    assert(expr.operands().size()==1);

    exprt tmp;
    tmp.swap(expr.op0());
    expr.swap(tmp);

    convert(expr, NEXT);
    return;
  }

  Forall_operands(it, expr)
    convert(*it, expr_mode);

  if(expr.id()==ID_symbol)
  {
    const std::string &identifier=expr.get_string(ID_identifier);

    if(identifier=="TRUE")
      expr=true_exprt();
    else if(identifier=="FALSE")
      expr=false_exprt();
    else if(identifier.find("::")==std::string::npos)
    {
      std::string id=module+"::var::"+identifier;

      smv_parse_treet::mc_varst::const_iterator it=
        modulep->vars.find(identifier);

      if(it!=modulep->vars.end())
        if(it->second.identifier!="")
          id=id2string(it->second.identifier);

      expr.set(ID_identifier, id);
      
      if(expr_mode==NEXT)
        expr.id(ID_next_symbol);
    }
  }
  else if(expr.id()=="smv_nondet_choice" ||
          expr.id()=="smv_union")
  {
    if(expr.operands().size()==0)
    {
      err_location(expr);
      str << "expected operand here";
      throw 0;
    }

    std::string identifier=
      module+"::var::"+i2string(nondet_count++);

    expr.set(ID_identifier, identifier);
    expr.set("#smv_nondet_choice", true);

    expr.id(ID_constraint_select_one);
  }
  else if(expr.id()=="smv_cases") // cases
  {
    if(expr.operands().size()<1)
    {
      err_location(expr);
      str << "Expected at least one operand for " << expr.id_string()
          << " expression";
      throw 0;
    }

    exprt tmp;
    tmp.operands().swap(expr.operands());
    expr.reserve_operands(tmp.operands().size()*2);

    Forall_operands(it, tmp)
    {
      if(it->operands().size()!=2)
      {
        err_location(*it);
        throw "case expected to have two operands";
      }

      exprt &condition=it->op0();
      exprt &value=it->op1();

      expr.move_to_operands(condition);
      expr.move_to_operands(value);
    }

    expr.id(ID_cond);
  }
}

/*******************************************************************\

Function: smv_typecheckt::to_string

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string smv_typecheckt::to_string(const exprt &expr)
{
  std::string result;
  expr2smv(expr, result);
  return result;
}

/*******************************************************************\

Function: smv_typecheckt::to_string

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string smv_typecheckt::to_string(const typet &type)
{
  std::string result;
  type2smv(type, result);
  return result;
}

/*******************************************************************\

Function: smv_typecheckt::typecheck

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::typecheck(
  smv_parse_treet::modulet::itemt &item)
{
  modet mode;

  switch(item.item_type)
  {
  case smv_parse_treet::modulet::itemt::INIT:
    mode=INIT;
    break;

  case smv_parse_treet::modulet::itemt::TRANS:
    mode=TRANS;
    break;

  default:
    mode=OTHER;
  }

  typecheck(item.expr, bool_typet(), mode);
}

/*******************************************************************\

Function: smv_typecheckt::convert

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::convert(
  smv_parse_treet::modulet::itemt &item)
{
  convert(item.expr, NORMAL);
}

/*******************************************************************\

Function: smv_typecheckt::convert_vars

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::convert(smv_parse_treet::mc_varst &vars)
{
  symbolt symbol;

  symbol.mode="SMV";
  symbol.module=modulep->name;

  for(smv_parse_treet::mc_varst::const_iterator it=vars.begin();
      it!=vars.end(); it++)
  {
    const smv_parse_treet::mc_vart &var=it->second;

    symbol.base_name=it->first;

    if(var.identifier=="")
      symbol.name=module+"::var::"+id2string(symbol.base_name);
    else
      symbol.name=var.identifier;

    symbol.value.make_nil();
    symbol.is_input=true;
    symbol.is_state_var=false;
    symbol.type=var.type;

    symbol_table.add(symbol);
  }
}

/*******************************************************************\

Function: smv_typecheckt::collect_define

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::collect_define(const exprt &expr)
{
  if(expr.id()!=ID_equal || expr.operands().size()!=2)
    throw "collect_define expects equality";

  const exprt &op0=expr.op0();
  const exprt &op1=expr.op1();

  if(op0.id()!=ID_symbol)
    throw "collect_define expects symbol on left hand side";

  const irep_idt &identifier=op0.get(ID_identifier);

  symbol_tablet::symbolst::iterator it=symbol_table.symbols.find(identifier);

  if(it==symbol_table.symbols.end())
  {
    str << "collect_define failed to find symbol `"
        << identifier << "'";
    throw 0;
  }

  symbolt &symbol=it->second;

  symbol.value.make_nil();
  symbol.is_input=false;
  symbol.is_state_var=false;
  symbol.is_macro=false;

  std::pair<define_mapt::iterator, bool> result=
    define_map.insert(std::pair<irep_idt, definet>(identifier, definet(op1)));

  if(!result.second)
  {
    err_location(expr);
    str << "symbol `" << identifier << "' defined twice" << std::endl;
    throw 0;
  }  
}

/*******************************************************************\

Function: smv_typecheckt::convert_define

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::convert_define(const irep_idt &identifier)
{
  definet &d=define_map[identifier];
  
  if(d.typechecked) return;
  
  if(d.in_progress)
  {
    str << "definition of `" << identifier << "' is cyclic";
    throw 0;
  }
  
  symbol_tablet::symbolst::iterator it=symbol_table.symbols.find(identifier);

  if(it==symbol_table.symbols.end())
  {
    str << "convert_define failed to find symbol `"
        << identifier << "'";
    throw 0;
  }

  symbolt &symbol=it->second;

  d.in_progress=true;
  
  typecheck(d.value, symbol.type, OTHER);
  
  d.in_progress=false;
  d.typechecked=true;

  if(symbol.type.is_nil())
    symbol.type=d.value.type();
}

/*******************************************************************\

Function: smv_typecheckt::convert_defines

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::convert_defines(exprt::operandst &invar)
{
  for(define_mapt::iterator it=define_map.begin();
      it!=define_map.end();
      it++)
  {
    convert_define(it->first);

    // generate constraint
    equal_exprt equality;
    equality.lhs()=exprt(ID_symbol, it->second.value.type());
    equality.lhs().set(ID_identifier, it->first);
    equality.rhs()=it->second.value;
    invar.push_back(equality);
  }
}

/*******************************************************************\

Function: smv_typecheckt::convert

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::convert(smv_parse_treet::modulet &smv_module)
{
  modulep=&smv_module;

  define_map.clear();

  convert(smv_module.vars);

  // transition relation

  symbolt module_symbol;

  module_symbol.base_name=smv_module.base_name;
  module_symbol.pretty_name=smv_module.base_name;
  module_symbol.name=smv_module.name;
  module_symbol.module=module_symbol.name;
  module_symbol.type=typet(ID_module);
  module_symbol.mode="SMV";
  module_symbol.value=transt();
  module_symbol.value.operands().resize(3);

  exprt::operandst trans_invar, trans_init, trans_trans;
  
  convert_ports(smv_module, module_symbol.type);

  Forall_item_list(it, smv_module.items)
    convert(*it);

  flatten_hierarchy(smv_module);
  
  // we first need to collect all the defines

  Forall_item_list(it, smv_module.items)
    if(it->is_define())
      collect_define(it->expr);

  // now turn them into INVARs
  convert_defines(trans_invar);

  // do the rest now

  Forall_item_list(it, smv_module.items)
    if(!it->is_define())
      typecheck(*it);

  Forall_item_list(it, smv_module.items)
    if(it->is_invar())
      trans_invar.push_back(it->expr);
    else if(it->is_init())
      trans_init.push_back(it->expr);
    else if(it->is_trans())
      trans_trans.push_back(it->expr);

  transt &trans=to_trans_expr(module_symbol.value);
  
  trans.invar()=conjunction(trans_invar);
  trans.init()=conjunction(trans_init);
  trans.trans()=conjunction(trans_trans);

  symbol_table.move(module_symbol);

  // spec

  if(do_spec)
  {
    unsigned nr=1;

    forall_item_list(it, smv_module.items)
      if(it->is_spec())
      {
        symbolt spec_symbol;

        spec_symbol.base_name=smv_module.base_name;
        spec_symbol.name=id2string(smv_module.name)+"::spec"+i2string(nr++);
        spec_symbol.module=smv_module.name;
        spec_symbol.type=typet(ID_bool);
        spec_symbol.is_property=true;
        spec_symbol.mode="SMV";
        spec_symbol.value=it->expr;
        spec_symbol.location=it->location;

        symbol_table.move(spec_symbol);
      }
  }
}

/*******************************************************************\

Function: smv_typecheckt::typecheck

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void smv_typecheckt::typecheck()
{
  smv_parse_treet::modulest::iterator it=smv_parse_tree.modules.find(module);

  if(it==smv_parse_tree.modules.end())
  {
    str << "failed to find module " << module;
    throw 0;
  }

  convert(it->second);
}

/*******************************************************************\

Function: smv_typecheck

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

bool smv_typecheck(
  smv_parse_treet &smv_parse_tree,
  symbol_tablet &symbol_table,
  const std::string &module,
  message_handlert &message_handler,
  bool do_spec)
{
  smv_typecheckt smv_typecheck(
    smv_parse_tree, symbol_table, module, do_spec, message_handler);
  return smv_typecheck.typecheck_main();
}

/*******************************************************************\

Function: smv_module_symbol

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string smv_module_symbol(const std::string &module)
{
  return "smv::"+module;
}
