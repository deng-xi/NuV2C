/***********************************************************************
 Tool Name : v2c
 Purpose : Verilog RTL to ANSI-C translator tool
 Author: Rajdeep Mukherjee, Michael Tautschnig and Daniel Kroening
***********************************************************************/

#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <util/i2string.h>
#include <util/arith_tools.h>
#include <util/location.h>
#include <util/expr_util.h>
#include <util/simplify_expr.h>
#include <util/identifier.h>
#include <util/std_expr.h>
#include <util/expr.h>
#include <util/std_types.h>
#include <util/config.h>
#include <util/message.h>
#include <util/namespace.h>
#include <util/base_type.h>
#include <util/std_code.h>
#include <util/find_symbols.h>
#include <util/pointer_offset_size.h>

#include <verilog/expr2verilog.h>
#include <verilog/expr2verilog.cpp>
#include <verilog/verilog_typecheck_expr.cpp>
#include <verilog/verilog_expr.h>
#include <verilog/verilog_parse_tree.h>
#include <queue>

#include "v2expr.h"
#include "expression_datatype.h"


/*******************************************************************\

Function: vtoexpr

Inputs:

Outputs:

Purpose: top level function

\*******************************************************************/

bool vtoexpr(symbol_tablet &symbol_table, const irep_idt &module, std::ostream &out) {
    namespacet ns(symbol_table);
//    symbol_table.show(std::cout);
    verilog_exprt verilog_expr(symbol_table, module);
    const symbolt &symbol = ns.lookup(module);//信息存储在type和value中
    out << "#include <stdio.h>" << std::endl;
    out << "#include <assert.h>" << std::endl;
    out << "#define TRUE 1" << std::endl;
    out << "#define FALSE 0" << std::endl << std::endl;
    // save the top module
    verilog_expr.top_name = symbol.name; //"Verilog::main"
    return verilog_expr.convert_module(symbol, out); //这个函数很重要
}

/*******************************************************************\

Function: verilog_expression2c

Inputs:

Outputs:

Purpose: top level function

\*******************************************************************/

static std::string verilog_expression2c(const exprt &expr, const namespacet &ns) {
    std::string code;
    datatypet exprdt(ns);
    exprdt.get_shorthands(expr);
    return exprdt.convert(expr); //cbmc::expr2c.cpp,转换verilog的每一项
}

/*******************************************************************\

Function: verilog_exprt::convert_module

Inputs:

Outputs:

Purpose:

\*******************************************************************/
std::set<std::string> verilog_exprt::exprSymbols(irept ireptTmp) {
    std::set<std::string> res;
    if (ireptTmp.id() == ID_member) {
        res.emplace(ireptTmp.get_string(ID_component_name));
        return res;
    } else if (ireptTmp.id() == ID_symbol) {
        res.emplace(ns.lookup(ireptTmp.get_string(ID_identifier)).base_name.c_str());
    }
    irept::subt myOperands = ireptTmp.get_sub();
    forall_irep(it, myOperands) {
        auto subRes = exprSymbols(*it);
        if (!subRes.empty()) {
            res.insert(subRes.begin(), subRes.end());
        }
    }
    return res;
}

//std::string bfs(std::queue<irept> myqueue) {
//    if (myqueue.empty()) return "";
//    irept ireptTmp = myqueue.front();
//    myqueue.pop();
//    if (ireptTmp.id() == ID_member)
//        return ireptTmp.get_string(ID_component_name);
//    irept::subt myOperands = ireptTmp.get_sub();
//    forall_irep(it, myOperands) {
//        myqueue.push(*it);
//    }
//    return bfs(myqueue);
//}

//std::string dfs(std::stack<irept> mystack) {
//    if (mystack.empty()) return "";
//    irept ireptTmp = mystack.top();
//    mystack.pop();
//    if (ireptTmp.id() == ID_member)
//        return ireptTmp.get_string(ID_component_name);
//    irept::subt myOperands = ireptTmp.get_sub();
//    std::reverse(myOperands.begin(), myOperands.end());
//    forall_irep(it, myOperands) {
//        mystack.push(*it);
//    }
//    return dfs(mystack);
//}
std::list<codet> myCodeAssert;

bool verilog_exprt::convert_module(const symbolt &symbol, std::ostream &out) {
    assert(symbol.value.id() == ID_verilog_module);
    code_blockt code_verilogblock;
    if (modules_done.find(symbol.name) != modules_done.end())
        return true;

    // check for cyclic module instantiations
    if (modules_in_progress.find(symbol.name) != modules_in_progress.end()) {
        error() << "cyclic module instantiation in module `"
                << symbol.name << "'" << eom;
        throw 0;
    }
    std::map<irep_idt, irep_idt> identifierv;
    std::map<irep_idt, irep_idt> *identifier_name_backup = identifier_name;
    identifier_name = &identifierv;
    irep_idt curr_module_backup = current_module;
    current_module = symbol.name;

    std::set<irep_idt>::iterator
            in_progress_it = modules_in_progress.insert(symbol.name).first;

    // Process module local symbols, symbols是模块名和本地变量名
    forall_symbol_module_map(it, symbol_table.symbol_module_map, symbol.name) {
        const symbolt &symbol1 = ns.lookup(it->second);
        if (symbol1.type.id() != ID_module && symbol1.type.id() != ID_module_instance)
            //只有一个"."即代表属于top模块变量
            if (as_string(symbol1.name).find_first_of(".") == as_string(symbol1.name).find_last_of("."))
                identifierv[symbol1.base_name] = symbol1.name;
    }

    // Store the name of the structure
    module_infot &modulevb = module_info[current_module];//modulevb为空, module_info也只有key
    modulevb.struct_name = std::string("s") + id2string(symbol.base_name);
    modulevb.st.set_tag(current_module);
    code_blockt code_verilogb;
    forall_operands(it, symbol.value) {
            if (it->id() != ID_decl) //排除所有非ID_decl类型,对ID_decl类型进行操作
                continue;
            const verilog_declt &statement = to_verilog_decl(*it);

            if (statement.get(ID_class) == ID_task) {
                convert_task(static_cast<const verilog_module_itemt &>(*it), out);
            }
            if (statement.get(ID_class) == ID_function) {
                convert_function(static_cast<const verilog_module_itemt &>(*it), out);
            }
        }

    // *****************************************************************************
    // perform dependency analysis to check for cyclic dependency
    // Algorithm: M1(a,b), M2(b,a)
    // Input:  a->M1, b->M2
    // Output: b->M1, a->M2
    // intersect({value(input,a),value(input,b)},{value(output,a),value(output,b)})
    // intersect({M1,M2},{M1,M2})
    // *****************************************************************************
    forall_operands(it, symbol.value) { //模块之间的依赖分析
            if (it->id() == ID_inst) {
                const irep_idt &identifier = it->get(ID_module);
                // must be in symbol_table
                const symbolt &symbol_module = ns.lookup(identifier);
                forall_operands(it, static_cast<const exprt &>(symbol.type.find(ID_ports))) {
                        if (it->get(ID_input) == "1") {
                            const irep_idt &input_name = ns.lookup(it->get(ID_identifier)).base_name;
                            input_dependency_map[input_name] = identifier;
                        } else {
                            const irep_idt &output_name = ns.lookup(it->get(ID_identifier)).base_name;
                            output_dependency_map[output_name] = identifier;
                        }
                    }
            }
        }

    std::set<irep_idt> inputm;
    std::set<irep_idt> outputm;
    for (std::map<irep_idt, irep_idt>::iterator iter = input_dependency_map.begin();
         iter != input_dependency_map.end(); ++iter) {
        irep_idt input_key = iter->first;
        std::map<irep_idt, irep_idt>::iterator found = output_dependency_map.find(input_key);
        if (found != output_dependency_map.end()) {
            inputm.insert(iter->second);
            outputm.insert(found->second);
        }
    }

    // check if intersection of input and output set is empty (above for loop with little change)
    std::set<irep_idt> intersect;
    for (std::set<irep_idt>::iterator iter = inputm.begin(); iter != inputm.end(); ++iter) {
        //irep_idt input_element = iter;
        std::set<irep_idt>::iterator found = outputm.find(*iter);
        if (found != outputm.end()) {
            intersect.insert(*iter);
        }
    }

    // print the modular dependency
    for (std::set<irep_idt>::iterator iter = intersect.begin(); iter != intersect.end(); ++iter) {
    }

    // Process module items
    forall_operands(it, symbol.value) { //一个模块
            if (it->id() == ID_inst) {
                const irep_idt &identifier = it->get(ID_module);
                // must be in symbol_table
                const symbolt &symbol_module = ns.lookup(identifier);
                convert_module(symbol_module, out);
            }

            // Convert module items
            // code_pairt is used to used to handle if-else blocks containing
            // non-blocking assignments in multiple always blocks as follows:
            // if(reset)             if(reset) tmp0 = 0;
            //   x <= 1'b0;          else tmp1 = 1;
            //  else         -->     if(reset) x = tmp0;
            //   x <= 1'b1;          else x = tmp1;
            // The first part of code_pairt here contains temporary assignments with
            // guards and the second part contains actual assignment with guards. This
            // is also needed with same if-else blocks defined in multiple clocked blocks.

            codet codefinal =
                    convert_module_item(static_cast<const verilog_module_itemt &>(*it));//给模块每个项赋具体值

            //删除被调函数中的assert
            if (codefinal.get_statement() == ID_assert) {
                myCodeAssert.push_back(codefinal);
                continue;
            }
            if (codefinal.get_statement() != ID_block)
                code_verilogblock.operands().push_back(codefinal);
            else
                // ID_block always contains {}, so just push back its operands
            forall_operands(itf, codefinal) code_verilogblock.operands().push_back(*itf);
        } //end of for loop


    code_blockt code_temp;
    code_temp.swap(code_verilogblock);
    // Declare all new temporary shadow variables introduced for non-blocking and blocking assignment
    for (std::list<code_declt>::const_iterator it4 = modulevb.new_var.begin();
         it4 != modulevb.new_var.end(); ++it4)
        code_verilogblock.operands().push_back(*it4);


    // handle the case of shadow assignments to be put before the clocked block
    for (std::list<codet>::const_iterator it3 = modulevb.shadowassign.begin();
         it3 != modulevb.shadowassign.end(); ++it3) {
        code_verilogblock.operands().push_back(*it3);
    }

    // Handle the case of continuous assignment
//    std::tr1::unordered_set<std::string> lhSymbols;
    Forall_operands(it, code_temp) {
            if (*it != codet()) { //是指不为空?
                code_verilogblock.operands().push_back(*it);
//                //增加依赖分析，便于实现连续赋值的 Read-After-Write 顺序
//                if (it->get(ID_statement) == ID_assert) //去除assert对依赖分析的影响
//                    continue;
//                std::string lhs = (*it).op0().get_string(ID_component_name);
//                if ((*it).get(ID_statement) == ID_ifthenelse) {
//                    if (it->op1().id() == ID_code &&
//                        it->op1().get(ID_statement) == ID_assign) { //todo then是一个block则把左值放到一个集合中
//                        if (it->op1().op0().id() == ID_index) {
//                            lhs = it->op1().op0().op0().get_string(ID_component_name);
//                        } else
//                            lhs = it->op1().op0().get_string(ID_component_name);
//                        assert(lhs != "");
//                    }
//                }
//                lhSymbols.insert(lhs);
//                for (std::list<code_assignt>::const_iterator it3 = modulevb.cassignReg.begin();
//                     it3 != modulevb.cassignReg.end(); ++it3) {
//                    bool allUpdated = true;
//                    auto rhSymbols = exprSymbols((*it3).op1()); //获取连续赋值右边表达式所有变量名
//                    bool rhsUpdated = false;
//                    for (auto rhSymbol: rhSymbols) {
//                        if (rhSymbol == lhs) {
//                            rhsUpdated = true;
//                        }
//                    }
//                    if (!rhsUpdated)
//                        continue;
//                    for (auto rhSymbol: rhSymbols) {
//                        if (!lhSymbols.count(rhSymbol)) {
//                            allUpdated = false;
//                        }
//                    }
//                    if (allUpdated) { //右边的寄存器变量更新了
//                        if ((*it).get(ID_statement) == ID_ifthenelse) {//暂时只考虑then块
//                            if ((*it).op1().get(ID_statement) != ID_block) {
//                                code_blockt mycode;
//                                mycode.copy_to_operands(code_verilogblock.operands().back().operands()[1]);
//                                mycode.add(to_code(*it3));
//                                code_verilogblock.operands().back().operands()[1] = mycode;
//                            } else {
//                                code_verilogblock.operands().back().operands()[1].operands().push_back(
//                                        to_code(*it3));
//                            }
//                        } else code_verilogblock.operands().push_back(*it3);
//
//                        std::string cassignReg_lhs = (*it3).op0().get_string(ID_identifier);
//                        for (std::list<code_assignt>::const_iterator it4 = modulevb.cassign.begin();
//                             it4 != modulevb.cassign.end(); ++it4) {
//                            std::string cassign_rhs = (*it4).op1().get_string(ID_identifier);
//                            if (cassign_rhs == cassignReg_lhs) //右边的线网变量更新了
//                                code_verilogblock.operands().push_back(*it4);
//                        }
//                    }
//                }
            }
        }
    // **************** Dependency Analysis *********************
    // Handle the case of continuous assignment with Registers on the RHS
    // Place these assignment statements after all the next states have been updated
    for (std::list<code_assignt>::const_iterator it3 = modulevb.cassignAll.begin(); //增加连续赋值cassignReg改为cassignAll
         it3 != modulevb.cassignAll.end(); ++it3) { //将最后一个连续赋值移动到assert前
//        if (code_verilogblock.operands().rbegin()->get(ID_statement) == ID_assert) {
//            code_verilogblock.operands().insert(code_verilogblock.operands().end() - 1, *it3);
//        } else
        code_verilogblock.operands().push_back(*it3);
    }

    //对所有输出增加赋值
    for (replace_symbolt::expr_mapt::const_iterator it = modulevb.output_var.expr_map.begin();
         it != modulevb.output_var.expr_map.end(); ++it) {
        if (modulevb.registers.expr_map.count(it->first)) {
            exprt lhs = it->second;
            exprt rhs = modulevb.registers.expr_map.find(it->first)->second;
            code_assignt myassign(lhs, rhs);
            code_verilogblock.operands().push_back(myassign);
        }
    }

    //将assert放到最后
    for (std::vector<exprt>::iterator it = code_verilogblock.operands().begin();
         it != code_verilogblock.operands().end(); ++it) {
        if (it->get(ID_statement) == ID_assert) {
            auto itTmp = *it;
            code_verilogblock.operands().erase(it);
            code_verilogblock.operands().push_back(itTmp);
            break;
        }
    }

    bool return_conv = do_conversion(code_verilogblock, symbol,
                                     curr_module_backup, in_progress_it, out);//这里写入文件
    identifier_name = identifier_name_backup;

    return return_conv;
}

/*******************************************************************\

Function: verilog_exprt::do_conversion

Inputs:

Outputs:

Purpose:

\*******************************************************************/

