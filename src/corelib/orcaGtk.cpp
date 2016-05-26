/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaGtk.cpp - GTK handler for gui module

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/
#include "orcaGtk.h"
#include "orcaStack.h"
#include "orcaException.h"
#include "orcaRoot.h"
#include "orcaList.h"
#include "orcaTuple.h"

static void gui_callback(GtkWidget* widget, gpointer param)/*{{{*/
{
	orcaVM* vm = get_current_vm();
	vm->m_stack->push((orcaObject*)param);
	vm->call(0);
	vm->m_stack->pop();
}
/*}}}*/

static void gui_list_tree_toggled_callback (GtkCellRendererToggle *cell, gchar *path_str, gpointer data, bool list)/*{{{*/
{
	signal_t* p = (signal_t*)data;
	orcaObject* fun = p->fun;
	GtkTreeModel *model = p->tree;
	orcaGtk *owner = p->owner;

	GtkTreeIter  iter;
	GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
	gboolean fixed;

	/* get toggled iter */
	gtk_tree_model_get_iter (model, &iter, path);
	gtk_tree_model_get (model, &iter, 0, &fixed, -1);

	/* do something with the value */
	fixed ^= 1;

	/* set new value */
	if (list)
		gtk_list_store_set (GTK_LIST_STORE (model), &iter, 0, fixed, -1);
	else 
		gtk_tree_store_set (GTK_TREE_STORE (model), &iter, 0, fixed, -1);

	/* clean up */
	gtk_tree_path_free (path);

	orcaGtkIter* ip = new orcaGtkIter();
	ip->m_gp = owner;
	ip->m_iter = iter;
	ip->m_type = list ? GUI_LIST : GUI_TREE;

	orcaVM* vm = get_current_vm();
	vm->m_stack->push((orcaObject*)fun);
	vm->push_param(fixed?true:false);
	vm->push_param(ip);
	vm->call(2);
	vm->m_stack->pop();
}
/*}}}*/

static void gui_list_toggled_callback (GtkCellRendererToggle *cell, gchar *path_str, gpointer data)/*{{{*/
{
	gui_list_tree_toggled_callback(cell, path_str, data, true);
}
/*}}}*/

static void gui_tree_toggled_callback (GtkCellRendererToggle *cell, gchar *path_str, gpointer data)/*{{{*/
{
	gui_list_tree_toggled_callback(cell, path_str, data, false);
}
/*}}}*/

static void gui_toggled_callback(GtkWidget* widget, gpointer param)/*{{{*/
{
	bool active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	
	orcaVM* vm = get_current_vm();
	vm->m_stack->push((orcaObject*)param);
	vm->push_param(active);
	vm->call(1);
	vm->m_stack->pop();
}
/*}}}*/

static void gui_combo_changed_callback(GtkWidget* widget, gpointer param)/*{{{*/
{
	gchar* text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget));
	string str = text;
	g_free(text);
	
	orcaVM* vm = get_current_vm();
	vm->m_stack->push((orcaObject*)param);
	vm->push_param(str);
	vm->call(1);
	vm->m_stack->pop();
}
/*}}}*/

static void gui_list_tree_changed_callback(GtkWidget* widget, gpointer param, bool list)/*{{{*/
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;

	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)) {
		orcaGtkIter* ip = new orcaGtkIter();
		signal_t* s = (signal_t*)param;
		ip->m_gp = s->owner;
		ip->m_iter = iter;
		if (list)
			ip->m_type = GUI_LIST;
		else
			ip->m_type = GUI_TREE;

		orcaVM* vm = get_current_vm();
		vm->m_stack->push(s->fun);
		vm->push_param(ip);
		vm->call(1);
		vm->m_stack->pop();
	}
}
/*}}}*/

static void gui_list_changed_callback(GtkWidget* widget, gpointer param)/*{{{*/
{
	gui_list_tree_changed_callback(widget, param, true);
}
/*}}}*/

static void gui_tree_changed_callback(GtkWidget* widget, gpointer param)/*{{{*/
{
	gui_list_tree_changed_callback(widget, param, false);
}
/*}}}*/

