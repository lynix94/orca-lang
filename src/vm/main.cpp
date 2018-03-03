/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  main.cpp -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#include "porting.h"

#include "orcaGlobal.h"
#include "orcaObject.h"
#include "orcaVM.h"
#include "orcaRoot.h"
#include "orcaLocal.h"
#include "orcaStack.h"
#include "orcaThread.h"

#include "parserParser.h"

int main(int argc, char* argv[]) 
{
	try {
		bool interactive = false;

		if (argc < 2) {
			interactive = true;
		}

		orcaVM vm;
		vm.init();

		bool flag = true;
		if (!interactive) {
			flag = orca_launch_module(&vm, argv[1], argc-2, &argv[2]);
		}
		else {
			orca_launch_interpreter(&vm);
		}

	#ifdef _VM_DEBUG_
		if (flag) {
			vm.m_local->dump();
			vm.m_module->member_dump();
			vm.m_stack->dump();
		}
	#endif
		g_thread_pool->join_all();
		orcaThread::join_remains();

		vm.m_local->decrease();
		vm.cleanup();
		//parse_cleanup();
	}
	catch (orcaException& e) {
		printf("uncaught exception: %s - %s\n", e.who(), e.what());
		cout << e.m_stack_trace << endl;
	}
}


