/*
 * widget_gtk.c
 *
 *  Created on: Mar 28, 2019
 *  Author: gualberto
 */
#include "widget_gtk.h"

controls *myWidgets;
gint valuepb;
gboolean flag_tmr;
gboolean flag_switch;
unsigned char counter;


/*Prototype hscale function*/
void hscale_moved (GtkRange *range, controls *_myWidgets);

/* Radio button Prototype function */
void on_rb_toggled (GtkToggleButton *togglebutton, controls *_myWidgets);

/** Prototype function Check button */
void on_clicked_chkbtn (GtkToggleButton *toggle_button, controls *_myWidgets);

/** Switch Button Prototype function */
void on_changed (GtkComboBox *widget, controls *_myWidgets);

/** Prototype open widgets windows handler*/
void button5_handler(GtkButton *mybutton, controls *_myWidgets);

/** Prototype switch active*/
void on_switch_active(GtkSwitch* myswitch);

/** Prototype window destroy*/
void on_widgets_gtk_destroy(GtkWindow *window);

/** Timer for progress bar function*/
gboolean tmr_progress_bar_handler(controls *widget);

/*Load CSS file*/
static void load_css_file(void);




/* Load css file*/
static void load_css_file(void){
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;
	GError *error = NULL;

	provider = gtk_css_provider_new ();
	display = gdk_display_get_default ();
	screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	const gchar *myCssFile = "css/mystyle.css";
	gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
}




void hscale_moved (GtkRange *range, controls *_myWidgets)
{
	gdouble pos = gtk_range_get_value(range);
	printf("Pos range: %f \n", pos);
	gtk_level_bar_set_value (myWidgets->mylvl_bar,pos);
}

void on_rb_toggled (GtkToggleButton *togglebutton, controls *_myWidgets)
{
	gchar *filename[] = {"img/r_b1.jpg", "img/r_b2.jpg"};
    //gtk_label_set_text(label, "1%");     // update label
	if ( ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(_myWidgets->r_btn_1)) ) == TRUE ){
		g_print("Button 1 Toggled\n");       // print to command line
		gtk_image_set_from_file (GTK_IMAGE (myWidgets->img_val_r), filename[1]);
	}

	if ( ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(_myWidgets->r_btn_2)) ) == TRUE ){
		g_print("Button 2 Toggled\n");       // print to command line
		gtk_image_set_from_file (GTK_IMAGE (myWidgets->img_val_r), filename[0]);
	}

}

void on_clicked_chkbtn (GtkToggleButton *toggle_button, controls *_myWidgets){

	char v_chechbox = 0;
	gchar *filename[] = {"img/open_v.png", "img/close_v.png"};

	if ( ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(_myWidgets->chk_btn_1)) ) == TRUE ){
		v_chechbox |= 0b00000001;
	}

	if ( ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(_myWidgets->chk_btn_2)) ) == TRUE ){
		v_chechbox |= 0b00000010;
	}

	/*
	 * True table
	 * 0	0	Not setting
	 * 0	1	Set image 1
	 * 1	0	Set image 2
	 * 1	1	Clear check box
	 *
	 * printf("0 true %d \n", ( v_chechbox & (1<<0) ) );
	 * printf("0 false %d \n", !( v_chechbox & (1<<0) ) );
	 * printf("1 true %d \n", ( v_chechbox & (1<<1) ) );
	 * printf("1 false %d \n", !( v_chechbox & (1<<1) ) );
	 * */

	if( ( v_chechbox & (1<<1)) && ( v_chechbox & (1<<0)) ){
		printf("Invalid option \n");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(_myWidgets->chk_btn_1), FALSE);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(_myWidgets->chk_btn_2), FALSE);
	}else if ( ( ( v_chechbox & (1<<0) ) ) && ( !( v_chechbox & (1<<1) ) ) ){
		printf("Open flow \n");
		gtk_image_set_from_file (GTK_IMAGE (myWidgets->img_val), filename[0]);
	}else if ( ( !( v_chechbox & (1<<0) ) ) && ( ( v_chechbox & (1<<1) ) ) ){
		printf("Close flow \n");
		gtk_image_set_from_file (GTK_IMAGE (myWidgets->img_val), filename[1]);
	}else{
		printf("Please select an option \n");
		GdkPixbufAnimation * animation;
		animation = gdk_pixbuf_animation_new_from_file ("img/pick_one.gif", NULL);
		gtk_image_set_from_animation (GTK_IMAGE(myWidgets->img_val), animation);
	}

}

void on_changed (GtkComboBox *widget, controls *_myWidgets)
{
  GtkComboBox *combo_box = widget;

  if (gtk_combo_box_get_active (combo_box) != 0) {
    //gchar *distro = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combo_box));
    gchar *datalabel = g_strdup_printf("You chose %s\n",
    		gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(combo_box)));
    gtk_label_set_text(GTK_LABEL(_myWidgets->lbl_combo), datalabel);
    g_print ("You chose %s\n", datalabel);
    g_free (datalabel);
  }

}

void button5_handler(GtkButton *mybutton, controls *_myWidgets){
	counter+=1;
	gchar *print_var = g_strdup_printf("%d", counter);
	/** Write project description*/
	gtk_label_set_text(GTK_LABEL(_myWidgets->lbl_counter), print_var);

}

void on_switch_active(GtkSwitch* myswitch){
	flag_switch = gtk_switch_get_active (myswitch);
	printf("Value of switch: %d \n", flag_switch);

}

