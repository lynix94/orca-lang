/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSelector.h -

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SELECTOR
#define _DEF_ORCA_SELECTOR

#include "porting.h"
#include "orcaObject.h"

class orcaSelector : public orcaObject 
{
public:
	orcaSelector(void* vp) {}

	~orcaSelector() {
		for (int i=0; i<fds.size(); i++) {
			fds[i].rc_dec();
		}
	}

	orcaObject* v_clone() {
		orcaSelector* fp = new orcaSelector(NULL);
		return fp;
	}

	orcaSelector()
	{
		set_name("selector");
		insert_native_function("size", (object_fp)&orcaSelector::ex_size);
		insert_native_function("->", (object_fp)&orcaSelector::ex_channel_out);
	}

	orcaData ex_size(orcaVM* vm, int n);
	orcaData ex_channel_out(orcaVM* vm, int n);
	int set_fd(fd_set* fd_rd);
	void pass_fds(vector<orcaData>& p)
	{
		fds = p;
	}

private:
	vector<orcaData> fds;
};


#endif

