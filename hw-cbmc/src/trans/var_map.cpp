/*******************************************************************\

Module: 

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <cassert>
#include <iostream>

#include <solvers/flattening/boolbv_width.h>

#include "var_map.h"

/*******************************************************************\

Function: var_mapt::add

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void var_mapt::add(
  const irep_idt &id,
  unsigned bit_nr,
  const vart &var)
{
  unsigned v=var.bits[bit_nr].current.var_no();

  switch(var.vartype)
  {
  case vart::VAR_LATCH:
    latches.insert(v);
    break;
            
  case vart::VAR_INPUT:
    inputs.insert(v);
    break;
    
  case vart::VAR_OUTPUT:
    outputs.insert(v);
    break;
    
  case vart::VAR_WIRE:
    wires.insert(v);
    break;
    
  default:;
    break;
  }
  
  if(var.is_latch() || var.is_input())
  {
    bv_varidt &reverse=reverse_map[v];
    reverse.id=id;
    reverse.bit_nr=bit_nr;
  }
}

/*******************************************************************\

Function: var_mapt::build_reverse_map

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void var_mapt::build_reverse_map()
{
  for(mapt::const_iterator
       it=map.begin();
       it!=map.end();
       it++)
  {
    const vart &var=it->second;
    for(unsigned bit_nr=0; bit_nr<var.bits.size(); bit_nr++)
      add(it->first, bit_nr, var);
  }
}

/*******************************************************************\

Function: var_mapt::get_current

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

const var_mapt::vart::bitt &var_mapt::get_bit(
  const irep_idt &id,
  unsigned bit_nr) const
{
  mapt::const_iterator it=map.find(id);

  if(it==map.end())
  {
    std::cerr << "failed to find identifier " 
              << id << "[" << bit_nr << "]" << std::endl;
    assert(false);
  }

  assert(it->second.bits.size()!=0);

  if(bit_nr>=it->second.bits.size())
  {
    std::cerr << "index out of range for " 
              << id << "[" << bit_nr << "]" << std::endl;
    std::cerr << "available range: 0.."
              << it->second.bits.size()-1 << std::endl;
    assert(false);
  }

  return it->second.bits[bit_nr];
}

/*******************************************************************\

Function: var_mapt::get_type

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

var_mapt::vart::vartypet var_mapt::get_type(
  const irep_idt &id) const
{
  mapt::const_iterator it=map.find(id);

  if(it==map.end())
  {
    std::cerr << "failed to find identifier " 
              << id << std::endl;
    assert(false);
  }

  return it->second.vartype;
}

/*******************************************************************\

Function: var_mapt::reverse

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

const bv_varidt &var_mapt::reverse(unsigned v) const
{
  reverse_mapt::const_iterator it=reverse_map.find(v);

  if(it==reverse_map.end())
  {
    std::cerr << "failed to find variable " 
              << v << std::endl;
    assert(false);
  }

  return it->second;
}

/*******************************************************************\

Function: var_mapt::output

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void var_mapt::output(std::ostream &out) const
{
  out << "Variable map:" << std::endl;

  for(mapt::const_iterator it=map.begin();
      it!=map.end(); it++)
  {
    const vart &var=it->second;

    for(unsigned i=0; i<var.bits.size(); i++)
    {
      out << "  " << it->first;
      if(var.bits.size()!=1) out << "[" << i << "]";
      out << "=";
      literalt l=var.bits[i].current;
      if(l.is_true())
        out << "true";
      else if(l.is_false())
        out << "false";
      else
      {
        if(l.sign()) out << "!";
        out << l.var_no();
      }
      
      out << " ";

      switch(var.vartype)
      {
       case vart::VAR_INPUT: out << "(input)"; break;
       case vart::VAR_LATCH: out << "(latch)"; break;
       case vart::VAR_WIRE:  out << "(wire)"; break;
       case vart::VAR_OUTPUT:out << "(output)"; break;
       case vart::VAR_UNDEF: out << "(?)"; break;
      }

      out << std::endl;
    }
  }

  out << std::endl
      << "Total no. of variable bits: " << reverse_map.size()
      << std::endl
      << "Total no. of latch bits: " << latches.size()
      << std::endl
      << "Total no. of input bits: " << inputs.size()
      << std::endl
      << "Total no. of output bits: " << outputs.size()
      << std::endl;
}
