/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  parser.y - main grammar

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

%{
#define __YACC__


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // tolower
#include <limits.h>
#include <vector>

#include "parserParser.h"

#include "parserCode.h"
#include "parserControl.h"
#include "parserOP.h"
#include "parserException.h"
#include "orca_opcode.h"
#include "parserParse.h"
#include "kyString.h"


//TEMP
#include "orcaRoot.h"

parserException s_ex;
parserException* g_ex = &s_ex;

// For parser
bool unary_minus = false;

int g_lvar_nil_check = 0;
int g_bnf_right_num = 0;

using namespace std;


%}

%union 
{
	const char* cp;
	int integer;
	double real;
	void* vector_cp;	
	struct cp2_t cp2; 
	struct int2_t int2;
	void* vp;	
};

%error-verbose

%left '+' '-'
%left '*' '/'
%left UMINUS



// type define/*{{{*/
%type <cp> name
%type <cp> argv_name
%type <cp> name_or_string
%type <cp> opt_name_or_string
%type <cp> lvar
%type <cp> p_var
%type <cp> object_path
%type <cp> superclass_path
%type <cp> opt_under
%type <cp> big_number
%type <cp> lambda_object
%type <cp> lambda_define_header
%type <cp> lambda_context_header
%type <cp> lambda_decode_header
%type <cp> lambda_parse_header


%type <integer> number					// integer
%type <integer> expression_stmt			// num of expr
%type <integer> expression_list			// num of expr
%type <integer> expr_extract_list		// num of expr
%type <integer> pair_list				// num of expr
%type <integer> opt_expr_list			// num of expr
%type <integer> elif_stmt_list			// num of elif stmt
%type <integer> reserved_object			// reserved object enum value
%type <integer> calling_body			// num of arguemnts
%type <integer> def						// flag
%type <integer> assign_type				// '=', '+' ...
%type <integer> pattern_list			// num of pattern
%type <integer> assign_target_list_with_argv
%type <integer> assign_target_list
%type <integer> channel_assign_target_list_with_argv
%type <integer> channel_assign_target_list

%type <real> real

%type <vector_cp> name_list
%type <vector_cp> opt_argument_list
%type <vector_cp> superclass_path_list
%type <vector_cp> opt_superclass

%type <vp> bnf_stmt_list
%type <vp> bnf_stmt
%type <vp> bnf_node_list
%type <vp> bnf_node
%type <vp> bnf_right_list
%type <vp> bnf_right
%type <vp> terminal
%type <cp> action_code
%type <cp> bnf_left
%type <cp> non_terminal

/*}}}*/

// token define /*{{{*/
%token NEW_LINE
%token STATIC 
%token DEF 
%token CLONE 
%token MY
%token OWNER
%token CALLER
%token ROOT
%token MODULE
%token PARENT
%token IF
%token ELIF
%token ELSE
%token DO
%token WHILE
%token TIMES
%token SELECT
%token SWITCH
%token DECODE
%token CASE
%token DEFAULT
%token FALLTHROUGH
%token PARSE
%token FOR
%token IN
%token RETURN_
%token CONTINUE
%token BREAK
%token EQ
%token NEQ
%token AND
%token OR
%token GT
%token GE
%token LT
%token LE
%token TRY
%token CATCH
%token FINALLY
%token THROW
%token DUMP
%token STACK
%token LOCAL
%token USING
%token TRUE
%token FALSE
%token DOUBLE_DOT
%token TRIPLE_DOT
%token ADD_ASSIGN
%token SUB_ASSIGN
%token MUL_ASSIGN
%token DIV_ASSIGN
%token NIL_
%token RIGHT_ARROW
%token LEFT_ARROW
%token PARALLEL
%token ASSIGNMENT
%token EVAL
%token COMPILE
%token LAMBDA
%token UNDER
%token IR_BRACKET

%token<cp> NAME
%token<cp> STRING
%token<cp> STRING_VAR_HEAD
%token<cp> STRING_VAR_TAIL
%token<cp> RE_STRING
%token<cp> RE_STRING_VAR_HEAD
%token<cp> HEX_STRING
%token<cp> SHELL_STRING_HEAD

%token<integer> NUMBER
%token<cp> BIG_NUMBER
%token<real> REAL
/*}}}*/

%%

statement_list:/*{{{*/
	statement_list statement
	| statement_list statement_block
	| statement_block
	| statement
	;
/*}}}*/

statement_block:/*{{{*/
	'{' statement_list '}'
	| '{' '}'
	;
/*}}}*/

statement:/*{{{*/
	expression_stmt 
		{
			if ($1 > 1) {
				for(int i=0; i<$1; i++)
					g_op->pop_stack();
			}
			else {
				g_op->fast_pop_stack();
			}
		}
	| control_stmt 
	| selection_stmt
	| loop_stmt
	| define_stmt
	| exception_stmt
	| using_stmt 
	| simple_call_stmt 
		{
			g_op->fast_pop_stack();
		}
	| shell_stmt 
		{
			g_op->fast_pop_stack();
		}
	| scope_stmt
	| parallel_stmt
	| debug_stmt 
	| channel_stmt 
	| ';'
	;
/*}}}*/

channel_stmt:/*{{{*/
	expression LEFT_ARROW
		{
			g_ctl->channel_in_start();
		}
	expression_list ';'
		{
			g_ctl->channel_in_end($4);
		}
	| expression RIGHT_ARROW
		{
			g_ctl->channel_out_start();
		}
	channel_assign_target_list_with_argv ';'
		{
			g_ctl->channel_out_end($4);
		}
	;
/*}}}*/

assign_target_list_with_argv:/*{{{*/
	assign_target_list
	| assign_target_list ',' argv_name
		{
			const char* cp = $3;
			cp += 3; // skip ...
			g_op->assign_local(cp); // already made as tuple
			g_op->pop_stack();
			$$ = -($1);
		}
	| argv_name
		{
			const char* cp = $1;
			cp += 3; // skip ...
			g_op->assign_local(cp); // already made as tuple
			g_op->pop_stack();
			$$ = 0;
		}
	;
/*}}}*/

assign_target_list:/*{{{*/
	  assign_target_list ',' assign_target
		{
			$$ = $1 + 1;
		}
	| assign_target
		{
			$$ = 1;
		}
	;
