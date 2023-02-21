/*******************************************************************\

Module: Unwinding Transition Systems

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <util/namespace.h>
#include <util/find_symbols.h>
#include <util/expr_util.h>

#include "instantiate.h"
#include "unwind.h"

/*******************************************************************\

Function: unwind

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void unwind(
  const transt &trans,
  messaget &message,
  decision_proceduret &decision_procedure,
  unsigned no_timeframes,
  const namespacet &ns,
  bool initial_state)
{
  const exprt &op_invar=trans.invar();
  const exprt &op_init=trans.init();
  const exprt &op_trans=trans.trans();

  // general constraints

  message.status() << "General constraints" << messaget::eom;

  if(!op_invar.is_true())
    for(unsigned c=0; c<no_timeframes; c++)
      instantiate(decision_procedure, op_invar, c, no_timeframes, ns);

  // initial state

  if(initial_state)
  {
    message.status() << "Initial state" << messaget::eom;

    if(!op_init.is_true())
      instantiate(decision_procedure, op_init, 0, no_timeframes, ns);
  }

  // transition relation

  message.status() << "Transition relation" << messaget::eom;

  if(!op_trans.is_true())
    for(unsigned c=0; c<no_timeframes-1; c++)
    {
      message.status() << "Transition " << c << "->" << c+1 << messaget::eom;

      instantiate(decision_procedure, op_trans, c, no_timeframes, ns);
    }
}
