#include "loader.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

static char* wordFile="";

const char *process(const char *input)
{
    return algorithm(input);
}

void plugin_set(GtkFileChooserButton *button)
{
    const char* fileName = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(button));
    void * dlh = dlopen(fileName+7, RTLD_NOW);
    if (!dlh)
    {
        GtkWidget* dialog = gtk_message_dialog_new (NULL,
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_CLOSE,
                                                    "Error1: %s",
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
                                                    "Error2: %s",
                                                    dlerror());
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
        return;
    }
    if(!strcmp(wordFile,""))
    {
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
    }
    algorithm = task;
    setup = setupf;
}

void wordlist_set(GtkFileChooserButton *button)
{
    const char* fileName = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(button));
    //strcpy(wordFile,fileName);
    //ERROR: PLEASE FIX
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
