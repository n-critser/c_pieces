/**
 * Converted K n R grep from chapter 5 with current
 * linux version of getline
 *
 * */
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include<string.h>

#define MAXLINE 1000

//int getline(char*line,int max);

int main(int argc, char**argv)
{
    char *line=NULL;
    long lineno =0;
    size_t len=0;
    ssize_t nread = 0;
    
    int c, except = 0, number =0, found =0;
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        while ((c = *++argv[0]))
        {
            switch (c)
            {
                case 'x':
                    except =1;
                    break;
                case 'n':
                    number =1;
                    break;
                default:
                    fprintf(stdout,"grepish: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    if (argc != 1)
    {
        fprintf(stdout,"usage: grepish -x -n pattern\n");
    }
    else
    {
        while ((nread = getline(&line, &len,stdin)) > 0)
        {
            lineno++;
            //fprintf(stdout,"nread=%zu\n",nread);
            
            if (( strstr(line, *argv) !=NULL) != except)
            {
                if (number)
                {
                    fprintf(stdout,"%ld:",lineno);
                }
                fprintf(stdout,"%s",line);
                found++;
            }
        }
    }
    free(line);
    
    return found;
}

                
