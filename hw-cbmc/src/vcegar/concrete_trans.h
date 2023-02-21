/*******************************************************************\

Module: The concrete transition system

Author: Daniel Kroening

Date: June 2003

\*******************************************************************/

#ifndef CPROVER_CONCRETE_TRANS_H
#define CPROVER_CONCRETE_TRANS_H

#include <util/std_expr.h>

#include <trans/var_map.h>

class concrete_transt
{
public:
  transt trans_expr;
  var_mapt var_map; //Mapping of variables present
};                  //in verilog file to literals. 

#endif