orcaGtk::orcaGtk()/*{{{*/
{
	gtk_init(NULL, NULL);

	set_name("gtk");
	insert_native_function("init", (object_fp)&orcaGtk::ex_init);
	insert_native_function("put", (object_fp)&orcaGtk::ex_put);
	insert_native_function("show", (object_fp)&orcaGtk::ex_show);
	insert_native_function("quit", (object_fp)&orcaGtk::ex_quit);
	insert_native_function("set_text", (object_fp)&orcaGtk::ex_set_text);
	insert_native_function("set_event", (object_fp)&orcaGtk::ex_set_event);
	insert_native_function("set_attr", (object_fp)&orcaGtk::ex_set_attr);
	insert_native_function("push_back", (object_fp)&orcaGtk::ex_push_back);

	// for list, tree
	insert_native_function("set_data", (object_fp)&orcaGtk::ex_set_data);
	insert_native_function("get_data", (object_fp)&orcaGtk::ex_get_data);

	insert_static("dialog", new orcaGtkDialog);
	init();
}
/*}}}*/

orcaData orcaGtk::ex_init(orcaVM* vm, int n) /*{{{*/
{
	if (n < 1) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	string s = vm->get_param(0).String();
	if (s == "window") type = GUI_WINDOW;
	else if (s == "fixed") type = GUI_FIXED;
	else if (s == "vbox") type = GUI_VBOX;
	else if (s == "hbox") type = GUI_HBOX;
	else if (s == "scroll") type = GUI_SCROLL;
	else if (s == "table") type = GUI_TABLE;
	else if (s == "hsep") type = GUI_HSEP;
	else if (s == "button") type = GUI_BUTTON;
	else if (s == "check") type = GUI_CHECK;
	else if (s == "radio") type = GUI_RADIO;
	else if (s == "combo") type = GUI_COMBO;
	else if (s == "label") type = GUI_LABEL;
	else if (s == "entry") type = GUI_ENTRY;
	else if (s == "menubar") type = GUI_MENUBAR;
	else if (s == "text") type = GUI_TEXT;
	else if (s == "list") type = GUI_LIST;
	else if (s == "tree") type = GUI_TREE;
	else if (s == "image") type = GUI_IMAGE;
	else if (s == "statusbar") type = GUI_STATUSBAR;
	else type = GUI_WINDOW;

	alloc();

	return NIL;
}
/*}}}*/

orcaData orcaGtk::ex_put(orcaVM* vm, int n)/*{{{*/
{
	if (n < 1) {
		throw orcaException(vm, "orca.param", "insufficient parameters");
	}

	orcaGtk* obj = dynamic_cast<orcaGtk*>(vm->get_param(0).Object());
	if (obj == NULL) {
		throw orcaException(vm, "orca.param", "native_gui type is needed");
	}
	
	switch(type)
	{
	case GUI_WINDOW:
		switch(obj->type)
		{
		case GUI_FIXED:
		case GUI_VBOX:
		case GUI_HBOX:
		case GUI_SCROLL:
		case GUI_TABLE:
			gtk_container_add(GTK_CONTAINER(handle), obj->handle);
			break;

		default:
			break;
		}

		break;

	case GUI_FIXED:
	  {
		int x = 0;
		int y = 0;

		orcaData d = obj->attr["xy"];
		if (isobj<orcaTuple>(d)) {
			orcaTuple* tp = castobj<orcaTuple>(d);
			x = tp->at(0).Integer();
			y = tp->at(1).Integer();
		}

		gtk_fixed_put(GTK_FIXED(handle), obj->handle, x, y);
	  }

		break;

	case GUI_VBOX:
	case GUI_HBOX:
		switch(obj->type)
		{
		case GUI_MENUBAR:
			gtk_box_pack_start(GTK_BOX(handle), obj->handle, FALSE, FALSE, 0);
			break;

		default:
			gtk_box_pack_start(GTK_BOX(handle), obj->handle, TRUE, TRUE, 0);
			break;
		}
		break;

	case GUI_SCROLL:
		gtk_container_add(GTK_CONTAINER(handle), obj->handle);
		break;

	case GUI_TABLE:
	  {
		int xs, xe, ys, ye;
		orcaData p1 = vm->get_param(1);
		orcaData p2 = vm->get_param(2);

		if (isobj<orcaTuple>(p1)) {
			orcaTuple* tp = castobj<orcaTuple>(p1);
			xs = tp->at(0).Integer();
			xe = tp->at(1).Integer();
		}

		if (isobj<orcaTuple>(p2)) {
			orcaTuple* tp = castobj<orcaTuple>(p2);
			ys = tp->at(0).Integer();
			ye = tp->at(1).Integer();
		}

		gtk_table_attach_defaults(GTK_TABLE(handle), obj->handle, xs, xe, ys, ye);
		break;
	  }

	default:
		break;
	}

	return NIL;
}
/*}}}*/

