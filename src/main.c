/*
 * main.c
 *
 *  Created on: Mar 26, 2019
 *      Author: gualberto
 */


#include "home_gtk.h"
#include "sqlite3.h"


int main(int argc, char **argv) {

	signed char variable;

	/* Init GTK+ */
	gtk_init( &argc, &argv);

	/** show main windows*/
	start_home_gtk();

	/* Start main loop */
	gtk_main();

}

