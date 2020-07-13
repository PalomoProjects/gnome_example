/*
 * widget_gtk.h
 *
 *  Created on: Mar 28, 2019
 *      Author: gualberto
 */

#ifndef WIDGET_GTK_H_
#define WIDGET_GTK_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

/** Main data structure definition */
typedef struct {
	 /* Widgets */
	    GtkWidget *widgets_window;  /* Main application window */

	    GtkProgressBar *progress_bar; /* Progress bar object*/
	    GtkLabel *lbl_progressb; /* Label for show the progress bar value*/

	    GtkSwitch *switch_obj; /* Switch for active and deactivate spinner */
	    GtkSpinner *spinner_obj; /* Spinner object */

	    GtkButton *btn_counter; /* Button for counter*/
	    GtkLabel *lbl_counter; /* Label for print Object object */

	    GtkWidget *scale_obj; /* Scale object*/

	    GtkComboBoxText *combo_box_txt_obj; /* */
	    GtkLabel *lbl_combo; /* */

	    GtkCheckButton *chk_btn_1; /** */
	    GtkCheckButton *chk_btn_2; /** */
	    GtkImage *img_val; /** */

	    GtkRadioButton *r_btn_1; /** */
	    GtkRadioButton *r_btn_2; /** */
	    GtkImage *img_val_r; /** */

	    GtkScale *h_scale;
	    GtkAdjustment *hadjustment;


	    GtkLevelBar *mylvl_bar;

}controls;

/** initialization widget window */
void start_widget_gtk(void);

#endif
