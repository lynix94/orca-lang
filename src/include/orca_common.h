/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orca_common.h - common define & struct which are used in both parser & vm

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_COMMON
#define _DEF_ORCA_COMMON

#include <map>
#include <string.h>

using namespace std;

//#define _VM_DEBUG_

#ifdef _VM_DEBUG_
#define PRINT0(f)					printf(f)
#define PRINT1(f, a)				printf(f, a)
#define PRINT2(f, a, b)				printf(f, a, b)
#define PRINT3(f, a, b, c)			printf(f, a, b, c)
#define PRINT4(f, a, b, c, d)		printf(f, a, b, c, d)
#define PRINT5(f, a, b, c, d, e)	printf(f, a, b, c, d, e)
#else
#define PRINT0(f)
#define PRINT1(f, a)
#define PRINT2(f, a, b)	
#define PRINT3(f, a, b, c)
#define PRINT4(f, a, b, c, d)
#define PRINT5(f, a, b, c, d, e)
#endif


#define ONE_K	1024
#define ONE_M	ONE_K * ONE_K

#define ORCA_VERSION_STRING	"0.5"

#define MAGIC_NO		0x19760108
#define ORCA_VERSION	0x00050000

#define BIT_DEFINE_STATIC	0x00000001
#define BIT_DEFINE_INIT		0x00000004
#define BIT_DEFINE_NAME_CHANGED		0x00000008
#define BIT_DEFINE_PARSE		0x00000010
#define BIT_IN_ATTR			0x10000000

struct OrcaHeader
{
	OrcaHeader() { }
	OrcaHeader(int d, int c, int dbg);

	char name[5];
	char dummy[3];
	unsigned int magic;
	unsigned int version;
	int def_size;
	int code_size;
	int debug_size;
};

struct CodeHeader
{
	CodeHeader() :	frame_size(0),
					argument_size(0),
					flag_argv(0),
					dummy(0) {}
					
	unsigned short frame_size;
	unsigned short argument_size;
	char  flag_argv;
	char  dummy;
};


// impl at parserParser.cpp
char* ll2l(long long i);
char* i2l(int i);
char* s2l(short s);
short l2s(char* c);
short l2s(const char* c);
short htols(short in);
int htoli(int in);
short ltohs(short in);


struct cp_cmp : public binary_function<const char*, const char*, bool>
{
	bool operator()(const char* l, const char* r) const {
		return (strcmp(l, r) < 0);
	}
};

template <typename T>
struct cp_map
{
	typedef map<const char*, T, cp_cmp> Type;
};

#endif

