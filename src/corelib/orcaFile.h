/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaFile.h - basic file interface

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_FILE
#define _DEF_ORCA_FILE

#include "orcaObject.h"
#include "orcaException.h"

void hex_dump(unsigned char* s, int m_size);
class orcaFile : public orcaObject 
{
public:
	orcaFile(void* vp) : m_fp(NULL) { }

	orcaFile() : m_fp(NULL)
	{
		set_name("file");

		insert_native_function("open", (object_fp)&orcaFile::ex_open);
		insert_native_function("close", (object_fp)&orcaFile::ex_close);
		insert_native_function("read", (object_fp)&orcaFile::ex_read);
		insert_native_function("read_line", (object_fp)&orcaFile::ex_read_line);
		insert_native_function("write", (object_fp)&orcaFile::ex_write);
		insert_native_function("seek", (object_fp)&orcaFile::ex_seek);
		insert_native_function("tell", (object_fp)&orcaFile::ex_tell);
	}

	~orcaFile() {
		if (m_fp) {
			fclose(m_fp);
		}
	}

	orcaObject* v_clone() {
		orcaFile* fp = new orcaFile(NULL);
		return fp;
	}

	orcaData ex_open(orcaVM* vm, int n) 
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

	orcaData ex_close(orcaVM* vm, int n) 
	{
		if (m_fp != NULL) {
			fclose(m_fp);
			m_fp = NULL;
		}

		return NIL;
	}

	orcaData ex_read(orcaVM* vm, int n) 
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

	orcaData ex_read_line(orcaVM* vm, int n) 
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
			if (fgets(buff, sizeof(buff), m_fp) != NULL) {
				line += buff;
			}

			if (buff[sizeof(buff)-1] != 0 || buff[sizeof(buff)-2] == 0) {
				break;
			}
		} while (true);

		return line;
	}

	orcaData ex_write(orcaVM* vm, int n) 
	{
		string& in = vm->get_param(0).String();

		if (m_fp == NULL) {
			return NIL;
		}

		return (int)fwrite(in.c_str(), 1, in.length(), m_fp);
	}

	orcaData ex_seek(orcaVM* vm, int n) 
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

	orcaData ex_tell(orcaVM* vm, int n) 
	{
		if (m_fp == NULL) {
			return NIL;
		}

		return (int)ftell(m_fp);
	}

private:
	FILE* m_fp;
	int m_size;
};


#endif

