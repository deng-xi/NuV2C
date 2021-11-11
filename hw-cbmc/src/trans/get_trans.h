/*******************************************************************\

Module: Get Transition System out of Context

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_TRANS_GET_TRANS_H
#define CPROVER_TRANS_GET_TRANS_H

#include <util/std_expr.h>
#include <util/namespace.h>

const transt &get_trans(
  const namespacet &ns,
  const irep_idt &module);

#endif
