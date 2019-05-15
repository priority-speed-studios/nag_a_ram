#include <stdio.h>
#include "forward_list.h"
#include "hash_table.h"

GHashTable* map;

int setup(const char* filename)
{	
	FILE* fi = fopen(filename + 7, "r");
	
	if(!fi)
		return 1;
	
	char s[100];
	
	map = g_hash_table_new(hash_table_value, hash_table_equal);
	
	while(1)
	{
		fscanf(fi, "%s", s);
		
		if(feof(fi))
			break;
		
		GHashTable* cs = charset(s);
		forward_list* p = g_hash_table_lookup(map, cs);
		
		if(p)
		{
			insert(p, s);
			g_hash_table_remove_all(cs);
		}
		else
		{
			forward_list* list = (forward_list*) malloc(sizeof(forward_list));
			list -> begin = list -> end = NULL;
			
			insert(list, s);
			
			g_hash_table_insert(map, cs, list);
		}
	}
	
	fclose(fi);
	
	return 0;
}

char* task(char* s)
{
	char* sol = (char*) malloc(sizeof(char) * 1024);
	strcpy(sol, "");
	
	GHashTable* p = charset(s);
	
	forward_list* list = g_hash_table_lookup(map, p);
	
	if(list)
		for(node* i = list -> begin; i; i = i -> next)
		{
			strcat(sol, i -> s);
			strcat(sol, "\n");
		}
	
	g_hash_table_remove_all(p);
	
	return sol;
}

/* This is only for demonstration purposes */
/*
int main()
{
	setup("dictionary.txt");
	
	printf("Loaded!\n");
	
	char s[25];
	scanf("%s", s);
	
	printf("\n");
	
	printf("%s", task(s));

	return 0;
}
*/
