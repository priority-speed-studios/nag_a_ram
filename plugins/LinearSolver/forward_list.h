#include <string.h>
#include <stdlib.h>

typedef struct _node
{
	char* s;
	struct _node* next;
} node;

node* node_new(char*);

typedef struct _forward_list
{
	node *begin, *end;
} forward_list;

forward_list* forward_list_new();
void insert(forward_list*, char*);

node* node_new(char* s)
{
	node* temp = (node*) malloc(sizeof(node));
	
	temp -> s = (char*) malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(temp -> s, s);
	
	temp -> next = NULL;
	
	return temp;
}

forward_list* forward_list_new()
{
	forward_list* temp = (forward_list*) malloc(sizeof(forward_list));
	temp -> begin = temp -> end = NULL;
	
	return temp;
}

void insert(forward_list* var, char* s) // const char* works as well
{
	node* temp = node_new(s);

	if(var -> begin)
		var -> end = var -> end -> next = temp;
	else
		var -> begin = var -> end = temp;
}