void on_widgets_gtk_destroy(GtkWindow *window){
	flag_tmr = FALSE;
	printf("BYE BYE... \n");
	gtk_main_quit();
	//gtk_window_close(window);
}

gboolean tmr_progress_bar_handler(controls *myWidgets){

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
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (myWidgets->progress_bar), fraction);
	}

	gchar *datalabel = g_strdup_printf("Value: %.2f%c", fraction * 100, 37);
	if(flag_tmr == TRUE){
		/** Write project description*/
		gtk_label_set_text(GTK_LABEL(myWidgets->lbl_progressb), datalabel);
	}

	if ( flag_switch ){
		if(flag_tmr == TRUE){
			gtk_spinner_start (GTK_SPINNER (myWidgets->spinner_obj));
		}

	}else{
		if(flag_tmr == TRUE){
			gtk_spinner_stop (GTK_SPINNER (myWidgets->spinner_obj));
		}
	}

	return flag_tmr;

}

void start_widget_gtk(void){
	GError *error = NULL;
	const gchar *uiFile= "glade/gui_main.glade";
	GtkBuilder *builder;

	load_css_file();

	/* Create new GtkBuilder object */
	builder = gtk_builder_new();

	if(!gtk_builder_add_from_file(builder, uiFile, &error ))
	{
		//g_warning( "%s", error->message );
		g_free(error);
		gtk_main_quit();
	}

	/* Allocate data structure */
	myWidgets = g_slice_new(controls);

	/**Get address from pointer objects*/
	myWidgets->widgets_window = GTK_WIDGET(gtk_builder_get_object(builder,"widgets_window"));

	myWidgets->progress_bar = GTK_PROGRESS_BAR(gtk_builder_get_object(builder,"progressbar1"));
	myWidgets->lbl_progressb = GTK_LABEL(gtk_builder_get_object(builder,"label22"));

	myWidgets->switch_obj = GTK_SWITCH(gtk_builder_get_object(builder,"switch1"));
	myWidgets->spinner_obj = GTK_SPINNER(gtk_builder_get_object(builder,"spinner1"));

	myWidgets->btn_counter = GTK_BUTTON(gtk_builder_get_object(builder,"button5"));
	myWidgets->lbl_counter = GTK_LABEL(gtk_builder_get_object(builder,"label16"));

	myWidgets->scale_obj = GTK_WIDGET(gtk_builder_get_object(builder,"scale1"));

	myWidgets->combo_box_txt_obj = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder,"comboboxtext1"));
	myWidgets->lbl_combo = GTK_LABEL(gtk_builder_get_object(builder,"label20"));

	myWidgets->chk_btn_1 = GTK_CHECK_BUTTON(gtk_builder_get_object(builder,"checkbutton1"));
	myWidgets->chk_btn_2 = GTK_CHECK_BUTTON(gtk_builder_get_object(builder,"checkbutton2"));
	myWidgets->img_val = GTK_IMAGE(gtk_builder_get_object(builder,"image3"));

	myWidgets->r_btn_1 = GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"radiobutton1"));
	myWidgets->r_btn_2 = GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"radiobutton2"));
	myWidgets->img_val_r = GTK_IMAGE(gtk_builder_get_object(builder,"image4"));

	myWidgets->h_scale = GTK_SCALE(gtk_builder_get_object(builder,"scale1"));
	myWidgets->hadjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder,"adjustment1"));

	myWidgets->mylvl_bar = GTK_LEVEL_BAR(gtk_builder_get_object(builder,"levelbar1"));




	/*Level Bar scale*/



	/*Set image flow for check box button*/
	GdkPixbufAnimation * animation;
	animation = gdk_pixbuf_animation_new_from_file ("img/pick_one.gif", NULL);
	gtk_image_set_from_animation (GTK_IMAGE(myWidgets->img_val), animation);

	/*Set radio button*/
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (myWidgets->r_btn_1), FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (myWidgets->r_btn_2), TRUE);
	gchar *filename = "img/r_b1.jpg";
	gtk_image_set_from_file (GTK_IMAGE (myWidgets->img_val_r), filename);

	/* Combo box setting*/
	const char *distros[] = {"Select your product", "Chips", "Raspberry", "Banana", "Melon", "Apple"};

	/* G_N_ELEMENTS is a macro which determines the number of elements in an array.*/
	for (int i = 0; i < G_N_ELEMENTS (distros); i++){
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (myWidgets->combo_box_txt_obj), distros[i]);
	}

	/* Choose to set the first row as the active one by default, from the beginning */
	  gtk_combo_box_set_active (GTK_COMBO_BOX (myWidgets->combo_box_txt_obj), 0);

	/* Connect signals */
	gtk_builder_connect_signals(builder,myWidgets);

	/* Destroy builder, since we don't need it anymore */
	g_object_unref( G_OBJECT( builder ) );

	/** Set handler progress bar*/
	g_timeout_add(100, (GSourceFunc)tmr_progress_bar_handler, myWidgets);
	valuepb = 0;
	flag_tmr = TRUE;

	counter = 0; /*Initialize counter variable*/

	/** Set Width and Height window*/
	gtk_window_set_default_size (GTK_WINDOW(myWidgets->widgets_window), 800,480);

	/** Set window position*/
	GtkWindowPosition position;
	position = GTK_WIN_POS_CENTER;
	gtk_window_set_position(GTK_WINDOW(myWidgets->widgets_window), position);

	/** Set full screen*/
	gtk_window_fullscreen(GTK_WINDOW(myWidgets->widgets_window));

	/* Show window. All other widgets are automatically shown by GtkBuilder */
	gtk_widget_show( myWidgets->widgets_window );
}