/*}}}*/

assign_target:/*{{{*/
	  lvar
		{
			g_op->assign_local($1);
			g_op->pop_stack();
		}
	| postfix_object '.' name_or_string
		{
			g_op->assign_member($3);
			g_op->pop_stack();
		}
	| postfix_object '.' reserved_object
		{
			g_op->assign_reserved($3);
			g_op->pop_stack();
		}
	| postfix_object '[' slice_expression ']'
		{
			g_op->assign_list(false);
			g_op->pop_stack();
		}
	| postfix_object '[' slice_expression IR_BRACKET
		{
			g_op->assign_list(true);
			g_op->pop_stack();
		}
	| DOUBLE_DOT name_or_string
		{
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->assign_member($2);
			g_op->pop_stack();
		}
	| DOUBLE_DOT reserved_object
		{
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->assign_reserved($2);
			g_op->pop_stack();
		}
	| '.' name_or_string
		{
			g_op->push_reserved(OP_PUSH_MY);
			g_op->assign_member($2);
			g_op->pop_stack();
		}
	| '.' reserved_object
		{
			g_op->push_reserved(OP_PUSH_MY);
			g_op->assign_reserved($2);
			g_op->pop_stack();
		}
	;
/*}}}*/

channel_assign_target_list_with_argv:/*{{{*/
	channel_assign_target_list
	| channel_assign_target_list ',' argv_name
		{
			const char* cp = $3;
			cp += 3; // skip ...
			g_op->assign_local(cp); // already made as tuple
			g_op->pop_stack();
			$$ = -($1);
		}
	| argv_name
		{
			const char* cp = $1;
			cp += 3; // skip ...
			g_op->assign_local(cp); // already made as tuple
			g_op->pop_stack();
			$$ = 0;
		}
	;
/*}}}*/

channel_assign_target_list:/*{{{*/
	  channel_assign_target_list ',' channel_assign_target
		{
			$$ = $1 + 1;
		}
	| channel_assign_target
		{
			$$ = 1;
		}
	;
/*}}}*/

channel_assign_target:/*{{{*/
	  lvar
		{
			g_op->assign_local($1);
			g_op->pop_stack();
		}
	| postfix_object '.' name_or_string
		{
			g_op->rotate();
			g_op->assign_member($3);
			g_op->pop_stack();
		}
	| postfix_object '.' reserved_object
		{
			g_op->rotate();
			g_op->assign_reserved($3);
			g_op->pop_stack();
		}
	| postfix_object '[' slice_expression ']'
		{
			g_op->rotate3();
			g_op->assign_list(false);
			g_op->pop_stack();
		}
	| postfix_object '[' slice_expression IR_BRACKET
		{
			g_op->rotate3();
			g_op->assign_list(true);
			g_op->pop_stack();
		}
	| DOUBLE_DOT name_or_string
		{
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->rotate();
			g_op->assign_member($2);
			g_op->pop_stack();
		}
	| DOUBLE_DOT reserved_object
		{
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->rotate();
			g_op->assign_reserved($2);
			g_op->pop_stack();
		}
	| '.' name_or_string
		{
			g_op->push_reserved(OP_PUSH_MY);
			g_op->rotate();
			g_op->assign_member($2);
			g_op->pop_stack();
		}
	| '.' reserved_object
		{
			g_op->push_reserved(OP_PUSH_MY);
			g_op->rotate();
			g_op->assign_reserved($2);
			g_op->pop_stack();
		}
	;
/*}}}*/

scope_stmt:/*{{{*/
	expression
		{
			//g_op->do_scope_start();
			g_ctl->scope_start();
		}
	statement_block
		{
			//g_op->do_scope_end();
			g_ctl->scope_end();
		}
	;
/*}}}*/

parallel_stmt:/*{{{*/
	PARALLEL DO
		{
			g_ctl->parallel_start();
		}
	statement_block
		{
			g_ctl->parallel_end();
		}
	| PARALLEL FOR lvar IN object parallel_option
		{
			g_ctl->parallel_for_start($3);
		}
	statement_block
		{
			g_ctl->parallel_for_end();
		}
	| PARALLEL postfix_object ';'
		{
			if (g_op->change_to_parallel_call() == false) {
				throw g_parser->strdup("object is not callable");
			}
		}
	;
/*}}}*/

parallel_option: /* empty *//*{{{*/
		{
			g_op->push_integer(0);	// by
			g_op->push_integer(1);	// per
		}
	| name expression
		{
			int opt = 0;
			if (strncmp($1, "by", 2) == 0) {
				g_op->push_integer(1);
			}
			else if (strncmp($1, "per", 3) == 0) {
				g_op->push_integer(0);
				g_op->rotate();
			}
			else {
				throw g_parser->strdup("parallel option 'by' or 'per' expected");
			}
		} 
	| name expression name expression
		{
			if (strncmp($1, "by", 2) != 0) {
				throw g_parser->strdup("parallel option 'by' expected");
			}

			if (strncmp($3, "per", 3) != 0) {
				throw g_parser->strdup("parallel option 'per' expected");
			}
		}
	;
/*}}}*/

simple_call_stmt:/*{{{*/
	postfix_object ':' expression_list  ';'
		{
			g_op->call($3);
		}
	;
/*}}}*/

shell_stmt:/*{{{*/
		{
			g_op->push_reserved(OP_PUSH_ROOT);
			g_op->find_member("os");
			g_op->find_member("run_cout");
		}
	shell_string 
		{	
			g_op->call(1);
		}
	;
/*}}}*/

shell_string:/*{{{*/
	  shell_string string_var_object
	| SHELL_STRING_HEAD
		{
			g_op->push_string($1);
		}
	;			 
/*}}}*/

exception_stmt:/*{{{*/
	try_stmt catch_stmt_list_with_finally
		{
			g_ex->pop();
		}
	| throw_stmt
	;
/*}}}*/

try_stmt:/*{{{*/
	TRY
		{
			g_ex->push();
			g_ctl->do_try();
		}
	statement_block
		{
			g_ex->goto_end();
			g_ctl->clean_try();
		}
	;
/*}}}*/

catch_stmt_list_with_finally:/*{{{*/
	  catch_stmt_list
		{
			g_ex->do_finally();
		}
	  finally_stmt
		{
			g_ex->goto_end();
		}
	| catch_stmt_list
	;
