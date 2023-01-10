#include <cassert>
#include <cctype>
#include <cstdio>

#include <util/config.h>

#include <ansi-c/c_types.h>

#include "expression_datatype.h"

/*******************************************************************\

Function: expr2ct::convert_rec

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string datatypet::convert_rec(
  const typet &src,
  const c_qualifierst &qualifiers,
  const std::string &declarator)
{
  c_qualifierst new_qualifiers(qualifiers);
  new_qualifiers.read(src);

  std::string q=new_qualifiers.as_string();
  
  std::string d=
    declarator==""?declarator:" "+declarator;
  
  if(src.id()==ID_signedbv ||
     src.id()==ID_unsignedbv)
  {
    // annotated?
    
    irep_idt c_type=src.get(ID_C_c_type);

    if(c_type==ID_unsigned_char)
      return q+"unsigned char"+d;
    else if(c_type==ID_signed_char)
      return q+"signed char"+d;
    else if(c_type==ID_char)
    {
      if(config.ansi_c.char_is_unsigned==
         (src.id()==ID_unsignedbv))
        return q+"char"+d;
      else
      {
        if(src.id()==ID_signedbv)
          return q+"signed char"+d;
        else
          return q+"unsigned char"+d;
      }
    }
    else if(c_type==ID_unsigned_short_int)
      return q+"unsigned short int"+d;
    else if(c_type==ID_signed_short_int)
      return q+"signed short int"+d;
    else if(c_type==ID_unsigned_int)
      return q+"unsigned int"+d;
    else if(c_type==ID_signed_int)
      return q+"signed int"+d;
    else if(c_type==ID_unsigned_long_int)
      return q+"unsigned long int"+d;
    else if(c_type==ID_signed_long_int)
      return q+"signed long int"+d;
    else if(c_type==ID_unsigned_long_long_int)
      return q+"unsigned long long int"+d;
    else if(c_type==ID_signed_long_long_int)
      return q+"signed long long int"+d;
    else if(c_type==ID_bool)
      return q+"_Bool"+d;
    else if(c_type==ID_signed_int128)
      return q+"signed __int128"+d;
    else if(c_type==ID_unsigned_int128)
      return q+"unsigned __int128"+d;
      
    // There is also wchar_t among the above, but this isn't a C type.

    mp_integer width=string2integer(src.get_string(ID_width));

    bool is_signed=src.id()==ID_signedbv;
    std::string sign_str=is_signed?"signed ":"unsigned ";
    if(width<=config.ansi_c.char_width)
    {
      // always include sign
      return q+sign_str+"char"+d;
    }
    else if(width<=config.ansi_c.short_int_width)
    {
      if(is_signed) sign_str="";
      return q+sign_str+"short int"+d;
    }

    if(width<=config.ansi_c.int_width)
    {
      if(is_signed) sign_str="";
      return q+sign_str+"int"+d;
    }
    else if(width<=config.ansi_c.long_int_width)
    {
      if(is_signed) sign_str="";
      return q+sign_str+"long int"+d;
    }
    else if(width<=config.ansi_c.long_long_int_width)
    {
      if(is_signed) sign_str="";
      return q+sign_str+"long long int"+d;
    }
    else if(width<=128)
    {
      if(is_signed) sign_str="";
      return q+sign_str+"__int128";
    }
     
  }

  return expr2ct::convert_rec(src, qualifiers, declarator); 
}
