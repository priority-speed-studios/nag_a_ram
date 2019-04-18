#include <stdio.h>
#include <gtk/gtk.h>

#define widgetName(a) #a

typedef union arko_is_star
{
    int seed;
    char string[100 + sizeof (int)];
} arko;

static arko hello;

static GtkBuilder* builder;

void check()
{
    printf("%s%d\n", hello.string + sizeof (int), hello.seed);
    const char* inputString = gtk_entry_get_text(
                GTK_ENTRY(gtk_builder_get_object(builder, widgetName(inputLabel))));
    char outputString[100] = "", newString[400]= ""; //need a way to decide the string size
    //breakpoint
    strcpy(outputString, inputString); //replace strcpy with arko's stuff
    //breakpoint
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(
                GTK_TEXT_VIEW(gtk_builder_get_object(builder, widgetName(outputLabel))));
    sprintf(newString, "%s\n%s\n%s", outputString, outputString, outputString);
    GtkTextIter end, start;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_delete(buffer, &start, &end);
    gtk_text_buffer_insert(buffer, &end, newString, -1);
}

int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);
    hello.seed = 4;
    strcpy(hello.string + sizeof (int), "Yay! It works.\n");
    builder = gtk_builder_new_from_file(widgetName(./mainWindow.glade));
    GtkWindow* window= GTK_WINDOW(gtk_builder_get_object(builder, widgetName(window_main)));
    gtk_widget_show(GTK_WIDGET(window));
    gtk_builder_connect_signals(builder, NULL);
    gtk_main();
    g_object_unref(builder);
    return 0;
}