/*}}}*/

finally_stmt:/*{{{*/
	FINALLY statement_block
	;
/*}}}*/

catch_stmt_list:/*{{{*/
	catch_stmt_list catch_stmt
	| catch_stmt
	;
/*}}}*/

catch_stmt:/*{{{*/
	CATCH object_path 
		{
			g_ex->catch_start($2);
		}
	statement_block
		{
			g_ex->goto_finally();
		}
	| CATCH object_path name name
		{
			if (strcmp($3, "as") != 0) {
				throw g_parser->strdup("as is expected");
			}

			g_ex->catch_start($2, $4);
		}
	statement_block
		{
			g_ex->goto_finally();
		}
	| CATCH object_path RIGHT_ARROW name_list
		{
			name_list_t* vp = (name_list_t*)$4;
			g_ex->catch_start($2, NULL, vp);
		}
	statement_block
		{
			g_ex->goto_finally();
		}
	| CATCH object_path name name RIGHT_ARROW name_list
		{
			if (strcmp($3, "as") != 0) {
				throw g_parser->strdup("as is expected");
			}

			name_list_t* vp = (name_list_t*)$6;
			g_ex->catch_start($2, $4, vp);
		}
	statement_block
		{
			g_ex->goto_finally();
		}
	;
/*}}}*/

throw_stmt:/*{{{*/
	THROW object_path ';'
		{
			g_op->push_integer(0); // reserve
			g_ex->do_throw($2, 0);
		}
	| THROW object_path
		{
			g_op->push_integer(0); // reserve
		}
	  LEFT_ARROW expression_list ';'
		{
			g_ex->do_throw($2, $5);
		}
	;
/*}}}*/

using_stmt:/*{{{*/
	USING object_path ';'
		{
			code_top->using_object($2);
		}
	;
/*}}}*/

object_path:/*{{{*/
	object_path '.' name_or_string
		{
			char buff[1024];
			snprintf(buff, 1024, "%s.%s", $1, $3);
			$$ = g_parser->strdup(buff);
		}
	| name_or_string
	;
/*}}}*/

debug_stmt:/*{{{*/
	STACK
		{
			g_op->dump_stack();
		}
	| LOCAL
		{
			g_op->dump_local();
		}
	;
/*}}}*/

control_stmt:/*{{{*/
	  RETURN_ opt_expr_list ';'
		{
			g_ctl->do_return($2);
		}
	| CONTINUE ';'
		{
			g_ctl->do_continue();
		}
	| BREAK ';'
		{
			g_ctl->do_break();
		}
	| FALLTHROUGH ';'
		{
			g_ctl->do_fallthrough();
		}
	;
/*}}}*/

opt_expr_list:/*{{{*/
	/* empty */
		{
			$$ = 0;
		}
	| expression_list
	;
/*}}}*/

selection_stmt:/*{{{*/
	  if_elif_else_stmt
	| decode_stmt
	| switch_stmt
	| select_stmt
	;
/*}}}*/

select_stmt:/*{{{*/
	SELECT
		{
			g_ctl->select_start();	
		}
	'{' select_case_stmt_list opt_select_default_stmt '}'
		{
			g_ctl->select_end();	
		}
	;
/*}}}*/

select_case_stmt_list:/*{{{*/
	  select_case_stmt_list select_case_stmt
	| select_case_stmt
	;
/*}}}*/

opt_select_default_stmt:/*{{{*/
	 /* empty */
	| DEFAULT ':' 
		{
			g_ctl->select_case_start();
			g_ctl->select_default_shift();
		}
	opt_statement_list
		{
			g_ctl->select_case_end(0);
		}
	;
/*}}}*/

select_case_stmt:/*{{{*/
		{
			g_ctl->select_case_start();
		}
	CASE expression RIGHT_ARROW 
		{
			g_ctl->select_case_shift();
		}
	assign_target_list_with_argv ':'
	opt_statement_list
		{
			g_ctl->select_case_end($6);
		}
	;
/*}}}*/

switch_stmt:/*{{{*/
	SWITCH expression
		{
			g_ctl->switch_start();
		}
	'{' switch_pattern_stmt_list opt_switch_default_stmt '}'
		{
			g_ctl->switch_end();
		}
	;
/*}}}*/

switch_pattern_stmt_list:/*{{{*/
	  switch_pattern_stmt_list switch_pattern_stmt
	| switch_pattern_stmt
	;
/*}}}*/

opt_switch_default_stmt:/*{{{*/
	 /* empty */
	| DEFAULT ':' 
		{
			g_ctl->switch_case_start();
		}
	opt_statement_list
		{
			g_ctl->switch_case_end();
		}
	;
/*}}}*/

switch_pattern_stmt:/*{{{*/
	CASE
		{
			g_ctl->switch_case_start();
		}
	expression_list ':'
		{
			g_ctl->switch_case_shift($3);
		}
	opt_statement_list
		{
			g_ctl->switch_case_end();
		}
	;
/*}}}*/

opt_statement_list:/*{{{*/
	/* empty */
	| statement_list
	;
/*}}}*/

decode_stmt:/*{{{*/
	DECODE expression 
		{
			g_ctl->decode_start();
		}
	'{' decode_pattern_stmt_list '}'
		{
			g_ctl->decode_end();
		}
	;
/*}}}*/

bnf_stmt_list:/*{{{*/
	bnf_stmt_list bnf_stmt
		{
			parse_t* pp = (parse_t*)$1;
			pp->push_rule((rule_t*)$2);
			$$ = pp;
		}
	| bnf_stmt
		{
			parse_t* pp = new parse_t();
			pp->push_rule((rule_t*)$1);
			$$ = pp;
		}
	;
/*}}}*/

bnf_stmt:/*{{{*/
	bnf_left ':' bnf_right_list ';'
		{
			rule_t* rp = (rule_t*)$3;
			rp->set_name($1);
			$$ = rp;
		}
	| NIL_ ':' terminal ';'
		{
			rule_t* rp = new rule_t();
			rp->set_name("nil");

			bnf_t* bp = new bnf_t();
			bp->push_expr((expr_t*)$3);
			rp->push_bnf(bp);

			$$ = rp;
		}
	
	;
/*}}}*/

