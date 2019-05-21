#include "loader.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

static char wordFile[100]="";

const char *process(const char *input_)
{
    char input[50];
    strcpy(input,input_);
    return algorithm(input);
}

void plugin_set()
{
    if(pluginsState)
        return;
    char fileName[50] = "./plugs/";
    strcat(fileName,gtk_combo_box_text_get_active_text(
               GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder,widgetName(algosbox)))));
    void * dlh = dlopen(fileName, RTLD_NOW);
    if (!dlh)
    {
        GtkWidget* dialog = gtk_message_dialog_new (NULL,
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_CLOSE,
                                                    "Error: %s",
                                                    dlerror());
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
        return;
    }
    SetupFunctions setupf = (SetupFunctions)dlsym(dlh,widgetName(setup));
    StringFunctions task = (StringFunctions)dlsym(dlh,widgetName(task));
    if (!task || !setupf)
    {
        GtkWidget* dialog = gtk_message_dialog_new (NULL,
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_CLOSE,
                                                    "Error: %s",
                                                    dlerror());
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
        return;
    }
    int code = setupf(wordFile);
    if(code)
    {
        GtkWidget* dialog = gtk_message_dialog_new (NULL,
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_CLOSE,
                                                    "Error: %d",
                                                    code);
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
    }
    algorithm = task;
    setup = setupf;
}

void wordlist_set(GtkFileChooserButton *button)
{
    const char* fileName = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(button));
    strcpy(wordFile,fileName);
    if(!algorithm)
        return;
    int code = setup(fileName);
    if(code)
    {
        GtkWidget* dialog = gtk_message_dialog_new (NULL,
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_CLOSE,
                                                    "Error: %d",
                                                    code);
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
    }
}