orcaData orcaGtk::ex_show(orcaVM* vm, int n)/*{{{*/
{
	gtk_widget_show_all(handle);
	gtk_main();

	return NIL;
}
/*}}}*/

orcaData orcaGtk::ex_quit(orcaVM* vm, int n)/*{{{*/
{
	gtk_widget_destroy(handle);
	return NIL;
}
/*}}}*/

orcaData orcaGtk::ex_set_text(orcaVM* vm, int n)/*{{{*/
{
	if (n < 1) vm->need_param();

	string str = vm->get_param(0).string_(vm);

	switch(type)
	{
	case GUI_WINDOW:
		gtk_window_set_title(GTK_WINDOW(handle), str.c_str());
		break;

	case GUI_BUTTON:
	case GUI_CHECK:
	case GUI_RADIO:
		gtk_button_set_label(GTK_BUTTON(handle), str.c_str());
		break;

	case GUI_LABEL:
		gtk_label_set_text(GTK_LABEL(handle), str.c_str());
		break;

	case GUI_TEXT:
	  {
		GtkTextBuffer *buffer;
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(handle));
		gtk_text_buffer_set_text(buffer, str.c_str(), -1);
		break;
	  }

	case GUI_STATUSBAR:
		gtk_statusbar_push(GTK_STATUSBAR(handle),
						   gtk_statusbar_get_context_id(GTK_STATUSBAR(handle), str.c_str()), 
						   str.c_str());
		break;

	case GUI_ENTRY:
		gtk_entry_set_text(GTK_ENTRY(handle), str.c_str());
		break;
	}

	text = str;
	return NIL;
}
/*}}}*/

