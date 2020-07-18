/* *******************************************
 *  File: widget_gtk.h
 *  Created on: July 17, 2020
 *  Author: gualberto
 *  Description:
 ********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <gtk/gtk.h>

#ifndef WIDGET_GTK_H_
#define WIDGET_GTK_H_

#define GTK_UX_WINDOW_NAME              "widgets_window"
#define GTK_UX_FILE									    "glade/gui_main.glade"
#define GTK_CSS_FILE                    "css/mystyle.css"

/* Main data structure definition */
typedef struct {
  	GtkWidget *window;  					      /* window */
    GObject *button5; 							    /* button */
  	GObject *label16; 								  /* label */
    GObject *comboboxtext1; 	          /* comboboxtext1 */
    GObject *label20; 									/* label */
    GObject *checkbutton1; 						  /* checkbutton */
  	GObject *checkbutton2; 						  /* checkbutton */
  	GObject *image3; 										/* image */
    GObject *radiobutton1; 							/* radiobutton */
    GObject *radiobutton2; 							/* radiobutton*/
    GObject *image4; 									  /* image */
    GObject *scale_obj; 								/* Scale object*/
  	GObject *h_scale;										/* h scale */
  	GObject *adjustment1;						    /* adjustment */
  	GObject *levelbar1;								  /* levelbar */
    GObject *progressbar1; 				      /* Progress bar */
  	GObject *label22; 							    /* Label */
  	GObject *switch1; 								  /* Switch */
  	GObject *spinner1; 							    /* Spinner */
}object;

/* display  */
typedef struct{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    GtkBuilder *builder; 	              /* Build an interface from an XML UI definition */
    GtkWindowPosition position;
}ux_control;

/* initialization widget window */
bool init_widget_gtk(object *widget, ux_control *screen, const gchar *glade, const gchar *css);

#endif
