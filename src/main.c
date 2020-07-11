/*
 * main.c
 *
 *  Created on: Mar 26, 2019
 *      Author: gualberto
 */


#include "home_gtk.h"

int main(int argc, char **argv) {

	/* Init GTK+ */
	gtk_init( &argc, &argv);

	/** show main windows*/
	start_home_gtk();

	/* Start main loop */
	gtk_main();

}