bnf_right_list:/*{{{*/
	bnf_right_list '|' bnf_right
		{
			rule_t* rp = (rule_t*)$1;
			rp->push_bnf((bnf_t*)$3);

			$$ = rp;
		}
	| bnf_right
		{
			rule_t* rp = new rule_t();
			rp->push_bnf((bnf_t*)$1);

			$$ = rp;
		}
	;
/*}}}*/

bnf_left:/*{{{*/
	non_terminal
	;
/*}}}*/

bnf_right:/*{{{*/
	bnf_node_list
	| /* empty */
		{
			$$ = NULL;
		}
	;
	/*}}}*/

bnf_node_list:/*{{{*/
	bnf_node_list bnf_node
		{
			bnf_t* bp = (bnf_t*)$1;
			expr_t* ep = (expr_t*)$2;
	
			bp->push_expr(ep);
			$$ = bp;
		}
	| bnf_node
		{
			bnf_t* bp = new bnf_t();
			expr_t* ep = (expr_t*)$1;

			bp->push_expr(ep);
			$$ = bp;
		}
	;
/*}}}*/

bnf_node:/*{{{*/
	terminal
	| non_terminal
		{
			expr_t* ep = new expr_t();
			ep->set_non_terminal($1);
			$$ = ep;
		}
	| action_code
		{
			expr_t* ep = new expr_t();
			ep->set_action_code($1);
			$$ = ep;
		}
	;
/*}}}*/

terminal:/*{{{*/
	STRING
		{
			expr_t* ep = new expr_t();
			ep->set_terminal($1);
			$$ = ep;
		}
	| RE_STRING
		{
			expr_t* ep = new expr_t();
			ep->set_terminal_re($1);
			$$ = ep;
		}
	;
/*}}}*/

non_terminal:/*{{{*/
	name
	;
/*}}}*/

action_code:/*{{{*/
	lambda_object
	;
/*}}}*/

decode_pattern_stmt_list:/*{{{*/
	  decode_pattern_stmt_list decode_pattern_stmt
	| decode_pattern_stmt
	;
/*}}}*/

decode_pattern_stmt:/*{{{*/
		{
			g_ctl->decode_pattern_start();
		}
	CASE decode_pattern ':'
		{
			g_ctl->decode_pattern_shift();
		}
	opt_statement_list
		{
			g_ctl->decode_pattern_end();
		}
	;
/*}}}*/

decode_pattern:/*{{{*/
	pattern_list
	| list_pattern
	;
/*}}}*/

list_pattern:/*{{{*/
	p_var  '[' p_var ']'
		{
			g_ctl->decode_cut_list($1, $3);
		}
	;
/*}}}*/

pattern_list:/*{{{*/
	pattern_list ',' pattern
		{
			$$ = $1 + 1;
		}
	| pattern
		{
			$$ = 1;
		}
	;
/*}}}*/

pattern:/*{{{*/
	expression
		{
			g_ctl->decode_match_expr();
		}
	| p_var
		{
			g_ctl->decode_shift($1);
		}
	| p_var '=' expression 
		{
			g_ctl->decode_match_and_assign($1);
		}
	;
/*}}}*/

p_var:/*{{{*/
	'%' lvar
		{
			$$ = $2;
		}	
	;
/*}}}*/

loop_stmt:/*{{{*/
	for_stmt
	| do_stmt
	| while_stmt
	| times_stmt
	;
/*}}}*/

def:/*{{{*/
	STATIC DEF
		{
			$$ = BIT_DEFINE_STATIC;
		}
	| DEF
		{
			$$ = 0;
		}
	;
/*}}}*/

opt_name_or_string:/*{{{*/
	/* empty */
		{
			$$ = NULL;
		}
	| name_or_string
	;
/*}}}*/

name_or_string:/*{{{*/
	name
	| STRING
	;
/*}}}*/

opt_under:/*{{{*/
	 /* empty */
		{
			$$ = NULL;
		}
	| UNDER object_path
		{
			$$ = $2;
		}
	| UNDER ROOT
		{
			$$ = "root";
		}
	;
/*}}}*/

define_stmt:/*{{{*/
	def name_or_string ';'
		{
			code_top->reg_object($2, $1);
		}
	| def name_or_string ASSIGNMENT 
		{
			code_top->reg_object($2, $1);
			code_top->init_object_start($2);

			g_op->push_reserved(OP_PUSH_MY);
		}
	   expression ';' 
		{
			g_op->assign_member($2);
			g_op->pop_stack();
			code_top->init_object_done();
		}
	| def opt_name_or_string opt_argument_list opt_superclass opt_under
		{
			const char* name = $2;
			static int count = 1;
			name_list_t* supers = (name_list_t*)$4;
			char buff[1024];
			if (name == NULL) {
				snprintf(buff, 1024, "__%s_%d_anonymous", g_parser->module_name.c_str(), count++);
				name = buff;
			}

			name_list_t* vp = (name_list_t*)$3;
			parserCode::push_code_stack(name, vp, $1, supers, $5);

			// check argv
			if (vp && strncmp((*vp)[vp->size()-1], "...", 3) == 0) {
				code_top->set_argv_on();
			}
		}
	  statement_block 
		{
			parserCode::pop_code_stack();
		}
	| define_context_stmt
	| define_parse_stmt
	| define_decode_stmt
	;
	/*}}}*/

define_context_stmt:/*{{{*/
	def '.' object_path opt_name_or_string opt_argument_list opt_superclass opt_under
		{
			const char* name = $4;
			static int count = 1;
			name_list_t* supers = (name_list_t*)$6;

			char buff[1024];
			if (name == NULL) {
				snprintf(buff, 1024, "__%s_%d_ctx_anonymous", g_parser->module_name.c_str(), count++);
				name = buff;
			}

			map<string, int> pos_map;
			const char* cp = lexer->get_context(pos_map);
			//print("lexer->get_context(): '%s'\n", cp);

			name_list_t* vp = (name_list_t*)$5;
			code_top->push_context_stack($3, cp, name, vp, $1, supers, $7, pos_map);

			if (vp && strncmp((*vp)[vp->size()-1], "...", 3) == 0) {
				code_top->set_argv_on();
			}
		}
	statement_block
		{
			parserCode::pop_code_stack();
		}
	;
/*}}}*/

