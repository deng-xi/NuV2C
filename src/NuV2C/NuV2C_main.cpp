/*******************************************************************\

Module: Main Module 

Tool: Verilog to C translator

\*******************************************************************/

#include "NuV2C_parseoptions.h"

/*******************************************************************\

  Function: main

  Inputs:

  Outputs:

  Purpose:

\*******************************************************************/

int main(int argc, const char **argv)
{
  NuV2C_parseoptionst NuV2C_parseoptions(argc, argv);
  return NuV2C_parseoptions.main();
}
