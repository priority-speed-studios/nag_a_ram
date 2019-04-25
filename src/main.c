#include <stdio.h>
#include "loader.h"

StringFunctions algorithm=NULL;
SetupFunctions setup=NULL;
GtkBuilder* builder=NULL;

void populate_widget()
{
    DIR *d;
    struct dirent *dir;
    d = opendir("./plugs");
    GtkComboBoxText* combo = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder,
                                                                       widgetName(algosbox)));
    if(d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_type != DT_REG)
                continue;
            gtk_combo_box_text_append(combo, NULL, dir->d_name);
        }
    }
}

void check()
{
    const char* inputString = gtk_entry_get_text(
                GTK_ENTRY(gtk_builder_get_object(builder, widgetName(inputLabel))));
    if(algorithm == NULL)
        return;
    const char* outputString = process(inputString);
    //breakpoint
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(
                GTK_TEXT_VIEW(gtk_builder_get_object(builder, widgetName(outputLabel))));
    GtkTextIter end, start;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_delete(buffer, &start, &end);
    gtk_text_buffer_insert(buffer, &end, outputString, -1);
}

int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file(widgetName(./mainWindow.xml));
    GtkWindow* window= GTK_WINDOW(gtk_builder_get_object(builder, widgetName(window_main)));
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, widgetName(./stylesheets.css), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(
                                            gtk_builder_get_object(builder,widgetName(wordlist))),
                                        "../wordlists/");
    gtk_widget_show(GTK_WIDGET(window));
    gtk_builder_connect_signals(builder, NULL);
    populate_widget();
    gtk_main();
    g_object_unref(builder);
    return 0;
}
