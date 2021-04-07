/**
 * K n R dcl recursive decent parser for C declarations
 * 
 * */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS 
};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;

char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main(int argc, char**argv)
{
    while( gettoken() !=EOF)
    {
        strcpy(datatype, token);

        out[0]='\0';
        dcl();
        if( tokentype != '\n')
        {
            fprintf(stderr, "syntax error\n");
        }
        fprintf(stdout, "%s : %s %s\n",name, out, datatype);
    }

    return (0);
}

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p= token;
    while( (c= getch()) == ' ' || c == '\t')
    {
        ;
    }
    if (c == '(')
    {
        if (( c = getch()) == ')')
        {
            strcpy(token, "()");

            return (tokentype = PARENS);
        }
        else
        {
            ungetch(c);
            return (tokentype = '(');
        }
    }
    
    

void dcl(void)
{
    int ns;

    for (nx = 0; gettoken() == '+';)
    {
        ns++;
    }
    dirdcl();
    while( ns-- > 0)
    {
        strcat(out, " pointer to ");
    }
}


void dirdcl( void)
{
    int type;

    if ( tokentype == '(')
    {
        dcl();
        if (tokentype != ')')
        {
            fprintf(stdout,"error: missing )\n");
        }
    }
    else if ( tokentype == NAME)
    {
        strcpy(name, token);
    }
    else
    {
        fprintf(stdout,"error: expected name or (dcl)\n");
    }
    while (( type = gettoken()) == PARENS || type == BRACKETS)
    {
        if ( type == PARENS)
        {
            strcat(out, " function returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

            
