/********************************************
 *  File: widget_gtk.c
 *  Created on: July 17, 2020
 *  Author: gualberto
 *  Description:
 *********************************************/
#include "widget_gtk.h"


gint valuepb = 0;
gboolean flag_tmr = true;
gboolean flag_switch = false;
int counter = 0;


void on_clicked_button5(GtkButton *btn_counter, object *widget);
void on_clicked_comboboxtext1(GtkComboBox *comboboxtext1, object *widget);
void on_clicked_checkbutton(GtkToggleButton *toggle_button, object *widgets);
void on_clicked_radiobuton (GtkToggleButton *togglebutton, object *widget);
gboolean tmr_progress_bar_handler(object *myWidgets);

/* init widgets */
bool init_widget_gtk(object *widget, ux_control *control, const gchar *glade, const gchar *css){

	GError *error = NULL;
	GdkPixbufAnimation * animation = NULL;
	gchar *filename = "img/r_b1.jpg";
	const char *distros[] = {"Select your product",
													"Chips",
													"Raspberry",
													"Banana",
													"Melon",
													"Apple"};

	/* load css properties */
	control->provider = gtk_css_provider_new();
	control->display = gdk_display_get_default();
	control->screen = gdk_display_get_default_screen (control->display);
	gtk_style_context_add_provider_for_screen (control->screen,
											GTK_STYLE_PROVIDER (control->provider),
											GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	if ( !gtk_css_provider_load_from_file(control->provider, g_file_new_for_path(css), &error) ){
		return false;
	}

	/* Create new GtkBuilder object */
	control->builder = gtk_builder_new();

	if( !gtk_builder_add_from_file(control->builder, glade, &error ) ){
		return false;
	}

	/* Allocate data structure */
	widget = g_slice_new(object);

	/* allocate ui definition from file (glade file) */
	widget->window = GTK_WIDGET( gtk_builder_get_object(control->builder, GTK_UX_WINDOW_NAME) );

	/* gets the objects named button5 and label16  */
	widget->button5 = gtk_builder_get_object( control->builder, "button5" );
	widget->label16 = gtk_builder_get_object( control->builder, "label16" );


	/* gets the objects name comboboxtext1 and  label20*/
	widget->comboboxtext1 = gtk_builder_get_object( control->builder, "comboboxtext1" );
	widget->label20 = gtk_builder_get_object( control->builder, "label20" );
	for (int i = 0; i < G_N_ELEMENTS (distros); i++){
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (widget->comboboxtext1), distros[i]);
	}
	/* Choose to set the first row as the active one by default, from the beginning */
	gtk_combo_box_set_active (GTK_COMBO_BOX (widget->comboboxtext1), 0);


	/* box14 gets name */
	widget->checkbutton1 = gtk_builder_get_object(control->builder,"checkbutton1");
	widget->checkbutton2 = gtk_builder_get_object(control->builder,"checkbutton2");
	widget->image3 = gtk_builder_get_object(control->builder,"image3");
	animation = gdk_pixbuf_animation_new_from_file ("img/pick_one.gif", NULL);
	gtk_image_set_from_animation (GTK_IMAGE(widget->image3), animation);


	widget->radiobutton1 = gtk_builder_get_object(control->builder,"radiobutton1");
	widget->radiobutton2 = gtk_builder_get_object(control->builder,"radiobutton2");
	widget->image4 = gtk_builder_get_object(control->builder,"image4");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget->radiobutton1), FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget->radiobutton2), TRUE);
	gtk_image_set_from_file (GTK_IMAGE (widget->image4), filename);


	widget->scale_obj = gtk_builder_get_object(control->builder,"scale1");
	widget->h_scale = gtk_builder_get_object(control->builder,"scale1");
	widget->adjustment1 = gtk_builder_get_object(control->builder,"adjustment1");
	widget->levelbar1 = gtk_builder_get_object(control->builder,"levelbar1");

	widget->progressbar1 = gtk_builder_get_object(control->builder,"progressbar1");
	widget->label22 = gtk_builder_get_object(control->builder,"label22");

	widget->switch1 = gtk_builder_get_object(control->builder,"switch1");
	widget->spinner1 = gtk_builder_get_object(control->builder,"spinner1");

	/* Connect signals */
	gtk_builder_connect_signals(control->builder, widget);

	/* Destroy builder, since we don't need it anymore */
	g_object_unref( G_OBJECT( control->builder ) );

	/* Set handler progress bar*/
	g_timeout_add(100, (GSourceFunc)tmr_progress_bar_handler, widget);

	/* Set Width and Height window */
	gtk_window_set_default_size (GTK_WINDOW(widget->window), 800,480);
	/* Set window position*/
	gtk_window_set_position(GTK_WINDOW(widget->window), control->position);

	/* Set full screen*/
	gtk_window_fullscreen(GTK_WINDOW(widget->window));
	/* Show window. All other widgets are automatically shown by GtkBuilder */
	gtk_widget_show( widget->window );

	return true;
}