orcaData orcaGtk::ex_set_attr(orcaVM* vm, int n)/*{{{*/
{
	if (n < 2) vm->need_param();
	orcaData key = vm->get_param(0);
	orcaData val = vm->get_param(1);
	attr[key] = val;

	if ((type == GUI_LIST || type == GUI_TREE) && is<TYPE_STR>(key)) {
		if (key.s() == "column") {
			orcaList* lp = castobj<orcaList>(val);
			if (lp == NULL) {
				throw orcaException(vm, "orca.type", "list type is required");
			}

			int width = lp->size();
			GtkCellRenderer *renderer;
			GtkTreeViewColumn *column;

			vector<pair<GtkCellRenderer*, orcaObject*> > signals;

			GType* types = new GType[width];

			for (int i=0; i<width; i++) {
				orcaTuple* tp = NULL;
				if (is<TYPE_STR>(lp->at(i))) {
					renderer = gtk_cell_renderer_text_new();
					column = gtk_tree_view_column_new_with_attributes(lp->at(i).String().c_str(), renderer, "text", i, NULL);
					types[i] = G_TYPE_STRING;
				}
				else if (tp = castobj<orcaTuple>(lp->at(i))) {
					string type = tp->at(1).String();
					if (type == "string") {
						renderer = gtk_cell_renderer_text_new();
						column = gtk_tree_view_column_new_with_attributes(tp->at(0).String().c_str(), renderer, "text", i, NULL);
						types[i] = G_TYPE_STRING;
					}
					else if (type == "toggle") {
						renderer = gtk_cell_renderer_toggle_new();
						column = gtk_tree_view_column_new_with_attributes(tp->at(0).String().c_str(), renderer, "active", i, NULL);

						if (tp->size() >= 3) {
							pair<GtkCellRenderer*, orcaObject*> p;
							p.first = renderer;
							p.second = tp->at(2).Object();
							signals.push_back(p);
						}

						types[i] = G_TYPE_BOOLEAN;
					}
				}

				gtk_tree_view_append_column(GTK_TREE_VIEW(handle), column);
			}

			if (type == GUI_LIST)
				store = GTK_TREE_MODEL(gtk_list_store_newv(width, types));
			else
				store = GTK_TREE_MODEL(gtk_tree_store_newv(width, types));

			delete types;

			gtk_tree_view_set_model(GTK_TREE_VIEW(handle), store);

			// register toggle signal
			if (!signals.empty()) {
				GtkTreeModel *model = gtk_tree_view_get_model (GTK_TREE_VIEW(handle));
				for (int i=0; i<signals.size(); i++) {
					signal_t* p = new signal_t;

					p->fun = signals[i].second;
					p->tree = model;
					p->owner = this;
					m_signals.push_back(p);

					if (type == GUI_LIST) {
						g_signal_connect(signals[i].first, "toggled",
										 G_CALLBACK(gui_list_toggled_callback), (gpointer)p);
					}
					else {
						g_signal_connect(signals[i].first, "toggled",
										 G_CALLBACK(gui_tree_toggled_callback), (gpointer)p);
					}
				}
			}

		}
	}
	else if (type == GUI_WINDOW && is<TYPE_STR>(key)) {
		if (key.s() == "wh") {
			if (isobj<orcaTuple>(val)) {
				orcaTuple* tp = castobj<orcaTuple>(val);
				int w = tp->at(0).Integer();
				int h = tp->at(1).Integer();
				gtk_window_set_default_size(GTK_WINDOW(handle), w, h);
				gtk_window_resize(GTK_WINDOW(handle), w, h);
			}
		}
		else if (key.s() == "xy") {
			if (isobj<orcaTuple>(val)) {
				orcaTuple* tp = castobj<orcaTuple>(val);
				int x = tp->at(0).Integer();
				int y = tp->at(1).Integer();
				gtk_window_move(GTK_WINDOW(handle), x, y);
			}
		}
		else if (key.s() == "resizable") {
			bool flag = val.Boolean();
			gtk_window_set_resizable(GTK_WINDOW(handle), flag);
		}
	}
	else if (type == GUI_RADIO && is<TYPE_STR>(key)) {
		if (key.s() == "group") {
			orcaObject* op = attr["group"].Object();
			orcaGtk* gp = castobj<orcaGtk>(op->get_member("handle"));
			if (gp == NULL) {
				throw orcaException(vm, "orca.param", "invalid radio");
			}

			GSList* group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(gp->handle));
			gtk_radio_button_set_group(GTK_RADIO_BUTTON(handle), group);
		}
	}
	else if (type == GUI_TABLE && is<TYPE_STR>(key)) {
		if (key.s() == "wh") {
			orcaData d = attr["wh"];
			if (isobj<orcaTuple>(d)) {
				orcaTuple* tp = castobj<orcaTuple>(d);
				int w = tp->at(0).Integer();
				int h = tp->at(1).Integer();
				handle = gtk_table_new(w, h, TRUE);
			}
		}
	}
	else if (type == GUI_BUTTON && is<TYPE_STR>(key)) {
		if (key.s() == "wh") {
			orcaData d = attr["wh"];
			if (isobj<orcaTuple>(d)) {
				orcaTuple* tp = castobj<orcaTuple>(val);
				int w = tp->at(0).Integer();
				int h = tp->at(1).Integer();
				gtk_widget_set_size_request(handle, w, h);
			}
		}
	}
	else if (type == GUI_IMAGE && is<TYPE_STR>(key)) {
		if (key.s() == "file") {
			gtk_image_set_from_file(GTK_IMAGE(handle), val.String().c_str());
		}

		if (key.s() == "file" || key.s() == "wh") {
			orcaData d = attr["wh"];
			if (isobj<orcaTuple>(d)) {
				orcaTuple* tp = castobj<orcaTuple>(d);
				int w = tp->at(0).Integer();
				int h = tp->at(1).Integer();

				GdkPixbuf *pixbuf =	gtk_image_get_pixbuf(GTK_IMAGE(handle));
				if (pixbuf == NULL) {
					return NIL;
				}
				
				pixbuf = gdk_pixbuf_scale_simple(pixbuf, w, h, GDK_INTERP_BILINEAR);
				gtk_image_set_from_pixbuf(GTK_IMAGE(handle), pixbuf);
			}
		}
	}


	return NIL;
}
/*}}}*/