define_parse_stmt:/*{{{*/
	  def '.' PARSE opt_name_or_string opt_argument_list opt_under
		{
			const char* name = $4;
			static int count = 1;
			char buff[1024];
			if (name == NULL) {
				snprintf(buff, 1024, "__%s_%d_parse_anonymous", g_parser->module_name.c_str(), count++);
				name = buff;
			}

			name_list_t* vp = (name_list_t*)$5;

			// check argv
			if (vp && strncmp((*vp)[vp->size()-1], "...", 3) == 0) {
				throw g_parser->strdup("argv not allowed in parse object");
			}

			if (vp == NULL) {
				throw g_parser->strdup("at least 1 argument needed in parse object");
			}

			int flag = $1;
			flag |= BIT_DEFINE_PARSE;
			parserCode::push_code_stack(name, vp, flag, NULL, $6);
		}
	'{' bnf_stmt_list '}'
		{
			parse_t* pp = (parse_t*)$9;
			bool ret = pp->process($4);
			if (ret == false) {
				throw g_parser->strdup("build so failed");
			}

			parserCode::pop_code_stack();
		}
	;
/*}}}*/

define_decode_stmt:/*{{{*/
	  def '.' DECODE opt_name_or_string opt_argument_list opt_under
		{
			const char* name = $4;
			static int count = 1;
			char buff[1024];
			if (name == NULL) {
				snprintf(buff, 1024, "__%s_%d_decode_anonymous", g_parser->module_name.c_str(), count++);
				name = buff;
			}

			name_list_t* vp = (name_list_t*)$5;
			parserCode::push_code_stack(name, vp, $1, NULL, $6);

			// check argv
			if (vp && strncmp((*vp)[vp->size()-1], "...", 3) == 0) {
				code_top->set_argv_on();
			}
			
			g_ctl->decode_func_start();
		}
	'{' decode_pattern_stmt_list '}'
		{
			g_ctl->decode_end();
			parserCode::pop_code_stack();
		}
	;
/*}}}*/

lambda_object:/*{{{*/
	lambda_define_header statement_block
		{
			parserCode::pop_code_stack();
			$$ = $1;
		}
	| lambda_context_header statement_block
		{
			parserCode::pop_code_stack();
			$$ = $1;
		}
	| lambda_decode_header '{' decode_pattern_stmt_list '}'
		{
			g_ctl->decode_end();
			parserCode::pop_code_stack();
			$$ = $1;
		}
	| lambda_parse_header '{' bnf_stmt_list '}'
		{
			vector<char>& def = parserCode::get_def();
			parserCode::pop_code_stack();
			$$ = $1;

			parse_t* pp = (parse_t*)$3;
			bool ret = pp->process($1);
			if (ret == false) {
				throw g_parser->strdup("build so failed");
			}
		}
	;
/*}}}*/

lambda_define_header:/*{{{*/
	LAMBDA opt_argument_list opt_superclass
		{
			name_list_t* params = (name_list_t*)$2;
			name_list_t* supers = (name_list_t*)$3;

			static int count = 1;
			char buff[1024];
			snprintf(buff, 1024, "#%d_lambda", count++);
			const char* name = g_parser->strdup(buff);

			parserCode::push_code_stack(name, params, 0, supers);

			// check argv
			if (params && strncmp((*params)[params->size()-1], "...", 3) == 0) {
				code_top->set_argv_on();
			}

			$$ = name;
		}
	;
/*}}}*/

lambda_context_header:/*{{{*/
	LAMBDA '.' object_path opt_argument_list opt_superclass 
		{
			// for serial tagging
			static int count = 1;
			char name[1024];
			name_list_t* supers = (name_list_t*)$5;

			snprintf(name, 1024, "__%s_%d_context", g_parser->module_name.c_str(), count++);

			name_list_t* vp = (name_list_t*)$4;
			map<string, int> pos_map;
			const char* cp = lexer->get_context(pos_map);
			code_top->push_context_stack($3, cp, name, vp, 0, supers, NULL, pos_map);

			// check argv
			if (vp && strncmp((*vp)[vp->size()-1], "...", 3) == 0) {
				code_top->set_argv_on();
			}

			$$ = name;
		}
	;
/*}}}*/

lambda_decode_header:/*{{{*/
	LAMBDA '.' DECODE opt_argument_list
		{
			name_list_t* vp = (name_list_t*)$4;

			static int count = 1;
			char buff[1024];
			snprintf(buff, 1024, "#%d_decode_lambda", count++);
			const char* name = g_parser->strdup(buff);
			parserCode::push_code_stack(name, vp);

			// check argv
			if (vp && strncmp((*vp)[vp->size()-1], "...", 3) == 0) {
				code_top->set_argv_on();
			}
			
			g_ctl->decode_func_start();

			$$ = name;
		}
	;
/*}}}*/

lambda_parse_header:/*{{{*/
	LAMBDA '.' PARSE opt_argument_list
		{
			name_list_t* vp = (name_list_t*)$4;

			// check argv
			if (vp && strncmp((*vp)[vp->size()-1], "...", 3) == 0) {
				throw g_parser->strdup("argv not allowed in parse object");
			}

			if (vp == NULL) {
				throw g_parser->strdup("at least 1 argument needed in parse object");
			}

			static int count = 1;
			char buff[1024];
			snprintf(buff, 1024, "#%d_parse_lambda", count++);
			const char* name = g_parser->strdup(buff);
			parserCode::push_code_stack(name, vp);

			$$ = name;
		}
	;
/*}}}*/

opt_superclass:/*{{{*/
	  // empty
		{
			$$ = 0;
		}
	| ':' superclass_path_list
		{
			$$ = $2;
		}
	;
/*}}}*/

superclass_path_list:/*{{{*/
	  superclass_path_list ',' superclass_path
		{
			name_list_t* vs = (name_list_t*)$1;
			vs->push_back($3);
			$$ = vs;
		}
	| superclass_path
		{
			name_list_t* vs = g_parser->new_name_list();
			vs->push_back($1);
			$$ = vs;
		}
	;
/*}}}*/

