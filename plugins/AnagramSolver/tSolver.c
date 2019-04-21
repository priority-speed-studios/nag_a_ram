#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


struct Hashtable
{
    int size;
    char *word;
    struct Hashtable *next; 
} Hashtable;

struct Hashtable *head = NULL;
struct Hashtable *curr = NULL;


struct Hashtable* createHash(char* val,int size);
struct Hashtable* readHashtable(char* word);
char *stringReplace(char *word, char *newLine, char *null);
void anagram(char enterWord[100]);

int hash(char* words)
{
	int i;
	int sum=0;
	for(i=0;i<strlen(words);i++)
	{
		if(tolower(words[i])>96 && tolower(words[i]<123))
		{
			sum += (unsigned int)(tolower(words[i])-96);
		}
	}	
	return sum;
}

struct Hashtable* createHash(char* val,int size)
{

    struct Hashtable *hashFirst = (struct Hashtable*)malloc(sizeof(struct Hashtable));
    hashFirst->size = size;
    hashFirst->word = val;
    hashFirst->next = NULL;
    head = curr = hashFirst;
    return hashFirst;
}

struct Hashtable* readHashtable(char* word)
{
    int index = hash(word);
    struct Hashtable *ListNode = head;
    struct Hashtable *temp = NULL;
    word = stringReplace(word,"\n","\0");
    if(NULL == head)
    {
        return (createHash(word, index));
    }
   struct Hashtable *newTable =  (struct Hashtable*)malloc(sizeof(struct Hashtable));
	newTable->size = index;
	newTable->word = word;
	newTable->next = NULL;
	newTable->next = head;
	head = newTable;
}

size_t len_string = 0;
char stringVal[1000];

char *stringReplace(char *word, char *newLine, char *null)
{
    
    int i;
    char *result, *ins, *temp;
    int len_newLine, len_null, len_front;

    if (!word)
    {
        return NULL;
    }

    len_newLine = (int) strlen(newLine);
    if (!newLine || !len_newLine) 
    {
        return NULL;
    }
    ins = strstr(word, newLine);
    if (ins == NULL)
    {
        return NULL;
    }

    if (!null)
    {
        null = "";
    }

    len_null = (int) strlen(null);
    for (i= 0; (temp = strstr(ins, newLine)); ++i) 
    {
        ins = temp + len_newLine;
    }

    temp = result = (char*) malloc(strlen(word) + (len_null - len_newLine) * i + 1);

    if (!result) 
    {
        return NULL;
    }

    while (i--)
    {
        ins = strstr(word, newLine);
        len_front = (int)(ins - word);
        temp = strncpy(temp, word, len_front) + len_front;
        temp = strcpy(temp, null) + len_null;
        word += len_front + len_newLine;
    }
    strcpy(temp, word);
    return result;
}

void sort(char* a)
{
	char temp;
	int i,j;
	for(i=0; i<strlen(a)-1; i++)
	{
		for(j=i;j<strlen(a); j++)
		{
			if(a[i]>a[j])
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}     
}

int compareString(char* a, char* b)
{
	sort(a);
	sort(b);
	return(strcmp(a,b));
}

void anagram(char* enterWord)
{
	int i;
	unsigned int sizeofWord = 128;
	int index = hash(enterWord);
	char* input = (char*) malloc(sizeofWord * sizeof(char));
	char* words = (char*) malloc(sizeofWord * sizeof(char));

	input = strdup(enterWord);

	struct Hashtable *value = NULL;
	value = head;

	while(value->next != NULL)
	{
		if(value->size == index)
		{
			words = strdup(value->word);
			for(i = 0; words[i]; i++)
			{
				words[i] = tolower(words[i]);
			}
			if(compareString(enterWord, words) == 0)
			{
				len_string += sprintf(stringVal+len_string,"%s\n",value->word);   
			}
		}			
		value = value->next;
	}
}

int freeMemory()
{
	struct Hashtable *temp1 = head;
	struct Hashtable *temp2 = head;

	while(temp1 != NULL)
	{
		temp2 = temp1;
		temp1 = temp1->next;
		free(temp2);
	}
} 


const char* task(const char* name)
{
	unsigned int sizeofWord = 128;
	len_string = 0;
	strcpy(stringVal,"");
	anagram(name);
	return stringVal;
}

int setup(const char* file)
{
	freeMemory();
	unsigned int sizeofWord = 128;
	if(!strcmp(file,""))
		return 0;
	FILE* dict = fopen(file+7, "r");
    if(dict == NULL) 
    {
		return 1;
    }
   	char* dictWord = (char*) malloc(sizeofWord * sizeof(char));
   	while(fgets(dictWord,sizeofWord,dict) != NULL)
   	{
		readHashtable(dictWord);
	}
}
