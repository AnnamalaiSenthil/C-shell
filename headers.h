#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <math.h>
#define ll long long
#define ans &&

int read_line(const char *filename, const char *search, char *result, size_t result_size);
int countTokens(const char *str, const char *delimiters);
int prompt(char * dir,int n,int time);
void changedir(char * input,char * def, char * prev,char * b,int y);
void peekfn(char *input,char *def,char *prev,char *b);
void proclore(char * input,char * def,char* prev, char * b);
void pastevents(char * input,char * def,char* prev, char * b,char ** filedata,int * time,int * background);
int process(char *input,char * def, char * prev, char * b,char ** filedata,int * time,int * background);
void pseudomain(char * inp,char * inpcopy,char * def,char * prev,char * b,int * time,int * background);


#endif