bool verilog_exprt::do_conversion(code_blockt &code_verilogblock, const symbolt &symbol,
                                  const irep_idt &curr_module_backup,
                                  const std::set<irep_idt>::iterator &in_progress_it,
                                  std::ostream &out) {

    module_infot &modulevb = module_info[current_module];

    std::ostringstream str_print;
    code_blockt code_parameterblock;
    // print the parameters without any enclosing {}
    if (modulevb.parameter) {
        out << std::endl;
        forall_operands(itp, parameter_block) { //str_print改为out,首先输出parameter
                out << verilog_expression2c(*itp, ns) << std::endl; // This is also correct
            }
        out << std::endl;
    }

    // Finally, iterate over a module to replace all reg type variables with its corresponding structure
    iterate_module(code_verilogblock, modulevb);

    // Declare the structure here
    if (modulevb.register_present) {
        out << "struct state_elements_" << symbol.base_name << "{" << std::endl;
        for (replace_symbolt::expr_mapt::const_iterator it = modulevb.registers.expr_map.begin();
             it != modulevb.registers.expr_map.end(); ++it) {
            symbol_exprt symstruct(it->first, ns.lookup(it->first).type);
            code_declt dstruct(symstruct);
            std::string d_str = verilog_expression2c(dstruct, ns);
            out << "  " << d_str.substr(0, d_str.size()) << std::endl;
        }
        // A module instance is also member of structure
        forall_symbol_module_map(it, symbol_table.symbol_module_map, symbol.name) {
            // RM: We need to check if the instantiated module also contains register type elements.
            //     If so, we can dump the corresponding structure as an element inside this structure
            const symbolt &symbol = ns.lookup(it->second);
            if (symbol.type.id() == ID_module_instance) {
                const symbolt &module_symbol = ns.lookup(symbol.value.get(ID_module));
                out << "  struct state_elements_"
                    << module_symbol.base_name
                    << " s" << symbol.base_name << ";\n ";
            }
        }
        out << "};" << std::endl;
        out << "struct state_elements_" << symbol.base_name << " s" << symbol.base_name << ";\n\n";
    }

    if (modulevb.initial == true) { //初始化函数
        out << "void initial_" + id2string(symbol.base_name) + "()";
        if (initial_block.op0().id() == ID_code && initial_block.operands().size() == 1) { //优化initial输出格式
            exprt exprBlock = initial_block.op0();
            initial_block.operands().pop_back();
            for (auto exprTmp: exprBlock.operands()) {
                initial_block.operands().push_back(exprTmp);
            }
        }
        out << verilog_expression2c(initial_block, ns) << std::endl << std::endl;
    }

    // Function definition printing here
    code_typet typev;
    typev.return_type() = empty_typet();
    for (std::list<symbol_exprt>::const_iterator it = modulevb.parameters.begin();
         it != modulevb.parameters.end(); ++it) {
        code_typet::parametert param(it->type());
        param.set_identifier(it->get_identifier());
        typev.parameters().push_back(param);
    }

    symbol_exprt sym(symbol.name, typev);
    code_declt d(sym);
    std::string d_str = verilog_expression2c(d, ns);
    assert(!d_str.empty());
    assert(*d_str.rbegin() == ';');
    out << d_str.substr(0, d_str.size() - 1) << std::endl;

    std::string code_str;
    // Finally calls the expr2c framework to get the C output
    code_str = verilog_expression2c(code_verilogblock, ns);
    // print the name of structure
//    if (modulevb.register_present) {
//        std::string struct_d = "struct state_elements_"
//                               + id2string(symbol.base_name) + "  " + id2string(modulevb.struct_name) + ";\n  ";
//        code_str.insert(4, struct_d);
//    }
    out << code_str + "\n\n";


    // Print the void main function
    if (symbol.name == module) {

        str_print << "void main() {" << "//main function" << std::endl;
        code_blockt code_blockv;
        // Declare the parameters of the top level function
        for (std::list<symbol_exprt>::const_iterator it = modulevb.local_sym.begin();
             it != modulevb.local_sym.end(); ++it) {
            symbol_exprt var = *it;
            const symbol_exprt sym(var.get_identifier(), var.type());
            str_print << "  " << verilog_expression2c(code_declt(sym), ns) << std::endl;
        }
        str_print << std::endl;
        if (modulevb.initial == true)
            str_print << "  initial_" + id2string(symbol.base_name) + "();\n\n";

        // print the while loop only for top level module call from the main function
        // and if the design is sequential circuit
        if (symbol.base_name != top_name && sequential)
            str_print << "  while(1) {" << std::endl;

        //增加input变量非确定性赋值
        for (symbol_tablet::symbolst::const_iterator it = symbol_table.symbols.begin();
             it != symbol_table.symbols.end(); ++it) {
            if (it->second.is_input) {
                std::string nondet;
                datatypet myexpr2ct(ns);
                nondet = id2string(it->second.base_name);
                std::string typeString = myexpr2ct.convert(it->second.type);
                if (typeString == "_Bool") {
                    typeString = "bool";
                } else if (typeString == "unsigned char") {
                    typeString = "uchar";
                } else if (typeString == "unsigned int") {
                    typeString = "uint";
                }
                nondet = nondet + " = nondet_" + typeString + "();\n";
                if (symbol.base_name != top_name && sequential)
                    str_print << "    " << nondet;
                else str_print << "  " << nondet;
            }
        }
        str_print << std::endl;
        // Just call the top level verilog module given as command line argument
        code_function_callt code_function_callv;
        const irep_idt &identifier = symbol.name;
        code_function_callv.function() = symbol_exprt(identifier);

        // must be in symbol_table
        for (std::list<symbol_exprt>::const_iterator it =
                modulevb.parameters.begin(); it != modulevb.parameters.end(); ++it) {
            exprt arg = *it;
            if (it->id() == ID_named_port_connection)
                arg = it->op1();
            if (it->type().id() == ID_pointer)
                arg = address_of_exprt(arg);
            code_function_callv.arguments().push_back(arg);
        }
        // Insert all modules having a always(poesdge clk) block
        // into a code block
        if (modulevb.always == true) {
            // End of while(1) loop
            str_print << "    " << verilog_expression2c(code_function_callv, ns) << std::endl << std::endl;

            //增加assert
            for (std::list<codet>::const_iterator it_assert = myCodeAssert.begin();
                 it_assert != myCodeAssert.end(); ++it_assert) {
                if (it_assert->get_statement() == ID_assert && it_assert->has_operands() &&
                    it_assert->get_sub().front().id() == ID_overlapped_implication) {
                    exprt before_implication = it_assert->op0().op0();
                    exprt after_implication = it_assert->op0().op1();
                    str_print << "    if(" << verilog_expression2c(before_implication, ns) << ") {\n";
                    if (after_implication.id() == ID_sva_cycle_delay) {
                        int delay_time = after_implication.op0().get_int(ID_value);
                        //二进制转换为十进制
                        int decimalNumber = 0, i = 0, remainder;
                        while (delay_time != 0) {
                            remainder = delay_time % 10;
                            delay_time /= 10;
                            decimalNumber += remainder * pow(2, i);
                            ++i;
                        }
                        for (; decimalNumber > 0; --decimalNumber) {
                            str_print << "      " << verilog_expression2c(code_function_callv, ns) << std::endl;
                        }
                        str_print << "      assert(" << verilog_expression2c(after_implication.op2(), ns) << ");\n";
                        str_print << "    }\n\n";
                    } else {
                        str_print << "      assert(" << verilog_expression2c(after_implication, ns) << ");\n";
                        str_print << "    }\n\n";
                    }
                } else {
                    str_print << "    " << verilog_expression2c(*it_assert, ns) << "\n\n";
                }
            }

            str_print << "  }" << std::endl << std::endl;
        } else
            str_print << "  " << verilog_expression2c(code_function_callv, ns) << std::endl;
        // End of top level function
        str_print << "}" << std::endl;
    }
    out << str_print.str();


    current_module = curr_module_backup;
    modules_in_progress.erase(in_progress_it);
    modules_done.insert(symbol.name);
    return true;
}

/*******************************************************************\

Function: verilog_exprt::iterate_module

Inputs:

Outputs:

Purpose: Replace all reg type items with its structure member

\*******************************************************************/

void verilog_exprt::iterate_module(exprt &module1, const module_infot &modulevb) {
    // can modify it
    Forall_operands(it, module1) iterate_module(*it, modulevb);
    if (module1.id() == ID_symbol) {

    } else if (module1.id() == ID_typecast && module1.type().id() == ID_integer)
        module1 = module1.op0();

        // side effect handling for functions
    else if (module1.id() == ID_function_call) {
        side_effect_expr_function_callt side_eff;
        side_eff.function() = module1.op0();
        side_eff.arguments() = module1.op1().operands();
        module1 = side_eff;
    }
}

/*******************************************************************\

Function: verilog_exprt::convert_module_item

Inputs: Verilog Module Items

Outputs: Return codet type

Purpose: Translates Verilog Module Items

\*******************************************************************/

codet verilog_exprt::convert_module_item(
        const verilog_module_itemt &module_item) {
    if (module_item.id() == ID_specify) {
    }
    if (module_item.id() == ID_decl) {
        return convert_decl(to_verilog_decl(module_item));
    } else if (module_item.id() == ID_parameter_decl ||
               module_item.id() == ID_local_parameter_decl) {
        return convert_parameter(module_item);
    } else if (module_item.id() == ID_always) {
        return convert_always(to_verilog_always(module_item));
    } else if (module_item.id() == ID_initial) {
        return convert_initial(to_verilog_initial(module_item));
    } else if (module_item.id() == ID_continuous_assign) {
        return convert_continuous_assign(to_verilog_continuous_assign(module_item));
    } else if (module_item.id() == ID_inst) {
        return convert_inst(to_verilog_inst(module_item));
    } else if (module_item.id() == ID_generate_block) {
        throw "unexpected generate module item during translation";
    } else if (module_item.id() == ID_assert) {
        return convert_assert(to_verilog_assert(module_item));
    }
        /*else if(module_item.id()==ID_assume) {
		return convert_assume(module_item);
	}*/
    else {
        error() << "unexpected module item during synthesis: `"
                << module_item.id() << "'" << eom;
        throw 0;
    }
}

/*******************************************************************\

Function: verilog_exprt::convert_decl

Inputs: "input reset; reg[31:0] sum; reg i = 1'b0;"

Outputs: bool reset; int sum; bool i = 0;

Purpose: Translates a Verilog declaration to C

\*******************************************************************/
codet verilog_exprt::convert_decl(
        const verilog_declt &statement) {
    code_blockt code_blockv;
    module_infot &modulevb = module_info[current_module];
    forall_operands(it, statement) {
            symbol_exprt curr_variable;
            irep_idt full_name;
            assert(identifier_name != 0);
            // check for symbol
            if (it->id() == ID_symbol) {
                curr_variable = to_symbol_expr(*it);
                full_name = (*identifier_name)[curr_variable.get_identifier()];
            }
                // check for array
            else if (it->id() == ID_array) {
                curr_variable = symbol_exprt(it->get(ID_identifier));
                full_name = (*identifier_name)[curr_variable.get_identifier()];
            } else {
                curr_variable = to_symbol_expr(it->op0());
                full_name = curr_variable.get_identifier();
            }
            const symbolt &symbol = ns.lookup(full_name);
            // check for ports (Input, Output)
            if (statement.get(ID_class) == ID_input) {
                assert(it->id() == ID_symbol);
                // Prepare symbol for the module parameter
                module_info[current_module].parameters.push_back(symbol.symbol_expr());

                // Prepare symbol for the module local symbol (local symbols are declared static)
                //symbol_exprt symb = symbol.symbol_expr();
                //to_code_type(symb.type());
                module_info[current_module].local_sym.push_back(symbol.symbol_expr());

            } else if (statement.get(ID_class) == ID_output) {
                assert(it->id() == ID_symbol);
                // Prepare symbol for the module local symbol
                module_info[current_module].local_sym.push_back(symbol.symbol_expr());
                module_info[current_module].output_var.insert(symbol.name, dereference_exprt(symbol.symbol_expr()));
                // Prepare symbol for the module parameter
                symbol_exprt symout = symbol.symbol_expr();
                symout.type() = pointer_typet(symbol.type);
                module_info[current_module].parameters.push_back(symout);
            }
                // check for register
            else if (statement.get(ID_class) == ID_reg) {
                symbol_exprt symout = symbol.symbol_expr();
                struct_typet::componentt sc;
                sc.set_name(ns.lookup(symout.get_identifier()).base_name);
                sc.type() = symout.type();
                module_info[current_module].st.components().push_back(sc);
                module_info[current_module].register_present = 1;
                member_exprt reg_member(symbol_exprt(modulevb.struct_name, modulevb.st), symbol.base_name);
                module_info[current_module].registers.insert(symbol.name, reg_member);
                // this is handled for non-blocking assignment 先删去所有的影子变量定义
//                symbol_exprt old_reg(symbol_exprt(id2string(symbol.base_name) +"_old"));
//                module_info[current_module].oldvar.insert(symbol.name, old_reg);
//                old_reg.type() = symbol.type;
//                // insert the newly created symbol into new_var
//                module_info[current_module].new_var.push_back(code_declt(old_reg));

                // this is handled for blocking assignment, this must be handled elsewhere because always_counter
                // is updated only after looking at an always block
                // 增加影子变量初始化
//                if (modulevb.nb_duplicate.insert(old_reg.get_identifier()).second) {
//                    modulevb.registers(reg_member);
//                    code_assignt code_nb(old_reg, reg_member);
//                    modulevb.shadowassign.push_back(code_nb);
//                }
            }
                // check for integer variable
            else if (statement.get(ID_class) == ID_integer) {
                if (it->id() != ID_array) {
                    symbol_exprt symint = symbol.symbol_expr();
                    symint.type() = signedbv_typet(32);
                    modulevb.new_var.push_back(code_declt(symint));
                } else {
                    symbol_exprt symarray = symbol.symbol_expr();
                    symarray.type() = symbol.type;
                    symarray.type().subtype() = signedbv_typet(32);
                    modulevb.new_var.push_back(code_declt(symarray));
                }
            }
                // check for real variable
            else if (statement.get(ID_class) == ID_realtime) {
                symbol_exprt symint = symbol.symbol_expr();
                symint.type() = signedbv_typet(64);
                modulevb.new_var.push_back(code_declt(symint));
            }

                // only wire declarations are processed
                // Declarations of the type wire x = 1'b0;
            else if (it->id() == ID_equal) {
                modulevb.new_var.push_back(code_declt(symbol.symbol_expr()));
                if (it->operands().size() != 2)
                    throw "expected two operands in assignment";
                exprt lhs = it->op0();
                exprt rhs = it->op1();
                module_infot &modulevb = module_info[current_module];

                if (rhs.id() == ID_extractbits) {
                    if (rhs.operands().size() != 3)
                        throw "extractbits takes three operands";
                    symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
                    mp_integer size_op1;
                    to_integer(rhs.op1(), size_op1);
                    mp_integer size_op2;
                    to_integer(rhs.op2(), size_op2);
                    unsigned diff = integer2unsigned(size_op1 - size_op2);
                    ashr_exprt shr(rhs_symbol, rhs.op2());
                    constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
                    bitand_exprt andexpr(shr, constant1);
                    rhs = andexpr;
                } else if (rhs.id() == ID_extractbit) {
                    if (rhs.operands().size() != 2)
                        throw "extractbit takes two operands";
                    symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
                    mp_integer size_op1;
                    to_integer(rhs.op1(), size_op1);
                    ashr_exprt shr(rhs_symbol, rhs.op1());
                    constant_exprt constant1 = from_integer(power(2, 1) - 1, integer_typet());
                    bitand_exprt andexpr(shr, constant1);
                    rhs = andexpr;
                }
                modulevb.registers(rhs);
                modulevb.output_var(rhs);
                code_assignt declv(lhs, rhs);
                code_blockv.operands().push_back(declv);
            }
                // all other declarations in code_block
            else {
                std::list<symbol_exprt>::iterator findIter = std::find(modulevb.local_sym.begin(),
                                                                       modulevb.local_sym.end(), symbol.symbol_expr());
                if (findIter == modulevb.local_sym.end())
                    modulevb.new_var.push_back(code_declt(symbol.symbol_expr()));
            }
        }  //end of forloop
    return code_blockv;
}

