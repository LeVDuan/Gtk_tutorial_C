#include <gtk/gtk.h>

GtkWidget *g_lbl_hello;
GtkWidget *g_lbl_count;


int main(int argc, char *argv[])
{
	GtkBuilder      *builder; 
    GtkWidget       *window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "../hello.glade", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder,"window_main"));
	gtk_builder_connect_signals(builder, NULL);

	g_lbl_hello = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_hello"));
	g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));

	g_object_unref(builder);

	gtk_widget_show(window);

	gtk_main();

	return 0;
}

// called when button is clicked
void on_btn_hello_clicked()
{
    static unsigned int count = 0;
    char str_count[30] = {0};
    
    gtk_label_set_text(GTK_LABEL(g_lbl_hello), "Hello, world!");
    count++;
    sprintf(str_count, "%d", count);
    gtk_label_set_text(GTK_LABEL(g_lbl_count), str_count);
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}