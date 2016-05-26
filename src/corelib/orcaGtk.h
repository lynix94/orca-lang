/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaGtk.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/
#ifndef _DEF_ORCA_GTK
#define _DEF_ORCA_GTK


#include "porting.h"

#include <gtk/gtk.h>
void store_filename(GtkFileSelection *file_selection, gpointer data);


#include "orcaObject.h"
#include "orcaMap.h"
#include "orcaTuple.h"
#include "orcaException.h"


enum handle_type 
{
	GUI_NULL,
	GUI_WINDOW,
	GUI_FIXED,
	GUI_VBOX,
	GUI_HBOX,
	GUI_SCROLL,
	GUI_TABLE,
	GUI_HSEP,
	GUI_BUTTON,
	GUI_CHECK,
	GUI_COMBO,
	GUI_RADIO,
	GUI_LABEL,
	GUI_ENTRY,
	GUI_TEXT,
	GUI_MENUBAR,
	GUI_LIST,
	GUI_TREE,
	GUI_IMAGE,
	GUI_STATUSBAR,
};


class orcaGtkDialog : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaGtkDialog);

	orcaGtkDialog()
	{
		set_name("dialog");
		insert_static_native_function("messagebox", (object_fp)&orcaGtkDialog::ex_messagebox);
		insert_static_native_function("fileopen", (object_fp)&orcaGtkDialog::ex_fileopen);
		insert_static_native_function("filesave", (object_fp)&orcaGtkDialog::ex_filesave);
	}

	orcaData ex_messagebox(orcaVM* vm, int n);
	orcaData ex_fileopen(orcaVM* vm, int n);
	orcaData ex_filesave(orcaVM* vm, int n);
};



class orcaGtk;
struct signal_t
{
	orcaObject* fun;
	GtkTreeModel* tree;
	orcaGtk* owner;
};

class orcaGtk : public orcaObject
{
public:
	orcaGtk();
	orcaGtk(void* vp)
	{
		init();
	}

	virtual ~orcaGtk() 
	{ 
		for (int i=0; i<m_signals.size(); i++) {
			delete m_signals[i];
		}

		if (store) {
			g_object_unref(store);
			store = NULL;
		}
	}

	orcaObject* v_clone()
	{
		orcaGtk* op = new orcaGtk(NULL);
		op->type = type;
		op->alloc();
		return op;
	}

	void init()
	{
		type = GUI_NULL;
		handle = NULL;
		store = NULL;
	}

	orcaData ex_init(orcaVM* vm, int n);
	orcaData ex_put(orcaVM* vm, int n);
	orcaData ex_show(orcaVM* vm, int n);
	orcaData ex_quit(orcaVM* vm, int n);
	orcaData ex_set_text(orcaVM* vm, int n);
	orcaData ex_set_event(orcaVM* vm, int n);
	orcaData ex_set_attr(orcaVM* vm, int n);
	orcaData ex_push_back(orcaVM* vm, int n);
	orcaData ex_set_data(orcaVM* vm, int n);
	orcaData ex_get_data(orcaVM* vm, int n);

	void alloc();

	GtkWidget *handle;
	GtkTreeModel* store;
	handle_type type;
	string text;
	map<orcaData, orcaData> attr;

	vector<signal_t*> m_signals;
};

class orcaGtkIter : public orcaObject
{
public:
	orcaGtkIter()
	{
		set_name("tree_iterator");
		insert_native_function("next", (object_fp)&orcaGtkIter::ex_next);
		insert_native_function("child_begin", (object_fp)&orcaGtkIter::ex_child_begin);
		insert_native_function("child_size", (object_fp)&orcaGtkIter::ex_child_size);
		insert_native_function("push_child", (object_fp)&orcaGtkIter::ex_push_child);
		insert_native_function("parent", (object_fp)&orcaGtkIter::ex_parent);
		insert_native_function("insert", (object_fp)&orcaGtkIter::ex_insert);
	}

	orcaGtkIter(void* vp) { }

	virtual ~orcaGtkIter() { }

	orcaObject* v_clone()
	{
		orcaGtkIter* ip =  new orcaGtkIter(NULL);
		ip->m_iter = m_iter;
		ip->m_gp = m_gp;
		ip->m_type = m_type;

		return ip;
	}

	orcaData ex_child_begin(orcaVM* vm, int n);
	orcaData ex_child_size(orcaVM* vm, int n);
	orcaData ex_push_child(orcaVM* vm, int n);

	virtual orcaData operator()(orcaVM* vm, int n);
	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_parent(orcaVM* vm, int n);
	orcaData ex_insert(orcaVM* vm, int n);

	GtkTreeIter m_iter;
	orcaGtk* m_gp;
	handle_type m_type;
};



#endif

