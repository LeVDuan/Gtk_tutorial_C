#include <gtk/gtk.h>

typedef struct {
    // Radio Buttons
    GtkWidget *w_rb_none;
    GtkWidget *w_rb_heads;
    GtkWidget *w_rb_tails;
    // Labels
    GtkWidget *w_lbl_result;
    GtkWidget *w_lbl_win_lose;
    GtkWidget *w_lbl_your_bet;
    // Buttons
    GtkWidget *w_btn_toss;
    GtkWidget *w_btn_play_again;
} app_widgets;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("../heads_tails.glade");

    // Get pointer to main window
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    
    // Get pointers to widgets
    widgets->w_rb_none          = GTK_WIDGET(gtk_builder_get_object(builder, "rb_none"));
    widgets->w_rb_heads         = GTK_WIDGET(gtk_builder_get_object(builder, "rb_heads"));
    widgets->w_rb_tails         = GTK_WIDGET(gtk_builder_get_object(builder, "rb_tails"));
    widgets->w_lbl_result       = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_result"));
    widgets->w_lbl_win_lose     = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_win_lose"));
    widgets->w_lbl_your_bet     = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_your_bet"));
    widgets->w_btn_toss         = GTK_WIDGET(gtk_builder_get_object(builder, "btn_toss"));
    widgets->w_btn_play_again   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_play_again"));
    
    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);
    gtk_widget_show(window);
    
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}

// Either "Heads" or "Tails" radio button clicked
void on_rb_heads_tails_toggled (GtkToggleButton *togglebutton, app_widgets *wdgts)
{
    // A radio button was selected, so enable the "Toss Coin" button
    gtk_widget_set_sensitive(wdgts->w_btn_toss, TRUE);
    
    // Find the selected radio button and update the selection in the text under "Your Bet:"
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wdgts->w_rb_heads))) {
        gtk_label_set_text(GTK_LABEL(wdgts->w_lbl_your_bet), "Heads");
    }
    else {
        gtk_label_set_text(GTK_LABEL(wdgts->w_lbl_your_bet), "Tails");
    }
}

// "Toss Coin" button clicked
void on_btn_toss_clicked(GtkButton *button, app_widgets *wdgts)
{
    gboolean result;    // Result of coin toss
    // Win and Lose text strings and settings
    // Win and Lose text strings and settings, change label color in GTK here
    gchar str_win[] = "<span foreground='green' weight='bold' font='14'>You Win!</span>";
    gchar str_lose[] = "<span foreground='red' weight='bold' font='14'>You Lose!</span>";
    
    // Toss the coin
    result = g_random_boolean();
    // Set the text to either "Heads" or "Tails" under the "Coin Toss Result:" heading
    if (result == TRUE) {
        gtk_label_set_text(GTK_LABEL(wdgts->w_lbl_result), "Heads");
    }
    else {
        gtk_label_set_text(GTK_LABEL(wdgts->w_lbl_result), "Tails");
    }
    
    // Determine if player won or lost the game, depending on bet placed
    if ((result == TRUE) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wdgts->w_rb_heads))) {
        // Player bet on heads and coin toss resulted in heads
        gtk_label_set_markup (GTK_LABEL (wdgts->w_lbl_win_lose), str_win);
    }
    else if ((result == FALSE) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wdgts->w_rb_tails))) {
        // Player bet on tails and coin toss resulted in tails
        gtk_label_set_markup (GTK_LABEL (wdgts->w_lbl_win_lose), str_win);
    }
    else {
        // Player lost the game
        gtk_label_set_markup (GTK_LABEL (wdgts->w_lbl_win_lose), str_lose);
    }
    
    // Show "Play Again" button
    gtk_widget_set_visible(wdgts->w_btn_play_again, TRUE);
    // Hide "Toss Coin" button
    gtk_widget_set_visible(wdgts->w_btn_toss, FALSE);
    // Disable "Toss Coin" buttons and radio buttons
    gtk_widget_set_sensitive(wdgts->w_btn_toss, FALSE);
    gtk_widget_set_sensitive(wdgts->w_rb_heads, FALSE);
    gtk_widget_set_sensitive(wdgts->w_rb_tails, FALSE);
}

// "Play Again" button clicked, so reset the game
void on_btn_play_again_clicked(GtkButton *button, app_widgets *wdgts)
{
    // Enable radio buttons
    gtk_widget_set_sensitive(wdgts->w_rb_heads, TRUE);
    gtk_widget_set_sensitive(wdgts->w_rb_tails, TRUE);
    // Select "none" radio button
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(wdgts->w_rb_none), TRUE);
    // Hide "Play Again" button
    gtk_widget_set_visible(wdgts->w_btn_play_again, FALSE);
    // Reset labels
    gtk_label_set_text(GTK_LABEL(wdgts->w_lbl_your_bet), "Heads or Tails?");
    gtk_label_set_text(GTK_LABEL(wdgts->w_lbl_result), "Heads or Tails?");
    gtk_label_set_text(GTK_LABEL(wdgts->w_lbl_win_lose), "Will You Win or Lose?");
    // Show "Toss Coin" button
    gtk_widget_set_visible(wdgts->w_btn_toss, TRUE);
    // Disable "Toss Coin" buton
    gtk_widget_set_sensitive(wdgts->w_btn_toss, FALSE);
    
}

// Called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}