/*******************************************************************\

Function: verilog_exprt::convert_expr

Inputs:

Outputs:

Purpose: convert expression of any type appearing in prodedural and
         non-procedural statements

\*******************************************************************/
exprt
verilog_exprt::convert_expr(exprt &expression, unsigned char &saved_diff, dstring expr_type) {
    while (expression.id() == ID_typecast)
        expression = expression.op0();
    if (expression.id() == ID_concatenation) {
        exprt concat_expr = expression;
        if (concat_expr.operands().size() == 0) {
            throw "concatenation expected to have at least one operand";
            throw 0;
        }
        bitor_exprt final_bitor;
        unsigned int diff = 0;
        exprt::operandst expr_concat;

        // Iterate over inverted direction to get the saved_diff properly !!
        for (exprt::operandst::reverse_iterator
                     it = concat_expr.operands().rbegin();
             it != concat_expr.operands().rend();
             it++) {
            if (it->id() == ID_extractbits) {
                exprt rhs = it->op0();
                if (it->operands().size() != 3)
                    throw "extractbits takes three operands";
                symbol_exprt rhs_symbol = to_symbol_expr(rhs);
                mp_integer size_op1;
                to_integer(it->op1(), size_op1);
                mp_integer size_op2;
                to_integer(it->op2(), size_op2);
                diff = integer2unsigned(size_op1 - size_op2);

                ashr_exprt shr(rhs_symbol, it->op2());
                constant_exprt constant = from_integer(power(2, diff + 1) - 1, integer_typet());
                bitand_exprt andexpr(shr, constant);
                shl_exprt shl(andexpr, saved_diff);
                saved_diff = saved_diff + (diff + 1);
                expr_concat.push_back(shl);
            } else if (it->id() == ID_extractbit) {
                exprt rhs = it->op0();
                if (it->operands().size() != 2)
                    throw "extractbit takes two operands";
                symbol_exprt rhs_symbol = to_symbol_expr(rhs);
                mp_integer size_op1;
                to_integer(it->op1(), size_op1);
                ashr_exprt shr(rhs_symbol, it->op1());
                diff = 0;

                if (it->op0().get(ID_type) == ID_unsignedbv &&
                    it->op0().find(ID_type).get_int(ID_width) - integer2unsigned(size_op1) > 1) { //8位的x[7]去掉&1
                    constant_exprt constant = from_integer(power(2, diff + 1) - 1, integer_typet());
                    bitand_exprt andexpr(shr, constant);
                    shl_exprt shl(andexpr, saved_diff);
                    saved_diff = saved_diff + (diff + 1);
                    expr_concat.push_back(shl);
                } else {
                    shl_exprt shl(shr, saved_diff);
                    saved_diff = saved_diff + (diff + 1);
                    expr_concat.push_back(shl);
                }
            } else if (it->id() == ID_unary_minus) { //处理连接表达式中的负号
                exprt exprt_minus = convert_expr(it->op0(), saved_diff, ID_unary_minus);
//                if (it->op0().id() == ID_extractbits) {
//                    exprt_minus.op0() = bitnot_exprt(exprt_minus.op0());
//                }
                expr_concat.push_back(exprt_minus);
            }
                // normal register assignment, handle constants
            else {
                exprt rhs = *it;
                shl_exprt shlsym(rhs, saved_diff);
                // find the size of the symbol
                mp_integer width = pointer_offset_bits(rhs.type(), ns);
                assert(width > 0);
                if (rhs.id() != ID_constant && width > 1 && width != 8 && width != 16 && width != 32 && width != 128) {
                    constant_exprt constant = from_integer(power(2, diff + 1) - 1, integer_typet());
                    bitand_exprt andexpr(shlsym, constant);
                    expr_concat.push_back(andexpr);
                } else {
//                    可能要删除常量0的位移? 其它地方也要改
//                    if (rhs.id() == ID_constant && rhs.get_int(ID_value) == 0)
//                        expr_concat.push_back(rhs);
//                    else
                    expr_concat.push_back(shlsym);
                }
                saved_diff = saved_diff + integer2unsigned(width);
            }
        } // end for
        // do a disjunction over all expressions stored in expr_concat
        bitor_exprt bitwise_or;
        std::swap(bitwise_or.operands(), expr_concat);
        // finally do the assignment
        expression = bitwise_or;
    } // end of concatenation handling
    else if (expression.id() == ID_extractbits) {
        exprt rhs = expression;
        if (rhs.operands().size() != 3)
            throw "extractbits takes three operands";
        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0()); //只取符号
        mp_integer size_op1;
        to_integer(rhs.op1(), size_op1);
        mp_integer size_op2;
        to_integer(rhs.op2(), size_op2);
        unsigned diff = integer2unsigned(size_op1 - size_op2);

        exprt expr_tmp = rhs_symbol;
        if (expr_type == ID_unary_minus) {
            expr_tmp = bitnot_exprt(rhs_symbol);
        }
        ashr_exprt shr(expr_tmp, rhs.op2());
        constant_exprt constant = from_integer(power(2, diff + 1) - 1, integer_typet());
        bitand_exprt andexpr(shr, constant);
        expression = andexpr;
        diff = integer2unsigned(size_op1 - size_op2);
        saved_diff = saved_diff = saved_diff + (diff + 1);
    } else if (expression.id() == ID_extractbit) {
        exprt rhs = expression;
        if (rhs.operands().size() != 2)
            throw "extractbit takes two operands";
        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
        mp_integer size_op1;
        to_integer(rhs.op1(), size_op1);
        exprt expr_tmp = rhs_symbol;
        if (expr_type == ID_unary_minus) {
            expr_tmp = bitnot_exprt(rhs_symbol);
        }
        ashr_exprt shr(expr_tmp, rhs.op1());
        constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
        bitand_exprt andexpr(shr, constant1);
        expression = andexpr;
        saved_diff = saved_diff = saved_diff + 1;
    } //处理= and nand or nor xor xnor not bitand bitor bitnot bitxor bitnand bitnor notequal >= <= > < + - * /
        //todo 还有一些类型没有考虑
    else if ((expression.id().get_no() == 37) || (expression.id().get_no() >= 40 && expression.id().get_no() <= 54) ||
             (expression.id().get_no() >= 356 && expression.id().get_no() <= 361) ||
             (expression.id().get_no() >= 364 && expression.id().get_no() <= 365)) {
        Forall_operands(it, expression) {
                unsigned char saved_diff = 0;
                *it = convert_expr(*it, saved_diff);
            }
    } else {
        if (expression.id() == ID_symbol) {
            if (expression.type().id() == ID_unsignedbv) {
                int width = expression.type().get_int(ID_width);
                if (width > 0 && width != 1 && width != 8 && width != 16 && width != 32 && width != 64 &&
                    width != 128) {
                    bitand_exprt band(expression,
                                      from_integer(power(2, width) - 1, integer_typet()));
                    expression = band;
                }
            }
        }
    }
    return expression;
}

/*******************************************************************\

Function: verilog_exprt::add_bitand

Inputs:

Outputs:

Purpose: add bitand to expression of any type appearing in prodedural and
         non-procedural statements

\*******************************************************************/

void verilog_exprt::add_bitand(exprt &expression) {
    while (expression.id() == ID_typecast)
        expression = expression.op0();
    if ((expression.id().get_no() == 37) || (expression.id().get_no() >= 40 && expression.id().get_no() <= 54) ||
        (expression.id().get_no() >= 356 && expression.id().get_no() <= 361) ||
        (expression.id().get_no() >= 364 && expression.id().get_no() <= 365)) {
        Forall_operands(it, expression) {
                add_bitand(*it);
            }
    } else if (expression.id() == ID_symbol) {
        if (expression.type().id() == ID_unsignedbv) { //数组索引也符合条件,数组名不符合
            int width = expression.type().get_int(ID_width);
            if (width > 0 && width != 1 && width != 8 && width != 16 && width != 32 && width != 64 &&
                width != 128) {
                bitand_exprt band(expression,
                                  from_integer(power(2, width) - 1, integer_typet()));
                expression = band;
            }
        }
    } else if (expression.id() == ID_index && expression.op0().id() == ID_symbol &&
               expression.op1().id() == ID_symbol) {//增加数组索引位与
        exprt expr_array = expression.op0();
        exprt expr_index = expression.op1();
        if (expr_index.type().id() == ID_unsignedbv) {
            int width = expr_index.type().get_int(ID_width);
            if (width > 0 && width != 1 && width != 8 && width != 16 && width != 32 && width != 64 &&
                width != 128) {
                bitand_exprt band(expr_index, from_integer(power(2, width) - 1, integer_typet()));
                expr_index = band;
                expression.op1() = expr_index;
            }
        }
    }
}

//std::string get_symbol(exprt expr) {
//    if (expr.id() == ID_symbol) {
//        return expr.get_string(ID_identifier);
//    }
//}

void verilog_exprt::add_cassignAll(code_blockt &my_code_block, std::set<std::string> &updated_sybmols) {
    module_infot &modulevb = module_info[current_module];
//    std::list<code_assignt> all_cassign;
//    all_cassign.assign(modulevb.cassignReg.begin(), modulevb.cassignReg.end());
//    all_cassign.
    for (std::list<code_assignt>::const_iterator it3 = modulevb.cassignAll.begin();
         it3 != modulevb.cassignAll.end(); ++it3) {
        auto cassign_rh_symbols = exprSymbols((*it3).op1()); //获取连续赋值右边表达式所有变量名
        bool updated_flag = false;
        for (auto updated_symbol: updated_sybmols) {
            if (cassign_rh_symbols.count(updated_symbol))
                updated_flag = true;
        }
        if (updated_flag) {
            std::string cassign_ls_symbol;
            if (it3->op0().id() == ID_symbol) {
                cassign_ls_symbol = ns.lookup(it3->op0().get(ID_identifier)).base_name.c_str();
            }
            if (it3->op0().id() == ID_dereference) {
                cassign_ls_symbol = ns.lookup(it3->op0().op0().get(ID_identifier)).base_name.c_str();
            }
            if (!updated_sybmols.count(cassign_ls_symbol)) {
                updated_sybmols.emplace(cassign_ls_symbol);
                my_code_block.add(*it3);
                add_cassignAll(my_code_block, updated_sybmols);
            }
        }
    }
}

/*******************************************************************\

Function: verilog_exprt::convert_parameter

Inputs: parameter lsb = 7; parameter foo = lsb+2; parameter x = log(y);

Outputs: int lsb; lsb = 7; int foo; foo = lsb+2;

Purpose: This function is used to convert parameter declaration
in verilog to constants in C

\*******************************************************************/

codet verilog_exprt::convert_parameter(const verilog_module_itemt &module_item) {
    module_infot &modulev = module_info[current_module];
    if (module_item.operands().size() != 1) {
        throw "parameter statement expected to have one operands";
    }

    code_blockt code_blockv;
    const symbol_exprt sym(module_item.op0().get(ID_identifier), signedbv_typet(32));
    code_blockv.operands().push_back(code_declt(sym));
    code_blockv.operands().back().copy_to_operands(
            constant_exprt(module_item.op0().find(ID_value).get(ID_value), integer_typet()));

    // ID_block always contains {}, so just push back its operands
    forall_operands(itp, code_blockv) parameter_block.operands().push_back(*itp);

    modulev.parameter = true;
    return codet();
}

/*******************************************************************\

Function: verilog_exprt::convert_initial

Inputs: initial begin
clk = 0;
reset = 0;
enable = 0;
data = 0;
end

Outputs: { clk = 0; reset = 0; enable = 0; data = 0 }

Purpose: Non-synthesizable

\*******************************************************************/

codet verilog_exprt::convert_initial(
        const verilog_initialt &module_item) {
    module_infot &modulev = module_info[current_module];
    code_blockt code_blockv;
    modulev.initial = true;
    if (module_item.operands().size() != 1) {
        throw "initial module item expected to have one operand";
    }
    // Implement initial block by pushing statements inside initial block
    // in initial_block as follows and then the call
    // verilog_expression2c(initial_block, ns) will translate initial_block
    initial_block.operands().push_back(translate_statement(module_item.statement()));
    return codet();
}

/*******************************************************************\

Function: verilog_exprt::convert_continuous_assign

Inputs: ex-1 {assign out = In_A & In_B;} ex-2 {c=b;b=a;d=c;}

Outputs: ex-1 {out = In_A & In_B} ex-2 {c=a;b=a;d=a;}

Purpose:

\*******************************************************************/

