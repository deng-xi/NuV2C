/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <cstdlib>
#include <sstream>

#include <util/lispexpr.h>
#include <util/lispirep.h>
#include <util/i2string.h>
#include <util/arith_tools.h>
#include <util/std_expr.h>

#include "expr2vhdl.h"
#include "expr2vhdl_class.h"

/*******************************************************************\

Function: expr2vhdlt::convert_trinary

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_trinary(
  const exprt &src,
  const std::string &symbol1,
  const std::string &symbol2,
  unsigned precedence)
{
  if(src.operands().size()!=3)
    return convert_norep(src, precedence);

  std::string dest;
  unsigned p0, p1, p2;

  std::string op0=convert(src.op0(), p0);
  std::string op1=convert(src.op1(), p1);
  std::string op2=convert(src.op2(), p2);

  if(precedence>p0) dest+='(';
  dest+=op0;
  if(precedence>p0) dest+=')';

  dest+=' ';
  dest+=symbol1;
  dest+=' ';

  if(precedence>p1) dest+='(';
  dest+=op1;
  if(precedence>p1) dest+=')';

  dest+=' ';
  dest+=symbol2;
  dest+=' ';

  if(precedence>p2) dest+='(';
  dest+=op2;
  if(precedence>p2) dest+=')';

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_binary

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_binary(
  const exprt &src,
  const std::string &symbol,
  unsigned precedence)
{
  if(src.operands().size()<2)
    return convert_norep(src, precedence);

  bool first=true;
  std::string dest;

  forall_operands(it, src)
  {
    if(first)
      first=false;
    else
    {
      dest+=' ';
      dest+=symbol;
      dest+=' ';
    }

    unsigned p;
    std::string op=convert(*it, p);

    if(precedence>p) dest+='(';
    dest+=op;
    if(precedence>p) dest+=')';
  }

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_with

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_with(
  const exprt &src,
  unsigned precedence)
{
  if(src.operands().size()<1)
    return convert_norep(src, precedence);

  unsigned p;
  std::string dest="("+convert(src.op0(), p);

  for(unsigned i=1; i<src.operands().size(); i+=2)
  {
    dest+=" WITH ";
    dest+=convert(src.operands()[i], p);
    dest+=":=";
    dest+=convert(src.operands()[i+1], p);
  }

  dest+=")";

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_concatenation

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_concatenation(
  const exprt &src,
  unsigned precedence)
{
  if(src.operands().size()<1)
    return convert_norep(src, precedence);

  bool first=true;
  std::string dest="{ ";

  forall_operands(it, src)
  {
    if(first)
      first=false;
    else
      dest+=", ";

    unsigned p;
    std::string op=convert(*it, p);

    if(precedence>p) dest+='(';
    dest+=op;
    if(precedence>p) dest+=')';
  }

  dest+=" }";

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_replication

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_replication(
  const exprt &src,
  unsigned precedence)
{
  if(src.operands().size()!=2)
    return convert_norep(src, precedence);

  std::string dest="{ ";

  dest+=convert(src.op0());
  dest+=" { ";
  dest+=convert(src.op1());
  dest+=" } }";

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_unary

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_unary(
  const exprt &src,
  const std::string &symbol,
  unsigned precedence)
{
  if(src.operands().size()!=1)
    return convert_norep(src, precedence);
    
  unsigned p;
  std::string op=convert(src.op0(), p);

  std::string dest=symbol;
  if(precedence>p) dest+='(';
  dest+=op;
  if(precedence>p) dest+=')';

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_typecast

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_typecast(
  const exprt &src,
  unsigned &precedence)
{
  if(src.operands().size()==1)
  {
    //const typet &from=src.op0().type();
    //const typet &to=src.type();

    // just ignore them for now
    return convert(src.op0(), precedence);
  }

  return convert_norep(src, precedence);
}

/*******************************************************************\

Function: expr2vhdlt::convert_index

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_index(
  const exprt &src,
  unsigned precedence)
{
  if(src.operands().size()!=2)
    return convert_norep(src, precedence);

  unsigned p;
  std::string op=convert(src.op0(), p);

  std::string dest;
  if(precedence>p) dest+='(';
  dest+=op;
  if(precedence>p) dest+=')';

  dest+='[';
  dest+=convert(src.op1());
  dest+=']';

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_extractbit

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_extractbit(
  const exprt &src,
  unsigned precedence)
{
  if(src.operands().size()!=2)
    return convert_norep(src, precedence);

  unsigned p;
  std::string op=convert(src.op0(), p);

  std::string dest;
  if(precedence>p) dest+='(';
  dest+=op;
  if(precedence>p) dest+=')';

  dest+='[';
  dest+=convert(src.op1());
  dest+=']';

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_extractbits

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_extractbits(
  const exprt &src,
  unsigned precedence)
{
  if(src.operands().size()!=3)
    return convert_norep(src, precedence);

  unsigned p;
  std::string op=convert(src.op0(), p);

  std::string dest;
  if(precedence>p) dest+='(';
  dest+=op;
  if(precedence>p) dest+=')';

  dest+='[';
  dest+=convert(src.op1());
  dest+=':';
  dest+=convert(src.op2());
  dest+=']';

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_member

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_member(
  const exprt &src,
  unsigned precedence)
{
  if(src.operands().size()!=1)
    return convert_norep(src, precedence);

  unsigned p;
  std::string op=convert(src.op0(), p);

  std::string dest;
  if(precedence>p) dest+='(';
  dest+=op;
  if(precedence>p) dest+=')';

  dest+='.';
  dest+=src.get_string(ID_component_name);

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_norep

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_norep(
  const exprt &src,
  unsigned &precedence)
{
  precedence=22;
  return src.to_string();
}

/*******************************************************************\

Function: expr2vhdlt::convert_symbol

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_symbol(
  const exprt &src,
  unsigned &precedence)
{
  precedence=22;
  std::string dest=src.get_string(ID_identifier);
 
  if(std::string(dest, 0, 9)=="Verilog::")
    dest.erase(0, 9);

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_nondet_symbol

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_nondet_symbol(
  const exprt &src,
  unsigned &precedence)
{
  return "nondet("+convert_symbol(src, precedence)+")";
}

/*******************************************************************\

Function: expr2vhdlt::convert_next_symbol

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_next_symbol(
  const exprt &src,
  unsigned &precedence)
{
  return "next("+convert_symbol(src, precedence)+")";
}

/*******************************************************************\

Function: expr2vhdlt::convert_constant

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_constant(
  const exprt &src,
  unsigned &precedence)
{
  precedence=22;

  const typet &type=src.type();
  const std::string &value=src.get_string(ID_value);
  std::string dest;

  if(type.id()==ID_bool)
  {
    if(src.is_true())
      dest+="1";
    else
      dest+="0";
  }
  else if(type.id()==ID_unsignedbv ||
          type.id()==ID_signedbv)
  {
    mp_integer i;
    to_integer(src, i);

    if(i>=256)
      dest="'h"+integer2string(i, 16);
    else
      dest=integer2string(i);
  }
  else if(type.id()==ID_integer || type.id()==ID_natural)
    dest=value;
  else
    return convert_norep(src, precedence);

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert_array

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert_array(
  const exprt &src,
  unsigned precedence)
{
  std::string dest="{ ";

  forall_operands(it, src)
  {
    std::string tmp=convert(*it, precedence);
      
    exprt::operandst::const_iterator next_it=it;
    next_it++;

    if(next_it!=src.operands().end())
    {
      tmp+=", ";
      if(tmp.size()>40) tmp+="\n    ";
    }

    dest+=tmp;
  }

  dest+=" }";

  return dest;
}

/*******************************************************************\

Function: expr2vhdlt::convert

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert(
  const exprt &src,
  unsigned &precedence)
{
  precedence=22;

  if(src.id()=="+")
    return convert_binary(src, "+", precedence=14);

  else if(src.id()==ID_if)
    return convert_trinary(src, "?", ":", precedence=14);

  else if(src.id()==ID_concatenation)
    return convert_concatenation(src, precedence=16);

  else if(src.id()==ID_with)
    return convert_with(src, precedence=16);

  else if(src.id()==ID_replication)
    return convert_replication(src, precedence=22);

  else if(src.id()==ID_array)
    return convert_array(src, precedence=22);

  else if(src.id()=="-")
  {
    if(src.operands().size()<2)
      return convert_norep(src, precedence);
    else     
      return convert_binary(src, "-", precedence=14);
  }

  else if(src.id()==ID_shl)
    return convert_binary(src, "<<", precedence=14);

  else if(src.id()==ID_lshr)
    return convert_binary(src, ">>", precedence=14);

  else if(src.id()=="unary-")
  {
    if(src.operands().size()!=1)
      return convert_norep(src, precedence);
    else     
      return convert_unary(src, "-", precedence=16);
  }

  else if(src.id()==ID_index)
    return convert_index(src, precedence=22);

  else if(src.id()==ID_extractbit)
    return convert_extractbit(src, precedence=22);

  else if(src.id()==ID_extractbits)
    return convert_extractbits(src, precedence=22);

  else if(src.id()==ID_member)
    return convert_member(src, precedence=22);

  else if(src.id()=="*" || src.id()=="/")
    return convert_binary(src, src.id_string(), precedence=14);

  else if(src.id()=="<" || src.id()==">" ||
          src.id()=="<=" || src.id()==">=")
    return convert_binary(src, src.id_string(), precedence=9);

  else if(src.id()=="=")
    return convert_binary(src, "==", precedence=9);

  else if(src.id()==ID_notequal)
    return convert_binary(src, "!=", precedence=9);

  else if(src.id()==ID_not)
    return convert_unary(src, "!", precedence=16);

  else if(src.id()==ID_bitnot)
    return convert_unary(src, "~", precedence=16);

  else if(src.id()==ID_typecast)
    return convert_typecast(src, precedence);

  else if(src.id()==ID_and)
    return convert_binary(src, "&&", precedence=7);

  else if(src.id()==ID_bitand)
    return convert_binary(src, "&", precedence=7);

  else if(src.id()==ID_or)
    return convert_binary(src, "||", precedence=6);

  else if(src.id()==ID_bitor)
    return convert_binary(src, "|", precedence=6);

  else if(src.id()=="=>")
    return convert_binary(src, "->", precedence=5);

  else if(src.id()=="<=>")
    return convert_binary(src, "<->", precedence=4);

  else if(src.id()==ID_AG || src.id()==ID_EG ||
          src.id()==ID_AX || src.id()==ID_EX)
    return convert_unary(src, src.id_string()+" ", precedence=4);

  else if(src.id()==ID_symbol)
    return convert_symbol(src, precedence);

  else if(src.id()==ID_nondet_symbol)
    return convert_nondet_symbol(src, precedence);

  else if(src.id()==ID_next_symbol)
    return convert_next_symbol(src, precedence);

  else if(src.id()==ID_constant)
    return convert_constant(src, precedence);
    
  else if(src.id()=="vhdl-constant")
  {
    const std::string width=src.type().get_string(ID_width);
    return width+"'b"+src.get_string(ID_value);
  }

  // no VERILOG language expression for internal representation 
  return convert_norep(src, precedence);
}

/*******************************************************************\

Function: expr2vhdlt::convert

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert(const exprt &src)
{
  unsigned precedence;
  return convert(src, precedence);
}

/*******************************************************************\

Function: expr2vhdlt::convert

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdlt::convert(const typet &type)
{
  if(type.id()==ID_bool)
    return "bool";
  else if(type.id()==ID_unsignedbv || type.id()==ID_signedbv)
  {
    unsigned width=to_bitvector_type(type).get_width();
    bool little_endian=type.get_bool(ID_C_little_endian);
    unsigned offset=atoi(type.get(ID_C_offset).c_str());

    if(width!=0)
    {
      std::string dest;
      if(type.id()==ID_unsignedbv)
        dest="bv";
      else if(type.id()==ID_signedbv)
        dest="signed bv";

      dest+='[';
      
      if(little_endian)
      {
        dest+=i2string(offset+width-1);
        dest+=":";
        dest+=i2string(offset);
      }
      else
      {
        dest+=i2string(offset);
        dest+=":";
        dest+=i2string(offset+width-1);
      }

      dest+="]";
      return dest;
    }
  }
  else if(type.id()==ID_array)
  {
    std::string dest="array [";
    
    dest+=convert(to_array_type(type).size());

    dest+="] of ";
    dest+=convert(type.subtype());
    
    return dest;
  }
  else if(type.id()==ID_genvar)
    return "genvar";
  else if(type.id()==ID_integer)
    return "integer";
  else if(type.id()==ID_real)
    return "real";

  return "IREP("+type.to_string()+")";
}

/*******************************************************************\

Function: expr2vhdl

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string expr2vhdl(const exprt &expr)
{
  expr2vhdlt expr2vhdl;
  return expr2vhdl.convert(expr);
}

/*******************************************************************\

Function: type2vhdl

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string type2vhdl(const typet &type)
{
  expr2vhdlt expr2vhdl;
  return expr2vhdl.convert(type);
}
