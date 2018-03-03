/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaNil.h - boolean type

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_NIL
#define _DEF_ORCA_NIL

#include "orcaObject.h"

class LIBORCA_API orcaNil : public orcaObject
{
public:
	orcaNil();
	orcaData string_();
};

extern orcaNil g_nil;

#endif