codet verilog_exprt::convert_continuous_assign(
        const verilog_continuous_assignt &module_item) {
    module_infot &modulevb = module_info[current_module];
    code_assignt code_assignv;
    forall_operands(it, module_item) {
            if (it->id() != ID_equal || it->operands().size() != 2) {
                error() << "unexpected continuous assignment" << eom;
                throw 0;
            }
            exprt lhs = it->op0();
            exprt rhs = it->op1();

            // handle extractbit
            if (lhs.id() == ID_extractbit || rhs.id() == ID_extractbit) {
                // Processing of statements like assign out = tmp[5];
                if (rhs.id() == ID_extractbit && lhs.id() != ID_extractbit) {
                    if (rhs.operands().size() != 2)
                        throw "extractbit takes two operands";
//                    symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
//                    mp_integer size_op1;
//                    to_integer(rhs.op1(), size_op1);
//                    ashr_exprt shr(rhs_symbol, rhs.op1());
//                    constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                    bitand_exprt andexpr(shr, constant1);
//                    rhs = andexpr;
                    unsigned char saved_diff = 0;
                    convert_expr(rhs, saved_diff);
                }
                // Processing of statements like assign out[5] = tmp;我认为是out=out&(2^width_of_out-1-2^5)|tmp<<5
                if (lhs.id() == ID_extractbit && rhs.id() != ID_extractbit) {//好像不太对 in1 = in1 | smain.x << 5;
                    if (lhs.operands().size() != 2)
                        throw "extractbits takes two operands";
                    symbol_exprt lhs_symbol = to_symbol_expr(lhs.op0());
                    mp_integer size_opl1;
                    to_integer(lhs.op1(), size_opl1);
                    shl_exprt shl(rhs, lhs.op1());
                    //增加4line,删除1line
                    int width = lhs_symbol.find(ID_type).get_int(ID_width);
                    constant_exprt zero = from_integer(power(2, width) - 1 - power(2, size_opl1), integer_typet());
                    bitand_exprt bitand_expr(lhs_symbol, zero);
                    bitor_exprt bitor_expr(bitand_expr, shl);
//                    bitor_exprt bitor_expr(lhs_symbol, shl);
                    rhs = bitor_expr;
                    lhs = lhs_symbol;
                }
                code_assignv.rhs() = rhs;
                code_assignv.lhs() = lhs;
            }

                // Processing of statements like out[a:b] = tmp[c:d];
                // 错误:out = (out & !(2^(width_of_out - 1) - 2^b)) | ((tmp & (2^(width_of_tmp - 1) - 2^d) >> d) << b);
                // 正确:out = (out & ((2^(width_of_out) - 1) - (2^a - 2^b + 2^a))) | (((tmp & (2^c - 2^d + 2^c)) >> d) << b);
            else if (lhs.id() == ID_extractbits && rhs.id() == ID_extractbits) { //修改了处理方式
                if (rhs.operands().size() != 3)
                    throw "extractbits takes three operands";
//                symbol_exprt lhs_symbol = to_symbol_expr(lhs.op0());
//                symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
//
//                // create the first operand of rhs
//                mp_integer size_opl1;
//                to_integer(lhs.op2(), size_opl1);
//                constant_exprt constant0 = from_integer(power(2, size_opl1), integer_typet());
//                mp_integer width = pointer_offset_bits(lhs.type(), ns);
//                assert(width > 0);
//
//                constant_exprt cwidth = from_integer(power(2, width - 1) - power(2, size_opl1), integer_typet());
//                bitnot_exprt notexp(cwidth);
//                bitand_exprt andexp(lhs_symbol, notexp);
//
//
//                // create the second operand of rhs
//                mp_integer size_op1;
//                to_integer(rhs.op1(), size_op1);
//                mp_integer size_op2;
//                to_integer(rhs.op2(), size_op2);
//                constant_exprt constant1 = from_integer(power(2, size_op2), integer_typet());
//                mp_integer widthr = pointer_offset_bits(rhs.type(), ns);
//                assert(widthr > 0);
//
//                constant_exprt cwidthr = from_integer(power(2, widthr - 1) - power(2, size_op2), integer_typet());
//                bitand_exprt andexpr(rhs_symbol, cwidthr);
//                ashr_exprt shrr(andexpr, rhs.op2());size_opl1
//                shl_exprt shlr(shrr, lhs.op2());
//
//
//                bitor_exprt bitor_expr(andexp, shlr);
//                rhs = bitor_expr;
//                lhs = lhs_symbol;
//                code_assignv.rhs() = rhs;
//                code_assignv.lhs() = lhs;
                code_assignv.lhs() = lhs.op0();
                symbol_exprt lhs_symbol = to_symbol_expr(lhs.op0());
                symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
                mp_integer size_a, size_b, size_c, size_d;
                to_integer(lhs.op1(), size_a);
                to_integer(lhs.op2(), size_b);
                to_integer(rhs.op1(), size_c);
                to_integer(rhs.op2(), size_d);
                int width = lhs.op0().find(ID_type).get_int(ID_width);
                constant_exprt lhs_constant = from_integer(
                        (power(2, width) - 1) - (power(2, size_a) - power(2, size_b) + power(2, size_a)),
                        integer_typet());
                bitand_exprt lhs_andexpr(lhs_symbol, lhs_constant);
                constant_exprt rhs_constant = from_integer(power(2, size_c) - power(2, size_d) + power(2, size_c),
                                                           integer_typet());
                bitand_exprt rhs_andexpr(rhs_symbol, rhs_constant);
                ashr_exprt shr(rhs_andexpr, rhs.op2());
                shl_exprt shl(shr, lhs.op2());
                bitor_exprt orexpr(lhs_andexpr, shl);
                rhs = orexpr;
                code_assignv.rhs() = rhs;
            }

                // Processing of statement like out[i] = tmp[k];
                // out = (out & ((2^(width_of_out)-1) - 2^i)) | (((tmp & 2^k) >> k) << i)
            else if (lhs.id() == ID_extractbit && rhs.id() == ID_extractbit) { //增加else
                if (lhs.operands().size() != 2)
                    throw "extractbit takes two operands";
                symbol_exprt lhs_symbol = to_symbol_expr(lhs.op0());
                symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());

                // create the first operand of rhs
                mp_integer size_opl1;
                to_integer(lhs.op1(), size_opl1);
                constant_exprt constant0 = from_integer(power(2, size_opl1), integer_typet());
                mp_integer width = pointer_offset_bits(lhs.type(), ns);
                assert(width > 0);

                constant_exprt cwidth = from_integer((power(2, width) - 1), integer_typet());
                mp_integer size;
                to_integer(cwidth, size);
                constant_exprt cwidthl = from_integer(size - power(2, size_opl1), integer_typet());
                bitand_exprt andexp(lhs_symbol, cwidthl);


                // create the second operand of rhs
                mp_integer size_opr1;
                to_integer(rhs.op1(), size_opr1);
                constant_exprt constant1 = from_integer(power(2, size_opr1), integer_typet());
                bitand_exprt andexpr(rhs_symbol, constant1);
                ashr_exprt ashr(andexpr, rhs.op1());
                shl_exprt shl(ashr, lhs.op1());

                bitor_exprt bitor_expr(andexp, shl);
                rhs = bitor_expr;
                lhs = lhs_symbol;
                code_assignv.rhs() = rhs;
                code_assignv.lhs() = lhs;
            }

                // ******** handle extractbits on one side *******
                // assign tr[4:2] = x;
                // assign x = out[7:5];
            else if (lhs.id() == ID_extractbits || rhs.id() == ID_extractbits) {
                if (rhs.id() == ID_extractbits && lhs.id() != ID_extractbits) {
                    if (rhs.operands().size() != 3)
                        throw "extractbits takes three operands";
//                    symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
//                    mp_integer size_op1;
//                    to_integer(rhs.op1(), size_op1);
//                    mp_integer size_op2;
//                    to_integer(rhs.op2(), size_op2);
//                    unsigned diff = integer2unsigned(size_op1 - size_op2);
//                    ashr_exprt shr(rhs_symbol, rhs.op2());
//                    constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//                    bitand_exprt andexpr(shr, constant1);
//                    rhs = andexpr;
                    unsigned char saved_diff = 0;
                    convert_expr(rhs, saved_diff);
                }
                if (lhs.id() == ID_extractbits && rhs.id() != ID_extractbits) {
                    if (lhs.operands().size() != 3)
                        throw "extractbits takes three operands";
                    symbol_exprt lhs_symbol = to_symbol_expr(lhs.op0());

                    // create the first operand of rhs
                    mp_integer size_opl1;
                    to_integer(lhs.op2(), size_opl1);
                    constant_exprt constant0 = from_integer(power(2, size_opl1), integer_typet());
                    mp_integer width = pointer_offset_bits(lhs.type(), ns);
                    assert(width > 0);

                    constant_exprt cwidth = from_integer(power(2, width - 1) - power(2, size_opl1), integer_typet());
                    bitnot_exprt notexp(cwidth);
                    bitand_exprt andexp(lhs_symbol, notexp);

                    // create the second operand of rhs
                    mp_integer size_opl0;
                    to_integer(lhs.op1(), size_opl0);
                    unsigned diff = integer2unsigned(size_opl1 - size_opl0);//修改正负号出错
                    constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
                    bitand_exprt andexpr(rhs.op0(), constant1);
                    shl_exprt shl1(andexpr, lhs.op2());

                    bitor_exprt bitor_expr(andexp, shl1);
                    rhs = bitor_expr;
                    lhs = lhs_symbol;
                }
                code_assignv.lhs() = lhs;
                code_assignv.rhs() = rhs;
            }
                // continuous assignment of type: "assign test = (reg1[11:8]==out[7:4]) && (reg1[12:9]==out[8:5]);"
//            else if (rhs.id() == ID_and || rhs.id() == ID_or) {
//                if (rhs.op0().id() == ID_equal) {
//                    // it can be extractbits
//                    if (rhs.op0().op1().id() == ID_extractbits) {
//                        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0().op1().op0());
//                        mp_integer size_op1;
//                        to_integer(rhs.op0().op1().op1(), size_op1);
//                        mp_integer size_op2;
//                        to_integer(rhs.op0().op1().op2(), size_op2);
//                        unsigned diff = integer2unsigned(size_op1 - size_op2);
//                        ashr_exprt shr(rhs_symbol, rhs.op0().op1().op2());
//                        constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//                        bitand_exprt andexpr(shr, constant1);
//                        rhs.op0().op1() = andexpr;
//                    }
//                    if (rhs.op0().op0().id() == ID_extractbits) {
//                        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0().op0().op0());
//                        mp_integer size_op1;
//                        to_integer(rhs.op0().op0().op1(), size_op1);
//                        mp_integer size_op2;
//                        to_integer(rhs.op0().op0().op2(), size_op2);
//                        unsigned diff = integer2unsigned(size_op1 - size_op2);
//                        ashr_exprt shr(rhs_symbol, rhs.op0().op0().op2());
//                        constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//                        bitand_exprt andexpr(shr, constant1);
//                        rhs.op0().op0() = andexpr;
//                    }
//                    // continuous assignment of type: "assign test = (reg1[11:8]==out[7:4]) && (reg1[12]==out[8]);"
//                    // it can be extractbit
//                    if (rhs.op0().op1().id() == ID_extractbit) {
//                        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0().op1().op0());
//                        mp_integer size_op1;
//                        to_integer(rhs.op0().op1().op1(), size_op1);
//                        ashr_exprt shr(rhs_symbol, rhs.op0().op1().op1());
//                        constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                        bitand_exprt andexpr(shr, constant1);
//                        rhs.op0().op1() = andexpr;
//                    }
//                    if (rhs.op0().op0().id() == ID_extractbit) {
//                        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0().op0().op0());
//                        mp_integer size_op1;
//                        to_integer(rhs.op0().op0().op1(), size_op1);
//                        ashr_exprt shr(rhs_symbol, rhs.op0().op0().op1());
//                        constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                        bitand_exprt andexpr(shr, constant1);
//                        rhs.op0().op0() = andexpr;
//                    }
//                }
//                if (rhs.op1().id() == ID_equal) {
//                    if (rhs.op1().op0().id() == ID_extractbits) {
//                        symbol_exprt lhs_symbol = to_symbol_expr(rhs.op1().op0().op0());
//                        mp_integer size_opl1;
//                        to_integer(rhs.op1().op0().op1(), size_opl1);
//                        mp_integer size_opl2;
//                        to_integer(rhs.op1().op0().op2(), size_opl2);
//                        unsigned diff = integer2unsigned(size_opl1 - size_opl2);
//                        ashr_exprt shr(lhs_symbol, rhs.op1().op0().op2());
//                        constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//                        bitand_exprt andexpr(shr, constant1);
//                        rhs.op1().op0() = andexpr;
//                    }
//                    if (rhs.op1().op1().id() == ID_extractbits) {
//                        symbol_exprt lhs_symbol = to_symbol_expr(rhs.op1().op1().op0());
//                        mp_integer size_opl1;
//                        to_integer(rhs.op1().op1().op1(), size_opl1);
//                        mp_integer size_opl2;
//                        to_integer(rhs.op1().op1().op2(), size_opl2);
//                        unsigned diff = integer2unsigned(size_opl1 - size_opl2);
//                        ashr_exprt shr(lhs_symbol, rhs.op1().op1().op2());
//                        constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//                        bitand_exprt andexpr(shr, constant1);
//                        rhs.op1().op1() = andexpr;
//                    }
//                    // it can be extractbit
//                    // continuous assignment of type: "assign test = (reg1[11:8]==out[7:4]) && (reg1[9]==out[5]);"
//                    if (rhs.op1().op1().id() == ID_extractbit) {
//                        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op1().op1().op0());
//                        mp_integer size_op1;
//                        to_integer(rhs.op1().op1().op1(), size_op1);
//                        ashr_exprt shr(rhs_symbol, rhs.op1().op1().op1());
//                        constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                        bitand_exprt andexpr(shr, constant1);
//                        rhs.op1().op1() = andexpr;
//                    }
//                    if (rhs.op1().op0().id() == ID_extractbit) {
//                        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op1().op0().op0());
//                        mp_integer size_op1;
//                        to_integer(rhs.op1().op0().op1(), size_op1);
//                        ashr_exprt shr(rhs_symbol, rhs.op1().op0().op1());
//                        constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                        bitand_exprt andexpr(shr, constant1);
//                        rhs.op1().op0() = andexpr;
//                    }
//                }
//                code_assignv.lhs() = lhs;
//                code_assignv.rhs() = rhs;
//            }
//                // continuous assignment of type: "assign test = (reg1[11:8]==out[7:4]);"
//            else if (rhs.id() == ID_equal) {
//                if (rhs.op1().id() == ID_extractbits) {
//                    symbol_exprt rhs_symbol = to_symbol_expr(rhs.op1().op0());
//                    mp_integer size_op1;
//                    to_integer(rhs.op1().op1(), size_op1);
//                    mp_integer size_op2;
//                    to_integer(rhs.op1().op2(), size_op2);
//                    unsigned diff = integer2unsigned(size_op1 - size_op2);
//                    ashr_exprt shr(rhs_symbol, rhs.op1().op2());
//                    constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//                    bitand_exprt andexpr(shr, constant1);
//                    rhs.op1() = andexpr;
//                }
//                if (rhs.op0().id() == ID_extractbits) {
//                    symbol_exprt lhs_symbol = to_symbol_expr(rhs.op0().op0());
//                    mp_integer size_opl1;
//                    to_integer(rhs.op0().op1(), size_opl1);
//                    mp_integer size_opl2;
//                    to_integer(rhs.op0().op2(), size_opl2);
//                    unsigned diff = integer2unsigned(size_opl1 - size_opl2);
//                    ashr_exprt shr(lhs_symbol, rhs.op0().op2());
//                    constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//                    bitand_exprt andexpr(shr, constant1);
//                    rhs.op0() = andexpr;
//                }
//                // continuous assignment of type: "assign test = (reg1[9]==out[5]);"
//                if (rhs.op1().id() == ID_extractbit) {
//                    symbol_exprt rhs_symbol = to_symbol_expr(rhs.op1().op0());
//                    mp_integer size_op1;
//                    to_integer(rhs.op1().op1(), size_op1);
//                    ashr_exprt shr(rhs_symbol, rhs.op1().op1());
//                    constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                    bitand_exprt andexpr(shr, constant1);
//                    rhs.op1() = andexpr;
//                }
//                if (rhs.op0().id() == ID_extractbit) {
//                    symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0().op0());
//                    mp_integer size_op1;
//                    to_integer(rhs.op0().op1(), size_op1);
//                    ashr_exprt shr(rhs_symbol, rhs.op0().op1());
//                    constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                    bitand_exprt andexpr(shr, constant1);
//                    rhs.op0() = andexpr;
//                }
//                code_assignv.lhs() = lhs;
//                code_assignv.rhs() = rhs;
//            }
//                // Handle statement assign "data_out = fifo[out[3:0]];"
//            else if (rhs.id() == ID_index) {
//                symbol_exprt main_symbol = to_symbol_expr(rhs.op0());
//                if (rhs.op1().id() == ID_extractbits) {
//                    symbol_exprt rhs_symbol = to_symbol_expr(rhs.op1().op0());
//                    mp_integer size_opl1;
//                    to_integer(rhs.op1().op1(), size_opl1);
//                    mp_integer size_opl2;
//                    to_integer(rhs.op1().op2(), size_opl2);
//                    unsigned diff = integer2unsigned(size_opl1 - size_opl2);
//                    ashr_exprt shr(rhs_symbol, rhs.op1().op2());
//                    constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//                    bitand_exprt andexpr(shr, constant1);
//                    rhs.op1() = andexpr;
//                }
//                code_assignv.rhs() = rhs;
//                code_assignv.lhs() = lhs;
//            }
//                // Handle statement assign "fifo[out[3:0]] = data_out;"
//            else if (lhs.id() == ID_index) {
//                symbol_exprt main_symbol = to_symbol_expr(lhs.op0());
//                if (lhs.op1().id() == ID_extractbits) {
//                    symbol_exprt rhs_symbol = to_symbol_expr(lhs.op1().op0());
//                    mp_integer size_opl1;
//                    to_integer(lhs.op1().op1(), size_opl1);
//                    mp_integer size_opl2;
//                    to_integer(lhs.op1().op2(), size_opl2);
//                    unsigned diff = integer2unsigned(size_opl1 - size_opl2);
//                    ashr_exprt shr(rhs_symbol, lhs.op1().op2());
//                    constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//                    bitand_exprt andexpr(shr, constant1);
//                    lhs.op1() = andexpr;
//                }
//                code_assignv.rhs() = rhs;
//                code_assignv.lhs() = lhs;
//            }
//                // concatenation assignment: assign x = {y[2:3], z, w[0] };
//            else if (rhs.id() == ID_concatenation) {
//                exprt concat_expr = rhs;
//                if (concat_expr.id() == ID_concatenation) {
//                    if (concat_expr.operands().size() == 0) {
//                        throw "concatenation expected to have at least one operand";
//                        throw 0;
//                    }
//                    bitor_exprt final_bitor;
//                    unsigned saved_diff = 0;
//                    unsigned int diff = 0;
//                    exprt::operandst expr_concat;
//
//                    // Iterate over inverted direction to get the saved_diff properly !!
//                    // Forall_operands(it, concat_expr)
//                    for (exprt::operandst::const_reverse_iterator
//                                 it = concat_expr.operands().rbegin();
//                         it != concat_expr.operands().rend();
//                         it++) {
//                        if (it->id() == ID_extractbits) {
//                            exprt rhs = it->op0();
//                            if (it->operands().size() != 3)
//                                throw "extractbits takes three operands";
//                            symbol_exprt rhs_symbol = to_symbol_expr(rhs);
//                            mp_integer size_op1;
//                            to_integer(it->op1(), size_op1);
//                            mp_integer size_op2;
//                            to_integer(it->op2(), size_op2);
//                            diff = integer2unsigned(size_op1 - size_op2);
//                            ashr_exprt shr(rhs_symbol, it->op2());
//                            constant_exprt constant = from_integer(power(2, diff + 1) - 1, integer_typet());
//                            bitand_exprt andexpr(shr, constant);
//                            shl_exprt shl(andexpr, saved_diff);
//                            saved_diff = saved_diff + (diff + 1);
//                            expr_concat.push_back(shl);
//                        } else if (it->id() == ID_extractbit) {
//                            exprt rhs = it->op0();
//                            if (it->operands().size() != 2)
//                                throw "extractbit takes two operands";
//                            symbol_exprt rhs_symbol = to_symbol_expr(rhs);
//                            mp_integer size_op1;
//                            to_integer(it->op1(), size_op1);
//                            ashr_exprt shr(rhs_symbol, it->op1());
//                            diff = integer2unsigned(size_op1);
//
//                            constant_exprt constant = from_integer(power(2, 1) - 1, integer_typet());
//                            bitand_exprt andexpr(shr, constant);
//                            shl_exprt shl(andexpr, saved_diff);
//                            saved_diff = saved_diff + (diff + 1);
//                            expr_concat.push_back(shl);
//                        }
//                            // normal register assignment, handle constants
//                        else { //if (it->id() == ID_symbol || it->id() == ID_constant) {
//                            exprt rhs = *it;
//                            shl_exprt shlsym(rhs, saved_diff);
//                            // find the size of the symbol
//                            mp_integer width = pointer_offset_bits(rhs.type(), ns);
//                            assert(width > 0);
//                            if (width > 1) {
//                                constant_exprt constant = from_integer(power(2, width) - 1, integer_typet());
//                                bitand_exprt andexpr(shlsym, constant);
//                                expr_concat.push_back(andexpr);
//                            } else
//                                expr_concat.push_back(shlsym);
//                            saved_diff = saved_diff + integer2unsigned(width);
//                        }
//                    } // end for
//                    // do a disjunction over all expressions stored in expr_concat
//                    bitor_exprt bitwise_or;
//                    std::swap(bitwise_or.operands(), expr_concat);
//                    // finally do the assignment
//                    code_assignv.rhs() = bitwise_or;
//                    code_assignv.lhs() = lhs;
//                } // end of concatenation handling
//            }
                // normal continuous assignments
                // need to handle special case like assign "x = {y,z} + t;"
                // handle the normal case of ID_constant and ID_symbol
            else {
                exprt rhsexp = rhs;
                if (rhs.id() == ID_typecast && rhs.type().id() == ID_integer) {
                    exprt rhsexp = rhs.op0();
                }

                exprt cexpr;
                exprt::operandst expressions;
                exprt rhs_op;
//                Forall_operands(it, rhsexp) {
//                        unsigned char saved_diff = 0;
//                        rhs_op = convert_expr(*it, saved_diff);
//                        expressions.push_back(rhs_op);
//                    }
//                cexpr = rhsexp; //todo 这里还没有转换
//                unsigned width = lhs.type().id() == ID_integer ? 32 : 1;
//                if (width > 1) {
//                    bitand_exprt band(cexpr,
//                                      from_integer(power(2, width) - 1, rhs.type()));
//                    code_assignv.rhs() = band;
//                } else {
//                    code_assignv.rhs() = cexpr;
//                }
                unsigned char saved_diff = 0;
                code_assignv.rhs() = convert_expr(rhsexp, saved_diff);
                code_assignv.lhs() = lhs;
            }// end of normal case
        } // end for


    // replace all register-type variables by member accesses (RHS only)  ???
    bool noreg = modulevb.registers.replace(code_assignv.rhs());

    // add dereferencing to all (remaining) output variables (RHS only)
    modulevb.output_var(code_assignv.rhs()); //()重载为replace()
    // create backup copies
    // NEW: code_orig
    code_assignt code_reg = code_assignv, code_orig = code_assignv;
    // apply same adjustments as above for RHS to LHS
    modulevb.registers(code_assignv.lhs());
    modulevb.output_var(code_assignv.lhs());
    // try replacements to see whether the LHS is a register-type
    // output variable, in which case both the register struct and the
    // output variable need to be assigned to
    modulevb.output_var(code_reg.lhs());

    if (noreg)
        modulevb.cassign.push_back(code_assignv);
    else
        modulevb.cassignReg.push_back(code_assignv);

    modulevb.cassignAll.push_back(code_assignv);

    return codet();
}

