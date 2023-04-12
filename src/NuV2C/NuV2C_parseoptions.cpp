/*******************************************************************\

Module: Main Module 

\*******************************************************************/
#include <util/irep.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <util/config.h>
#include <util/get_module.h>
#include <util/std_expr.h>
#include <langapi/mode.h>
#include <verilog/verilog_language.h>

#include "Nuv2expr.h"
#include "NuV2C_parseoptions.h"


/*******************************************************************\

  Function: NuV2C_parseoptionst::translator()

  Inputs:

  Outputs:

  Purpose: Translator parse options

\*******************************************************************/

bool NuV2C_parseoptionst::translator() {
    if (cmdline.args.size() == 0) {
        error() << "Please provide a source file to translate" << eom;
        return true;
    }

    try {
        if (cmdline.isset("show-parse-tree")) {
            if (cmdline.args.size() != 1) {
                error() << "Please give one source file only" << eom;
                return true;
            }

            std::string filename = cmdline.args[0];

#ifdef _MSC_VER
            std::ifstream infile(widen(filename).c_str());
#else
            std::ifstream infile(filename.c_str());
#endif

            if (!infile) {
                error() << "failed to open input file `" << filename << "'" << eom;
                return true;
            }

            languaget *language = get_language_from_filename(filename);

            if (language == NULL) {
                error() << "failed to figure out type of file `" << filename << "'" << eom;
                return true;
            }

            language->set_message_handler(get_message_handler());

            status("Parsing", filename);

            if (language->parse(infile, filename)) {
                error() << "PARSING ERROR" << eom;
                return true;
            }

            language->show_parse(std::cout);
            return true;
        } else {
            std::string filename = cmdline.args[0];
            status("Parsing", filename);

            if (parse(filename)) {
                error() << "PARSING ERROR" << eom;
                return true;
            }

            if (typecheck()) return true; //只注释这一个地方是不行的，注释了函数里面的代码
            if (final()) return true; //一定是条件为false

            // we no longer need any parse trees or language files
            clear_parse();
        }
    }

    catch (const char *e) {
        error() << e << eom;
        return true;
    }
    catch (const std::string e) {
        error() << e << eom;
        return true;
    }
    catch (int) {
        return true;
    }
    catch (std::bad_alloc) {
        error() << "Out of memory" << eom;
        return true;
    }

    return false;
}

/*******************************************************************\

  Function: NuV2C_parseoptionst::translate_module

  Inputs:

  Outputs:

  Purpose: add additional (synchonous) modules

\*******************************************************************/

bool NuV2C_parseoptionst::translate_module() {
    const std::string module =
            cmdline.isset("module") ? cmdline.get_value("module") : "";

    std::string output;

    if (cmdline.args.size() == 2)
        output = cmdline.args[1];
    else {
        error() << "Insufficient number of arguments";
        throw 0;
    }

    status() << "The output filename is " << output << eom;

    if (module != "" && output != "") {
        try {
            const symbolt &symbol =
                    get_module(symbol_table, module, get_message_handler());
            const irep_idt &module1 = symbol.name; //"Verilog::main"

            status() << "Translating Verilog to C" << eom;

            std::ofstream out(output.c_str());

            if (!out) {
                error() << "Failed to open output file" << eom;
                throw 0;
            }

            vtoexpr(symbol_table, module1, out);//这个函数很重要,开始向文件中写入程序

            return false;
        }
        catch (int e) {
            return true;
        }
    }

    return false;
}

/*******************************************************************\

  Function: NuV2C_parseoptionst::help

  Inputs:

  Outputs:

  Purpose: display command line help

\*******************************************************************/

void NuV2C_parseoptionst::help() {
    std::cout <<
              "NuV2C accepts the following options:\n"
//              " --show-parse-tree            shows the parse tree\n"
              " --module name                top module for unwinding\n"
//              " --string                     print string_container\n"
//              " --symbol_table               print symbol_table\n"
              "\n";
}

/*******************************************************************\

  Function: NuV2C_parseoptionst::register_languages

  Inputs:

  Outputs:

  Purpose:

\*******************************************************************/

void NuV2C_parseoptionst::register_languages() {
    register_language(new_verilog_language);
}

/*******************************************************************\
  Function: NuV2C_parseoptionst:: doit
  Purpose: invoke main modules
\*******************************************************************/

int NuV2C_parseoptionst::doit() {
    std::cout << "                                NuV2C                                      \n";
    std::cout << "                       基于综合语义的Verilog到C转换系统                        \n";
    std::cout << "使用方法: NuV2C source_files.v --module <name of top module> output_c_file.c\n";
    std::cout << "****************************************************************************\n\n";

    register_languages();
    // command line options
    if (config.set(cmdline)) {
        usage_error();
        exit(1);
    }

    if (!translator() && !translate_module()) {
        if (cmdline.isset("string")) {
//            char fullname[30]; //输出string容器到解析目录下
//            gethostname(fullname, 30);
//            std::string realname = fullname;
//            size_t pos = realname.find("-VirtualBox");
//            if (pos != std::string::npos)
//                realname = realname.substr(0, pos);
//            std::string path = "/home/" + realname + "/NuV2C/bin/string.h";
//            std::ofstream string_out(path);
            std::ofstream string_out("./string");
            if (string_out)
                string_container.my_showall(string_out);
//        symbol_table.show(string_out);
        }
        if (cmdline.isset("symbol")) {
            std::ofstream string_out("./symbol");
            if (string_out)
                symbol_table.show(string_out);
        }
        return 0;
    } else
        return 1;
}