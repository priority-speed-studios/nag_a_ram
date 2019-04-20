#ifndef LOADER_H
#define LOADER_H
#include <gtk/gtk.h>

#define widgetName(a) #a

typedef const char* (*StringFunctions)(const char*);
typedef int(*SetupFunctions)(const char*);
extern StringFunctions algorithm;
extern SetupFunctions setup;
extern GtkBuilder* builder;
const char* process(const char* input);
void plugin_set(GtkFileChooserButton *button);

#endif
