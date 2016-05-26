/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaFloat.h - real number type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_FLOAT
#define _DEF_ORCA_FLOAT

#include "orcaObject.h"

class LIBORCA_API orcaFloat : public orcaObject
{
public:
	orcaFloat();
	orcaData string_(orcaVM* vm, double f);
	orcaData float_(orcaVM* vm, double f);
	orcaData integer(orcaVM* vm, double f);
};


extern orcaFloat g_float;

#endif

