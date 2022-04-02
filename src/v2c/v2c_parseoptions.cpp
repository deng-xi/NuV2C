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

#include "v2expr.h"
#include "v2c_parseoptions.h"

/*******************************************************************\

  Function: v2c_parseoptionst:: vtoc

  Inputs:

  Outputs:

  Purpose: invoke main modules

\*******************************************************************/

int v2c_parseoptionst::doit() {
    std::cout << "|----------------------------------------------------------------------|\n";
    std::cout << "|*********                    v2c 0.1                             *****|\n";
    std::cout << "|*********            Verilog to C Translator                     *****|\n";
    std::cout << "|********* Authors: Rajdeep Mukherjee and Michael Tautschnig      *****|\n";
    std::cout << "|*********           Developed at University of Oxford            *****|\n";
    std::cout << "|********* Usage: v2c main.v --module <name of top module> main.c *****|\n";
    std::cout << "|----------------------------------------------------------------------|\n";

    register_languages();

    //
    // command line options
    //

    if (config.set(cmdline)) {
        usage_error();
        exit(1);
    }

    if (!translator() && !translate_module()) {
        if (cmdline.isset("debug")) {
            char fullname[30]; //输出string容器到解析目录下
            gethostname(fullname, 30);
            std::string realname = fullname;
            size_t pos = realname.find("-VirtualBox");
            if (pos != std::string::npos)
                realname = realname.substr(0, pos);
            std::string path = "/home/" + realname + "/myv2c/bin/string.h";
            std::ofstream string_out(path);
            if (string_out)
                string_container.my_showall(string_out);
//        symbol_table.show(string_out);
        }
        return 0;
    } else
        return 1;
}

/*******************************************************************\

  Function: v2c_parseoptionst::translator()

  Inputs:

  Outputs:

  Purpose: Translator parse options

\*******************************************************************/

bool v2c_parseoptionst::translator() {
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

  Function: v2c_parseoptionst::translate_module

  Inputs:

  Outputs:

  Purpose: add additional (synchonous) modules

\*******************************************************************/

bool v2c_parseoptionst::translate_module() {
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

  Function: v2c_parseoptionst::help

  Inputs:

  Outputs:

  Purpose: display command line help

\*******************************************************************/

void v2c_parseoptionst::help() {
    std::cout <<
              "v2c accepts the following options:\n"
              " --show-parse-tree            shows the parse tree\n"
              " --module name                top module for unwinding\n"
              "\n";
}

/*******************************************************************\

  Function: v2c_parseoptionst::register_languages

  Inputs:

  Outputs:

  Purpose:

\*******************************************************************/

void v2c_parseoptionst::register_languages() {
    register_language(new_verilog_language);
}