/*******************************************************************\

Function: verilog_exprt::convert_inst

Inputs: "dff inst_1 (.d(data), .q(net_1), .clk(clock));"

Outputs: dff(data,net_1,clock);

Purpose: module_instance declared inside a module

\*******************************************************************/

codet verilog_exprt::convert_inst(
        const verilog_instt &statement) {
    const module_infot &modulevb = module_info[current_module];

    code_function_callt code_function_callv;
    const irep_idt &identifier = statement.get(ID_module);
    code_function_callv.function() = symbol_exprt(identifier);
    const module_infot &modulev = module_info[identifier];
    unsigned int i = 0;
    for (std::list<symbol_exprt>::const_iterator it2 = modulev.parameters.begin();
         it2 != modulev.parameters.end(); ++it2, ++i) {
        exprt arg = statement.op0().operands()[i];
        if (arg.id() == ID_named_port_connection) {
            exprt tmp = *it2;
            if (it2->type().id() == ID_pointer)
                tmp.type() = tmp.type().subtype();
            forall_operands(it, statement.op0()) if (it->id() == ID_named_port_connection && it->op0() == tmp) {
                        arg = it->op1();
                        break;
                    }
        }
        if (it2->type().id() == ID_pointer)
            arg = address_of_exprt(arg);
        modulevb.registers(arg);
        code_function_callv.arguments().push_back(arg);
    }

    return code_function_callv;
}

/*******************************************************************\

Function: verilog_exprt::convert_always

Inputs: always @(posedge clk)
if(reset) begin
q <= 0;
end
else if (enable) begin
q <= d;
end
endmodule


Outputs: { if(reset) ...... else if(enable) .... }

Purpose:

\*******************************************************************/

codet verilog_exprt::convert_always(
        const verilog_alwayst &module_item) {
    if (module_item.operands().size() != 1) {
        throw "always module item expected to have one operand";
    }
    //modulevb.counter++;
    return translate_statement(module_item.statement());
}

/*******************************************************************\

Function: verilog_exprt::convert_assert

Inputs:

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::convert_assert(const verilog_assertt &module_item) {
    module_infot &modulevb = module_info[current_module];
    code_assertt code_assertv;
    if (module_item.operands().size() != 2) {
        throw "assert module item expected to have two operands";
    }
    const irep_idt &identifier = module_item.get(ID_identifier);
    const symbolt &symbol = ns.lookup(identifier);

    // translate all register elements in the assertion with struct elements
    exprt condition = symbol.value.op0();
//    增加按位与和转换为寄存器变量放在后面
//    add_bitand(condition);
//    modulevb.registers(condition);

    //将assert中表达式转换为对应位操作
//    std::stack<exprt *> condition_stack;
//    condition_stack.push(&condition);
//    while (!condition_stack.empty()) {
//        exprt *condition_tmp = condition_stack.top();
//        condition_stack.pop();
//        while (condition_tmp->id() == ID_typecast)
//            condition_tmp->op0();
//        if (condition_tmp->id() == ID_overlapped_implication || condition_tmp->id() == ID_and ||
//            condition_tmp->id() == ID_nand || condition_tmp->id() == ID_or ||
//            condition_tmp->id() == ID_nor || condition_tmp->id() == ID_xor || condition_tmp->id() == ID_xnor) {
//            condition_stack.push(&condition_tmp->op1());
//            condition_stack.push(&condition_tmp->op0());
//        } else if (condition_tmp->id() == ID_not) {
//            condition_stack.push(&condition.op0());
//        } else if (condition_tmp->id() == ID_equal) {
//            exprt lhs = condition_tmp->op0();
//            while (lhs.id() == ID_typecast)
//                lhs = lhs.op0();
//            unsigned char saved_diff = 0;
//            lhs = convert_expr(lhs, saved_diff);
//            condition_tmp->op0() = lhs;
//            saved_diff = 0;
//            condition_tmp->op1() = convert_expr(condition.op1(), saved_diff);
//        } else {
//            unsigned char saved_diff = 0;
//            *condition_tmp = convert_expr(*condition_tmp, saved_diff);
//        }
//    }
    if (condition.id() == ID_overlapped_implication) {
        unsigned char saved_diff = 0;
        convert_expr(condition.op0(), saved_diff);
        saved_diff = 0;
        convert_expr(condition.op1(), saved_diff);
    } else {
        unsigned char saved_diff = 0;
        convert_expr(condition, saved_diff);
    }
    modulevb.registers(condition);
    code_assertv.copy_to_operands(condition);
//    code_assertv.copy_to_operands(symbol.value.op0());
    return code_assertv;
}


/*******************************************************************\

Function: verilog_exprt::convert_task

Inputs:

Outputs:

Purpose:

\*******************************************************************/

void verilog_exprt::convert_task(const verilog_module_itemt &module_item, std::ostream &out) {
    const exprt &body = static_cast<const exprt &>(module_item.find(ID_body));
    code_blockt code_funct = to_code_block(translate_block(to_verilog_block(body)));

    const symbol_exprt &fn_symbol = static_cast<const symbol_exprt &>(module_item.find(ID_symbol));
    const symbol_exprt &fn_output = static_cast<const symbol_exprt &>(module_item.find(ID_output));
    const symbolt &fn_name = ns.lookup(fn_symbol.get_identifier());

    code_typet typev;
    typev = to_code_type(fn_name.type);
    typev.return_type() = unsignedbv_typet(8);

    code_declt fn_decl(fn_symbol);
    fn_decl.symbol().type() = typev;

    std::string output_fn = verilog_expression2c(fn_decl, ns);
    output_fn = output_fn.substr(0, output_fn.size() - 1);
    out << output_fn << std::endl;
    std::string name_fn = id2string(fn_output.get_identifier());
    name_fn += "." + id2string(fn_name.base_name);
    symbol_exprt sym(name_fn, unsignedbv_typet(8));

    code_funct.add(code_returnt(sym));
    // convert function code here
    out << verilog_expression2c(code_funct, ns) << std::endl;
}

/*******************************************************************\

Function: verilog_exprt::convert_function

Inputs:

Outputs:

Purpose:

\*******************************************************************/

void verilog_exprt::convert_function(const verilog_module_itemt &module_item, std::ostream &out) {
    const exprt &body = static_cast<const exprt &>(module_item.find(ID_body));
    code_blockt code_funct = to_code_block(translate_block(to_verilog_block(body))); //转换函数

    const symbol_exprt &fn_symbol = static_cast<const symbol_exprt &>(module_item.find(ID_symbol));

    const symbolt &fn_name = ns.lookup(fn_symbol.get_identifier());

    code_typet typev;
    typev = to_code_type(fn_name.type);
    //我已经在前端赋值好了返回值变量,没必要强制变成8bit位向量
//    typev.return_type() = unsignedbv_typet(8);

    code_declt fn_decl(fn_symbol);
    fn_decl.symbol().type() = typev;

    std::string output_fn = verilog_expression2c(fn_decl, ns);
    output_fn = output_fn.substr(0, output_fn.size() - 1);
    out << output_fn << std::endl;
    //增加函数内局部变量定义
    const exprt &declarations = static_cast<const exprt &>(module_item.find(dstring("declarations")));
    bool has_local_var = false;
    forall_operands (it, declarations) {
            if (it->get(ID_class) == ID_reg) {
                exprt local_var = *it;
                std::string local_sym = local_var.op0().get_string(ID_identifier);
                int big = local_var.find(ID_type).find(ID_range).get_sub()[0].get_int(ID_value);
                int low = local_var.find(ID_type).find(ID_range).get_sub()[1].get_int(ID_value);
                int width = big - low + 1;
                if (!has_local_var) {
                    out << "{" << std::endl;
                    has_local_var = true;
                }
                if (width <= 8) {
                    out << "  unsigned char " + local_sym << ";\n";
                } else if (width <= 16) {
                    out << "  unsigned short " + local_sym << ";\n";
                } else if (width <= 32) {
                    out << "  unsigned int " + local_sym << ";\n";
                } else if (width <= 64) {
                    out << "  unsigned long long int " + local_sym << ";\n";
                } else {
                    out << "  unsigned __int128" + local_sym << ";\n";
                }
            }
        }
    std::string name_fn = id2string(fn_symbol.get_identifier());
    name_fn += "." + id2string(fn_name.base_name);
    symbol_exprt sym(name_fn, typev.return_type());
    code_declt d(sym);

    code_funct.operands().insert(code_funct.operands().begin(), d);
    code_funct.add(code_returnt(sym));
    if (has_local_var)
        out << verilog_expression2c(code_funct, ns).substr(2) << std::endl << std::endl;
    else out << verilog_expression2c(code_funct, ns) << std::endl << std::endl;
}

