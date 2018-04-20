/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSelect.cpp -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaSelect.h"
#include "orcaList.h"
#include "orcaSocket.h"

orcaData orcaSelect::ex_select(orcaVM* vm, int n) 
{
	orcaList* rd = dynamic_cast<orcaList*>(vm->get_param(0).Object());
	orcaList* wd = dynamic_cast<orcaList*>(vm->get_param(1).Object());
	orcaList* ed = dynamic_cast<orcaList*>(vm->get_param(2).Object());

	double tmout = -1;
	if (n > 3) {
		tmout = vm->get_param(3).Double();
	}

	fd_set fd_rd, fd_wd, fd_ed;

	FD_ZERO(&fd_rd);
	FD_ZERO(&fd_wd);
	FD_ZERO(&fd_ed);
	
	int max_fd = 0;

	orcaListIter li;

	if (rd) {
		for(li = rd->begin(); li != rd->end(); ++li) {
			int fd = (*li).Integer();
			FD_SET(fd, &fd_rd);
			if (fd > max_fd) {
				max_fd = fd;
			}
		}
	}

	if (wd) {
		for(li = wd->begin(); li != wd->end(); ++li) {
			int fd = (*li).Integer();
			FD_SET(fd, &fd_wd);
			if (fd > max_fd) {
				max_fd = fd;
			}
		}
	}

	if (ed) {
		for(li = ed->begin(); li != ed->end(); ++li) {
			int fd = (*li).Integer();
			FD_SET(fd, &fd_ed);
			if (fd > max_fd) {
				max_fd = fd;
			}
		}
	}

	struct timeval tv;
	struct timeval* tvp = NULL;

	if (tmout >= 0) {
		tv.tv_sec = int(tmout);
		tv.tv_usec = (long long)(tmout * 1000000) % 1000000;
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

orcaData orcaSelect::ex_readable(orcaVM* vm, int n) 
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



orcaData orcaSelector::ex_size(orcaVM* vm, int n)
{
	struct timeval tv;
	fd_set fd_rd;
	FD_ZERO(&fd_rd);
	int max_fd = set_fd(&fd_rd);
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	int ret = select(max_fd+1, &fd_rd, NULL, NULL, &tv);

	return ret;
}

orcaData orcaSelector::ex_channel_out(orcaVM* vm, int n)
{
	struct timeval tv;
	fd_set fd_rd;
	FD_ZERO(&fd_rd);
	int max_fd = set_fd(&fd_rd);
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	int ret = select(max_fd+1, &fd_rd, NULL, NULL, &tv);

	orcaTuple *tp = new orcaTuple();	
	if (ret) {
		for (int i=0; i<fds.size(); i++) {
			orcaData d = fds[i];
			if (is<TYPE_INT>(d)) {
				if (FD_ISSET(d.i(), &fd_rd)) {
					tp->push_back(d);
				}
			}
			else if (is<TYPE_OBJ>(d)) {
				orcaObject* o = d.o();
				orcaSocket* so = dynamic_cast<orcaSocket*>(o);
				if (so) {
					if (FD_ISSET(so->get_handle(), &fd_rd)) {
						tp->push_back(so);
					}
				}
				// add other fd base objects (like pipe)
			}
		}
	}

	return tp;
}

int orcaSelector::set_fd(fd_set* fd_rd)
{
	int max_fd = 0;

	for (int i=0; i<fds.size(); i++) {
		orcaData d = fds[i];
		if (is<TYPE_INT>(d)) {
			FD_SET(d.i(), fd_rd);	
			max_fd = max(max_fd, d.i());
		}
		else if (is<TYPE_OBJ>(d)) {
			orcaObject* o = d.o();
			orcaSocket* so = dynamic_cast<orcaSocket*>(o);
			if (so) {
				FD_SET(so->get_handle(), fd_rd);
				max_fd = max(max_fd, so->get_handle());
			}
			// add other fd base objects (like pipe)
		}
	}

	return max_fd;
}


