/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaOS.h - system utils

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_OS
#define _DEF_ORCA_OS

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "orcaObject.h"


namespace fs = boost::filesystem;

using namespace std;
using namespace boost;

class orcaDirIter : public orcaObject
{
public:
	orcaDirIter(void* vp) { } 
	virtual ~orcaDirIter();
	orcaObject* v_clone();

	orcaDirIter(string& path);
	orcaData ex_next(orcaVM* vm, int n);

private:
	fs::directory_iterator* m_iter;
	fs::directory_iterator m_end;
};


class orcaDirTraverse : public orcaObject
{
public:
	orcaDirTraverse(void* vp) { } 
	virtual ~orcaDirTraverse();
	orcaObject* v_clone();
	orcaDirTraverse(string& path);

	orcaData ex_next(orcaVM* vm, int n);

private:
	vector<fs::directory_iterator*> m_iter;
	fs::directory_iterator m_end;
};

class orcaOS : public orcaObject 
{
public:
	orcaOS();

	orcaData ex_getpid(orcaVM* vm, int n);
	orcaData ex_getppid(orcaVM* vm, int n);
	orcaData ex_fork(orcaVM* vm, int n);

	orcaData ex_run_cout(orcaVM* vm, int n);
	orcaData ex_run(orcaVM* vm, int n);
	orcaData ex_system(orcaVM* vm, int n); 

	orcaData ex_getenv(orcaVM* vm, int n);
	orcaData ex_cwd(orcaVM* vm, int n);
	orcaData ex_cd(orcaVM* vm, int n);

	orcaData ex_touch(orcaVM* vm, int n);
	orcaData ex_dir_iterator(orcaVM* vm, int n);
	orcaData ex_dir_traverser(orcaVM* vm, int n);
	orcaData ex_mkdir(orcaVM* vm, int n);
	orcaData ex_remove(orcaVM* vm, int n);
	orcaData ex_ls(orcaVM* vm, int n);

	orcaData ex_rename(orcaVM* vm, int n);
	orcaData ex_copy(orcaVM* vm, int n);
	orcaData ex_isexists(orcaVM* vm, int n);
	orcaData ex_isdir(orcaVM* vm, int n);
	orcaData ex_isfile(orcaVM* vm, int n);
	orcaData ex_read(orcaVM* vm, int n);
	orcaData ex_write(orcaVM* vm, int n);
	orcaData ex_file_size(orcaVM* vm, int n);
	orcaData ex_last_write_time(orcaVM* vm, int n);
};

#endif

