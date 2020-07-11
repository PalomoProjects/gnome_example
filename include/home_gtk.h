/*
 * home_gtk.h
 *
 *  Created on: Mar 26, 2019
 *  Author: gualberto
 */

 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <gtk/gtk.h>

#ifndef HOME_GTK_H_
#define HOME_GTK_H_

/** Main data structure definition */
typedef struct {
	 /* Widgets */
	    GtkWidget *main_window;  /* Main application window */
	    GtkLabel *lbl_time_date;  /* time stamp Label */
	    GtkImage *img_profile;  /* Profile picture Image*/
	    GtkLabel *lbl_prj_descr;  /* Project description Label */
	    GtkImage *img_projects;  /* Project GIF container image */
	    GtkButton *btn_widgets_window;  /* Open widgets window */
	    GtkButton *btn_catalog_window;  /* Open widgets window */
	    GtkButton *btn_pos_window;  /* Open point of sale window */
	    GtkButton *btn_sqlite_window;

	    GtkWidget *page1;
	    GtkWidget *content1;
		GtkWidget *page2;
		GtkWidget *content2;
		GtkWidget *page3;
		GtkWidget *content3;
		GtkWidget *notebook;
}root_widgets;

unsigned int dataaux;

/** Prototype release window*/
void start_home_gtk(void);



#endif /* HOME_GTK_H_ */
