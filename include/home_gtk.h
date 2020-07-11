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
}root_widgets;

/** Prototype release window*/
void start_home_gtk(void);

#endif /* HOME_GTK_H_ */
