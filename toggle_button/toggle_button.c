#include <gtk/gtk.h>
 
int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "../window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}

// lbl_button_state is set in User data field of Signals tab in Glade - this maps to text_label
void on_togglebuttonState_toggled(GtkToggleButton *togglebutton, GtkLabel *text_label)
{
	gboolean button_state;
	
	button_state = gtk_toggle_button_get_active(togglebutton);
	
	if (button_state) {
		// button is active
		gtk_label_set_text(text_label, "Button State: Active");
	}
	else {
		// button is inactive
		gtk_label_set_text(text_label, "Button State: Inactive");
	}
}
 
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}