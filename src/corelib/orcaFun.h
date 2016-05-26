/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaFun.h - for functional programming

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_FUN
#define _DEF_ORCA_FUN

#include <stdlib.h>

#include "porting.h"
#include "orcaStack.h"
#include "orcaObject.h"

class orcaFun : public orcaObject 
{
public:
	orcaFun()
	{
		set_name("__fun");
		insert_static_native_function("apply", (object_fp)&orcaFun::ex_apply);
	}

	orcaData ex_apply(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		int len = 0;
		orcaData f  = vm->get_param(0);
		vm->m_stack->push(f);

		orcaList* lp = dynamic_cast<orcaList*>(vm->get_param(1).Object());
		orcaTuple* tp = dynamic_cast<orcaTuple*>(vm->get_param(1).Object());
		if (lp != NULL) {
			for(orcaListIter li=lp->begin(); li!=lp->end(); ++li) {
				vm->m_stack->push(*li);
			}

			len = lp->size();
		}
		else if (tp != NULL) {
			for(int i=0; i<tp->size(); i++) {
				vm->m_stack->push(tp->at(i));
			}

			len = tp->size();
		}
		else {
			throw orcaException(vm, "orca.param", "list or tuple type required");
		}

		vm->call(len);
		return vm->m_stack->pop();
	}
};

#endif

