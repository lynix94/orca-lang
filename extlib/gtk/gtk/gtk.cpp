// gtk.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "gtk.h"
#include "orcaGtk.h"




extern "C" GTK_API void* get_gtk() 
{
	orcaGtk* gp = new orcaGtk();
	return gp;
}

