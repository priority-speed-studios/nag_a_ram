#include <stdio.h>
#include <gtk/gtk.h>



static GtkBuilder* builder;

void check()
{
    const char* inputString = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder,"inputLabel")));
    char outputString[100] = ""; //need a way to decide the string size
    //breakpoint
    strcpy(outputString,inputString); //replace strcpy with arko's stuff
    //breakpoint
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtk_builder_get_object(builder,"outputLabel")));
    GtkTextIter end,start;
    gtk_text_buffer_get_end_iter(buffer,&end);
    gtk_text_buffer_get_start_iter(buffer,&start);
    gtk_text_buffer_delete(buffer,&start,&end);;
    gtk_text_buffer_insert(buffer,&end,outputString,-1);
}

int main(int argc,char** argv)
{
    gtk_init(&argc,&argv);
    builder = gtk_builder_new_from_file("./mainWindow.glade");
    GtkWindow* window= GTK_WINDOW(gtk_builder_get_object(builder,"window_main"));
    gtk_widget_show(GTK_WIDGET(window));
    gtk_builder_connect_signals(builder,NULL);
    gtk_main();
    return 0;
}
