/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaVirtList.h - virtual list for decode

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_VIRT_LIST
#define _DEF_ORCA_VIRT_LIST

#include "orcaList.h"
#include "orcaStack.h"

#define TO_VIRT_LIST(a)	static_cast<orcaVirtList*>(a)


class LIBORCA_API orcaVirtList : public orcaList
{
friend class orcaForStack;

public:
	orcaVirtList() {}
	orcaVirtList(void* vp) : orcaList(vp) {}

	orcaObject* v_clone() {
		orcaList* lp = new orcaList();
		return lp;
	}

	virtual ~orcaVirtList() 
	{
		m_lp->rc_dec();
	}

	void init(orcaList* lp);
	orcaVirtList* cut_head();

	// internal
	virtual orcaData slice(int start, int end, bool include_right);
	virtual orcaData& at(int idx);
	virtual orcaListIter begin(); 
	virtual orcaListIter end();
	virtual int size();
	

private:
	orcaList* m_lp;
	orcaListIter m_begin;
	int m_head;
};

#endif

