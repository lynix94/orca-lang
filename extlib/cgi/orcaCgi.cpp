/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaCgi.h - 

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "porting.h"
#include "orcaCgi.h"

extern "C" void* get_cgi() 
{
	orcaCgi* cp = new orcaCgi();
	return cp;
}


