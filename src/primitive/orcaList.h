/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaList.h - list type

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_LIST
#define _DEF_ORCA_LIST

#include "orcaObject.h"
#include "orcaTuple.h"
#include "orcaListIter.h"

#define TO_LIST(a)	static_cast<orcaList*>(a)

class orcaForStack;

bool islist(orcaData d);

class LIBORCA_API orcaList : public orcaObject
{
friend class orcaForStack;
friend class orcaListIter;

public:
	orcaList();
	orcaList(void* vp);
	orcaObject* v_clone();
	virtual ~orcaList();

	// internal
	virtual orcaData& at(int idx); 
	virtual orcaData slice(int start, int end, bool include_right);
	virtual orcaData slice(orcaListIter start, orcaListIter end);
	void update(int indx, orcaData& d);
	void update_range(int start, int end, bool include_right, orcaData& d);
	void sort(orcaVM* vm, orcaData fun);

	// member function
	orcaData ex_size(orcaVM* vm, int n);
	orcaData ex_tuple(orcaVM* vm, int n);
	orcaData ex_push_back(orcaVM* vm, int n);
	orcaData ex_pop_back(orcaVM* vm, int n);
	orcaData ex_push_front(orcaVM* vm, int n);
	orcaData ex_pop_front(orcaVM* vm, int n);
	orcaData ex_find(orcaVM* vm, int n);
	orcaData ex_iter(orcaVM* vm, int n);
	orcaData ex_piter(orcaVM* vm, int n);
	orcaData ex_first(orcaVM* vm, int n);
	orcaData ex_last(orcaVM* vm, int n);
	orcaData ex_end(orcaVM* vm, int n);
	orcaData ex_sort(orcaVM* vm, int n);
	orcaData ex_empty(orcaVM* vm, int n);
	orcaData ex_clear(orcaVM* vm, int n);
	orcaData ex_channel_out(orcaVM* vm, int n);
	orcaData ex_channel_in(orcaVM* vm, int n);

	// operator
	virtual orcaData operator_add(orcaVM* vm, orcaData& p);
	virtual orcaData operator_eq(orcaVM* vm, orcaData& p);

	// etc
    bool compare(orcaVM* vm, orcaList* rhs, int len, orcaListIter it);
    orcaListIter search(orcaVM* vm, orcaList* rhs, orcaListIter it);

	void push_front(orcaData p);
	void push_back(orcaData p); 
	orcaData pop_front(); 
	orcaData pop_back();

	int get_timestamp()
	{
		return m_timestamp;
	}

	void inc_timestamp()
	{
		m_timestamp++;
	}

	virtual void string_(orcaVM* vm, string& str);
	virtual void repr(orcaVM* vm, string& str);
	void dump(); 

	// virtual 
	virtual int size();
	virtual orcaListIter begin();
	virtual orcaListIter end();

protected:
	list<orcaData> m_value;
	static cp_map<orcaData>::Type m_static_list;
	int m_timestamp;
};

#endif