/*******************************************************************\

Function: verilog_exprtt::translate_statement

Inputs:

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_statement(
        const verilog_statementt &statement, bool need_cassign) {
    if (statement.id() == ID_block)
        return translate_block(to_verilog_block(statement), need_cassign);

    else if (statement.id() == ID_case ||
             statement.id() == ID_casex ||
             statement.id() == ID_casez)
        return translate_case(statement, need_cassign);
    else if (statement.id() == ID_blocking_assign)
        return translate_block_assign(statement, need_cassign);

    else if (statement.id() == ID_continuous_assign)
        throw "synthesis of procedural continuous assignment not supported";

    else if (statement.id() == ID_assert)
        return translate_assert(to_verilog_assert(statement));

    else if (statement.id() == ID_assume)
        return translate_assume(to_verilog_assume(statement));

    else if (statement.id() == ID_non_blocking_assign)
        return translate_nb_assign(statement, need_cassign);

    else if (statement.id() == ID_if)
        return translate_if(to_verilog_if(statement), need_cassign);

    else if (statement.id() == ID_event_guard)
        return translate_event_guard(to_verilog_event_guard(statement));

    else if (statement.id() == ID_delay)
        return translate_delay(to_verilog_delay(statement));

    else if (statement.id() == ID_for)
        return translate_for(to_verilog_for(statement));

    else if (statement.id() == ID_while)
        return translate_while(to_verilog_while(statement));

    else if (statement.id() == ID_repeat)
        return translate_repeat(to_verilog_repeat(statement));

    else if (statement.id() == ID_forever)
        return translate_forever(to_verilog_forever(statement));

    else if (statement.id() == ID_skip)
        return codet();

    else {
        error() << "unexpected statement during translation: " << eom;
        throw 0;
    }
}

/*******************************************************************\

Function: verilog_exprt::translate_block

Inputs:

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_block(const verilog_blockt &statement, bool need_cassign) {
    code_blockt verilog_block1;
    forall_operands(it, statement) {
//            if (it->id() != ID_skip) //忽略skip语句,或者后面covert忽略也行
//                continue;
            bool is_blocking_assign = false;
            if (static_cast<const verilog_statementt &>(*it).id() == ID_blocking_assign && need_cassign)
                is_blocking_assign = true;
            codet save_block = translate_statement(static_cast<const verilog_statementt &>(*it), need_cassign);
            //去除连续赋值引入的大括号
            if (is_blocking_assign) {
                forall_operands(it, save_block) {
                        verilog_block1.operands().push_back(*it);
                    }
            } else {
                verilog_block1.operands().push_back(save_block);
            }
        }

    return
            verilog_block1;
}

/*******************************************************************\

Function: verilog_exprt::translate_if

Inputs:

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_if(
        const verilog_ift &statement, bool need_cassign) {

    module_infot &modulevb = module_info[current_module];
    code_ifthenelset codeif;
    if (statement.operands().size() != 2 &&
        statement.operands().size() != 3) {
        throw "if statement expected to have two or three operands";
    }

    // Build the AST of the if() expression and feed it to expr2c framework
    // Now consider the two cases of if statement (true case and false case)
    // Handle the case when if(|t[10:9])
    // ***************
    exprt expr_cond_typecast = statement.condition();
    exprt expr_cond = statement.condition();
//    // handling extractbits
//    if (expr_cond_typecast.id() == ID_typecast)
//        expr_cond = expr_cond_typecast.op0();
//    if (expr_cond.id() == ID_extractbits) {
//        if (expr_cond.operands().size() != 3)
//            throw "extractbits takes three operands";
//        symbol_exprt rhs_symbol = to_symbol_expr(expr_cond.op0());
//        mp_integer size_op1;
//        to_integer(expr_cond.op1(), size_op1);
//        mp_integer size_op2;
//        to_integer(expr_cond.op2(), size_op2);
//        unsigned diff = integer2unsigned(size_op1 - size_op2);
//        ashr_exprt shr(rhs_symbol, expr_cond.op2());
//        constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//        bitand_exprt andexpr(shr, constant1);
//        expr_cond = andexpr;
//        codeif.cond() = expr_cond;
//    }
//    if (expr_cond.id() == ID_extractbit) {
//        if (expr_cond.operands().size() != 2)
//            throw "extractbit takes two operands";
//        symbol_exprt expr_symbol = to_symbol_expr(expr_cond.op0());
//        mp_integer size_op1;
//        to_integer(expr_cond.op1(), size_op1);
//        ashr_exprt shr(expr_symbol, expr_cond.op1());
//        constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//        bitand_exprt andexpr(shr, constant1);
//        expr_cond = andexpr;
//        codeif.cond() = expr_cond;
//    }
//        // handling reduction operator
//    else if (expr_cond.id() == ID_reduction_or || expr_cond.id() == ID_reduction_and ||
//             expr_cond.id() == ID_reduction_nor || expr_cond.id() == ID_reduction_nand ||
//             expr_cond.id() == ID_reduction_xor || expr_cond.id() == ID_reduction_xnor) {
//        exprt new_expr = expr_cond.op0();
//        if (expr_cond.id() == ID_reduction_or) {
//            if (new_expr.id() == ID_extractbit) {
//                if (new_expr.operands().size() != 2)
//                    throw "extractbit takes two operands";
//                symbol_exprt expr_symbol = to_symbol_expr(new_expr.op0());
//                mp_integer size_op1;
//                to_integer(new_expr.op1(), size_op1);
//                ashr_exprt shr(expr_symbol, new_expr.op1());
//                constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                bitand_exprt andexpr(shr, constant1);
//                new_expr = andexpr;
//                codeif.cond() = new_expr;
//            } else if (new_expr.id() == ID_extractbits) {
//                if (new_expr.operands().size() != 3)
//                    throw "extractbit takes two operands";
//                symbol_exprt expr_symbol = to_symbol_expr(new_expr.op0());
//                mp_integer size_op1;
//                to_integer(new_expr.op1(), size_op1);
//                ashr_exprt shr1(expr_symbol, new_expr.op1());
//                constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                bitand_exprt and1(shr1, constant1);
//                mp_integer size_op2;
//                to_integer(new_expr.op2(), size_op2);
//                ashr_exprt shr2(expr_symbol, new_expr.op2());
//                constant_exprt constant2 = from_integer(power(2, 0), integer_typet());
//                bitand_exprt and2(shr2, constant2);
//                bitor_exprt orexpr(and1, and2);
//                new_expr = orexpr;
//                codeif.cond() = new_expr;
//            }
//        }
//    }
////    else if (expr_cond.id() == ID_and || expr_cond.id() == ID_or ) { //增加if条件的and情况
////        assert(expr_cond.operands().size() == 2);
////        Forall_operands(it, expr_cond) {
////            bool changed = false;
////               exprt converted =  convert_expr(*it, &changed);
////               if (changed) {
////                   *it = converted;
////               }
////        }
////        codeif.cond() = expr_cond;
////    }
//        // save the condition
//    else {
//        //DFS处理if条件中的表达式
////        exprt *expr_ref = &expr_cond;
////        std::stack<exprt *> exp_st;
////        exp_st.push(expr_ref);
////        while (!exp_st.empty()) {
////            exprt *exp_tmp = exp_st.top();
////            exp_st.pop();
////            while (exp_tmp->id() == ID_typecast)
////                exp_tmp = &(exp_tmp->op0());
//
////            if (exp_tmp->id() == ID_and || exp_tmp->id() == ID_nand || exp_tmp->id() == ID_or ||
////                exp_tmp->id() == ID_nor || exp_tmp->id() == ID_xor || exp_tmp->id() == ID_xnor ||
////                exp_tmp->id() == ID_equal || exp_tmp->id() == dstring(358, 0) || exp_tmp->id() == dstring(359, 0) ||
////                exp_tmp->id() == dstring(360, 0)) {
////                exp_st.push(&(exp_tmp->op0()));
////                exp_st.push(&(exp_tmp->op1()));
//        //处理= and nand or nor xor xnor not bitand bitor bitnot bitxor bitnand bitnor notequal >= <= > < + - * /
////            if ((exp_tmp->id().get_no() == 37) || (exp_tmp->id().get_no() >= 40 && exp_tmp->id().get_no() <= 54) ||
////                (exp_tmp->id().get_no() >= 356 && exp_tmp->id().get_no() <= 361) ||
////                (exp_tmp->id().get_no() >= 364 && exp_tmp->id().get_no() <= 365)) {
////                Forall_operands(it, *exp_tmp) {
////                        exp_st.push(&(*it));
////                    }
////            } else if (exp_tmp->id() == ID_extractbit || exp_tmp->id() == ID_extractbits) {
////                unsigned char saved_diff = 0;
////                *exp_tmp = convert_expr(*(exp_tmp), saved_diff);
////            }
////        }
////        codeif.cond() = expr_cond;
//        unsigned char saved_diff = 0;
//        codeif.cond() = convert_expr(expr_cond, saved_diff);
//        codeif.cond() = statement.condition();
//    }
    //if条件转换改为直接调用函数
    unsigned char saved_diff = 0;
    codeif.cond() = convert_expr(expr_cond, saved_diff);

    codet save_thenpair = translate_statement(statement.true_case(), need_cassign);
    codeif.then_case() = save_thenpair;

    modulevb.oldvar(codeif.cond());
    modulevb.registers(codeif.cond());
    codet save_elsepair;
    //codet final_assignment;

    if (statement.operands().size() == 3) {
        save_elsepair = translate_statement(statement.false_case(), need_cassign);
        codeif.else_case() = save_elsepair;
    }

    return codeif;
}

/*******************************************************************\

Function: verilog_exprt::translate_block_assign

Inputs: "a = b"

Outputs:

Purpose: Normal execution like C

\*******************************************************************/

