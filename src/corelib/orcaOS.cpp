/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaOS.h - system utils

  Copyright (C) 2009-2018 Lee, Ki-Yeul

**********************************************************************/

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "porting.h"
#include "orcaOS.h"
#include "orcaList.h"
#include "orcaDatetime.h"

#ifdef WINDOWS
#include <direct.h>
#endif


orcaDirIter::~orcaDirIter()
{
	delete m_iter;
}

orcaObject* orcaDirIter::v_clone() 
{
	orcaDirIter* ip = new orcaDirIter(NULL);
	ip->m_iter = m_iter;
	return ip;
}

orcaDirIter::orcaDirIter(string& path)
{
	m_iter = new fs::directory_iterator(path);

	set_name("iterator");
	insert_native_function("next", (object_fp)&orcaDirIter::ex_next);
}


orcaData orcaDirIter::ex_next(orcaVM* vm, int n)
{
	if (*m_iter == m_end) {
		throw orcaException(vm, "done", "done");
	}

	string str = (*m_iter)->path().string();
	++(*m_iter);

	return str;
}


orcaDirTraverse::~orcaDirTraverse()
{
	while (!m_iter.empty()) {
		delete m_iter[m_iter.size()-1];
		m_iter.pop_back();
	}
}

orcaObject* orcaDirTraverse::v_clone() 
{
	orcaDirTraverse* ip = new orcaDirTraverse(NULL);
	ip->m_iter = m_iter;
	return ip;
}


orcaDirTraverse::orcaDirTraverse(string& path)
{
	m_iter.push_back(new fs::directory_iterator(path));

	set_name("traverse");
	insert_native_function("next", (object_fp)&orcaDirTraverse::ex_next);
}

orcaData orcaDirTraverse::ex_next(orcaVM* vm, int n)
{
retry:
	if (m_iter.empty()) {
		throw orcaException(vm, "done", "done");
	}

	fs::directory_iterator* iter = m_iter[m_iter.size()-1];
	
	if (*iter == m_end) {
		m_iter.pop_back();
		delete iter;
		goto retry;
	}

	string str = (*iter)->path().string();
	++(*iter);

	if (fs::is_directory(str)) {
		m_iter.push_back(new fs::directory_iterator(str));
	}

	return str;
}


orcaOS::orcaOS() 
{
	set_name("os");

	insert_static_native_function("getpid", (object_fp)&orcaOS::ex_getpid);
	insert_static_native_function("getppid", (object_fp)&orcaOS::ex_getppid);
	insert_static_native_function("fork", (object_fp)&orcaOS::ex_fork);

	insert_static_native_function("run_cout", (object_fp)&orcaOS::ex_run_cout);
	insert_static_native_function("run", (object_fp)&orcaOS::ex_run);
	insert_static_native_function("system", (object_fp)&orcaOS::ex_system);
	insert_static_native_function("getenv", (object_fp)&orcaOS::ex_getenv);

	// file work
	insert_static_native_function("cwd", (object_fp)&orcaOS::ex_cwd);
	insert_static_native_function("mkdir", (object_fp)&orcaOS::ex_mkdir);
	insert_static_native_function("rename", (object_fp)&orcaOS::ex_rename);
	insert_static_native_function("copy", (object_fp)&orcaOS::ex_copy);
	insert_static_native_function("remove", (object_fp)&orcaOS::ex_remove);
	insert_static_native_function("ls", (object_fp)&orcaOS::ex_ls);
	insert_static_native_function("cd", (object_fp)&orcaOS::ex_cd);
	insert_static_native_function("touch", (object_fp)&orcaOS::ex_touch);

	insert_static_native_function("isexists", (object_fp)&orcaOS::ex_isexists);
	insert_static_native_function("isfile", (object_fp)&orcaOS::ex_isfile);
	insert_static_native_function("isdir", (object_fp)&orcaOS::ex_isdir);

	insert_static_native_function("dir_iterator", (object_fp)&orcaOS::ex_dir_iterator);
	insert_static_native_function("dir_traverser", (object_fp)&orcaOS::ex_dir_traverser);

	insert_static_native_function("read", (object_fp)&orcaOS::ex_read);
	insert_static_native_function("write", (object_fp)&orcaOS::ex_write);
	insert_static_native_function("file_size", (object_fp)&orcaOS::ex_file_size);
	insert_static_native_function("last_write_time", (object_fp)&orcaOS::ex_last_write_time);
}


orcaData orcaOS::ex_getpid(orcaVM* vm, int n) 
{
	return getpid();
}

