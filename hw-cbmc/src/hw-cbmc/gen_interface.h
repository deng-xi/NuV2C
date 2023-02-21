/*******************************************************************\

Module: Variable Mapping HDL<->C

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_CBMC_GEN_INTERFACE_H
#define CPROVER_CBMC_GEN_INTERFACE_H

#include <ostream>

#include <util/symbol_table.h>

void gen_interface(
  const symbol_tablet &symbol_table,
  const symbolt &top_module,
  bool have_bound,
  std::ostream &out,
  std::ostream &err);

#endif
