#include <gtk/gtk.h>


//custom structure that will hold pointer to widgets and / or user variables
typedef struct 
{
	GtkWidget *w_lbl_time;
	GtkWidget *w_lbl_count;
	
} app_widgets;

int main(int argc, char *argv[])
{
	GtkBuilder *builder;
	GtkWidget	*window;

	app_widgets *widgets = g_slice_new(app_widgets);


	gtk_init(&argc, &argv);

	builder = gtk_builder_new();

	gtk_builder_add_from_file(builder, "../pointer_struct.glade", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));


	widgets->w_lbl_time = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_time"));
	widgets->w_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));
	
	gtk_builder_connect_signals(builder, widgets);
	g_object_unref(builder);

	gtk_widget_show(window);
	gtk_main();

	g_slice_free(app_widgets, widgets);

	return 0;
}

//callback funcion for button clicked signal
void on_btn_update_clicked(GtkButton *button, app_widgets *app_wdgts)
{
	GDateTime *time;
	gchar	  *time_str;
	static gint count = 0;
	gchar     *count_str;

	time = g_date_time_new_now_local();
	time_str = g_date_time_format(time, "%H:%M:%S");
	count++;
	count_str = g_strdup_printf("%d", count);

	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_time), time_str);
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_count), count_str);

	g_free(time_str); g_free(count_str);
	g_date_time_unref(time);
}

void on_window_main_destroy()
{
	gtk_main_quit();
}