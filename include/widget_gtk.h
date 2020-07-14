/*
 * widget_gtk.h
 *
 *  Created on: Mar 28, 2019
 *      Author: gualberto
 */

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
  	GtkWidget *window;  					/* Main application window */
    GObject *button5; 							/* Button for counter*/
  	GObject *label16; 								/* Label for print Object object */
    GObject *comboboxtext1; 	/* */
    GObject *label20; 									/* */
    GObject *checkbutton1; 						/* */
  	GObject *checkbutton2; 						/* */
  	GObject *image3; 										/* */
    GObject *radiobutton1; 							/* */
    GObject *radiobutton2; 							/* */
    GObject *image4; 									/* */
    GObject *scale_obj; 								/* Scale object*/
  	GObject *h_scale;										/* */
  	GObject *adjustment1;						/* */
  	GObject *levelbar1;								/* */
    GObject *progressbar1; 				/* Progress bar object*/
  	GObject *label22; 							/* Label for show the progress bar value*/
  	GtkSwitch *switch1; 								/* Switch for active and deactivate spinner */
  	GtkSpinner *spinner1; 							/* Spinner object */
}object;

/* display  */
typedef struct{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    GtkBuilder *builder; 	/* Build an interface from an XML UI definition */
    GtkWindowPosition position;
}ux_control;

/* initialization widget window */
bool init_widget_gtk(object *widget, ux_control *screen, const gchar *glade, const gchar *css);

#endif
