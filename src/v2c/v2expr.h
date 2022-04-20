/***********************************************************************
	Tool Name : v2c
	Purpose : Verilog RTL to ANSI-C translator tool
    Author: Rajdeep Mukherjee, Michael Tautschnig and Daniel Kroening
 ***********************************************************************/
#include <cassert>
#include <map>
#include <set>
#include<string>
#include <util/hash_cont.h>
#include <util/mp_arith.h>
#include <util/string_hash.h>
#include <util/message.h>
#include <util/options.h>
#include <util/replace_symbol.h>
#include <util/std_expr.h>
#include <util/std_code.h>
#include <verilog/verilog_typecheck_base.h>
#include <verilog/verilog_symbol_table.h>
#include <util/symbol_table.h>
#include <verilog/verilog_typecheck_base.h>
#include <verilog/verilog_symbol_table.h>

class verilog_blockt;

bool vtoexpr(symbol_tablet &symbol_table, const irep_idt &module, std::ostream &out);

/*******************************************************************\

Class: verilog_exprt

Inputs: Main class file

Outputs:

Purpose:

\*******************************************************************/
typedef std::pair<codet, codet> code_pairt;

class verilog_exprt : public messaget {
public:
    verilog_exprt(symbol_tablet &_symbol_table,
            const irep_idt &_module) :
            module(_module),
            ns(_symbol_table),
            symbol_table(_symbol_table),
            identifier_name(0) {
    }

    bool convert_module(const symbolt &symbol, std::ostream &out);

    irep_idt top_name;
    bool sequential;
protected:
    const irep_idt &module;
    irep_idt current_module;
    const namespacet ns;
    const symbol_tablet &symbol_table;
    std::set<irep_idt> modules_done;
    std::set<irep_idt> modules_in_progress;
    std::map<std::string, std::string> ef_map;
    std::stringstream stypedef;
    std::map<irep_idt, irep_idt> input_dependency_map;
    std::map<irep_idt, irep_idt> output_dependency_map;

    bool do_conversion(code_blockt &code_verilogblock, const symbolt &symbol,
                       const irep_idt &curr_module_backup, const std::set<irep_idt>::iterator &in_progress_it,
                       std::ostream &out);

    struct module_infot {
        std::list<symbol_exprt> parameters;
        std::list<symbol_exprt> local_sym;
        std::set<irep_idt> nb_duplicate;
        std::set<irep_idt> block_duplicate;

        replace_symbolt registers;
        replace_symbolt output_var;
        replace_symbolt oldvar;
        replace_symbolt oldvar_blocking;
        bool always;
        bool initial;
        bool parameter;
        int counter;
        int always_counter;
        int register_present;
        irep_idt struct_name;
        struct_typet st;
        std::list<code_declt> new_var;
        std::list<code_assignt> cassign;
        std::list<code_assignt> cassignReg;
        std::list<codet> shadowassign;
        std::list<codet> blockingassign;
        std::list<codet> functioncall;

        module_infot() : always(false), initial(false), counter(0), always_counter(0), register_present(0) {}
    };

    code_blockt initial_block;
    code_blockt parameter_block;
    std::map<irep_idt, module_infot> module_info;
    std::map<irep_idt, irep_idt> *identifier_name;

    // **************** convert module items ***************
    codet convert_module_item(const class verilog_module_itemt &module_item);

    codet translate_block(const verilog_blockt &statement, bool need_cassign = false);

    codet convert_decl(const class verilog_declt &statement);

    codet convert_assert(const class verilog_assertt &statement);

    void convert_function(const class verilog_module_itemt &statement, std::ostream &out);

    void convert_task(const class verilog_module_itemt &statement, std::ostream &out);

    codet convert_initial(const class verilog_initialt &module_item);

    codet convert_continuous_assign(const class verilog_continuous_assignt &module_item);

    codet convert_inst(const class verilog_instt &statement);

    codet convert_always(const class verilog_alwayst &module_item);

    codet convert_parameter(const class verilog_module_itemt &module_item);

    void iterate_module(exprt &module1, const module_infot &modulevb);

    // ****************** Translate statements *****************
    codet translate_block_assign(const class verilog_statementt &statement, bool need_cassign = false);

    codet translate_statement(const class verilog_statementt &statement, bool need_cassign = false);

    codet translate_if(const class verilog_ift &statement, bool need_cassign = false);

    codet translate_assert(const class verilog_assertt &statement);

    codet translate_assume(const class verilog_assumet &statement);

    codet translate_nb_assign(const class verilog_statementt &statement, bool need_cassign = false);

    codet translate_event_guard(const class verilog_event_guardt &statement);

    codet translate_delay(const class verilog_delayt &statement);

    codet translate_case(const class verilog_statementt &statement, bool need_cassign = false);

    codet translate_for(const class verilog_fort &statement);

    codet translate_while(const class verilog_whilet &statement);

    codet translate_repeat(const class verilog_repeatt &statement);

    codet translate_forever(const class verilog_forevert &statement);

    exprt translate_case_values(const exprt &values, const exprt &case_operand);

    exprt case_comparison(const exprt &case_operand, const exprt &pattern);

    void collect_continuous_assign(const class verilog_module_itemt &module_item);

    void do_collect_continuous_assign(const class verilog_continuous_assignt &module_item);

    exprt convert_expr(exprt &expression, unsigned char &saved_diff, dstring expr_type = ID_nil);

    void add_bitand(exprt &expression);
};