codet verilog_exprt::translate_block_assign(
        const verilog_statementt &statement, bool need_cassign) {
    module_infot &modulevb = module_info[current_module];
    code_blockt code_blockv;

    code_assignt code_block_assignv;
    //code_assignt code_block_assignt;
    if (statement.operands().size() != 2) {
        throw "assign statement expected to have two operands";
    }

    // save all updates to the lhs of blocking assignments that happens in multiple clocked block
    /* always @(posedge clk) begin    // save for first clocked block
	   y=a;                           x_b1 = u1.x;
     end                            y_b1 = u1.y;
     always @(posedge clk) begin    // save for second clocked block
      x=y;                          x_b2 = u1.x;
      z=x;                          y_b2 = u1.y;
     end                            // do for first clock
                                    y_b1 = a;
                                    // do for second clock
                                    x_b2 = y_b2;
                                    u1.x = y_b2;
                                    z_b2 = x_b2;
                                    u1.z = x_b2; */

    // Handle the case of blocking assignment
    code_block_assignv.lhs() = statement.op0();

    exprt lhs = statement.op0();
    exprt rhs = statement.op1();
    // drop all type casts
    while (rhs.id() == ID_typecast)
        rhs = rhs.op0();
    while (lhs.id() == ID_typecast)
        lhs = lhs.op0();

    // Processing of statement like out[i] = tmp[k];
    // out = (out & ((2^(width_of_out)-1) - 2^i)) | (((tmp & 2^k) >> k) << i)
//    if (lhs.id() == ID_extractbit && rhs.id() == ID_extractbit) {
//        if (lhs.operands().size() != 2)
//            throw "extractbit takes two operands";
//        symbol_exprt lhs_symbol = to_symbol_expr(lhs.op0());
//        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
//
//        // create the first operand of rhs
//        mp_integer size_opl1;
//        to_integer(lhs.op1(), size_opl1);
//        constant_exprt constant0 = from_integer(power(2, size_opl1), integer_typet());
//        mp_integer width = pointer_offset_bits(lhs.type(), ns);
//        assert(width > 0);
//        if (width > 1) {
//            constant_exprt cwidth = from_integer(power(2, width) - 1, integer_typet());
//        }
//
//        // create the second operand of rhs
//        mp_integer size_opr1;
//        to_integer(rhs.op1(), size_opr1);
//        constant_exprt constant1 = from_integer(power(2, size_opr1), integer_typet());
//        bitand_exprt andexpr(rhs_symbol, constant1);
//        ashr_exprt ashr(andexpr, rhs.op1());
//        shl_exprt shl(ashr, lhs.op1());
//
//        //bitor_exprt bitor_expr(andexp,shl);
//        bitor_exprt bitor_expr(lhs_symbol, shl);
//        rhs = bitor_expr;
//        lhs = lhs_symbol;
//        code_block_assignv.rhs() = rhs;
//        code_block_assignv.lhs() = lhs;
//    }
    // Processing of statement like out[i] = tmp[k];
    //       out = (out & ((2^(width_of_out)-1) - 2^i)) | (((tmp & 2^k) >> k) << i)
    // 代码为:out = (out & ((2^(width_of_out)-1) - 2^i)) | ((tmp >> k) & 1) << i)
    if (lhs.id() == ID_extractbit) {
        if (lhs.operands().size() != 2)
            throw "extractbit takes two operands";
        symbol_exprt lhs_symbol = to_symbol_expr(lhs.op0());
        unsigned char saved_diff = 0;
        convert_expr(rhs, saved_diff);
        shl_exprt shl(rhs, lhs.op1());

        mp_integer size_opl1;
        to_integer(lhs.op1(), size_opl1);
        constant_exprt constant0 = from_integer(power(2, size_opl1), integer_typet()); //2^i
        mp_integer width = pointer_offset_bits(lhs_symbol.type(), ns);
        assert(width > 0);
        constant_exprt cwidth;
        cwidth = from_integer(power(2, width) - 1, integer_typet()); //2^(width_of_out)-1
        minus_exprt minus_expr(cwidth, constant0);
        bitand_exprt bitand_expr(lhs_symbol, minus_expr);
        bitor_exprt bitor_expr(bitand_expr, shl);
        code_block_assignv.rhs() = bitor_expr;
        code_block_assignv.lhs() = lhs_symbol;
    }
        // Processing of statement like out[i] = tmp;
        // out = (out & ((2^(width_of_out)-1) - 2^i)) | ((tmp & 1)) << i)
//    else if (lhs.id() == ID_extractbit && rhs.id() != ID_extractbit) {
//        if (lhs.operands().size() != 2)
//            throw "extractbit takes two operands";
//        symbol_exprt lhs_symbol = to_symbol_expr(lhs.op0());
//        mp_integer size_opl1;
//        to_integer(lhs.op1(), size_opl1);
//        shl_exprt shl(rhs, lhs.op1());
//
//
//        // create the first operand of rhs (mask with the width of lhs)
//        constant_exprt constantl1 = from_integer(power(2, size_opl1), integer_typet());
//
//
//        bitor_exprt bitor_expr(lhs_symbol, shl);
//        rhs = bitor_expr;
//        lhs = lhs_symbol;
//        code_block_assignv.rhs() = rhs;
//        code_block_assignv.lhs() = lhs;
//    }

        // Processing of statements like out = tmp[5];
        // out = (tmp >> 5)&1;
    else if (lhs.id() != ID_extractbit && rhs.id() == ID_extractbit) {
        // For assignments like x=1, where x is a single bit register
        // the rhs.id() of the statement x=1 is of type ID_extractbit
        // For assignments like x=1'b1, the assignment is normal and consists
        // of a symbol(x) and constant(1).
        if (rhs.operands().size() != 2)
            throw "extractbit takes two operands";
        //不知道怎么解析的函数if块内的concatenation,解析到了extractbit里面
        //因此自己在这里增加一个判断与转换
        if (rhs.op0().id() == ID_concatenation && rhs.op1().id() == ID_constant && rhs.op1().get_int(ID_value) == 0) {
            code_block_assignv.lhs() = lhs;
            unsigned char saved_diff = 0;
            rhs = convert_expr(rhs.op0(), saved_diff);
            code_block_assignv.rhs() = rhs;
        } else {
            code_block_assignv.lhs() = lhs;
            unsigned char saved_diff = 0;
            convert_expr(rhs, saved_diff);
            code_block_assignv.rhs() = rhs;
//            symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
//            mp_integer size_op1;
//            to_integer(rhs.op1(), size_op1);
//            ashr_exprt shr(rhs_symbol, rhs.op1());
//            constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//            bitand_exprt andexpr(shr, constant1);
//            rhs = andexpr;
//            code_block_assignv.rhs() = rhs;
            //增加阻塞赋值语句lhs数组索引位与
//            if (lhs.id() == ID_index && lhs.op0().id() == ID_symbol && lhs.op1().id() == ID_symbol) {
//                exprt expr_array = lhs.op0();
//                exprt expr_index = lhs.op1();
//                if (expr_index.type().id() == ID_unsignedbv) {
//                    int width = expr_index.type().get_int(ID_width);
//                    if (width > 0 && width != 1 && width != 8 && width != 16 && width != 32 && width != 64 &&
//                        width != 128) {
//                        bitand_exprt band(expr_index, from_integer(power(2, width) - 1, integer_typet()));
//                        expr_index = band;
//                        lhs.operands().pop_back();
//                        lhs.operands().push_back(expr_index);
//                        code_block_assignv.lhs() = lhs;
//                    }
//                }
//            }
        }
    }

        // Processing of statements like out = tmp[5:3];
//    else if (lhs.id() != ID_extractbits && rhs.id() == ID_extractbits) {
//        if (rhs.operands().size() != 3)
//            throw "extractbits takes three operands";
//        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
//        mp_integer size_op1;
//        to_integer(rhs.op1(), size_op1);
//        mp_integer size_op2;
//        to_integer(rhs.op2(), size_op2);
//        unsigned diff = integer2unsigned(size_op1 - size_op2);
//        ashr_exprt shr(rhs_symbol, rhs.op2());
//        constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//        bitand_exprt andexpr(shr, constant1);
//        rhs = andexpr;
//        code_block_assignv.rhs() = rhs;
//    }

        // Processing of statements like out[a:b] = tmp[c:d];
        // 正确:out = (out & ((2^(width_of_out) - 1) - (2^a - 2^b + 2^a))) | (((tmp & (2^c - 2^d + 2^c)) >> d) << b);
        //上面论文中的做法复杂了,代码实现改为:
        // out = (out & ((2^(width_of_out) - 1) - (2^a - 2^b + 2^a))) | ((tmp >> d) & 2^(c-d+1) << b);
//    else if (lhs.id() == ID_extractbits && rhs.id() == ID_extractbits) {
//        if (rhs.operands().size() != 3)
//            throw "extractbits takes three operands";
    else if (lhs.id() == ID_extractbits) {
        code_block_assignv.lhs() = lhs.op0();
        symbol_exprt lhs_symbol = to_symbol_expr(lhs.op0());
//        symbol_exprt rhs_symbol = to_symbol_expr(rhs.op0());
        mp_integer size_a, size_b, size_c, size_d;
        to_integer(lhs.op1(), size_a);
        to_integer(lhs.op2(), size_b);
//        to_integer(rhs.op1(), size_c);
//        to_integer(rhs.op2(), size_d);
        int width = lhs.op0().find(ID_type).get_int(ID_width);
        constant_exprt lhs_constant = from_integer(
                (power(2, width) - 1) - (power(2, size_a) - power(2, size_b) + power(2, size_a)),
                integer_typet());
        bitand_exprt lhs_andexpr(lhs_symbol, lhs_constant);
//        constant_exprt rhs_constant = from_integer(power(2, size_c) - power(2, size_d) + power(2, size_c),
//                                                   integer_typet());
//        bitand_exprt rhs_andexpr(rhs_symbol, rhs_constant);
//        ashr_exprt shr(rhs_andexpr, rhs.op2());
//        shl_exprt shl(shr, lhs.op2());
        unsigned char saved_diff = 0;
        rhs = convert_expr(rhs, saved_diff);
        shl_exprt shl(rhs, lhs.op2());
        bitor_exprt orexpr(lhs_andexpr, shl);
//        unsigned diff = integer2unsigned(size_op1 - size_op2);
//        ashr_exprt shr(rhs_symbol, rhs.op2());
//        constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
//        bitand_exprt andexpr(shr, constant1);
//        rhs = andexpr;
        rhs = orexpr;
        code_block_assignv.rhs() = rhs;
    }
//    else if (rhs.id() == ID_concatenation || rhs.id() == ID_xor) {
//        // handle ID_concatenation
//        //转换成调用convert_expr
//        exprt concat_expr = rhs;
//        if (concat_expr.id() == ID_concatenation) {
//            unsigned char saved_diff = 0;
//            code_block_assignv.rhs() = convert_expr(rhs, saved_diff);
//        } // end of concatenation handling
//
//        // handle ID_bitxor
//        exprt::operandst xor_expr;
//        exprt bitxor_expr = rhs;
//        if (bitxor_expr.id() == ID_xor) {
//            if (bitxor_expr.operands().size() == 0) {
//                throw "bit-wise xor expected to have at least one operand";
//                throw 0;
//            }
//            Forall_operands(it, bitxor_expr) {
//                    if (it->id() == ID_xor) {
//                    }
//
//                    if (it->id() == ID_symbol) { //赋值给异或表达式
//                        xor_expr.push_back(*it);
//                    }
//
//                    if (it->id() == ID_extractbit) {
//                        exprt rhs = it->op0();
//                        if (it->operands().size() != 2)
//                            throw "extractbit takes two operands";
//                        symbol_exprt rhs_symbol = to_symbol_expr(rhs);
//                        mp_integer size_op1;
//                        to_integer(it->op1(), size_op1);
//                        ashr_exprt shr(rhs_symbol, it->op1());
//                        constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
//                        bitand_exprt andexpr(shr, constant1);
//                        //rhs = andexpr;
//                        //code_block_assignv.rhs() = andexpr;
//                        xor_expr.push_back(andexpr);
//                    }
//                }
////            exprt conjunction_expr = conjunction(xor_expr);
////            code_block_assignv.rhs() = conjunction_expr;
//            code_block_assignv.rhs() = bitxor_expr; //这里先直接将异或赋值
//        }
//    } // end of ID_concatenation or ID_bitxor
        //增加函数内直接调用函数
    else if (rhs.id() == ID_function_call && rhs.op1().id() == dstring(0, 0) && rhs.op1().has_operands() &&
             rhs.op1().op0().id() == ID_concatenation) { //rhs.op1().op0()是函数的参数
        exprt arg = rhs.op1().op0();
        code_block_assignv.lhs() = lhs;
        unsigned char saved_diff = 0;
        arg = convert_expr(arg, saved_diff);
        rhs.op1().op0() = arg;
        code_block_assignv.rhs() = rhs;
    }
        // handle the case of ID_constant and normal assignments
    else {
//        exprt rhsexp = rhs;
//        if (rhs.id() == ID_typecast && rhs.type().id() == ID_integer) {
//            exprt rhsexp = rhs.op0();
//        }
//
//        exprt cexpr;
//        exprt::operandst expressions;
//        exprt rhs_op;
//        //不改变运算符为conjunction
//        int i = 0;
//        bool flag = 0;
//        Forall_operands(it, rhsexp) {
//                unsigned char saved_diff = 0;
//                rhs_op = convert_expr(*it, saved_diff);
//                rhsexp.operands()[i] = rhs_op;
//                i++;
//            }
//        cexpr = rhsexp;
//        exprt *expr_ref = &cexpr; //DFS给过程赋值单个bv类型与位宽不匹配时加&
//        std::stack<exprt *> exp_st;
//        exp_st.push(expr_ref);
//        while (!exp_st.empty()) {
//            exprt *exp_tmp = exp_st.top();
//            exp_st.pop();
//            while (exp_tmp->id() == ID_typecast)
//                exp_tmp = &(exp_tmp->operands().back());
//            if (exp_tmp->operands().size() == 2) { //二元运算符连接的表达式或数组名+索引
//                exprt *firstexp = &(exp_tmp->operands()[0]), *secondexp = &(exp_tmp->operands()[1]);
//                exp_st.push(firstexp);
//                exp_st.push(secondexp);
//            } else if (exp_tmp->operands().size() == 0) {
//                if (exp_tmp->id() == ID_symbol) {
//                    if (exp_tmp->type().id() == ID_unsignedbv) { //数组索引也符合条件,数组名不符合
//                        int width = exp_tmp->type().get_int(ID_width);
//                        if (width > 0 && width != 1 && width != 8 && width != 16 && width != 32 && width != 64 &&
//                            width != 128) {
//                            bitand_exprt band(*exp_tmp,
//                                              from_integer(power(2, width) - 1, integer_typet()));
//                            *exp_tmp = band;
//                        }
//                    }
//                }
//            }
//        }
//
//        unsigned width = lhs.type().id() == ID_integer ? 32 : 1;
//        if (lhs.type().id() == ID_unsignedbv && rhs.operands().size() > 1) { //过程赋值左值bv类型与位宽不匹配时右边增加&
//            width = lhs.type().get_int(ID_width);
//        }
        //修改过程赋值rhs是否增加&判定
//        if (width > 0 && width != 1 && width != 8 && width != 16 && width != 32 && width != 64 && width != 128) {
        //todo 暂时过程赋值rhs是否增加&判定
//        if (false) {
//            bitand_exprt band(cexpr,
//                              from_integer(power(2, width) - 1, rhs.type()));
//            code_block_assignv.rhs() = band;
//        } else {
//            code_block_assignv.rhs() = cexpr;
//        }

        unsigned char saved_diff = 0;
        convert_expr(rhs, saved_diff);
        code_block_assignv.rhs() = rhs;
    }// end of normal case

    // replace all register-type variables by member accesses (RHS only)
    modulevb.registers(code_block_assignv.rhs());

    // add dereferencing to all (remaining) output variables (RHS only)
    modulevb.output_var(code_block_assignv.rhs());
    // create backup copies
    // NEW: code_orig
    code_assignt code_reg = code_block_assignv, code_orig = code_block_assignv;
    // apply same adjustments as above for RHS to LHS
    modulevb.registers(code_block_assignv.lhs());
    modulevb.output_var(code_block_assignv.lhs());
    //modulevb.registers(code_block_assignv.rhs());

    // try replacements to see whether the LHS is a register-type
    // output variable, in which case both the register struct and the
    // output variable need to be assigned to
    modulevb.output_var(code_reg.lhs());

    //在阻塞赋值中判断是否增加连续赋值
    if (need_cassign) {
        code_blockt my_code_block;
        std::string lhs_symbol;
        if (code_block_assignv.lhs().id() == ID_member)
            lhs_symbol = code_block_assignv.lhs().get_string(ID_component_name);
        assert(lhs_symbol != "");
//        for (std::list<code_assignt>::const_iterator it3 = modulevb.cassignReg.begin();
//             it3 != modulevb.cassignReg.end(); ++it3) {
//            auto cassign_rh_symbols = exprSymbols((*it3).op1()); //获取连续赋值右边表达式所有变量名
//            if (cassign_rh_symbols.count(lhs_symbol)) {
//                my_code_block.add(*it3);
//            }
//        }
        std::set<std::string> updated_symbols;
        updated_symbols.emplace(lhs_symbol);
        add_cassignAll(my_code_block, updated_symbols);
        my_code_block.operands().insert(my_code_block.operands().begin(), code_block_assignv);
        return my_code_block;
    }

    return code_block_assignv;
}

/*******************************************************************\

Function: verilog_exprtt:: translate_assert

Inputs:

Outputs:

Purpose: Handle SVA assertions

\*******************************************************************/

codet verilog_exprt::translate_assert(const verilog_assertt &statement) {
    code_assertt code_assertv;
    if (statement.operands().size() != 2) {
        throw "assert statement expected to have two operands";
    }
    code_assertv.assertion() = statement.condition();
    return code_assertv;
}

/*******************************************************************\

Function: verilog_exprt::translate_assume

Inputs:

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_assume(
        const verilog_assumet &statement) {
    code_assumet code_assumev;
    if (statement.operands().size() != 2) {
        throw "assume statement expected to have two operands";
    }

    code_assumev.assumption() = statement.condition();
    return code_assumev;
}

/*******************************************************************\

Function: verilog_exprt::translate_non-blocking_assign

Inputs:

Outputs:

Purpose: Introduce a shadow variable here and pass it to code_assignt
         ID_concatenation: reg [14:0] Y; Y={A, B, (2{C}}, 3'b110};
\*******************************************************************/

