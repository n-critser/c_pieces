#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
    char * wave;
    char* say;
    char* sep1;
    char* saveptr1;
    char* token;
    int i;


    char*test;

    sep1="_";

    char firstpart[256]="\0";
    char secondpart[256]="\0";

    char out1[256]="\0";
    char out2[256]="\0";

    wave= "YOU.SAY_ITS_YOUR_BIRTHDAY";
    char* wave2=strdup(wave);
    fprintf(stderr,"%s\n",wave);

    say=strstr(wave,"SAY");
    if (say !=NULL)
        {
            fprintf(stderr,"%s\n",say);
        }
    else
        {
            exit(-1);
        }
    test=strdup(say);
    for(i=0; ;test=NULL,i++)
        {
            token=strtok_r(test,sep1,&saveptr1);
            if (token==NULL)
                {
                    break;
                }
            else
                {
                    //fprintf(stdout,"test:%s\n",test);

                    char * tstr=strdup(token);
                    if (0==i)
                        {
                            strncat(firstpart,":",strlen(":"));
                            strncat(firstpart,tstr,strlen(tstr));
                        }
                    else if (1==i)
                        {
                            strncat(firstpart,"_",strlen("_"));
                            strncat(firstpart,tstr,strlen(tstr));
                        }
                    else if (2==i)
                        {
                            strncat(secondpart,":",strlen(":"));
                            strncat(secondpart,tstr, strlen(tstr));
                        }
                    else if (3==i)
                        {
                            strncat(secondpart,"_",strlen("_"));
                            strncat(secondpart,tstr,strlen(tstr));
                        }
                    fprintf(stdout,"token%d: %s\n",i,tstr);
                    free(tstr);
                }
        }
    fprintf(stdout,"first- \"%s\"\n",firstpart);
    fprintf(stdout,"second- \"%s\"\n",secondpart);


    strncat(out1,wave2,strlen(wave2));
    strncat(out1,firstpart,strlen(firstpart));

    strncat(out2,wave2,strlen(wave2));
    strncat(out2,secondpart,strlen(secondpart));

    fprintf(stdout,"out1- \"%s\"\n",out1);
    fprintf(stdout,"out2- \"%s\"\n",out2);

    free(test);
    return (0);
}
