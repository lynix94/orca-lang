/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaCgi.h - 

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/
#ifdef LINUX // Not yet in windows

#ifndef _DEF_ORCA_CGI
#define _DEF_ORCA_CGI

#include <iostream>
#include <libcgi/cgi.h>
#include <libcgi/session.h>

#include "orcaObject.h"
#include "orcaException.h"
#include "orcaMap.h"

using namespace std;

class orcaTag : public orcaObject
{
public:
	DEFAULT_NATIVE_DEFINE(orcaTag);

	orcaTag(string& name, string& out) : m_name(name)
	{
		set_name("tag");
		insert_native_function("{", (object_fp)&orcaTag::ex_scope_start);
		insert_native_function("}", (object_fp)&orcaTag::ex_scope_end);

		m_out = &out;
	}

	orcaData ex_scope_start(orcaVM* vm, int n)
	{
		(*m_out) += "<" + m_name + " " + m_attr + ">\n";
		return NIL;
	}

	orcaData ex_scope_end(orcaVM* vm, int n)
	{
		(*m_out) += "</" + m_name + ">\n";
		return NIL;
	}

	void add_attr(orcaData attr)
	{
		if (is<TYPE_STR>(attr)) {
			m_attr += " " + attr.s();
		}
		else if (isobj<orcaMap>(attr)) {
			orcaMap* mp = TO_MAP(attr.o());
			orcamap_iterator it = mp->begin();

			for(; it != mp->end(); ++it) {
				if (isall<TYPE_STR>(it->first, it->second)) {
					m_attr += " " + it->first.s() + "=" + it->second.s();
				}
				else {
					orcaVM* vm = get_current_vm();
					m_attr += " " + it->first.string_(vm) + "=" + it->second.string_(vm);
				}
			}
		}
		else if (isobj<orcaList>(attr)) {
			orcaList* lp = TO_LIST(attr.o());
			orcaListIter it = lp->begin();

			for(; it != lp->end(); ++it) {
				m_attr += " " + (*it).String();
			}
		}
	}

private:
	string m_name;
	string m_attr;
	string* m_out;
};


class orcaCookie : public orcaObject
{
public:
	orcaCookie()
	{
		set_name("cookie");
		insert_static_native_function("set", (object_fp)&orcaCookie::ex_set);
		insert_static_native_function("get", (object_fp)&orcaCookie::ex_get);
	}

	orcaData ex_set(orcaVM* vm, int n)
	{
		if (n < 2) vm->need_param();

		string key = vm->get_param(0).String();
		string value = vm->get_param(1).String();

		const char* expire = NULL;
		const char* path = NULL;
		const char* domain = NULL;
		bool secure = false;

		if (n >= 3) {
			expire = vm->get_param(2).String().c_str();
		}
		if (n >= 4) {
			path = vm->get_param(3).String().c_str();
		}
		if (n >= 5) {
			domain = vm->get_param(4).String().c_str();
		}
		if (n >= 6) {
			secure = vm->get_param(5).Boolean();
		}

		cgi_add_cookie(key.c_str(), value.c_str(), expire, path, domain, secure?1:0);

		return NIL;
	}

	orcaData ex_get(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		string key = vm->get_param(0).String();
		char* cp = cgi_cookie_value(key.c_str());

		return cp ? cp : NIL;
	}
};

class orcaSession : public orcaObject
{
public:
	DEFAULT_NATIVE_DEFINE(orcaSession);

	orcaSession()
	{
		set_name("session");
		insert_static_native_function("exist", (object_fp)&orcaSession::ex_exist);
		insert_static_native_function("get", (object_fp)&orcaSession::ex_get);
		insert_static_native_function("set", (object_fp)&orcaSession::ex_set);
		insert_static_native_function("add", (object_fp)&orcaSession::ex_add);
		insert_static_native_function("remove", (object_fp)&orcaSession::ex_remove);
		insert_static_native_function("destroy", (object_fp)&orcaSession::ex_destroy);
	}

	virtual orcaData operator()(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		cgi_session_cookie_name(vm->get_param(0).String().c_str());
		cgi_session_start();

		return NIL;
	}

	orcaData ex_get(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();
		
		char* cp =  cgi_session_var(vm->get_param(0).String().c_str());
		if (cp == NULL) {
			cp = (char*)"(null)";
		}

		return cp;
	}

	orcaData ex_exist(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();
		
		return cgi_session_var_exists(vm->get_param(0).String().c_str()) != 0;
	}

	orcaData ex_add(orcaVM* vm, int n)
	{
		if (n < 2) vm->need_param();

		cgi_session_register_var(vm->get_param(0).String().c_str(),
								 vm->get_param(1).String().c_str());
		return NIL;
	}

	orcaData ex_set(orcaVM* vm, int n)
	{
		if (n < 2) vm->need_param();

		cgi_session_alter_var(vm->get_param(0).String().c_str(),
							  vm->get_param(1).String().c_str());
		return NIL;
	}

	orcaData ex_remove(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();
		
		cgi_session_unregister_var((char*)vm->get_param(0).String().c_str());
		return NIL;
	}

