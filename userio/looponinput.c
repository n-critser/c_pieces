#include<stdio.h>
#include<stdlib.h>

int get_limit(int *limit)
{

    fprintf(stdout, "how many words would you like int your pw 1-10? ");
    char line[128];

    if (fgets(line,sizeof(line),stdin))
    {
        // fprintf(stdout,"line: %s",line);
        sscanf(line,"%d",limit);
    }
    return ((*limit > 0) && (*limit <11));
}

int main(int argc, char**argv)
{
    int limit;
    int ret;
    
    do
    {
        ret = get_limit(&limit);
        fprintf(stdout,"looponinput: (limit=%d)\n",limit);
    }while(ret);
}

    