orcaData orcaGtk::ex_set_event(orcaVM* vm, int n)/*{{{*/
{
	if (n < 2) vm->need_param();

	string e = vm->get_param(0).String();
	orcaObject* action = vm->get_param(1).Object();

	if (e == "clicked") {
		g_signal_connect(handle, "clicked", G_CALLBACK(gui_callback), (gpointer)action);
	}
	else if (e == "changed") {
		if (type == GUI_COMBO)
			g_signal_connect(G_OBJECT(handle), "changed", G_CALLBACK(gui_combo_changed_callback), (gpointer)action);
		else if (type == GUI_LIST || GUI_TREE) {
			GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(handle)); 
			signal_t* s = new signal_t;
			s->owner = this;
			s->fun = action;
			m_signals.push_back(s);

			if (type == GUI_LIST)
				g_signal_connect(G_OBJECT(selection), "changed",
								 G_CALLBACK(gui_list_changed_callback), (gpointer)s);
			else
				g_signal_connect(G_OBJECT(selection), "changed",
								 G_CALLBACK(gui_tree_changed_callback), (gpointer)s);
		}
	}
	else if (e == "toggled") {
		g_signal_connect(handle, "toggled", G_CALLBACK(gui_toggled_callback), (gpointer)action);
	}
	else if (e == "destroy") {
		g_signal_connect(handle, "destroy", G_CALLBACK(gui_callback), (gpointer)action);
	}

	return NIL;
}
/*}}}*/

static void set_list_to_store(orcaList* lp, GtkTreeModel* store, GtkTreeIter* iter, handle_type type)/*{{{*/
{
	orcaListIter it = lp->begin();
	for (int i=0; it != lp->end(); ++it, i++) {
		GValue value = { 0, };

		if (is<TYPE_STR>(*it)) {
			g_value_init(&value, G_TYPE_STRING);
			g_value_set_string(&value, (*it).String().c_str());
		}
		else if (is<TYPE_BOOL>(*it)) {
			g_value_init(&value, G_TYPE_BOOLEAN);
			g_value_set_boolean(&value, (*it).i());
		}

		if (type == GUI_LIST)
			gtk_list_store_set_value(GTK_LIST_STORE(store), iter, i, &value);
		else
			gtk_tree_store_set_value(GTK_TREE_STORE(store), iter, i, &value);
	}
}
/*}}}*/

orcaData orcaGtk::ex_push_back(orcaVM* vm, int n)/*{{{*/
{
	switch (type)
	{
	case GUI_MENUBAR:
	  {
		if (n < 2) vm->need_param();

		string name = vm->get_param(0).String();
		orcaList* lp = castobj<orcaList>(vm->get_param(1));
		if (lp == NULL) {
			throw orcaException(vm, "orca.type", "list type is required");
		}

		GtkWidget* menu = gtk_menu_new();
		GtkWidget* title = gtk_menu_item_new_with_label(name.c_str());

		orcaListIter li = lp->begin();
		for (; li != lp->end(); ++li) {
			name = (*li).String();
			if (++li == lp->end()) break;
			orcaObject* action = (*li).Object();

			GtkWidget* item = gtk_menu_item_new_with_label(name.c_str());
			gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
			g_signal_connect(item, "activate", G_CALLBACK(gui_callback), (gpointer)action);
		}

		gtk_menu_item_set_submenu(GTK_MENU_ITEM(title), menu);
		gtk_menu_shell_append(GTK_MENU_SHELL(handle), title);
		break;
	  }

	case GUI_LIST:
	case GUI_TREE:
	  {
		if (n < 1) vm->need_param();

		GtkTreeIter iter;

		if (type == GUI_LIST)
			gtk_list_store_append(GTK_LIST_STORE(store), &iter);
		else
			gtk_tree_store_append(GTK_TREE_STORE(store), &iter, NULL);

		orcaList* lp = castobj<orcaList>(vm->get_param(0));
		if (lp == NULL) {
			throw orcaException(vm, "orca.type", "list type is required");
		}

		set_list_to_store(lp, store, &iter, type);
		break;
	  }

	case GUI_COMBO:
	  {
		if (n < 1) vm->need_param();
		
		gtk_combo_box_append_text(GTK_COMBO_BOX(handle), vm->get_param(0).String().c_str());
		break;
	  }
	}

	return NIL;
}
/*}}}*/