superclass_path:/*{{{*/
	superclass_path '.' name_or_string
		{
			char buff[1024];
			snprintf(buff, 1024, "%s.%s", $1, $3);
			$$ = g_parser->strdup(buff);
		}
	| name_or_string
		{
			char* cp = code_top->find_in_space($1);
			if (cp == NULL) {
				char buff[1024];
				snprintf(buff, 1024, "can't find parent module %s in line: %d", $1, g_parser->lineno);
				throw g_parser->strdup(buff);
			}

			$$ = cp;
		}
	;
/*}}}*/

opt_argument_list:/*{{{*/
	  // empty
		{
			$$ = 0;
		}
	| '(' ')'	
		{
			$$ = 0;
		}
	| '(' argv_name ')'	
		{
			name_list_t* vs = g_parser->new_name_list();
			vs->push_back($2);
			$$ = vs;
		}
	| '(' name_list ')'
		{
			$$ = $2;
		}
	| '(' name_list ',' argv_name ')'
		{
			name_list_t* vs = (name_list_t*)$2;
			vs->push_back($4);
			$$ = vs;
		}
	;
/*}}}*/

argv_name:/*{{{*/
	TRIPLE_DOT name
		{
			char buff[1024];
			snprintf(buff, 1024, "...%s", $2);
			$$ = g_parser->strdup(buff);
		}
	;
	/*}}}*/

name_list:/*{{{*/
	name_list ',' name
		{
			name_list_t* vs = (name_list_t*)$1;
			vs->push_back($3);
			$$ = vs;
		}
	| name
		{
			name_list_t* vs = g_parser->new_name_list();
			vs->push_back($1);
			$$ = vs;
		}
	;
/*}}}*/

if_elif_else_stmt:/*{{{*/
	if_stmt
		{
			g_ctl->if_end();
		}
	| if_stmt else_stmt
		{
			g_ctl->else_end();
		}
	| if_stmt elif_stmt_list else_stmt
		{
			g_ctl->else_end();
			for(int i=0; i<$2; i++)
				g_ctl->else_end();
		}
	| if_stmt elif_stmt_list
		{
			g_ctl->if_end();
			for(int i=0; i<$2; i++)
				g_ctl->else_end();
		}
	;
/*}}}*/

elif_stmt_list:/*{{{*/
	elif_stmt_list elif_stmt
		{
			$$ = $1 + 1;
		}
	| elif_stmt
		{
			$$ = 1;
		}
	;
/*}}}*/

elif_stmt:/*{{{*/
	ELIF
		{
			g_ctl->else_start();
		}
	bool_expr 
		{
			g_ctl->if_start();
		}
	statement_block
	;
/*}}}*/

else_stmt:/*{{{*/
	ELSE
		{
			g_ctl->else_start();
		}
	statement_block
	;
/*}}}*/

if_stmt:/*{{{*/
	IF bool_expr 
		{
			g_ctl->if_start();
		}
	statement_block
	;
/*}}}*/

do_stmt:/*{{{*/
	DO	
		{
			g_ctl->do_start();
		}
	statement_block WHILE bool_expr ';'
		{
			g_ctl->do_end();
		}
	;
/*}}}*/

times_stmt:/*{{{*/
	expression TIMES DO
		{
			g_ctl->times_start();
		}
	statement_block 
		{
			g_ctl->times_end();
		}
	;
/*}}}*/

while_stmt:/*{{{*/
	WHILE		
		{
			g_ctl->while_start_1();
		}
	bool_expr 
		{
			g_ctl->while_start_2();
		}
	statement_block
		{
			g_ctl->while_end();
		}
	;
/*}}}*/

for_stmt:/*{{{*/
	FOR lvar IN object 
		{
			g_ctl->for_start($2);
		}
	statement_block
		{
			g_ctl->for_end();
		}
	| FOR lvar ',' lvar IN object 
		{
			g_ctl->for_start_2($2, $4);
		}
	statement_block
		{
			g_ctl->for_end();
		}
	;
	/*}}}*/

expression_stmt:/*{{{*/
	expression_list ';'
	;
/*}}}*/

expression_list:/*{{{*/
	expression_list ',' expression
		{
			$$ = $1 + 1;
		}
	| expression
		{
			$$ = 1;
		}
	;
/*}}}*/

expression:/*{{{*/
	  assign_expr
	;
/*}}}*/

assign_expr:	/*{{{*/
	  lvar assign_type 
		{
			if ($2 != '=') {
				g_op->push_lvar($1);
			}
		}
	  expression
		{
			switch ($2)
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_local($1);
		}
	| postfix_object '.' name_or_string assign_type 
		{
			g_op->clear_last_find_position();
			if ($4 != '=') {
				g_op->dup();
				g_op->find_member($3);
			}
		}
	  expression
		{
			switch ($4)
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member($3);
		}
	| postfix_object '.' reserved_object assign_type
		{
			if ($4 != '=') {
				g_op->dup();
				g_op->find_reserved($3);
			}
		}
	  expression
		{
			switch ($4)
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved($3);
		}
	| postfix_object '[' slice_expression ']' assign_type 
		{
			if ($5 != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(false);
			}
		}
	  expression
		{
			switch ($5)
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			if ($5 != '=') {
				g_op->do_rc_dec();
			}

			g_op->assign_list(false);
		}
	| postfix_object '[' slice_expression IR_BRACKET assign_type 
		{
			if ($5 != '=') {
				g_op->dup2(); 
				g_op->do_rc_inc();
				g_op->listat(true);
			}
		}
	  expression
		{
			switch ($5)
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			if ($5 != '=') {
				g_op->do_rc_dec();
			}

			g_op->assign_list(true);
		}
	| DOUBLE_DOT name_or_string assign_type
		{
			g_op->push_reserved(OP_PUSH_OWNER);

			if ($3 != '=') {
				g_op->dup(); 
				g_op->find_member($2);
			}
		}
	  expression
		{
			switch ($3)
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member($2);
		}
	| DOUBLE_DOT reserved_object assign_type
		{
			g_op->push_reserved(OP_PUSH_OWNER);

			if ($3 != '=') {
				g_op->dup(); 
				g_op->find_reserved($2);
			}
		}
	  expression
		{
			switch ($3)
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved($2);
		}
	| '.' name_or_string assign_type
		{
			g_op->push_reserved(OP_PUSH_MY);

			if ($3 != '=') {
				g_op->dup(); 
				g_op->find_member($2);
			}
		}
	  expression
		{
			switch ($3)
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_member($2);
		}
	| '.' reserved_object assign_type
		{
			g_op->push_reserved(OP_PUSH_MY);

			if ($3 != '=') {
				g_op->dup(); 
				g_op->find_reserved($2);
			}
		}
	  expression
		{
			switch ($3)
			{
			case '+': g_op->add(); break;
			case '-': g_op->sub(); break;
			case '*': g_op->mul(); break;
			case '/': g_op->div(); break;
			}

			g_op->assign_reserved($2);
		}
	| bool_expr
	;
