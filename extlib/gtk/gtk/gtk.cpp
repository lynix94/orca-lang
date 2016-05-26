// gtk.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "gtk.h"
#include "orcaGtk.h"




extern "C" GTK_API void* get_gtk() 
{
	orcaGtk* gp = new orcaGtk();
	return gp;
}