void orcaGtk::alloc()/*{{{*/
{
	switch(type)
	{
	case GUI_WINDOW:
		handle = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(handle), text.c_str());
		gtk_window_set_default_size(GTK_WINDOW(handle), 800, 600);
		gtk_window_set_position(GTK_WINDOW(handle), GTK_WIN_POS_CENTER);
		g_signal_connect_swapped(G_OBJECT(handle), "destroy",
								 G_CALLBACK(gtk_main_quit), G_OBJECT(handle));
		break;

	case GUI_FIXED:
		handle = gtk_fixed_new();
		break;

	case GUI_VBOX:
		handle = gtk_vbox_new(FALSE, 0);
		break;

	case GUI_HBOX:
		handle = gtk_hbox_new(FALSE, 0);
		break;

	case GUI_HSEP:
		handle = gtk_hseparator_new();
		break;

	case GUI_BUTTON:
		handle = gtk_button_new_with_label(text.c_str());
		gtk_widget_set_size_request(handle, 100, 100);
		break;

	case GUI_CHECK:
		handle = gtk_check_button_new_with_label(text.c_str());
		break;

	case GUI_RADIO:
		handle = gtk_radio_button_new_with_label (NULL, text.c_str());
		break;

	case GUI_COMBO:
		handle = gtk_combo_box_new_text();
		break;

	case GUI_LABEL:
		handle = gtk_label_new(text.c_str());
		break;

	case GUI_ENTRY:
		handle = gtk_entry_new();
		break;

	case GUI_TEXT:
		handle = gtk_text_view_new();
		break;

	case GUI_MENUBAR:
		handle = gtk_menu_bar_new();
		break;

	case GUI_LIST:
	case GUI_TREE:
		handle = gtk_tree_view_new();
		gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(handle), TRUE);
		break;

	case GUI_SCROLL:
		handle = gtk_scrolled_window_new(NULL, NULL);
		break;

	case GUI_TABLE:
		handle = NULL;
		break;

	case GUI_IMAGE:
		handle = gtk_image_new();
		break;

	case GUI_STATUSBAR:
		handle = gtk_statusbar_new();
		break;
	}
}
/*}}}*/

orcaData orcaGtk::ex_set_data(orcaVM* vm, int n)/*{{{*/
{
	if (n < 2) vm->need_param();
	orcaData key = vm->get_param(0);
	orcaData val = vm->get_param(1);

	if (type == GUI_LIST || GUI_TREE) {
		int nth = key.Integer();

		GtkTreeIter iter;
		gtk_tree_model_get_iter_first(store, &iter);
		
		for (int i=0; i<nth; i++) {
			if (!gtk_tree_model_iter_next(store, &iter))
				throw orcaException(vm, "orca.index", "out of index");
		}

		orcaList* lp = castobj<orcaList>(val);
		if (lp == NULL) {
			throw orcaException(vm, "orca.type", "list type is required");
		}

		set_list_to_store(lp, store, &iter, type);
	}

	return NIL;
}
/*}}}*/

