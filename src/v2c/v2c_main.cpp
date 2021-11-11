/*******************************************************************\

Module: Main Module 

Tool: Verilog to C translator

\*******************************************************************/

#include "v2c_parseoptions.h"

/*******************************************************************\

  Function: main

  Inputs:

  Outputs:

  Purpose:

\*******************************************************************/

int main(int argc, const char **argv)
{
  v2c_parseoptionst v2c_parseoptions(argc, argv);
  return v2c_parseoptions.main();
}
