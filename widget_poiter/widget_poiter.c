#include <gtk/gtk.h>


int main(int argc, char *argv[])
{
	GtkBuilder *builder;
	GtkWidget	*window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "../widget_poiter.glade", NULL);


	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	gtk_builder_connect_signals(builder, NULL);

	g_object_unref(builder);

	gtk_widget_show(window);
	gtk_main();
	return 0;
}

void on_btn_print_txt_clicked(GtkButton *button, GtkLabel *text_label)
{
	gtk_label_set_text(text_label, "you clicked the button!");
	
}

void on_btn_print_txt_clicked1(GtkButton *button, GtkLabel *count_label)
{

    static unsigned int count = 0;
    char str_count[30] = {0};
    count ++;
    sprintf(str_count, "%d", count);
    gtk_label_set_text(count_label, str_count);
    if(count == 5){
    	gtk_main_quit();
    }
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}