orcaData orcaGtk::ex_get_data(orcaVM* vm, int n)/*{{{*/
{
	if (n < 1) vm->need_param();
	orcaData key = vm->get_param(0);

	if (type == GUI_LIST || type == GUI_TREE) {
		if (is<TYPE_INT>(key)) {
			int nth = key.Integer();

			GtkTreeIter iter;
			gtk_tree_model_get_iter_first(store, &iter);

			for (int i=0; i<nth; i++) {
				if (!gtk_tree_model_iter_next(store, &iter))
					throw orcaException(vm, "orca.index", "out of index");
			}

			orcaList* lp = new orcaList();

			int width = gtk_tree_model_get_n_columns(store);
			for (int i=0; i<width; i++) {
				GValue value = { 0, };
				gtk_tree_model_get_value(store, &iter, i, &value);

				GType t = value.g_type;
				if (t == G_TYPE_STRING) {
					char* cp = (char*)g_value_get_string(&value);
					if (cp == NULL) cp = (char*)"";
					lp->push_back(cp);
				}
				else if (t == G_TYPE_BOOLEAN) {
					bool r = g_value_get_boolean(&value);
					lp->push_back(r);
				}
				else {
					lp->push_back(NIL);
				}

				g_value_unset(&value);
			}

			return lp;
		}

		string str = key.String();
		if (str == "begin") {
			orcaGtkIter* bp = new orcaGtkIter();
			bp->m_gp = this;
			gtk_tree_model_get_iter_first(store, &bp->m_iter);
			if (type == GUI_LIST)
				bp->m_type = GUI_LIST;
			else
				bp->m_type = GUI_TREE;

			return bp;
		}
		else if (type == GUI_TREE && str == "branch") {
			orcaTuple* path = castobj<orcaTuple>(vm->get_param(1));

			if (path == NULL) {
				return NIL;
			}
			
			orcaGtkIter* bp = new orcaGtkIter();
			bp->m_gp = this;
			bp->m_type = GUI_TREE;
			GtkTreeIter iter;
			GtkTreeIter parent;
			for (int i=0; i<path->size(); i++) {
				if (i==0) {
					gtk_tree_model_get_iter_first(store, &iter);
					for (int j=0; j<path->at(0).Integer(); j++) {
						if (!gtk_tree_model_iter_next(store, &iter))
							throw orcaException(vm, "orca.index", "out of index");
					}

					parent = iter;
					bp->m_iter = iter;
					continue;
				}
				
				if (!gtk_tree_model_iter_nth_child(store, &iter, &parent, path->at(i).Integer()))
						throw orcaException(vm, "orca.index", "out of index");

				parent = iter;
				bp->m_iter = iter;
			}

			return bp;
		}
	}
	else if (type == GUI_ENTRY) {
		if (key.String() == "text") {
			char* p = gtk_editable_get_chars(GTK_EDITABLE(handle), 0, -1);
			return p;
		}
	}

	return NIL;
}
/*}}}*/

orcaData orcaGtkDialog::ex_messagebox(orcaVM* vm, int n)/*{{{*/
{
	GtkWidget* window = NULL;
	if (is<TYPE_OBJ>(vm->get_param(0))) {
		orcaObject* op = vm->get_param(0).o();
		orcaGtk* gp = castobj<orcaGtk>(op->get_member("handle"));
		if (gp != NULL) {
			window = gp->handle;
		}
	}

	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(window),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_OK,
									"Download Completed", "title");
	gtk_window_set_title(GTK_WINDOW(dialog), "Information");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

	return NIL;
}
/*}}}*/

orcaData orcaGtkDialog::ex_fileopen(orcaVM* vm, int n)/*{{{*/
{
	GtkWidget* window = NULL;
	if (is<TYPE_OBJ>(vm->get_param(0))) {
		orcaObject* op = vm->get_param(0).o();
		orcaGtk* gp = castobj<orcaGtk>(op->get_member("handle"));
		if (gp != NULL) {
			window = gp->handle;
		}
	}

	string filename;
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Open File",
										GTK_WINDOW(window),
										GTK_FILE_CHOOSER_ACTION_OPEN,
										GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
										GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
										NULL);
 
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		char *cp = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		filename = cp;
		g_free (cp);
	}
 
	gtk_widget_destroy (dialog);

	return filename;
}
/*}}}*/

orcaData orcaGtkDialog::ex_filesave(orcaVM* vm, int n)/*{{{*/
{
	GtkWidget* window = NULL;
	if (is<TYPE_OBJ>(vm->get_param(0))) {
		orcaObject* op = vm->get_param(0).o();
		orcaGtk* gp = castobj<orcaGtk>(op->get_member("handle"));
		if (gp != NULL) {
			window = gp->handle;
		}
	}

	string filename;
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Save File",
										GTK_WINDOW(window),
										GTK_FILE_CHOOSER_ACTION_SAVE,
										GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
										GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
										NULL);

	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
 
#if 0
 if (user_edited_a_new_document)
   {
	 gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), default_folder_for_saving);
	 gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "Untitled document");
   }
 else
   gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (dialog), filename_for_existing_document);
 
