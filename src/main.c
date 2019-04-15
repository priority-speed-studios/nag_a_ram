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
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder,"outputLabel")),outputString);
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
