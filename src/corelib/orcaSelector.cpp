/**********************************************************************

  orcaSelector.cpp -

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#include "orcaSelector.h"
#include "orcaList.h"
#include "orcaSocket.h"



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