#endif
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		char *cp = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		filename = cp;
		g_free (cp);
	}
 
	gtk_widget_destroy (dialog);

	return filename;
}
/*}}}*/

orcaData orcaGtkIter::ex_child_size(orcaVM* vm, int n)/*{{{*/
{
	return gtk_tree_model_iter_n_children(m_gp->store, &m_iter);
}
/*}}}*/

orcaData orcaGtkIter::ex_child_begin(orcaVM* vm, int n)/*{{{*/
{
	orcaGtkIter* ip = (orcaGtkIter*)clone(this);
	GtkTreeIter parent = ip->m_iter;
	gtk_tree_model_iter_children(ip->m_gp->store, &ip->m_iter, &parent);
	return ip;
}
/*}}}*/

orcaData orcaGtkIter::ex_push_child(orcaVM* vm, int n)/*{{{*/
{
	if (n<1) vm->need_param();

	GtkTreeIter iter;
	gtk_tree_store_append(GTK_TREE_STORE(m_gp->store), &iter, &m_iter);

	orcaList* lp = castobj<orcaList>(vm->get_param(0));
	if (lp == NULL) {
		throw orcaException(vm, "orca.type", "list type is required");
	}

	set_list_to_store(lp, m_gp->store, &iter, m_type);
	return NIL;
}
/*}}}*/

orcaData orcaGtkIter::ex_next(orcaVM* vm, int n)/*{{{*/
{
	if (!gtk_tree_model_iter_next(m_gp->store, &m_iter)) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	return this;
}
/*}}}*/

orcaData orcaGtkIter::ex_parent(orcaVM* vm, int n)/*{{{*/
{
	orcaGtkIter* ip = new orcaGtkIter();
	ip->m_gp = m_gp;
	ip->m_type = m_type;

	bool ret = gtk_tree_model_iter_parent(m_gp->store, &ip->m_iter, &m_iter);
	if (ret == false) {
		delete ip;
		return NIL; 
	}

	return ip;
}
	
/*}}}*/

orcaData orcaGtkIter::ex_insert(orcaVM* vm, int n)/*{{{*/
{
	if (n < 1) vm->need_param();

	GtkTreeIter iter;

	if (m_type == GUI_LIST) 
		gtk_list_store_insert_before(GTK_LIST_STORE(m_gp->store), &iter, &m_iter);
	else {
		GtkTreeIter parent;
		GtkTreeIter* pp = NULL;
		if (gtk_tree_model_iter_parent(m_gp->store, &parent, &m_iter))
			pp = &parent;

		gtk_tree_store_insert_before(GTK_TREE_STORE(m_gp->store), &iter, pp, &m_iter);
	}

	orcaList* lp = castobj<orcaList>(vm->get_param(0));
	if (lp == NULL) {
		throw orcaException(vm, "orca.type", "list type is required");
	}

	set_list_to_store(lp, m_gp->store, &iter, m_type);
	return NIL;
}
	
/*}}}*/

orcaData orcaGtkIter::operator()(orcaVM* vm, int n)/*{{{*/
{
	if (n > 0) {
		orcaList* lp = castobj<orcaList>(vm->get_param(0));
		if (lp == NULL) {
			throw orcaException(vm, "orca.type", "list type is required");
		}

		set_list_to_store(lp, m_gp->store, &m_iter, m_type);
		return lp;
	}
	else {
		orcaList* lp = new orcaList();

		int width = gtk_tree_model_get_n_columns(m_gp->store);
		for (int i=0; i<width; i++) {
			GValue value = { 0, };
			gtk_tree_model_get_value(m_gp->store, &m_iter, i, &value);

			GType t = value.g_type;
			if (t == G_TYPE_STRING) {
				char* cp = (char*)g_value_get_string(&value);
				if (cp == NULL) cp = (char*)"";
				lp->push_back(cp);
			}
			else if (t == G_TYPE_BOOLEAN) {
				bool r = g_value_get_boolean(&value);
				lp->push_back(r);
			}
			else {
				lp->push_back(NIL);
			}

			g_value_unset(&value);
		}

		return lp;
	}
}
/*}}}*/

