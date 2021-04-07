#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char**argv)
{

    char print[256];
    char p2[256];
    char clear[256];
    
    
    double afterprint=-.999;    
    double z = 0.000000011;
    double x = 0.123;
    
    snprintf(print,255,"%.9g",x);
    fprintf(stdout,"%s\n",print);
    afterprint=atof(print);
    fprintf(stdout,"atof 20f - %.20f\n",afterprint);

    snprintf(print,255,"%.9g",z);
    snprintf(clear,255,"%d",0);
    fprintf(stdout,"string 9g - %s\n",print);
    afterprint=atof(print);
    fprintf(stdout,"atof 20f - %.20f\n",afterprint);

    memcpy(p2,print,256);
    fprintf(stdout,"p2: %s\n",p2);
    memcpy(p2,clear,256);
    memcpy(p2,print,-20);
    fprintf(stdout,"p2: %s\n",p2);
    
            
    return(0);
}
