/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSbf.h - set builder form type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SBF
#define _DEF_ORCA_SBF

#include "orcaList.h"
#include "orcaStack.h"
#include "parser_common.h"

#define TO_SBF(a)	static_cast<orcaSbf*>(a)

struct range_gen
{
	range_gen(int var, orcaLocal* loc, orcaList* lp); 
	range_gen(int var, orcaLocal* loc, orcaData start, orcaData end, orcaData step = 1);

	~range_gen(); 

	bool first();
	bool next();

	orcaData start;
	orcaData end;
	orcaData curr;
	orcaData step;

	bool reverse;

	orcaList* list_p;
	orcaListIter it;

	int lvar;
	orcaLocal* local;
};


class LIBORCA_API orcaSbf : public orcaList
{
friend class orcaForStack;

public:
	orcaSbf();
	orcaSbf(void* vp);
	orcaObject* v_clone();

	virtual ~orcaSbf();

	void set_result(char* code);
	void set_code(char* code);
	void set_vm(orcaVM* vm);

	// internal
	virtual void string_(orcaVM* vm, string& str);
	virtual orcaData slice(int start, int end, bool include_right);
	virtual orcaData& at(int idx);
	virtual orcaListIter begin();
	virtual orcaListIter end();
	virtual int size();
	bool eof(int at);
	bool evaluate(int at);

	orcaData result();
	int get_eval();
	void push_gen(int var, orcaData start, orcaData end, orcaData step);
	void push_gen(int var, orcaList* op);
	void push_rule(char* addr);

	bool check();
	bool first();
	bool inc(int i);
	bool next();

private:
	int m_eval;
	bool m_done;

	//vector<orcaData> m_value;
	vector<char*> m_rule;
	vector<range_gen> m_range;

	char* m_result;
	orcaVM* m_vm;
	orcaLocal* m_local;
	char* m_code;
};

#endif