	orcaData ex_destroy(orcaVM* vm, int n)
	{
		cgi_session_destroy();
		return NIL;
	}
};

class orcaHeader : public orcaObject
{
public:
	orcaHeader()
	{
		set_name("header");
		insert_static_native_function("{", (object_fp)&orcaHeader::ex_scope_start);
		insert_static_native_function("}", (object_fp)&orcaHeader::ex_scope_end);

		insert_static("session", new orcaSession());
		insert_static("cookie", new orcaCookie());
	}

	orcaData ex_scope_start(orcaVM* vm, int n)
	{
		cgi_init();
		cgi_process_form();
		return NIL;
	}
	
	orcaData ex_scope_end(orcaVM* vm, int n)
	{
		return NIL;
	}

};

class orcaHtml : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaHtml);

	orcaHtml() 
	{
		set_name("html");
		insert_static_native_function("{", (object_fp)&orcaHtml::ex_scope_start);
		insert_static_native_function("}", (object_fp)&orcaHtml::ex_scope_end);

		insert_static_native_function("tag", (object_fp)&orcaHtml::ex_tag);
		insert_static_native_function("ctag", (object_fp)&orcaHtml::ex_ctag);
		insert_static_native_function("br", (object_fp)&orcaHtml::ex_br);
		insert_static_native_function("text", (object_fp)&orcaHtml::ex_text);
		insert_static_native_function("puts", (object_fp)&orcaHtml::ex_puts);
	}

	orcaData ex_scope_start(orcaVM* vm, int n)
	{
		m_stream = "";
		return NIL;
	}

	orcaData ex_scope_end(orcaVM* vm, int n)
	{
		cgi_init_headers();
		cout << m_stream << endl;
		cgi_end();
		return NIL;
	}

	orcaData ex_tag(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		string name = vm->get_param(0).String();
		string attr = "";

		orcaTag* tp = new orcaTag(name, m_stream);

		if (n > 1) {
			for (int i=1; i<n; i++) {
				tp->add_attr(vm->get_param(i));
			}
		}
		
		return tp;
	}

	orcaData ex_ctag(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		string name = vm->get_param(0).String();
		string attr = "";

		if (n > 1) {
			for (int i=1; i<n; i++) {
				attr += " " + vm->get_param(i).String();
			}
		}
		
		m_stream += "<" + name + " " + attr + "/>\n";
		return NIL;
	}

	orcaData ex_br(orcaVM* vm, int n)
	{
		m_stream += "<br>\n";
		return NIL;
	}

	orcaData ex_puts(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		string attr;
		for (int i=0; i<n; i++) {
			attr += " " + vm->get_param(i).string_(vm);
		}

		m_stream += attr;
		return NIL;
	}

	orcaData ex_text(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		string text = vm->get_param(0).String();

		if (n > 1) {
			string font = vm->get_param(1).String();
			string size = "";

			if (n > 2 ) {
				int i = vm->get_param(2).Integer();
				char buff[11];
				sprintf(buff, "%d", i);
				size = string("size=") + buff;
			}

			m_stream += "<font face=\'" + font + "\' " + size + ">" + 
						text + "</font>\n";
		}

		return NIL;
	}

private:
	string m_stream;
};


class orcaCgi : public orcaObject 
{
public:
	orcaCgi(void* vp) 
	{
		cgi_init(); // for init_hex_table
	}

	~orcaCgi() {}

	orcaObject* v_clone() 
	{
		return new orcaCgi(NULL); 
	}

	orcaCgi() 
	{
		set_name("cgi");
		insert_static_native_function("get_param", (object_fp)&orcaCgi::ex_get_param);
		insert_static_native_function("urlenc", (object_fp)&orcaCgi::ex_urlenc);
		insert_static_native_function("urldec", (object_fp)&orcaCgi::ex_urldec);
		insert_static_native_function("htmlenc", (object_fp)&orcaCgi::ex_htmlenc);
		insert_static_native_function("redirect", (object_fp)&orcaCgi::ex_redirect);

		insert_static("header", new orcaHeader());
		insert_static("html", new orcaHtml());

		cgi_init();
	}

	orcaData ex_get_param(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		string name = vm->get_param(0).String();
		char* cp = cgi_param(name.c_str());

		return cp ? cp : NIL;
	}

	orcaData ex_redirect(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		cgi_redirect((char*)vm->get_param(0).String().c_str());
		cgi_end();
		return NIL;
	}

	orcaData ex_urlenc(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		string str = vm->get_param(0).String();
		char* cp = cgi_escape_special_chars((char*)str.c_str());

		return cp ? cp : NIL;
	}

	orcaData ex_urldec(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		string str = vm->get_param(0).String();
		char* cp = cgi_unescape_special_chars((char*)str.c_str());

		return cp ? cp : NIL;
	}

	orcaData ex_htmlenc(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();

		string str = vm->get_param(0).String();
		char* cp = htmlentities((char*)str.c_str());

		return cp ? cp : NIL;
	}
};


#endif

#endif // LINUX

