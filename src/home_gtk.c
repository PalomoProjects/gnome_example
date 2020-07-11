/*
 * home_gtk.c
 *
 *  Created on: Mar 26, 2019
 *      Author: gualberto
 */

#include "home_gtk.h"
#include "widget_gtk.h"
#include "catalog_gtk.h"
#include "sqlitedemo.h"




/*Load CSS file*/
void load_css_file(void);

/** Prototype window destroy*/
void on_home_gtk_destroy();

/** printing time with timer handler*/
gboolean show_date_time_handler(root_widgets *widgets);

/** slide image handler*/
gboolean show_slide_image_handler(root_widgets *widgets);

/** Prototype open widgets windows handler*/
void show_widgets_window(GtkButton *mybutton);

/** Prototype open catalog windows handler*/
void show_catalog_window(GtkButton *mubutton);









/* Load css file*/
void load_css_file(void){
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;
	GError *error = NULL;

	provider = gtk_css_provider_new ();
	display = gdk_display_get_default ();
	screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	const gchar *myCssFile = "mystyle.css";
	gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
}

/*Open widgets window*/
void show_widgets_window(GtkButton *mybutton){

	/** show widgets windows*/
	puts("BUTTON OPEN WIDGET WINDOW");
	flag_tmr = FALSE;
	start_widget_gtk();
	puts("WINDOW OPENED");
	puts("CONTINUE MAIN");
}

/*Open catalog window*/
void show_catalog_window(GtkButton *mybutton){

	/** show widgets windows*/
	puts("BUTTON OPEN CATALOG WINDOW");
	start_catalog_gtk();
	puts("CATALOG OPENED");
	puts("CONTINUE MAIN");
}

/*Open sqlite table window*/
void show_sqlite_window(GtkButton *mybutton){

	/** show widgets windows*/
	puts("BUTTON OPEN SQLITE WINDOW");
	start_sqlite_window();
	puts("SQLITE OPENED");
	puts("CONTINUE MAIN");
}


/** handler for the 30 second timer tick*/
gboolean show_slide_image_handler(root_widgets *widgets){

	gchar *files[] = {"1.png", "2.png", "3.png", "4.png", "5.png", "6.png", "7.png", "8.png"};
	gchar *descrip[] = {
			"Read Finger USB application",
			"Scan code bar application",
			"Interface for payment in a Bus",
			"Vending machine software with uM",
			"Vending machine software with uM",
			"Interface for Locker machine with NFC cards",
			".NET with Visual Basic application",
			"Scan code bar with Locker system"
	};

	if (dataaux == 7)
		dataaux = 0;

	/** Write project description*/
	gtk_label_set_text(GTK_LABEL(widgets->lbl_prj_descr), descrip[dataaux]);

	/** Load profile image*/
	gtk_image_set_from_file (GTK_IMAGE (widgets->img_projects), files[dataaux]);

	dataaux++;

	return TRUE;
}


/** handler for the 1 second timer tick*/
gboolean show_date_time_handler(root_widgets *widgets){
    GDateTime *date_time;
    gchar *dt_format;

    date_time = g_date_time_new_now_local();// get local time
    dt_format = g_date_time_format(date_time, "%H:%M:%S    %A");// 24hr time format
    gtk_label_set_text(GTK_LABEL(widgets->lbl_time_date), dt_format);// update label
    g_free (dt_format);

    return TRUE;
}