orcaData orcaOS::ex_getppid(orcaVM* vm, int n) 
{
	return getppid();
}

orcaData orcaOS::ex_fork(orcaVM* vm, int n) 
{
	return fork();
}

orcaData orcaOS::ex_run_cout(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param();
	string& cmd = vm->get_param(0).String();

	FILE* fp = popen(cmd.c_str(), "r");
	if (fp == NULL) {
		return NIL;
	}

	// check __cout__
	bool cout_update = false;
	orcaData ret;
	if (vm->get_caller().o()->has_member("__cout__", ret)) {
		if (is<TYPE_NIL>(ret) || is<TYPE_STR>(ret)) {
			cout_update = true;
		}
	}

	// read and print
	stringstream ss;
	char buff[1024];
	while(fgets(buff, 1024, fp)) {
		if (cout_update)  ss << buff;
		printf("%s", buff);
	}

	if (cout_update) {
		vm->get_caller().o()->update_member("__cout__", ss.str());
	}

	return NIL;
}


orcaData orcaOS::ex_run(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param();
	string& cmd = vm->get_param(0).String();

	orcaObject* out = NULL;
	orcaData in;
	bool flag_ret = false;
	if (is<TYPE_OBJ>(vm->get_param(1))) {
		out = vm->get_param(1).o();
		in = out->get_member("<-");
	}

	FILE* fp = popen(cmd.c_str(), "r");
	if (fp == NULL) {
		return NIL;
	}

	stringstream ss;
	char buff[1024];
	while(fgets(buff, 1024, fp)) {
		if (out == NULL) {
			ss << buff;
		}
		else {
			vm->push_param(in);
			vm->push_param(buff);
			vm->call(1);
		}
	}

	return ss.str();
}

orcaData orcaOS::ex_system(orcaVM* vm, int n) 
{
	if (n < 1) vm->need_param();
	return ::system(vm->get_param(0).String().c_str());
}

orcaData orcaOS::ex_getenv(orcaVM* vm, int n) 
{
	string& env = vm->get_param(0).String();
	char* ep = getenv(env.c_str());
	if (ep == NULL) {
		throw orcaException(vm, "orca.name", string("env ") + env + " not exists");
	}

	return ep;
}

orcaData orcaOS::ex_cwd(orcaVM* vm, int n) 
{
	return fs::current_path().string();
}

orcaData orcaOS::ex_cd(orcaVM* vm, int n) 
{
	string& name = vm->get_param(0).String();
	int ret = chdir(name.c_str());
	return NIL;
}

orcaData orcaOS::ex_touch(orcaVM* vm, int n) 
{
	string& name = vm->get_param(0).String();
	FILE* fp = fopen(name.c_str(), "a+");
	if (fp) { 
		fclose(fp);
	}

	struct stat st;
	time_t mtime;
	struct utimbuf new_times;

	stat(name.c_str(), &st);
	mtime = st.st_mtime;

	new_times.actime = st.st_atime;
	new_times.modtime = time(NULL);
	utime(name.c_str(), &new_times);

	return NIL;
}

orcaData orcaOS::ex_dir_iterator(orcaVM* vm, int n) 
{
	string& name = vm->get_param(0).String();
	orcaDirIter* ip = new orcaDirIter(name);
	return ip;
}

orcaData orcaOS::ex_dir_traverser(orcaVM* vm, int n) 
{
	string& name = vm->get_param(0).String();
	orcaDirTraverse* tp = new orcaDirTraverse(name);
	return tp;
}

orcaData orcaOS::ex_mkdir(orcaVM* vm, int n) 
{
	string& name = vm->get_param(0).String();

	try {
		fs::create_directory(name);
	} catch(...) {
		throw orcaException(vm, "orca.file", string("directory ") + name + "creation failed");
	}

	return NIL;
}

orcaData orcaOS::ex_remove(orcaVM* vm, int n) 
{
	string& name = vm->get_param(0).String();

	try {
		fs::remove(name);
	} catch(...) {
		throw orcaException(vm, "orca.file", string("remove ") + name + " failed");
	}

	return NIL;
}

orcaData orcaOS::ex_ls(orcaVM* vm, int n) 
{
	string& name = vm->get_param(0).String();
	orcaList* lp = new orcaList();

	try {
		fs::directory_iterator end;
		fs::directory_iterator itr(name);

		for(; itr != end; ++itr) {
			lp->push_back(itr->path().string());
		}

	} catch(...) {
		delete lp;
		throw orcaException(vm, "orca.file", string("list dir ") + name + " failed");
	}

	return lp;
}

