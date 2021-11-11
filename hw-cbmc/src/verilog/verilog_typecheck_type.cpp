/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <util/arith_tools.h>

#include "verilog_typecheck_expr.h"

/*******************************************************************\

Function: verilog_typecheck_exprt::convert_type

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void verilog_typecheck_exprt::convert_type(
  const irept &src,
  typet &dest)
{
  if(src.is_nil() || src.id()==ID_reg)
  {
    // it's just a bit
    dest=bool_typet();
    return;
  }
  
  if(src.id()==ID_array)
  {
    const exprt &range=static_cast<const exprt &>(src.find(ID_range));

    mp_integer msb, lsb;
    convert_range(range, msb, lsb);

    bool little_endian=(lsb<=msb);

    mp_integer width=(little_endian?msb-lsb:lsb-msb)+1;
    mp_integer offset=little_endian?lsb:msb;
    
    // let's look at the subtype
    const irept &subtype=
      static_cast<const typet &>(src).subtype();
    
    if(subtype.is_nil() ||
       subtype.id()==ID_signed ||
       subtype.id()==ID_unsigned)
    {
      // we have a bit-vector type, not an array

      dest=typet(subtype.id()==ID_signed?ID_signedbv:ID_unsignedbv);

      dest.add_source_location()=
        static_cast<const source_locationt &>(src.find(ID_C_source_location));
      dest.set(ID_width, integer2string(width));
      dest.set(ID_C_little_endian, little_endian);
      dest.set(ID_C_offset, integer2string(offset));
    }
    else
    {
      // we have a genuine array, and do a recursive call
      dest=array_typet();
      dest.set(ID_size, from_integer(width, integer_typet()));
      dest.add_source_location()=
        static_cast<const source_locationt &>(src.find(ID_C_source_location));
      dest.set(ID_offset, from_integer(offset, integer_typet()));
      convert_type(subtype, dest.subtype());
    }
  }
  else
  {
    err_location(src);
    throw "unexpected type: `"+src.id_string()+"'";
  }
}
