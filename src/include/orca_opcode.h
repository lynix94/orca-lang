/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orca_opcode.h - op codes 

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_OP_CODE
#define _DEF_ORCA_OP_CODE

// op code
#define OP_NOP						0x00
#define OP_CALL						0x02
#define OP_CALL_					0x03
#define OP_ASSIGN_LOCAL				0x04
#define OP_ASSIGN_LOCAL_			0x05
#define OP_ASSIGN_MEMBER			0x06
#define OP_ASSIGN_MEMBER_			0x07
#define OP_ASSIGN_RESERVED			0x08
#define OP_ASSIGN_RESERVED_			0x09
#define OP_ASSIGN_LIST				0x0A
#define OP_ASSIGN_LIST_				0x0B
#define OP_ASSIGN_LIST_IR			0x0C
#define OP_ASSIGN_LIST_IR_			0x0D

#define OP_ADD						0x10
#define OP_MUL						0x11
#define OP_SUB						0x12
#define OP_DIV						0x13
#define OP_AND						0x14		
#define OP_OR						0x15
#define OP_MINUS					0x16
#define OP_ROTATE					0x17
#define OP_DUP						0x18
#define OP_DUP2						0x19
#define OP_NOT						0x1A
#define OP_MOD						0x1B

#define OP_JMP_TRUE					0x20	
#define OP_JMP_FALSE				0x21
#define OP_GT						0x22
#define OP_GE						0x23
#define OP_LT						0x24			
#define OP_LE						0x25
#define OP_EQ						0x26
#define OP_NEQ						0x27
#define OP_JMP						0x2B

#define OP_PUSH_LVAR				0x30
#define OP_PUSH_MVAR				0x31
#define OP_PUSH_OVAR				0x32	
#define OP_PUSH_CVAR				0x33
#define OP_PUSH_INT					0x34
#define OP_PUSH_STR					0x35
#define OP_PUSH_OWNER				0x36
#define OP_PUSH_CALLER				0x37
#define OP_PUSH_ROOT				0x38
#define OP_PUSH_MODULE				0x39
#define OP_FIND_MEMBER				0x3A
#define OP_FIND_RESERVED			0x3B
#define OP_PUSH_PARENT				0x3C
#define OP_PUSH_MY					0x3D
#define OP_PUSH_BOOLEAN				0x3E
#define OP_PUSH_REAL				0x3F
#define OP_PUSH_BIGNUM				0x40
#define OP_PUSH_LONG_STR			0x41
#define OP_PUSH_NIL					0x42
#define OP_FIND_MEMBER_LAST			0x43

#define OP_MAKE_LIST				0x50
#define OP_MAKE_TUPLE				0x51
#define OP_CLONE					0x52
#define OP_LIST_AT					0x53
#define OP_LIST_AT_IR				0x54
#define OP_MAKE_PAIR				0x55
#define OP_MAKE_REGEX				0x56
#define OP_MAKE_MAP					0x57
#define OP_MAKE_LONG_LIST			0x58
#define OP_MAKE_LONG_TUPLE			0x59
#define OP_MAKE_LONG_MAP			0x5A

#define OP_RETURN					0x60
#define OP_RETURN_NIL				0x61
#define OP_FOR						0x62
#define OP_FOR_END					0x63
#define OP_FOR_POP					0x64
#define OP_THROW					0x65
#define OP_THROW_WITH_ARG			0x66
#define OP_MARK_TRY					0x67
#define OP_DONE_TRY					0x68
#define OP_SCOPE_START				0x69
#define OP_SCOPE_END				0x6A
#define OP_PARALLEL_START			0x6B
#define OP_PARALLEL_END				0x6C
#define OP_PARALLEL_FOR				0x6D
#define OP_MARK_STACK				0x6E
#define OP_MARK_STACK_POP			0x6F

#define OP_DECODE					0x70
#define OP_DECODE_END				0x71
#define OP_PATTERN_START			0x72
#define OP_MATCH_EXPR				0x73
#define OP_MATCH_EXPR_W_SHIFT		0x74
#define OP_MATCH_N_ASSIGN			0x75	
#define OP_MATCH_N_ASSIGN_W_SHIFT	0x76
#define OP_SHIFT_ALL				0x77
#define OP_CUT_LIST					0x78
#define OP_DECODE_CHECK_REMAIN		0x79
#define OP_PARSE_INIT				0x7A
#define OP_PARSE					0x7B
#define OP_ONCE						0x7C
#define OP_ONCE_END					0x7D
#define OP_FOR_SUB					0x7E

#define OP_SBF						0x80
#define OP_SBF_LIST					0x81
#define OP_SBF_RANGE				0x82
#define OP_SIMPLE_RETURN			0x83

#define OP_RC_INC					0x90
#define OP_RC_DEC					0x91

#define OP_DUMP_STACK				0xF0
#define OP_DUMP_LOCAL				0xF1
#define OP_POP_STACK				0xF2
#define OP_POP_STACK_SILENT			0xF3



// define code
#define OP_DEF_START				0xC1
#define OP_DEF_END					0xC3
#define OP_REG						0xC4		
#define OP_DEF_CODE					0xC6
#define OP_DEF_SUPER				0xC7
#define OP_USING					0xC8
#define OP_USING_EXT				0xC9
#define OP_DEF_START_PARSER			0xCA
#define OP_DEF_INIT					0xCB
#define OP_CONTEXT					0xCC

#endif

