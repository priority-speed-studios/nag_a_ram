#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

char *str2md5(const char *str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
} 

char filename[100];
int setup(const char* file)
{
    strcpy(filename,file+7);
    return 0;
}


const char* task(const char* name)
{
    fflush(stdout);
    char *result,*text;
    text = malloc(100);
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(filename, "r");
    if (fp == NULL)
        return "";
    while ((read = getline(&line, &len, fp)) != -1) 
    {
        line[strlen(line)-1]=0;
        strcpy(text,line);
        result = str2md5(text, strlen(text));
        if(!strcmp(name,result))
            return text;
        free(result);
    }
    fclose(fp);
    return "";
}

