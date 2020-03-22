/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaFile.cpp - basic file interface

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/

#include "orcaFile.h"


orcaData orcaFile::ex_open(orcaVM* vm, int n) 
{
	if (n<1) {
		return NIL;
	}

	string& name = vm->get_param(0).String();

	string mode;
	if (is<TYPE_NIL>(vm->get_param(1))) 
		mode = "r+";
	else
		mode = vm->get_param(1).String();

	if (m_fp != NULL) {
		fclose(m_fp);
	}

	m_fp = fopen(name.c_str(), mode.c_str());
	if (m_fp == NULL) {
		throw orcaException(vm, "io.file.handle", "invalid file handle");
	}

	fseek(m_fp, 0, SEEK_END);
	m_size = ftell(m_fp);
	fseek(m_fp, 0, SEEK_SET);

	return NIL;
}

orcaData orcaFile::ex_close(orcaVM* vm, int n) 
{
	if (m_fp != NULL) {
		fclose(m_fp);
		m_fp = NULL;
	}

	return NIL;
}

orcaData orcaFile::ex_read(orcaVM* vm, int n) 
{
	if (m_fp == NULL) {
		return NIL;
	}

	int size = m_size;;
	if (n >= 1) {
		size = vm->get_param(0).Integer();
	}

	string s;
	s.resize(size);
	int ret = fread(&s[0], 1, size, m_fp);
	s.resize(ret);
	return s;
}

orcaData orcaFile::ex_read_line(orcaVM* vm, int n) 
{
	if (m_fp == NULL) {
		return NIL;
	}

	if (feof(m_fp)) {
		throw orcaException(vm, "orca.file.eof", "EOF");
	}

	string line;
	do {
		char buff[4*ONE_K];
		char* cp = fgets(buff, sizeof(buff), m_fp);
		if (cp == NULL) {
			throw orcaException(vm, "orca.file.eof", "EOF");
		}

		line += cp;
		int len = strlen(cp);
		if (cp[len-1] == '\n') {
			break;
		}
	} while (true);

	return line;
}

orcaData orcaFile::ex_write(orcaVM* vm, int n) 
{
	string& in = vm->get_param(0).String();

	if (m_fp == NULL) {
		return NIL;
	}

	return (int)fwrite(in.c_str(), 1, in.length(), m_fp);
}

orcaData orcaFile::ex_seek(orcaVM* vm, int n) 
{
	if (n < 1) vm->need_param();

	int pos = vm->get_param(0).Integer();

	string from = "SEEK_SET";
	if (n == 2) {
		from = vm->get_param(1).String();
	}
	
	if (m_fp == NULL) {
		return NIL;
	}

	int mode;
	if (from == "SEEK_SET") mode = SEEK_SET;
	else if (from == "SEEK_CUR") mode = SEEK_CUR;
	else if (from == "SEEK_END") mode = SEEK_END;

	fseek(m_fp, pos, mode);
	return (int)ftell(m_fp);
}

orcaData orcaFile::ex_tell(orcaVM* vm, int n) 
{
	if (m_fp == NULL) {
		return NIL;
	}

	return (int)ftell(m_fp);
}

orcaFile* init_stdout()
{
	orcaFile* of = new orcaFile();
	of->set_fp(stdout);

	return of;
}

orcaFile* init_stdin()
{
	orcaFile* of = new orcaFile();
	of->set_fp(stdin);

	return of;
}

orcaFile* init_stderr()
{
	orcaFile* of = new orcaFile();
	of->set_fp(stderr);

	return of;
}


