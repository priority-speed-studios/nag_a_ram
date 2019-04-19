#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char textArray[100][100];
static int no_textArray;

int check_anagram(char a[], char b[])
{
	int first[26] = {0}, second[26] = {0}, c=0;
	while (a[c] != '\0')
	{
		first[a[c]-'a']++;
		c++;
	}
	c = 0;
	while (b[c] != '\0')
	{
		second[b[c]-'a']++;
		c++;
	}
	for (c = 0; c < 26; c++)
	{
		if (first[c] != second[c])
			return 0;
	}
	return 1;
}

const char* task(const char* name)
{
	char *ret = malloc(100);
	ret[0]=0;
	for(int i=0;i<no_textArray;i++)
	{
		if(check_anagram(name,textArray[i]))
		{
			sprintf(ret,"%s%s",ret,textArray[i]);
		}
	}
	return ret;
}

int setup(const char* file)
{
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int no=0;
    fp = fopen(file+7, "r");
    if (fp == NULL)
        return 1;
    while ((read = getline(&line, &len, fp)) != -1) 
    {
        strcpy(textArray[no],line);
        no++;
    }
	no_textArray = no;
    fclose(fp);
    printf("Setup complete\n");
    fflush(stdout);
    return 0;
}
