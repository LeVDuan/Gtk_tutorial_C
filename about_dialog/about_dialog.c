#include <gtk/gtk.h>

typedef struct {
    GtkWidget *w_txtvw_main;            // Pointer to text view object
    GtkWidget *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkTextBuffer *textbuffer_main; 	// Pointer to text buffer
    GtkWidget *w_dlg_about;			// Pointer to about dialog box

} app_widgets;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("../window_main.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    // Get pointers to widgets
    widgets->w_txtvw_main = GTK_WIDGET(gtk_builder_get_object(builder, "txtvw_main"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->textbuffer_main = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer_main"));
    widgets->w_dlg_about = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_about"));
    
    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *file_name = NULL;        // Name of file to open from dialog box
    gchar *file_contents = NULL;    // For reading contents of file
    gboolean file_success = FALSE;  // File read status
    
    // Show the "Open Text File" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Text File dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) {
            // Copy the contents of the file to dynamically allocated memory
            file_success = g_file_get_contents(file_name, &file_contents, NULL, NULL);
            if (file_success) {
                // Put the contents of the file into the GtkTextBuffer
                gtk_text_buffer_set_text(app_wdgts->textbuffer_main, file_contents, -1);
            }
            g_free(file_contents);
        }
        g_free(file_name);
    }

    // Finished with the "Open Text File" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

// File --> Close
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    // Clear the text from window "Close the file"
    gtk_text_buffer_set_text(app_wdgts->textbuffer_main, "", -1);
}

// File --> Quit
void on_menuitm_quit_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_main_quit();
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}


// Help --> About
void on_menuitm_about_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
	gtk_widget_show(app_wdgts->w_dlg_about);
}

//about dialog box close button
void on_dlg_about_close(GtkDialog *dialog,app_widgets *app_wdgts)
{
	gtk_widget_hide(app_wdgts->w_dlg_about);
}