/*}}}*/

assign_type:/*{{{*/
	 '='
		{
			$$ = '='; 
		}
	| ADD_ASSIGN
		{ 
			$$ = '+'; 
		}
	| SUB_ASSIGN
		{ 
			$$ = '-'; 
		}
	| MUL_ASSIGN
		{ 
			$$ = '*'; 
		}
	| DIV_ASSIGN
		{ 
			$$ = '/'; 
		}
	;			 
/*}}}*/

bool_expr:/*{{{*/
	or_expr
	;
/*}}}*/

or_expr:/*{{{*/
	or_expr OR 
		{
			g_op->dup();
			g_ctl->if_start(false);
		}
	and_expr
		{
			g_op->do_or();
			g_ctl->if_end();
		}
	| and_expr
	;
/*}}}*/

and_expr:
	and_expr AND 
		{
			g_op->dup();
			g_ctl->if_start();
		}
	bit_or_expr
		{
			g_op->do_and();
			g_ctl->if_end();
		}
	| bit_or_expr
	;


bit_or_expr:
	bit_or_expr '|' bit_xor_expr
		{
			g_op->bit_or();
		}
	| bit_xor_expr
	;

bit_xor_expr:
	bit_xor_expr '^' bit_and_expr
		{
			g_op->bit_xor();
		}
	| bit_and_expr
	;

bit_and_expr:
	bit_and_expr '&' not_expr
		{
			g_op->bit_and();
		}
	| not_expr
	;

not_expr:/*{{{*/
	'!' logical_compare_expr
		{
			g_op->do_not();
		}
	| logical_compare_expr
	;
/*}}}*/

logical_compare_expr:/*{{{*/
	logical_compare_expr GT logical_eq_expr
		{
			g_op->gt();
		}
	| logical_compare_expr GE logical_eq_expr
		{
			g_op->ge();
		}
	| logical_compare_expr LT logical_eq_expr
		{
			g_op->lt();
		}
	| logical_compare_expr LE logical_eq_expr
		{
			g_op->le();
		}
	| logical_eq_expr
	;
/*}}}*/

logical_eq_expr:/*{{{*/
	logical_eq_expr EQ numeric_expr
		{
			g_op->eq();
		}
	| logical_eq_expr NEQ numeric_expr
		{
			g_op->neq();
		}
	| numeric_expr
	;
/*}}}*/

numeric_expr:/*{{{*/
	add_expr
	;
/*}}}*/

add_expr:/*{{{*/
	add_expr '+' mul_expr
		{
			g_op->add();
		}
	| add_expr '-' mul_expr
		{
			g_op->sub();
		}
	| mul_expr
	;
/*}}}*/

mul_expr:/*{{{*/
	  mul_expr '*' object
		{
			g_op->mul();
		}
	| mul_expr '/' object
		{
			g_op->div();
		}
	| mul_expr '%' object
		{
			g_op->mod();
		}
	| unary_expr
	;
/*}}}*/

unary_expr:/*{{{*/
	  '-'
		{
			unary_minus = true;
		}
	  object 
		{
			if (unary_minus)
				g_op->minus();

			unary_minus = false;
		} %prec UMINUS
	| '+' object
	| object
	;
/*}}}*/

list:/*{{{*/
	'[' ']'
		{
			g_op->make_list(0);
		}
	| '[' expr_extract_list ']'
		{
			g_op->make_list($2);
		}
	| '[' expr_extract_list ','']'
		{
			g_op->make_list($2);
		}
	| '[' expression DOUBLE_DOT expression ']'
		{
			g_op->make_list(-2);
		}
	| '[' expression DOUBLE_DOT expression ':' expression ']'
		{
			g_op->make_list(-3);
		}
	| sbf
	| '[' ',' ']'
		{
			g_op->make_list(0);
		}
	;
/*}}}*/

tuple:/*{{{*/
	'(' expr_extract_list ',' expr_or_extract ')'
		{
			g_op->make_tuple($2 + 1);
		}
	| '(' expr_extract_list ',' ')'
		{
			g_op->make_tuple($2);
		}
	| '(' expression DOUBLE_DOT expression ')'
		{
			g_op->make_tuple(-2);
		}
	| '(' expression DOUBLE_DOT expression ':' expression ')'
		{
			g_op->make_tuple(-3);
		}
	| '(' ',' ')'
		{
			g_op->make_tuple(0);
		}
	;
/*}}}*/

map:/*{{{*/
	'{' pair_list '}'
		{
			g_op->make_map($2);
		}
	| '{' pair_list ',' '}'
		{
			g_op->make_map($2);
		}
	| '{' ',' '}'
		{
			g_op->make_map(0);
		}
	;
/*}}}*/

sbf:/*{{{*/
	'%''[' 
		{
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		}
	sbf_result ':' 
		{
			g_ctl->sbf_rule_start();
		}
	sbf_rule_list ']'
		{
			g_ctl->sbf_end();
			g_lvar_nil_check++;
		}
	;
/*}}}*/

sbf_result:/*{{{*/
	expression
	;
/*}}}*/

sbf_rule_list:/*{{{*/
	sbf_rule_list ',' sbf_rule
	| sbf_rule
	;
/*}}}*/

sbf_rule:/*{{{*/
	bool_expr
		{
			g_ctl->sbf_rule();
		}
	| in_expr
		{
			g_ctl->sbf_in();
		}
	;
/*}}}*/

in_expr:/*{{{*/
	lvar LEFT_ARROW expression
		{
			g_ctl->sbf_list_gen($1);
		}
	| lvar LEFT_ARROW range_expr
		{
			g_ctl->sbf_range_gen($1);
		}
	;
/*}}}*/

range_expr:/*{{{*/
	range_expr_sub ':' expression
	| range_expr_sub
		{
			g_op->push_integer(1);
		}
	;
