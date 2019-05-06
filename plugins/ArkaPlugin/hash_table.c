#include <glib.h>

unsigned int hash_table_value(const void* _var)
{
	GHashTable* var = (GHashTable*) _var;
	
	unsigned int hash = 0;
	
	GHashTableIter i;
	gpointer k, v;
	
	g_hash_table_iter_init(&i, var);
	while(g_hash_table_iter_next(&i, &k, &v))
		hash += *((int*) k) * *((int*) k) + *((int*) k) + *((int*) v);
	/*
		Szudizk's Function for x >= y
		Here, k >= v
	*/
	
	return hash;
}

int hash_table_equal(const void* _x, const void* _y)
{
	GHashTable* x = (GHashTable*) _x;
	GHashTable* y = (GHashTable*) _y;
	
	GHashTableIter i;
	gpointer k, v;
	
	g_hash_table_iter_init(&i, x);
	while(g_hash_table_iter_next(&i, &k, &v))
	{
		int* value = g_hash_table_lookup(y, (int*) k);
		
		if(!value)
			return 0;
		else if(*value != *((int*) v))
				return 0;
	}
	
	return 1;
}

GHashTable* charset(char* s)
{
	GHashTable* temp = g_hash_table_new(g_int_hash, g_int_equal);
	
	for(int i = 0; s[i]; ++i)
	{
		int x = s[i];
		int* value = g_hash_table_lookup(temp, &x);
		
		if(value)
			++(*value);
		else
		{
			int *k, *v;
			
			k = (int*) malloc(sizeof(int));
			v = (int*) malloc(sizeof(int));
			
			*k = (int) s[i];
			*v = 1;
			
			g_hash_table_insert(temp, k, v);
		}
	}
	
	return temp;
}
