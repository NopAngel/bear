#include <gtk/gtk.h>

// Callback para el keybinding Ctrl+Q (salir)
static void quit_app(GtkWidget *widget, gpointer data) {
    g_application_quit(G_APPLICATION(data));
}

// Callback para Ctrl+S (guardar)
static void save_file(GtkWidget *widget, gpointer data) {
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(data);
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
    // Aquí iría la lógica para guardar en un archivo...
    g_print("Texto a guardar:\n%s\n", text);
    g_free(text);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    app = gtk_application_new("com.github.emacs-like-c", G_APPLICATION_FLAGS_NONE);
    
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}

static void on_activate(GtkApplication *app, gpointer user_data) {
    // Crear ventana principal
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Mini Emacs (C + GTK)");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    
    // Crear contenedor principal (vertical)
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), vbox);
    
    // Área de texto con scroll
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view), TRUE);  // Fuente monoespaciada
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);
    gtk_box_append(GTK_BOX(vbox), scrolled_window);
    
    // Barra de estado
    GtkWidget *statusbar = gtk_statusbar_new();
    gtk_box_append(GTK_BOX(vbox), statusbar);
    
    // Keybindings globales (Ctrl+Q, Ctrl+S)
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), buffer);
    
    gtk_widget_show(window);
}

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(data);
    
    // Ctrl+Q = Salir
    if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_q)) {
        g_application_quit(G_APPLICATION(g_application_get_default()));
        return TRUE;
    }
    
    // Ctrl+S = Guardar
    if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_s)) {
        save_file(widget, buffer);
        return TRUE;
    }
    
    return FALSE;  // Propagar otros eventos
}
