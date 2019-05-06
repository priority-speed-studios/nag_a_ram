#include <string.h>
#include <stdlib.h>

typedef struct _node
{
	char* s;
	struct _node* next;
} node;

typedef struct _forward_list
{
	node *begin, *end;
} forward_list;

void insert(forward_list* var, char* s) // const char* works as well
{
	node* temp = (node*) malloc(sizeof(node));
	temp -> s = (char*) malloc(sizeof(char) * (strlen(s) + 1));
	
	strcpy(temp -> s, s);
	temp -> next = NULL;

	if(var -> begin)
		var -> end = var -> end -> next = temp;
	else
		var -> begin = var -> end = temp;
}
