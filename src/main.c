/********************************************
*  File: main.c
*  Created on: Mar 26, 2019
*  Author: gualberto
*  Description: main entry point for this example
********************************************/

#include "widget_gtk.h"


int main(int argc, char **argv) {

	object widget;					/* data structures with widgets */
	ux_control control;			/* display properties */

	/* Init GTK+ */
	gtk_init( &argc, &argv);

	/* Set window position */
	control.position = GTK_WIN_POS_CENTER;

	/* show main windows */
	if (init_widget_gtk(&widget, &control, GTK_UX_FILE, GTK_CSS_FILE) != true){
		gtk_main_quit();
		return 0;
	}

	/* Start main loop */
	gtk_main();

	return 0;
}
