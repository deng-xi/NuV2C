/*******************************************************************\

Module: Command Line Parsing

\*******************************************************************/

#ifndef CPROVER_TRANSLATOR_PARSEOPTIONS_H
#define CPROVER_TRANSLATOR_PARSEOPTIONS_H

#include <util/parse_options.h>
#include <langapi/language_ui.h>

#define TRANSLATOR_OPTIONS \
  "(string)(symbol)(show-parse-tree)(module):(translate-c):"

class NuV2C_parseoptionst:public parse_options_baset,
                        public language_uit
{
public:
  virtual int doit();
  virtual void help();
  
  NuV2C_parseoptionst(int argc, const char **argv):
    parse_options_baset(TRANSLATOR_OPTIONS, argc, argv),  //类中只有cmdline,和一个bool成员变量
    language_uit("VerilogtoC Version 1",cmdline)  //类中只有args和options两个成员变量
  {
  }

protected:
  void register_languages();
  bool translator();
  bool translate_module();
};

#endif
