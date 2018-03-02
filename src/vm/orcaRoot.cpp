/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaRoot.cpp - orcaRoot orcaObject of all modules

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#include <iostream>

#include "orcaRoot.h"
#include "orcaIO.h"
#include "orcaOS.h"
#include "orcaFile.h"
#include "orcaDL.h"
#include "orcaThread.h"
#include "orcaSocket.h"
#include "orcaIPC.h"
#include "orcaSelect.h"
#include "orcaDatetime.h"
#include "orcaDate.h"
#include "orcaTime.h"
#include "orcaPack.h"
#include "orcaStopWatch.h"
#include "orcaBase64.h"
#include "orcaType.h"
#include "orcaOrca.h"
#include "orcaRandom.h"
#include "orcaUtil.h"
#include "orcaMath.h"
#include "orcaOperator.h"
#include "orcaSort.h"
#include "orcaCPP.h"
#include "orcaSystem.h"
#include "orcaQueue.h"
#include "orcaSqlite3.h"


#define USE_GTK

#if defined(LINUX)
#if defined(USE_GTK)
	#include "orcaGtk.h"
#endif
#endif

using namespace std;


orcaRoot s_root;
orcaRoot* g_root = &s_root;


orcaRoot::orcaRoot() 
{
	set_name("root");
	rc_inc(); // for permanant life

	insert_static("io", new orcaIO());
	insert_static("file", new orcaFile());
	insert_static("os", new orcaOS());
	insert_static("dl", new orcaDL());
	insert_static("thread", new orcaThread());
	insert_static("socket", new orcaSocket());
	insert_static("fdselect", new orcaSelect());
	insert_static("ipc", new orcaIPC());
	insert_static("time", new orcaTime());
	insert_static("date", new orcaDate());
	insert_static("datetime", new orcaDatetime());
	insert_static("pack", g_pack = new orcaPack());
	insert_static("stopwatch", new orcaStopWatch());
	insert_static("base64", new orcaBase64());
	insert_static("type", new orcaTypes());
	insert_static("orca", new orcaOrca());
	insert_static("random", new orcaRandom());
	insert_static("__util", new orcaUtil());
	insert_static("math", new orcaMath());
	insert_static("operator", new orcaOperator());
	insert_static("sort", new orcaSort());
	insert_static("cpp", new orcaCPP());
	insert_static("system", new orcaSystem());
	insert_static("queue", new orcaQueue());
	insert_static("sqlite3", new orcaSqlite3());

#if defined(LINUX)
#if defined(USE_GTK)
	if (gtk_init_check(NULL, NULL) == false) {
		printf("[WARNING] Can't open gtk display.\n");
	} else {
		insert_static("gtk", new orcaGtk());
	}
#endif

#endif
}

orcaRoot::~orcaRoot() { }