void on_clicked_button5(GtkButton *btn_counter, object *widget)
{
	GtkLabel *label = GTK_LABEL(widget->label16);
	counter+=1;
	gchar *print_var = g_strdup_printf("%d", counter);
	gtk_label_set_text( label, print_var );
}

void on_clicked_comboboxtext1(GtkComboBox *comboboxtext1, object *widget)
{
	gchar *datalabel = NULL;
  GtkComboBox *combobox = comboboxtext1;

  if (gtk_combo_box_get_active (combobox) != 0) {
    datalabel = g_strdup_printf("%s",
						gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combobox)));
    gtk_label_set_text(GTK_LABEL(widget->label20), datalabel);
    g_print ("%s\n", datalabel);
    g_free (datalabel);
  }

}

void on_clicked_checkbutton(GtkToggleButton *toggle_button, object *widget)
{

	char v_chechbox = 0;
	gchar *filename[] = {"img/open_v.png", "img/close_v.png"};
	GdkPixbufAnimation *animation;

	if ( ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->checkbutton1)) ) == TRUE ){
		v_chechbox |= 0b00000001;
	}

	if ( ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->checkbutton2)) ) == TRUE ){
		v_chechbox |= 0b00000010;
	}

	/* just for illustrate the bit manupulation */
	if( ( v_chechbox & (1<<1)) && ( v_chechbox & (1<<0)) ){
		printf("Invalid option \n");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget->checkbutton1), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(widget->checkbutton2), FALSE);
	}else if ( ( ( v_chechbox & (1<<0) ) ) && ( !( v_chechbox & (1<<1) ) ) ){
		printf("Open flow \n");
		gtk_image_set_from_file (GTK_IMAGE (widget->image3), filename[0]);
	}else if ( ( !( v_chechbox & (1<<0) ) ) && ( ( v_chechbox & (1<<1) ) ) ){
		printf("Close flow \n");
		gtk_image_set_from_file (GTK_IMAGE (widget->image3), filename[1]);
	}else{
		printf("Please select an option \n");
		animation = gdk_pixbuf_animation_new_from_file ("img/pick_one.gif", NULL);
		gtk_image_set_from_animation (GTK_IMAGE(widget->image3), animation);
	}

}

void on_clicked_radiobuton (GtkToggleButton *togglebutton, object *widget)
{
	gchar *filename[] = {"img/r_b1.jpg", "img/r_b2.jpg"};

	if ( ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->radiobutton1)) ) == TRUE ){
		printf("Button 1 Toggled\n");
		gtk_image_set_from_file (GTK_IMAGE (widget->image4), filename[1]);
	}

	if ( ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->radiobutton2)) ) == TRUE ){
		printf("Button 2 Toggled\n");
		gtk_image_set_from_file (GTK_IMAGE (widget->image4), filename[0]);
	}

}

void on_moved_hscale (GtkRange *range, object *widget)
{
	gdouble pos = gtk_range_get_value(range);
	printf("Pos range: %f \n", pos);
	gtk_level_bar_set_value (GTK_LEVEL_BAR(widget->levelbar1), pos);
}

void on_switch_activated(GtkSwitch* switch1){
	flag_switch = gtk_switch_get_active (switch1);
	printf("Value of switch: %d \n", flag_switch);
}



void on_clicked_exit(GtkWindow *window){
	flag_tmr = FALSE;
	printf("BYE BYE... \n");
	gtk_main_quit();
	//gtk_window_close(window);
}



gboolean tmr_progress_bar_handler(object *widget)
{

	gdouble fraction;
	fraction = valuepb;
	fraction /= 10000;
	valuepb+=10;

	if(valuepb > 10000){
		printf("PROGRESS BAR:%d %f \n",valuepb, fraction);
		valuepb = 0;
	}

	if(flag_tmr == TRUE){
		/*Fill in the bar with the new fraction*/
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (widget->progressbar1), fraction);
	}

	gchar *datalabel = g_strdup_printf("Value: %.2f%c", fraction * 100, 37);
	if(flag_tmr == TRUE){
		/* Write project description*/
		gtk_label_set_text(GTK_LABEL(widget->label22), datalabel);
	}

	if ( flag_switch ){
		if(flag_tmr == TRUE){
			gtk_spinner_start (GTK_SPINNER (widget->spinner1));
		}

	}else{
		if(flag_tmr == TRUE){
			gtk_spinner_stop (GTK_SPINNER (widget->spinner1));
		}
	}

	return flag_tmr;

}
