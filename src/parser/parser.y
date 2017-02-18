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


//TEMP
#include "orcaRoot.h"

parserException s_ex;
parserException* g_ex = &s_ex;

// For parser
bool unary_minus = false;

int g_lvar_nil_check = 0;
int g_bnf_right_num = 0;

using namespace std;


const char* get_context();

%}

%union 
{
	const char* cp;
	int integer;
	double real;
	void* vector_cp;	
	struct bnf* bp;	
	struct cp2_t cp2; 
	struct int2_t int2;
};

%error-verbose


// type define/*{{{*/
%type <cp> name
%type <cp> name_or_string
%type <cp> lvar
%type <cp> p_var
%type <cp> object_path
%type <cp> big_number
%type <cp> minus_big_number
%type <cp> lambda_define_header
%type <cp> lambda_decode_header
%type <cp> lambda_parse_header

%type <bp> terminal
%type <bp> non_terminal
%type <bp> action_code
%type <bp> bnf_left
%type <bp> bnf_node

%type <integer> number					// integer
%type <integer> minus_number					// integer
%type <integer> expression_stmt			// num of expr
%type <integer> expression_list			// num of expr
%type <integer> pair_list				// num of expr
%type <integer> opt_expr_list			// num of expr
%type <integer> opt_superclass			// num of superclass
%type <integer> elif_stmt_list			// num of elif stmt
%type <integer> reserved_object			// reserved object enum value
%type <integer> calling_body			// num of arguemnts
%type <integer> def						// flag
%type <integer> assign_type				// '=', '+'...
%type <integer> pattern_list			// num of pattern

%type <real> real
%type <real> minus_real

%type <vector_cp> name_list
%type <vector_cp> opt_argument_list


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
%token SWITCH
%token DECODE
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
%token ONCE 
%token EVAL
%token LAMBDA

%token<cp> NAME
%token<cp> STRING
%token<cp> FORMAT_STRING_HEAD
%token<cp> FORMAT_STRING_TAIL
%token<cp> RE_STRING
%token<cp> RE_FORMAT_STRING_HEAD
%token<cp> HEX_STRING
%token<cp> SHELL_STRING_HEAD

%token<cp2> CONTEXT 

%token<integer> NUMBER
%token<integer> MINUS_NUMBER
%token<cp> BIG_NUMBER
%token<cp> MINUS_BIG_NUMBER
%token<real> REAL
%token<real> MINUS_REAL
/*}}}*/

%%

statement_list:/*{{{*/
	statement_list statement
	| statement_list statement_block
	| statement
	;
/*}}}*/

statement_or_block/*{{{*/
	: statement 
	| statement_block
	;
/*}}}*/

statement_block:/*{{{*/
	'{' statement_list '}'
	| '{' '}'
	;
/*}}}*/

open_statement_block:/*{{{*/
	statement_list '}'
	| '}'
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
	| ';'
	;
/*}}}*/

