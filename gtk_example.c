#include <gtk/gtk.h>

void on_submit_clicked(GtkWidget *widget, gpointer data) {
    const char *answer = gtk_entry_get_text(GTK_ENTRY(data));
    printf("Player's answer: %s\n", answer); // Replace with game logic
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *vbox, *label, *entry, *button;

    gtk_init(&argc, &argv);

    // Create a window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Trivia Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);

    // Create a vertical box layout
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Add a label for the question
    label = gtk_label_new("What is 2 + 2?");
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    // Add a text entry for the answer
    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);

    // Add a submit button
    button = gtk_button_new_with_label("Submit");
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    // Connect the submit button to a callback
    g_signal_connect(button, "clicked", G_CALLBACK(on_submit_clicked), entry);

    // Show all widgets
    gtk_widget_show_all(window);

    // Main event loop
    gtk_main();

    return 0;
}