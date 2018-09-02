/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTuple.h - tuple type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_TUPLE
#define _DEF_ORCA_TUPLE

#include "orcaObject.h"

#define TO_TUPLE(a)	static_cast<orcaTuple*>(a)
typedef vector<orcaData>::iterator orcatuple_iterator;

class orcaForStack;

class LIBORCA_API orcaTuple : public orcaObject
{
friend class orcaForStack;

public:
	orcaTuple();
	orcaTuple(void* vp);
	orcaTuple(int n);
	virtual ~orcaTuple();

	orcaObject* v_clone();

	// internal
	orcaData& at(int idx);
	orcaData slice(int start, int end, bool include_right);
	int size()
	{
		return m_value.size();
	}

	void update(int idx, orcaData d);
	void update_range(int start, int end, bool include_right, orcaData& d);

	void push_back(orcaData d) 
	{
		m_value.push_back(d);
		d.rc_inc();
	}

	bool pop_back() 
	{
		if (m_value.size() == 0) {
			return false;
		}
		m_value[m_value.size()-1].rc_dec();
		m_value.pop_back();
		return true;
	}


	// static
	orcaData ex_get_at(orcaVM* vm, int n);
	orcaData ex_set_at(orcaVM* vm, int n);
	orcaData ex_size(orcaVM* vm, int n);
	orcaData ex_list(orcaVM* vm, int n);
	orcaData ex_push_back(orcaVM* vm, int n);
	orcaData ex_pop_back(orcaVM* vm, int n);
	orcaData ex_iter(orcaVM* vm, int n);
	orcaData ex_piter(orcaVM* vm, int n);
	orcaData ex_first(orcaVM* vm, int n);
	orcaData ex_last(orcaVM* vm, int n);
	orcaData ex_end(orcaVM* vm, int n);
	orcaData ex_find(orcaVM* vm, int n);
	orcaData ex_empty(orcaVM* vm, int n);
	orcaData ex_clear(orcaVM* vm, int n);
	orcaData ex_channel_out(orcaVM* vm, int n);
	orcaData ex_channel_in(orcaVM* vm, int n);

	// operator
	virtual orcaData operator_add(orcaVM* vm, orcaData& p);
	virtual orcaData operator_eq(orcaVM* vm, orcaData& p);

	// etc
	virtual void string_(orcaVM* vm, string& str);
	virtual void repr(orcaVM* vm, string& str);
	void dump();

	orcatuple_iterator begin() 
	{
		return m_value.begin();
	}

	orcatuple_iterator end() 
	{
		return m_value.end();
	}

	int get_timestamp()
	{
		return m_timestamp;
	}
	
	void inc_timestamp()
	{
		m_timestamp++;
	}

	vector<orcaData>* raw_value()
	{
		return &m_value;
	}

protected:
	vector<orcaData> m_value;
	static cp_map<orcaData>::Type m_static_tuple;

	int m_timestamp;
};

#endif