void start_home_gtk(void){
	GError *error = NULL;

	root_widgets *_myWidgets;
	const gchar *_uiFile= "gui_main.glade";
	GtkBuilder *_builder;

	/*This function loads the all widgets in css*/
	load_css_file();

	/* Create new GtkBuilder object */
	_builder = gtk_builder_new();

	if(!gtk_builder_add_from_file(_builder, _uiFile, &error ))
	{
		//g_warn_message( "%s", error->message );
		g_free(error);
		gtk_main_quit();
	}

	/* Allocate data structure */
	_myWidgets = g_slice_new( root_widgets );

	/**Get address from pointer objects*/
	_myWidgets->main_window = GTK_WIDGET(gtk_builder_get_object(_builder,"main_window"));
	_myWidgets->img_profile = GTK_IMAGE(gtk_builder_get_object( _builder, "image1" ));
	_myWidgets->img_projects = GTK_IMAGE(gtk_builder_get_object( _builder, "image2" ));
	_myWidgets->lbl_time_date = GTK_LABEL(gtk_builder_get_object( _builder, "label3" ));
	_myWidgets->lbl_prj_descr = GTK_LABEL(gtk_builder_get_object( _builder, "label2" ));
	_myWidgets->btn_widgets_window = GTK_BUTTON(gtk_builder_get_object( _builder, "button3" ));
	_myWidgets->btn_catalog_window = GTK_BUTTON(gtk_builder_get_object( _builder, "button2" ));
	_myWidgets->btn_sqlite_window = GTK_BUTTON(gtk_builder_get_object( _builder, "button7" ));

	_myWidgets->page1 = GTK_WIDGET(gtk_builder_get_object(_builder, "page1"));
	_myWidgets->content1 = GTK_WIDGET(gtk_builder_get_object(_builder, "textview1"));
	_myWidgets->page2 = GTK_WIDGET(gtk_builder_get_object(_builder, "page2"));
	_myWidgets->content2 = GTK_WIDGET(gtk_builder_get_object(_builder, "textview2"));
	_myWidgets->page3 = GTK_WIDGET(gtk_builder_get_object(_builder, "page3"));
	_myWidgets->content3 = GTK_WIDGET(gtk_builder_get_object(_builder, "textview3"));
	_myWidgets->notebook = GTK_WIDGET(gtk_builder_get_object(_builder, "notebook1"));

	/* Connect signals */
	gtk_builder_connect_signals(_builder,_myWidgets);

	/* Destroy builder, since we don't need it anymore */
	g_object_unref( G_OBJECT( _builder ) );

	/** Set handler current time label*/
	g_timeout_add_seconds(1, (GSourceFunc)show_date_time_handler, _myWidgets);

	/** Set handler slide image*/
	g_timeout_add_seconds(5, (GSourceFunc)show_slide_image_handler, _myWidgets);

	/** Set Width and Height window*/
	gtk_window_set_default_size (GTK_WINDOW(_myWidgets->main_window), 800,480);

	/** Set window position*/
	GtkWindowPosition position;
	position = GTK_WIN_POS_CENTER;
	gtk_window_set_position(GTK_WINDOW(_myWidgets->main_window), position);

	/** Load profile image*/
	GdkPixbufAnimation * animation;
	animation = gdk_pixbuf_animation_new_from_file ("1.gif", NULL);
	gtk_image_set_from_animation (GTK_IMAGE(_myWidgets->img_profile), animation);


	/** Write project description*/
	gtk_label_set_text(GTK_LABEL(_myWidgets->lbl_prj_descr),
			"Read Finger USB application");
	/** Load image on project section*/
	gchar *filename2 = "1.png";
	gtk_image_set_from_file (GTK_IMAGE (_myWidgets->img_projects), filename2);
	dataaux++;

	/** Set TextBox*/
	GtkTextBuffer *buffer;
	gchar *mytext_data = g_malloc(512);

	g_strlcpy(mytext_data,"I really like spent my time with my family one of my favorite places is theaters, in my free time I want to read a great novel or watch a good movie. \n", 256);
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (_myWidgets->content1));
	gtk_text_buffer_set_text (buffer, mytext_data, -1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(_myWidgets->content1), FALSE);


	g_strlcpy(mytext_data,"Jesus Palomo\nEmbeeded System Engineer\nMy background is in C and C++ on x86 and ARM.\nI also have a big interest in web programming in PHP and I'm fan of Python.\n", 512);
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (_myWidgets->content2));
	gtk_text_buffer_set_text (buffer, mytext_data, -1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(_myWidgets->content2), FALSE);

	g_strlcpy(mytext_data,"jgualberto.palomo@gmail.com\nMobile: +52 55 5210 2467 \n ", 128);
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (_myWidgets->content3));
	gtk_text_buffer_set_text (buffer, mytext_data, -1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(_myWidgets->content3), FALSE);

	/* Show window. All other widgets are automatically shown by GtkBuilder */
	gtk_widget_show( _myWidgets->main_window );

}


void on_home_gtk_destroy(){
	printf("BYE BYE... \n");
	gtk_main_quit();
}





