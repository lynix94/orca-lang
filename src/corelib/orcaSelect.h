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
	orcaSelect()
	{
		set_name("select");
		insert_native_function("select", (object_fp)&orcaSelect::ex_select);
		insert_native_function("readable", (object_fp)&orcaSelect::ex_readable);
	}

	orcaData ex_select(orcaVM* vm, int n) 
	{
		orcaList* rd = dynamic_cast<orcaList*>(vm->get_param(0).Object());
		orcaList* wd = dynamic_cast<orcaList*>(vm->get_param(1).Object());
		orcaList* ed = dynamic_cast<orcaList*>(vm->get_param(2).Object());

		int tmout = -1;
		if (n > 3) {
			tmout = vm->get_param(3).Integer();
		}

		fd_set fd_rd, fd_wd, fd_ed;

		FD_ZERO(&fd_rd);
		FD_ZERO(&fd_wd);
		FD_ZERO(&fd_ed);
		
		int max_fd = 0;

		orcaListIter li;
		for(li = rd->begin(); li != rd->end(); ++li) {
			int fd = (*li).Integer();
			FD_SET(fd, &fd_rd);
			if (fd > max_fd) {
				max_fd = fd;
			}
		}
		for(li = wd->begin(); li != wd->end(); ++li) {
			int fd = (*li).Integer();
			FD_SET(fd, &fd_wd);
			if (fd > max_fd) {
				max_fd = fd;
			}
		}
		for(li = ed->begin(); li != ed->end(); ++li) {
			int fd = (*li).Integer();
			FD_SET(fd, &fd_ed);
			if (fd > max_fd) {
				max_fd = fd;
			}
		}

		struct timeval tv;
		struct timeval* tvp = NULL;

		if (tmout >= 0) {
			tv.tv_sec = tmout / 1000;
			tv.tv_usec = (tmout % 1000) * 1000;
			tvp = &tv;
		}

		orcaTuple* tp = new orcaTuple(3);
		int ret = select(max_fd+1, &fd_rd, &fd_wd, &fd_ed, tvp);
		if (ret) {
			orcaList* rlp = new orcaList();
			orcaList* wlp = new orcaList();
			orcaList* elp = new orcaList();
			for (int i=0; i<max_fd+1; i++) {
				if (FD_ISSET(i, &fd_rd)) {
					rlp->push_back(i);
				}

				if (FD_ISSET(i, &fd_wd)) {
					wlp->push_back(i);
				}

				if (FD_ISSET(i, &fd_ed)) {
					elp->push_back(i);
				}
			}

			tp->update(0, rlp);
			tp->update(1, wlp);
			tp->update(2, elp);
		}

		return tp;
	}

	orcaData ex_readable(orcaVM* vm, int n) 
	{
		int fd = vm->get_param(0).Integer();
		int timeout = -1;

		if (!is<TYPE_NIL>(vm->get_param(1))) {
			timeout = vm->get_param(1).Integer();
		}

		fd_set fd_rd;
		FD_ZERO(&fd_rd);
		FD_SET(fd, &fd_rd);
		
		struct timeval tv;
		tv.tv_sec = timeout / 1000;
		tv.tv_usec = (timeout % 1000) * 1000;
		struct timeval* tp = &tv;
		if (timeout < 0) tp = NULL;

		int ret = select(fd+1, &fd_rd, NULL, NULL, tp);
		if (ret) {
			if (FD_ISSET(fd, &fd_rd)) {
				return true;
			}
		}

		return false;
	}
};


#endif

