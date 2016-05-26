/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSort.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SORT
#define _DEF_ORCA_SORT

#include "porting.h"
#include "orcaObject.h"
#include "orcaList.h"

struct sort_compare : public binary_function<const char*, const char*, bool>
{
	sort_compare() : fun(NIL), vm(NULL) {}

	orcaData fun;
	orcaVM* vm;

	bool operator()(const orcaData& l, const orcaData& r) const 
	{
		vm->push_stack(fun);
		vm->push_param(l);
		vm->push_param(r);
		vm->call(2);
		return vm->m_stack->pop().Boolean();
	}
};

class orcaSort : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaSort);
	orcaSort()
	{
		set_name("sort");
	}

	virtual orcaData operator()(orcaVM* vm, int n) 
	{
		if (n<1) vm->need_param();

		orcaData p = vm->get_param(0);
		orcaList* lp = castobj<orcaList>(p);
		if (lp) {
			orcaList* lp2 = TO_LIST(lp->v_clone());
			lp2->sort(vm, vm->get_param(1));
			return lp2;
		}

		orcaTuple* tp = castobj<orcaTuple>(p);
		if (tp) {
			orcaTuple* tp2 = TO_TUPLE(tp->v_clone());
			vector<orcaData>* vp = tp2->raw_value();
			orcaData fun = vm->get_param(1);

			if (is<TYPE_NIL>(fun)) {
				sort(vp->begin(), vp->end());
			}
			else {
				sort_compare cmp;
				cmp.vm = vm;
				cmp.fun = vm->get_param(1);
				sort(vp->begin(), vp->end(), cmp);
			}

			return tp2;
		}

		return NIL;
	}
};


#endif