codet verilog_exprt::translate_nb_assign(const verilog_statementt &statement, bool need_cassign) {
    module_infot &modulevb = module_info[current_module];

    code_assignt code_blockv;
    code_assignt code_assignv;
    if (statement.operands().size() != 2) {
        throw "assign statement expected to have two operands";
    }
    symbol_exprt nvar;
    if (statement.op0().id() == ID_extractbit)
        nvar = symbol_exprt(id2string(statement.op0().op0().get(ID_identifier)).
                substr(id2string(current_module).size() + 1) + "_old", statement.op0().op0().type());
    else
        nvar = symbol_exprt(id2string(statement.op0().get(ID_identifier)).
                substr(id2string(current_module).size() + 1) + "_old", statement.op0().type());
    code_blockv.lhs() = nvar;

    if (modulevb.nb_duplicate.insert(nvar.get_identifier()).second) {
        modulevb.new_var.push_back(code_declt(nvar)); //出现nb_assign才定义影子变量
        exprt reg_lhs = statement.op0();
        modulevb.registers(reg_lhs);
        code_assignt code_nb(nvar, reg_lhs);
        modulevb.shadowassign.push_back(code_nb);
    }

    exprt lhs = statement.op0();
    exprt rhs = statement.op1();
    code_assignv.lhs() = statement.op0();

    //RM: do I need this?
    code_blockv.rhs() = statement.op1();

    // handle ID_concatenation
    // Convert the following statement: "x <= { y[5:2], z[6:1] };" into
    // x = ((y >> 2 & 15) << 6) | (z >> 1 & 63);

    exprt concat_expr = statement.op1();
    if (concat_expr.id() == ID_concatenation) {
        if (concat_expr.operands().size() == 0) {
            throw "concatenation expected to have at least one operand";
            throw 0;
        }
        bitor_exprt final_bitor;
        unsigned saved_diff = 0;
        unsigned int diff = 0;
        exprt::operandst expr_concat;

        // Iterate over inverted direction to get the saved_diff properly !!
        // Forall_operands(it, concat_expr)
        for (exprt::operandst::const_reverse_iterator
                     it = concat_expr.operands().rbegin();
             it != concat_expr.operands().rend();
             it++) {
            if (it->id() == ID_extractbits) {
                exprt rhs = it->op0();
                if (it->operands().size() != 3)
                    throw "extractbits takes three operands";
                symbol_exprt rhs_symbol = to_symbol_expr(rhs);
                mp_integer size_op1;
                to_integer(it->op1(), size_op1);
                mp_integer size_op2;
                to_integer(it->op2(), size_op2);
                diff = integer2unsigned(size_op1 - size_op2);

                ashr_exprt shr(rhs_symbol, it->op2());
                constant_exprt constant = from_integer(power(2, diff + 1) - 1, integer_typet());
                bitand_exprt andexpr(shr, constant);
                shl_exprt shl(andexpr, saved_diff);
                saved_diff = saved_diff + (diff + 1);
                expr_concat.push_back(shl);
            } else if (it->id() == ID_extractbit) {
                exprt rhs = it->op0();
                if (it->operands().size() != 2)
                    throw "extractbit takes two operands";
                symbol_exprt rhs_symbol = to_symbol_expr(rhs);
                mp_integer size_op1;
                to_integer(it->op1(), size_op1);
                ashr_exprt shr(rhs_symbol, it->op1());
                diff = integer2unsigned(size_op1);

                constant_exprt constant = from_integer(power(2, 1) - 1, integer_typet());
                bitand_exprt andexpr(shr, constant);
                shl_exprt shl(andexpr, saved_diff);
                saved_diff = saved_diff + (diff + 1);
                expr_concat.push_back(shl);
            }
                // normal register assignment
            else if (it->id() == ID_symbol) {
                exprt rhs = *it;
                symbol_exprt rhs_symbol = to_symbol_expr(rhs);

                expr_concat.push_back(rhs_symbol);
            }
                // handle constants
            else if (it->id() == ID_constant) {
                expr_concat.push_back(*it);
            }
        } // end for
        // do a disjunction over all expressions stored in expr_concat
        exprt disjunction_expr = disjunction(expr_concat);
        // finally do the assignment
        code_blockv.rhs() = disjunction_expr;
        return code_blockv;
    } // end of concatenation handling

    // Convert the following statement: "t[3] <= out" into
    // t = (t & 0xF7) | ((out & 1) << 3);, assuming t is 8 bits
    if (statement.op0().id() == ID_extractbit) {
        if (lhs.operands().size() != 2)
            throw "extractbits takes two operands";
        symbol_exprt lhs_symbol = to_symbol_expr(statement.op0().op0());
        mp_integer size_opl1;
        to_integer(lhs.op1(), size_opl1);
        shl_exprt shl(rhs, lhs.op1());
        bitor_exprt bitor_expr(lhs_symbol, shl);
        exprt rhs1 = bitor_expr;
        exprt lhs1 = lhs_symbol;
        code_assignv.lhs() = lhs1;
    }

        // There can be different types of rhs statement as follows
    else if (statement.op0().id() == ID_extractbit) {
        if (rhs.operands().size() != 2)
            throw "extractbit takes two operands";
        symbol_exprt rhs_symbol = to_symbol_expr(statement.op0().op0());
        mp_integer size_op1;
        to_integer(statement.op1(), size_op1);
        ashr_exprt shr(rhs_symbol, statement.op1().op1());
        constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
        bitand_exprt andexpr(shr, constant1);
        exprt rhs1 = andexpr;
        code_assignv.rhs() = rhs;
        code_blockv.rhs() = rhs1;
    }
        // Convert the following statement: "fifo2[out[3:0]] <= out"
    else if (lhs.id() == ID_index) {
        symbol_exprt main_symbol = to_symbol_expr(lhs.op0());
        if (lhs.op1().id() == ID_extractbits) {
            symbol_exprt rhs_symbol = to_symbol_expr(lhs.op1().op0());
            mp_integer size_opl1;
            to_integer(lhs.op1().op1(), size_opl1);
            mp_integer size_opl2;
            to_integer(lhs.op1().op2(), size_opl2);
            unsigned diff = integer2unsigned(size_opl1 - size_opl2);
            ashr_exprt shr(rhs_symbol, lhs.op1().op2());
            constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
            bitand_exprt andexpr(shr, constant1);
            lhs.op1() = andexpr;
        }
        code_assignv.lhs() = lhs;
    }

        // Convert the following statement: "out <= fifo2[out[3:0]];"
    else if (rhs.id() == ID_index) {
        // Convert the following statement: "out <= fifo2[3];"
        if (rhs.op1().id() == ID_constant) {
            mp_integer size_op1;
            to_integer(rhs.op1(), size_op1);
            unsigned cons = integer2unsigned(size_op1);
            constant_exprt constant1 = from_integer(cons, integer_typet());
            rhs.op1() = constant1;
        } else if (rhs.op1().id() == ID_extractbits) {
            symbol_exprt rhs_symbol = to_symbol_expr(rhs.op1().op0());
            mp_integer size_opl1;
            to_integer(rhs.op1().op1(), size_opl1);
            mp_integer size_opl2;
            to_integer(rhs.op1().op2(), size_opl2);
            unsigned diff = integer2unsigned(size_opl1 - size_opl2);
            ashr_exprt shr(rhs_symbol, rhs.op1().op2());
            constant_exprt constant1 = from_integer(power(2, diff + 1) - 1, integer_typet());
            bitand_exprt andexpr(shr, constant1);
            rhs.op1() = andexpr;
        }
            // Convert the following statement: "out <= fifo2[out[3]];"
        else if (rhs.op1().op0().id() == ID_extractbit) {
            symbol_exprt rhs_symbol = to_symbol_expr(rhs.op1().op0().op0());
            mp_integer size_op1;
            to_integer(rhs.op1().op0().op1(), size_op1);
            ashr_exprt shr(rhs_symbol, rhs.op1().op0().op1());
            constant_exprt constant1 = from_integer(power(2, 0), integer_typet());
            bitand_exprt andexpr(shr, constant1);
            rhs.op1().op0() = andexpr;
            //code_blockv.rhs() = rhs;
        }
        code_blockv.rhs() = rhs;
    }

        // handle the normal case of ID_constant and ID_symbol
    else {
        exprt rhsexp = rhs;
        if (rhs.id() == ID_typecast && rhs.type().id() == ID_integer) {
            exprt rhsexp = rhs.op0();
        }

        exprt cexpr;
        exprt::operandst expressions;
        exprt rhs_op;
        Forall_operands(it, rhsexp) {
                unsigned char saved_diff = 0;
                rhs_op = convert_expr(*it, saved_diff);
                expressions.push_back(rhs_op);
            }
        cexpr = rhsexp; //todo 这里还么转换
        unsigned width = lhs.type().id() == ID_integer ? 32 : 1;
        if (width > 1) {
            bitand_exprt band(cexpr,
                              from_integer(power(2, width) - 1, rhs.type()));
            code_assignv.rhs() = band;
        } else {
            code_assignv.rhs() = cexpr;
        }
    }// end of normal case

    // replace all register-type variables by member accesses (RHS only)
    modulevb.registers(code_blockv.rhs());
    modulevb.oldvar(code_assignv.rhs());
    modulevb.registers(code_assignv.rhs());
    // add dereferencing to all (remaining) output variables (RHS only)
    modulevb.output_var(code_assignv.rhs());
    // create backup copies
    // NEW: code_orig
    code_assignt code_reg = code_assignv, code_orig = code_assignv;
    // apply same adjustments as above for RHS to LHS
    modulevb.registers(code_assignv.lhs());
    modulevb.output_var(code_assignv.lhs());
    // try replacements to see whether the LHS is a register-type
    // output variable, in which case both the register struct and the
    // output variable need to be assigned to
    modulevb.output_var(code_reg.lhs());
    return code_assignv;
}

/*******************************************************************\

Function: verilog_exprt::translate_event_guard

Inputs: @(posedge clk) begin ... end

Outputs: if(clk) { ... }

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_event_guard(
        const verilog_event_guardt &statement) {
    code_ifthenelset codeifv;
    module_infot &modulev = module_info[current_module];
    modulev.counter++;

    // store the value of always counter
    modulev.always_counter = modulev.counter;
    if (statement.operands().size() != 2) {
        throw "event_guard expected to have two operands";
    }
    const exprt &event_guard_expr = statement.guard();
    // these guards are ORed
    exprt::operandst guards;

    forall_operands(it, event_guard_expr) {
            if (it->id() == ID_posedge || it->id() == ID_negedge) {
                // clocked mean sequential circuit, set the sequential flag
                sequential = true;

                if (it->operands().size() != 1) {
                    throw "pos/negedge expected to have one operand";
                }

                if (it->op0().id() != ID_symbol) {
                    throw "pos/negedge expected to have symbol as operand ";
                    "but got " + it->op0().pretty();
                }

                if (it->op0().type().id() != ID_bool) {
                    throw "pos/negedge expected to have Boolean as operand ";
                }
                modulev.always = true;
            } else if (it->id() != ID_posedge && it->id() != ID_negedge) {

                modulev.always = false;
                guards.push_back(*it);
            }
        }
    return translate_statement(statement.body(), true);
}

/*******************************************************************\

Function: verilog_exprt::translate_delay

Inputs:  #10  a = 1;

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_delay(
        const verilog_delayt &statement) {
    code_blockt code_delayv;
    if (statement.operands().size() != 2) {
        throw "delay expected to have two operands";
    }

    codet delay_case = translate_statement(statement.body());
    // check that second pair is empty
    assert(delay_case == codet());
    code_delayv.operands().push_back(delay_case);
    return code_delayv;
}

/*******************************************************************\

Function: verilog_exprt::translate_case

Inputs:

Outputs:

Purpose: Model this as switch-case or if-then-else as Verilog synthesis case

\*******************************************************************/

codet verilog_exprt::translate_case(const verilog_statementt &statement, bool need_cassign) {
    code_blockt code_blockv;
    if (statement.operands().size() < 1) {
        throw "case statement expected to have at least one operand";
    }

    exprt case_operand = statement.op0();
    // we convert the rest to if-then-else
    exprt start;
    exprt *last_if = &start;
    for (unsigned i = 1; i < statement.operands().size(); i++) {
        const exprt &e = statement.operands()[i];
        if (e.id() != ID_case_item)
            throw "expected case_item";
        if (e.operands().size() != 2) {
            throw "case_item expected to have two operands";
        }
        exprt if_statement(ID_if);
        if_statement.reserve_operands(3);
        if_statement.operands().resize(2);
        if_statement.op0() = translate_case_values(e.op0(), case_operand);
        if_statement.op1() = e.op1();
        last_if->move_to_operands(if_statement);
        last_if = &last_if->operands().back();
    }

    if (!start.operands().empty()) {
        codet sw_case = translate_statement(static_cast<verilog_statementt &>(start.op0()), need_cassign);
        code_blockv.operands().push_back(sw_case);
    }
    return code_blockv;
}

/*******************************************************************\

Function: verilog_exprt::translate_case_values

Inputs:

Outputs:

Purpose:

\*******************************************************************/

exprt verilog_exprt::translate_case_values(
        const exprt &values,
        const exprt &case_operand) {
    if (values.id() == ID_default)
        return true_exprt();
    exprt::operandst op;
    op.reserve(values.operands().size());

    forall_operands(it, values) {
            exprt pattern = *it;
            op.push_back(case_comparison(case_operand, pattern));
        }
    return disjunction(op);
}

/*******************************************************************\

Function: verilog_exprt::case_comparison

Inputs:

Outputs:

Purpose:

\*******************************************************************/

exprt verilog_exprt::case_comparison(
        const exprt &case_operand,
        const exprt &pattern) {
    // we need to take case of ?, x, z in the pattern
    if (pattern.type().id() == ID_verilog_signedbv ||
        pattern.type().id() == ID_verilog_unsignedbv) {
        // try to simplify the pattern
        exprt tmp = pattern;

        simplify(tmp, ns);

        if (tmp.id() != ID_constant) {
            throw "unexpected case pattern ";
        } else {
            exprt new_case_operand = case_operand;

            // the pattern has the max type
            unsignedbv_typet new_type;
            new_type.set_width(pattern.type().get_int(ID_width));
            new_case_operand.make_typecast(new_type);

            // we are using masking!
            std::string new_pattern_value =
                    id2string(to_constant_expr(tmp).get_value());
            // ?zx -> 0
            for (unsigned i = 0; i < new_pattern_value.size(); i++)
                if (new_pattern_value[i] == '?' ||
                    new_pattern_value[i] == 'z' ||
                    new_pattern_value[i] == 'x')
                    new_pattern_value[i] = '0';

            constant_exprt new_pattern(new_type);
            new_pattern.set_value(new_pattern_value);

            std::string new_mask_value =
                    id2string(to_constant_expr(tmp).get_value());

            // ?zx -> 0, 0 -> 1
            for (unsigned i = 0; i < new_mask_value.size(); i++)
                if (new_mask_value[i] == '?' ||
                    new_mask_value[i] == 'z' ||
                    new_mask_value[i] == 'x')
                    new_mask_value[i] = '0';
                else
                    new_mask_value[i] = '1';

            constant_exprt new_mask(new_type);
            new_mask.set_value(new_mask_value);

            exprt bitand_expr = bitand_exprt(new_case_operand, new_mask);

            return equal_exprt(bitand_expr, new_pattern);
        }
    }

    if (pattern.type() == case_operand.type())
        return equal_exprt(case_operand, pattern);

    // the pattern has the max type
    exprt tmp_case_operand = typecast_exprt(case_operand, pattern.type());
    return equal_exprt(tmp_case_operand, pattern);
}

/*******************************************************************\

Function: verilog_exprt::translate_for

Inputs:

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_for(const verilog_fort &statement) {
    code_fort code_forv;
    if (statement.operands().size() != 4) {
        throw "for expected to have four operands";
    }
    codet for_init = translate_statement(statement.initialization());
    code_forv.init() = for_init;
    code_forv.init().id(ID_side_effect);
    code_forv.cond() = statement.condition();
    codet for_iter = translate_statement(statement.inc_statement());
    code_forv.iter() = for_iter;
    code_forv.iter().id(ID_side_effect);
    codet for_body = translate_statement(statement.body());
    code_forv.body() = for_body;
    return code_forv;
}

/*******************************************************************\

Function: verilog_exprt::translate_while

Inputs:

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_while(
        const verilog_whilet &statement) {
    code_whilet code_whilev;
    if (statement.operands().size() != 2) {
        throw "while expected to have two operands";
    }

    code_whilev.cond() = statement.condition();
    codet while_body = translate_statement(statement.body());
    code_whilev.body() = while_body;
    return code_whilev;
}

/*******************************************************************\

Function: verilog_exprt::translate_repeat

Inputs:

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_repeat(
        const verilog_repeatt &statement) {
    code_skipt code_skipv;
    if (statement.operands().size() != 2) {
        throw "repeat expected to have two operands";
    }

    throw "`repeat' is not synthesizable, so can't translate";
    return code_skipv;
}

/*******************************************************************\

Function: verilog_exprt::translate_forever

Inputs:

Outputs:

Purpose:

\*******************************************************************/

codet verilog_exprt::translate_forever(
        const verilog_forevert &statement) {
    code_skipt code_skipv;
    if (statement.operands().size() != 1) {
        throw "forever expected to have one operand";
    }
    throw "`forever' is not synthesizable, so can't translate";
    return code_skipv;
}