/*}}}*/

range_expr_sub:/*{{{*/
	expression '~' expression
	| expression '~' 
		{
			g_op->push_nil();
		}
	| '~'
		{
			g_op->push_nil();
		} 
	  expression 
	;  
/*}}}*/

pair_list:/*{{{*/
	  pair_list ',' pair_expression
		{
			$$ = $1 + 1;
		}
	| pair_expression
		{
			$$ = 1;
		}
	;
/*}}}*/

pair_expression:/*{{{*/
	expression ':' expression
	;
/*}}}*/

primary_object:/*{{{*/
	  list
	| tuple
	| map
	| lambda_object
		{
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member($1);
		}
	| lvar
		{
			if (g_op->check_lvar($1) == false) {
				throw g_parser->strdup(kyString::sprintf("variable %s is not defiend", $1).c_str());
			}

			g_op->push_lvar($1);
		}
	| number
		{
			g_op->push_integer($1);
		}
	| big_number
		{
			g_op->push_bignum('+', $1);
		}
	| real
		{
			g_op->push_real($1);
		}
	| regex
		{
			g_op->make_regex();
		}
	| string
		{
			// already in stack
		}
	| reserved_object
		{
			g_op->push_reserved($1);
		}
	| TRUE
		{
			g_op->push_boolean(true);
		}
	| FALSE
		{
			g_op->push_boolean(false);
		}
	| NIL_
		{
			g_op->push_nil();
		}
	| '(' expression ')'
	| reserved_functions
	;
/*}}}*/

reserved_functions:/*{{{*/
	eval_function
	| compile_function
	;
/*}}}*/

eval_function:/*{{{*/
	EVAL '(' expression ')'
		{
			g_op->eval();
		}
	;
/*}}}*/

compile_function:/*{{{*/
	COMPILE '(' expression_list ')'
		{
			if ($3 != 2) {
				throw g_parser->strdup("insufficient parameter to compile");
			}
			g_op->compile();
		}
	;
/*}}}*/

postfix_object:/*{{{*/
	  postfix_object '.' name_or_string
		{
			g_op->set_last_find_position();
			g_op->find_member($3);
		}
	| postfix_object '.' reserved_object
		{
			g_op->find_reserved($3);
		}
	| postfix_object 
		{
			g_op->clear_last_find_position();
		}
	  calling_body
		{
			g_op->call($3);
		}
	| postfix_object '[' slice_expression ']'
		{
			g_op->listat(false);
		}
	| postfix_object '[' slice_expression IR_BRACKET
		{
			g_op->listat(true);
		}
	| DOUBLE_DOT name_or_string
		{
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_member($2);
		}
	| DOUBLE_DOT reserved_object
		{
			g_op->push_reserved(OP_PUSH_OWNER);
			g_op->find_reserved($2);
		}
	| '.' name_or_string
		{
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member($2);
		}
	| '.' reserved_object
		{
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_reserved($2);
		}
	| name
		{
			if (g_op->push_mvar_using_space($1) == false) {
				throw g_parser->strdup("invalid object name in name'string' format");
			}
		}
	  string
		{
			g_op->clone(1);
		}
	| postfix_object '.' CLONE calling_body
		{
			g_op->clone($4);

			// this is not normal function call (virtual function call)
			// so it should mark that don't fast popping
			g_op->disable_fast_pop();
		}
	| primary_object
	;
/*}}}*/

slice_expression:/*{{{*/
	  expression ':' expression
		{
			g_op->make_pair();
		}
	| ':'
		{
			g_op->push_integer(0);
		}
	  expression
		{
			g_op->make_pair();
		}
	| expression ':'
		{
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
	| ':'
		{
			g_op->push_integer(0);
			g_op->push_integer(INT_MAX);
			g_op->make_pair();
		}
	| expression
	;
/*}}}*/

calling_body:/*{{{*/
	  '(' ')'
		{
			$$ = 0;
		}
	| '(' expr_extract_list ')'
		{
			$$ = $2;
		}
	;
/*}}}*/

expr_extract_list:/*{{{*/
	expr_extract_list ',' expr_or_extract
		{
			$$ = $1 + 1;
		}
	| expr_or_extract
		{
			$$ = 1;
		}
	;
/*}}}*/

expr_or_extract:/*{{{*/
	expression
	| extract
	;
/*}}}*/

extract:/*{{{*/
	expression TRIPLE_DOT
		{
			g_op->extract();
		}
	;
/*}}}*/

object:/*{{{*/
	postfix_object
		{
			g_op->fix_last_find_position();
		}
	;
/*}}}*/

reserved_object:/*{{{*/
	OWNER
		{
			$$ = OP_PUSH_OWNER;
		}
	| CALLER
		{
			$$ = OP_PUSH_CALLER;
		}
	| ROOT
		{
			$$ = OP_PUSH_ROOT;
		}
	| MODULE
		{
			$$ = OP_PUSH_MODULE;
		}
	| MY
		{
			$$ = OP_PUSH_MY;
		}
	;
/*}}}*/

lvar:/*{{{*/
	name
	;
/*}}}*/

format_string:/*{{{*/
	  format_string string_var_object
	| STRING_VAR_HEAD
		{
			g_op->push_string($1);
		}
	;			 
/*}}}*/

re_format_string:/*{{{*/
	  re_format_string string_var_object
	| RE_STRING_VAR_HEAD
		{
			g_op->push_string($1);
		}
	;			 
/*}}}*/

string_var_object:/*{{{*/
	 '$' '{' expression STRING_VAR_TAIL
		{
			g_op->add();

			g_op->push_string($4);

			g_op->add();
		}
	;			 
/*}}}*/

regex:/*{{{*/
	 RE_STRING
		{
			g_op->push_string($1);
		}
	| re_format_string
	;
/*}}}*/

string: // char* /*{{{*/
	 STRING
		{
			g_op->push_string($1);
		}
	| format_string
	| HEX_STRING
		{
			g_op->push_string($1);
		}
	;
/*}}}*/

name: // char* /*{{{*/
	NAME
	;
/*}}}*/

number: /*{{{*/
	NUMBER
	;
/*}}}*/

big_number: /*{{{*/
	BIG_NUMBER 
	;
/*}}}*/

real: /*{{{*/
	REAL 
	;
/*}}}*/

%%