scope_stmt:/*{{{*/
	expression
		{
			g_op->do_scope_start();
		}
	statement_block
		{
			g_op->do_scope_end();
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
	;
/*}}}*/

parallel_option: /* empty *//*{{{*/
		{
			g_op->push_integer(0);	// by
			g_op->push_integer(1);	// per
		}
	| NAME expression
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
				yyerror("parallel option 'by' or 'per' expected");
			}
		} 
	| NAME expression NAME expression
		{
			if (strncmp($1, "by", 2) != 0) {
				yyerror("parallel option 'by' expected");
			}

			if (strncmp($3, "per", 3) != 0) {
				yyerror("parallel option 'per' expected");
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
			g_op->find_member("run");
		}
	shell_string 
		{	
			g_op->call(1);
		}
	;
/*}}}*/

shell_string:/*{{{*/
	  shell_string format_object
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
		}
	statement_block
		{
			g_ex->goto_end();
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
	| CATCH object_path ':' name_list
		{
			name_list_t* vp = (name_list_t*)$4;
			g_ex->catch_start($2, vp);
		}
	statement_block
		{
			g_ex->goto_finally();
		}
	| CATCH 
		{
			g_ex->catch_start(NULL);
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
			g_ex->do_throw($2, 0);
		}
	| THROW object_path ',' expression_list ';'
		{
			g_ex->do_throw($2, $4);
		}
	;
/*}}}*/

using_stmt:/*{{{*/
	USING object_path ';'
		{
			code_top->using_object($2, NULL);
		}
	| USING object_path STRING ';'
		{
			code_top->using_object($2, $3);
		}
	;
/*}}}*/

object_path:/*{{{*/
	object_path '.' name_or_string
		{
			char buff[1024];
			sprintf(buff, "%s.%s", $1, $3);
			$$ = g_parser->strdup(buff);
		}
	| name_or_string
		{
			$$ = $1;
		}
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
	;
/*}}}*/

opt_expr_list:/*{{{*/
	/* empty */
		{
			$$ = 0;
		}
	| expression_list
		{
			$$ = $1;
		}
	;
/*}}}*/

selection_stmt:/*{{{*/
	  if_elif_else_stmt
	| decode_stmt
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
	| bnf_stmt
	;
/*}}}*/

bnf_stmt:/*{{{*/
	bnf_left 
		{
			g_parse->set_current_bnf($1);
		}
	':' bnf_right_list ';'
		{

		}
	| '~' ':' terminal ';'
		{
			bnf* b = $3;
			b->type = BNF_WS;
		}
	
	;
/*}}}*/

bnf_right_list:/*{{{*/
	bnf_right_list '|' bnf_right
	| bnf_right
	;
/*}}}*/

bnf_left:/*{{{*/
	non_terminal
	;
/*}}}*/

bnf_right:/*{{{*/
		{
			g_bnf_right_num = 1;
			g_parse->current_bnf()->add_rule();
		}
	bnf_right_
	;
	/*}}}*/

bnf_right_:/*{{{*/
	bnf_node_list
	;
/*}}}*/

bnf_node_list:/*{{{*/
	bnf_node_list bnf_node
		{
			g_bnf_right_num++;
			g_parse->current_bnf()->current_rule()->push_bnf($2);
		}
	| bnf_node
		{
			g_parse->current_bnf()->current_rule()->push_bnf($1);
		}
	;
/*}}}*/

bnf_node:/*{{{*/
	terminal
	| non_terminal
	| action_code
	;
/*}}}*/

terminal:/*{{{*/
	STRING
		{
			$$ = g_parse->get_term_bnf($1);
		}
	| RE_STRING
		{
			$$ = g_parse->get_term_bnf($1, true);
		}
	;
/*}}}*/

non_terminal:/*{{{*/
	name
		{
			string name = "`\a";
			name += $1;
			$$ = g_parse->get_nonterm_bnf(name);
		}
	;
/*}}}*/

action_code:/*{{{*/
	lambda_object
		{
			$$ = g_parse->get_action_bnf(g_bnf_right_num);
		}
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
	decode_pattern RIGHT_ARROW 
		{
			g_ctl->decode_pattern_shift();
		}
	statement_or_block 
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
	p_var ':' p_var
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

def:
	STATIC DEF
		{
			$$ = BIT_DEFINE_STATIC;
		}
	| DEF
		{
			$$ = 0;
		}
	;


name_or_string:/*{{{*/
	name
		{
			$$ = $1;
		}
	| STRING
		{
			$$ = $1;
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
	| define_header opt_superclass
		{
			if ($2) {
				code_top->make_super($2);
			}
		}
	  statement_block 
		{
			parserCode::pop_code_stack();
		}
	| def '.' name_or_string name_or_string '{'
		{
			const char* cp = get_context();
			print("get_context(): '%s'\n", cp);
			code_top->do_context($3, $4, cp);
			//TODO: fail check
		}
	| def '.' PARSE name_or_string opt_argument_list
		{
			name_list_t* vp = (name_list_t*)$5;

			// check argv
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				yyerror("argv not allowed in parse object");
			}

			if (vp == NULL) {
				yyerror("at least 1 argument needed in parse object");
			}

			parserCode::push_code_stack($4, vp);
			g_parse->do_parse_init();
		}
	'{' bnf_stmt_list '}'
		{
			vector<char>& def = parserCode::get_def();

			g_parse->make_table();
			//g_parse->dump();
			g_parse->do_parse(def);
			g_parse->cleanup();

			parserCode::pop_code_stack();
		}
	| def '.' DECODE name_or_string opt_argument_list
		{
			name_list_t* vp = (name_list_t*)$5;

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			parserCode::push_code_stack($4, vp, $1);

			if (flag_argv == true) {
				code_top->find_lvar("argv");
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

define_header:/*{{{*/
	def name_or_string opt_argument_list
		{
			name_list_t* vp = (name_list_t*)$3;

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			parserCode::push_code_stack($2, vp, $1);

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}
		}
	;
/*}}}*/

once_expr:/*{{{*/
	ONCE
		{
			g_ctl->once_start();
		}
	open_statement_block
		{
			g_ctl->once_end();
		}
	;
/*}}}*/

lambda_object:/*{{{*/
	lambda_define_header opt_superclass
		{
			if ($2) {
				code_top->make_super($2);
			}
		}
	statement_block
		{
			parserCode::pop_code_stack();
			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member($1);
		}
	| LAMBDA '.' name_or_string  '{'
		{
			// for serial tagging
			static int count = 1;
			char name[256];
			sprintf(name, "__%s_%d_context", g_parse_module_name.c_str(), count++);

			const char* cp = get_context();
			//print("get_context(): '%s'\n", cp);
			code_top->do_context($3, name, cp);
			//TODO: fail check

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member(name);
		}
	| lambda_decode_header '{' decode_pattern_stmt_list '}'
		{
			g_ctl->decode_end();
			parserCode::pop_code_stack();

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member($1);
		}
	| lambda_parse_header '{' bnf_stmt_list '}'
		{
			vector<char>& def = parserCode::get_def();

			g_parse->make_table();
			//g_parse->dump();
			g_parse->do_parse(def);
			g_parse->cleanup();

			parserCode::pop_code_stack();

			g_op->push_reserved(OP_PUSH_MY);
			g_op->find_member($1);
		}
	;
/*}}}*/

lambda_define_header:
	LAMBDA opt_argument_list
		{
			name_list_t* vp = (name_list_t*)$2;

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			static int count = 1;
			char buff[256];
			sprintf(buff, "#%d_lambda", count++);
			const char* name = g_parser->strdup(buff);
			parserCode::push_code_stack(name, vp, 0);

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}

			$$ = name;
		}
	;


lambda_decode_header:
	LAMBDA '.' DECODE opt_argument_list
		{
			name_list_t* vp = (name_list_t*)$4;

			// check argv
			bool flag_argv = false;
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				vp->pop_back();
				flag_argv = true;

				if (vp->empty()) {	// if argv only, make vp as NULL
					vp = NULL;
				}
			}

			static int count = 1;
			char buff[256];
			sprintf(buff, "#%d_decode_lambda", count++);
			const char* name = g_parser->strdup(buff);
			parserCode::push_code_stack(name, vp, 0);

			if (flag_argv == true) {
				code_top->find_lvar("argv");
				code_top->set_argv_on();
			}
			
			g_ctl->decode_func_start();

			$$ = name;
		}
	;


