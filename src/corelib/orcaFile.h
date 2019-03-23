/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaFile.h - basic file interface

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/


#ifndef _DEF_ORCA_FILE
#define _DEF_ORCA_FILE

#include "orcaObject.h"
#include "orcaException.h"

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

	~orcaFile()
	{
		if (m_fp) {
			fclose(m_fp);
		}
	}

	orcaObject* v_clone()
	{
		orcaFile* fp = new orcaFile(NULL);
		return fp;
	}

	void set_fp(FILE* fp)
	{
		m_fp = fp;
	}

	orcaData ex_open(orcaVM* vm, int n);
	orcaData ex_close(orcaVM* vm, int n);

	orcaData ex_read(orcaVM* vm, int n);
	orcaData ex_read_line(orcaVM* vm, int n);
	orcaData ex_write(orcaVM* vm, int n);

	orcaData ex_seek(orcaVM* vm, int n);
	orcaData ex_tell(orcaVM* vm, int n) ;

private:
	FILE* m_fp;
	int m_size;
};



orcaFile* init_stdout();
orcaFile* init_stdin();
orcaFile* init_stderr();

#endif