orcaData orcaOS::ex_rename(orcaVM* vm, int n) 
{
	string& src = vm->get_param(0).String();
	string& dst = vm->get_param(1).String();

	try {
		if (!fs::exists(src)) {
			throw orcaException(vm, "orca.file", string("file ") + src + " not exists");
		}

		if (fs::exists(dst)) {
			throw orcaException(vm, "orca.file", string("destion file ") + dst + " exists");
		}

		fs::rename(src, dst);
	} catch(...) {
		throw orcaException(vm, "orca.file", string("rename ") + src + " failed");
	}

	return NIL;
}

orcaData orcaOS::ex_copy(orcaVM* vm, int n) 
{
	string& src = vm->get_param(0).String();
	string& dst = vm->get_param(1).String();

	try {
		if (!fs::exists(src)) {
			throw orcaException(vm, "orca.file", string("file ") + src + " not exists");
		}

		if (fs::exists(dst)) {
			throw orcaException(vm, "orca.file", string("destion file ") + dst + " exists");
		}

		fs::copy_file(src, dst);
	} catch(...) {
		throw orcaException(vm, "orca.file", string("copy ") + src + " failed");
	}

	return NIL;
}

orcaData orcaOS::ex_isexists(orcaVM* vm, int n) 
{
	try {
		string& name = vm->get_param(0).String();
		return fs::exists(name);
	}
	catch (...) {
		return false;
	}
}

orcaData orcaOS::ex_isdir(orcaVM* vm, int n) 
{
	try {
		string& name = vm->get_param(0).String();
		return fs::is_directory(name);
	}
	catch (...) {
		return false;
	}
}

orcaData orcaOS::ex_isfile(orcaVM* vm, int n) 
{
	try {
		string& name = vm->get_param(0).String();
		return (fs::exists(name) && !fs::is_directory(name));
	}
	catch (...) {
		return false;
	}
}

orcaData orcaOS::ex_read(orcaVM* vm, int n) 
{
	if (n < 1) vm->need_param();

	int size = INT_MAX;
	int offset = 0;

	string& path = vm->get_param(0).String();
	if (!is<TYPE_NIL>(vm->get_param(2))) {
		offset = vm->get_param(2).Integer();
	}

	if (!is<TYPE_NIL>(vm->get_param(1))) {
		size = vm->get_param(1).Integer();
		if (size < 0) size = INT_MAX;
	}

	FILE* fp = fopen(path.c_str(), "r");
	if (fp == NULL) {
		throw orcaException(vm, "orca.file", string("file ") + path + " not exists");
	}

	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	fseek(fp, offset, SEEK_SET);

	int rsize = size;
	if (fsize - offset < rsize) {
		rsize = fsize - offset;
	}

	string buff;
	buff.resize(rsize);
	int ret = fread(&buff[0], 1, rsize, fp);
	buff.resize(ret);
	fclose(fp);
	
	return buff;
}

orcaData orcaOS::ex_write(orcaVM* vm, int n) 
{
	if (n < 2) vm->need_param();

	int size = INT_MAX;
	int offset = 0;
	string buff;

	string& path = vm->get_param(0).String();
	if (!is<TYPE_NIL>(vm->get_param(2))) {
		offset = vm->get_param(2).Integer();
	}

	buff = vm->get_param(1).String();
	

	FILE* fp = fopen(path.c_str(), "r+");
	if (fp == NULL) {
		fp = fopen(path.c_str(), "w");
		if (fp == NULL) {
			throw orcaException(vm, "orca.file", string("file ") + path + " creation fail");
		}
	}

	fseek(fp, offset, SEEK_SET);
	int ret = fwrite(buff.c_str(), 1, buff.length(), fp);
	fclose(fp);
	
	return ret;
}

orcaData orcaOS::ex_file_size(orcaVM* vm, int n) 
{
	if (n < 1) vm->need_param();

	string& path = vm->get_param(0).String();
	FILE* fp = fopen(path.c_str(), "r");
	if (fp == NULL) {
		throw orcaException(vm, "orca.file", string("file ") 
							+ path + " not exists");
	}

	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	fclose(fp);
	return fsize;
}

orcaData orcaOS::ex_last_write_time(orcaVM* vm, int n) 
{
	if (n < 1) vm->need_param();

	string& path = vm->get_param(0).String();
	try {
		time_t tt = fs::last_write_time(fs::path(path));

		return new orcaDatetime(from_time_t(tt));
	}
	catch (...) {
		throw orcaException(vm, "orca.param", string("file ") + path + " is invalid");
	}
}


