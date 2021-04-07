#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <error.h>
/**
 * GLOBAL CONSTANTS
 */
const int MAXLEN = 512;
const int MAXLINE= 100;
const int MAXSTRING=1024;


void show_lines(char*lines[],int n_lines)
{
    int i;

    for(i =0; i < n_lines; i++)
    {
        fprintf(stdout,"%s",lines[i]);
    }
    fprintf(stdout,"\n");
    
}

/* void qsort(void*lineptr[],int left, int right, */
/*            int(*comp)(void*,void*)); */

int cmpstring(const void*s1,const void*s2)
{
    char* str1=(char*)s1;
    char* str2=(char*)s2;
    return(strcmp(str1,str2));
}


int read_file_to_buf(FILE* fin,char *buffer[]);

int main(int argc, char**argv)
{

    if (argc <2)
    {
        fprintf(stderr,"INVALID ARGUMENTS\n");
        
        exit(EXIT_FAILURE);
    }
    char* fname;
    
    fprintf(stdout,"%s\n",argv[1]);
    
    fname = (char*)malloc(MAXSTRING);
    if (fname !=NULL)
    {
        strncpy(fname,argv[1],MAXSTRING-1);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    FILE* fp = fopen(fname,"rw");
    if (fp != NULL)
    {
        char *buffer[MAXLINE];
        int n_lines=0;
        
        if ((n_lines = read_file_to_buf(fp,buffer))>0)
        {
            fprintf(stdout,"n_lines:%d\n",n_lines);
            
            show_lines(buffer,n_lines);
            /**
             * how does qsort behave if the size of the array doesn't
             * match the number of live elements?
             * Will it only sort the number of elements 
             * */
            qsort(buffer,n_lines,sizeof(char*),cmpstring);
            
            fprintf(stdout,"n_lines:%d\n",n_lines);

            show_lines(buffer,n_lines);
            
        }
        else
        {
            fprintf(stdout,"no lines to show\n");
        }
        
        
    }
    return(0);
    
}



int read_file_to_buf(FILE* fin,char *buf[])
{
    int lc=0;
    char *p, line[MAXLEN];
    if (fin !=NULL)
    {
        while( fgets(line,MAXLEN,fin) !=NULL)
        {
            p =(char*) malloc(strlen(line)+1);
            
            if (lc > MAXLINE || p == 0)
            {
                fprintf(stderr,"virtual memory exhausted\n");
                return -1;
            }
            else
            {
                // add a newline to any line that doesn't already have one
                line[strlen(line)]='\0';
                strncpy(p,line,strlen(line)+1);
                buf[lc++] = p;
            }
        }
    }
    return(lc);
}
