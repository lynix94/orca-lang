/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSelect.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SELECT
#define _DEF_ORCA_SELECT

#include "porting.h"
#include "orcaObject.h"

class orcaSelect : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaSelect);

	orcaSelect()
	{
		set_name("fdselect");
		insert_native_function("fdselect", (object_fp)&orcaSelect::ex_select);
		insert_native_function("readable", (object_fp)&orcaSelect::ex_readable);
	}

	orcaData ex_select(orcaVM* vm, int n);
	orcaData ex_readable(orcaVM* vm, int n);
};


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

