/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaListIter.h - list type iterator

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_LIST_ITER
#define _DEF_ORCA_LIST_ITER

#include "orcaData.h"

class orcaList;
class orcaSbf;

enum LIST_TYPE
{
	LIST_STL,
	LIST_SBF,
};


class LIBORCA_API orcaListIter
{
public:
	orcaListIter() {} // just for forstack

	orcaListIter(orcaList* lp, list<orcaData>::iterator li);
	orcaListIter(orcaSbf* lp);

	orcaListIter(const orcaListIter& rhs) 
	{
		m_type = rhs.m_type;
		m_iter = rhs.m_iter;
		m_curr = rhs.m_curr;
		m_lp = rhs.m_lp;
		m_timestamp = rhs.m_timestamp;
	}

	orcaListIter& operator=(const orcaListIter& rhs)
	{
		m_type = rhs.m_type;
		m_iter = rhs.m_iter;
		m_curr = rhs.m_curr;
		m_lp = rhs.m_lp;
		m_timestamp = rhs.m_timestamp;
		return *this;
	}

	orcaListIter operator++(int dummy);
	orcaListIter& operator++();
	orcaListIter operator--(int dummy);
	orcaListIter& operator--();
	orcaData& operator*();	// should ref count in outer
	bool operator==(const orcaListIter& rhs);
	bool operator!=(const orcaListIter& rhs);

	void set_idx(int idx);
	LIST_TYPE get_type();
	
	void raw_erase();
	void raw_insert(orcaData d);

private:
	bool valid();

private:
	list<orcaData>::iterator m_iter;
	LIST_TYPE m_type;
	int m_curr;
	orcaList* m_lp;
	int m_timestamp;
};

#endif