lambda_parse_header:
	LAMBDA '.' PARSE opt_argument_list
		{
			name_list_t* vp = (name_list_t*)$4;

			// check argv
			if (vp && strcmp((*vp)[vp->size()-1], "...") == 0) {
				yyerror("argv not allowed in parse object");
			}

			if (vp == NULL) {
				yyerror("at least 1 argument needed in parse object");
			}

			static int count = 1;
			char buff[256];
			sprintf(buff, "#%d_parse_lambda", count++);
			const char* name = g_parser->strdup(buff);
			parserCode::push_code_stack(name, vp);
			g_parse->do_parse_init();

			$$ = name;
		}
	;


opt_superclass:/*{{{*/
	  // empty
		{
			$$ = 0;
		}
	| ':' expression_list
		{
			$$ = $2;
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
	| '(' TRIPLE_DOT ')'	
		{
			name_list_t* vs = g_parser->new_name_list();
			vs->push_back("...");
			$$ = vs;
		}
	| '(' name_list ')'
		{
			$$ = $2;
		}
	| '(' name_list ',' TRIPLE_DOT ')'
		{
			name_list_t* vs = (name_list_t*)$2;
			vs->push_back("...");
			$$ = vs;
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
	;
	/*}}}*/

expression_stmt:/*{{{*/
	expression_list ';'
		{ 
			$$ = $1; 
		}
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
	| once_expr
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
	| postfix_object '[' slice_expression ')' assign_type 
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

and_expr:/*{{{*/
	and_expr AND 
		{
			g_op->dup();
			g_ctl->if_start();
		}
	not_expr
		{
			g_op->do_and();
			g_ctl->if_end();
		}
	| not_expr
	;
/*}}}*/

not_expr:/*{{{*/
	'!' logical_expr
		{
			g_op->do_not();
		}
	| logical_expr
	;
/*}}}*/

logical_expr:/*{{{*/
	numeric_expr GT numeric_expr
		{
			g_op->gt();
		}
	| numeric_expr GE numeric_expr
		{
			g_op->ge();
		}
	| numeric_expr LT numeric_expr
		{
			g_op->lt();
		}
	| numeric_expr LE numeric_expr
		{
			g_op->le();
		}
	| numeric_expr EQ numeric_expr
		{
			g_op->eq();
		}
	| numeric_expr NEQ numeric_expr
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
	| add_expr minus_number
		{
			g_op->push_integer($2);
			g_op->add();
		}
	| add_expr minus_big_number
		{
			g_op->push_bignum('-', $2);
			g_op->add();
		}
	| add_expr minus_real
		{
			g_op->push_real($2);
			g_op->add();
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
		}
	| '+' object
	| object
	;
/*}}}*/

list:/*{{{*/
	'[' opt_expr_list ']'
		{
			g_op->make_list($2);
		}
	| '[' expression_list ','']'
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
	;
/*}}}*/

tuple:/*{{{*/
	'(' expression_list ',' expression ')'
		{
			g_op->make_tuple($2 + 1);
		}
	| '(' expression_list ',' ')'
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
	;
/*}}}*/

sbf:/*{{{*/
	'%''[' 
		{
			g_lvar_nil_check--;
			g_ctl->sbf_start();
		}
	sbf_result '|' 
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
	| lvar
		{
			if (g_op->check_lvar($1) == false) {
				string msg = "variable ";
				msg += $1;
				msg += " is not defined";
				yyerror(msg.c_str());
			}

			g_op->push_lvar($1);
		}
	| number
		{
			g_op->push_integer($1);
		}
	| minus_number
		{
			g_op->push_integer($1);
		}
	| big_number
		{
			g_op->push_bignum('+', $1);
		}
	| minus_big_number
		{
			g_op->push_bignum('-', $1);
		}
	| real
		{
			g_op->push_real($1);
		}
	| minus_real
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

reserved_functions:
	eval_function
	;


eval_function:
	EVAL '(' expression ')'
		{
			g_op->eval();
		}
	;

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
	| postfix_object '[' slice_expression ')'
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
				yyerror("invalid object name in name'string' format");
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
	| '(' expression_list ')'
		{
			$$ = $2;
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
		{
			$$ = $1;
		}
	;
/*}}}*/

format_string:/*{{{*/
	  format_string format_object
	| FORMAT_STRING_HEAD
		{
			g_op->push_string($1);
		}
	;			 
/*}}}*/

re_format_string:/*{{{*/
	  re_format_string format_object
	| RE_FORMAT_STRING_HEAD
		{
			g_op->push_string($1);
		}
	;			 
/*}}}*/

format_object:/*{{{*/
	 '$' '{' expression FORMAT_STRING_TAIL
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
		{
			$$ = $1;
		}
	;
/*}}}*/

minus_number: /*{{{*/
	MINUS_NUMBER
		{
			$$ = $1;
		}
	;
/*}}}*/

number: /*{{{*/
	NUMBER
		{
			$$ = $1;
		}
	;
/*}}}*/

minus_big_number: /*{{{*/
	MINUS_BIG_NUMBER 
		{
			$$ = $1;
		}
	;
/*}}}*/

big_number: /*{{{*/
	BIG_NUMBER 
		{
			$$ = $1;
		}
	;
/*}}}*/

real: /*{{{*/
	REAL 
		{
			$$ = $1;
		}
	;
/*}}}*/

minus_real: /*{{{*/
	MINUS_REAL 
		{
			$$ = $1;
		}
	;
/*}}}*/

%%


