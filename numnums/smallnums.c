#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(int argc,char**argv)
{

    char print[256];
    double afterprint=-.999;    
    float x = 0.0000000000000000000000000456;
    double y = 0.0000000000000000000000000456;
    double z = 0.000000011;
    fprintf(stdout,"e   - %e \n",x);
    fprintf(stdout,"g   - %g \n",y);
    fprintf(stdout,"g   - %g \n",z);
    fprintf(stdout,"12f - %.30f \n",x);
    fprintf(stdout,"9g - %.9g  \n",x);
    snprintf(print,255,"%.9g",x);
    fprintf(stdout,"%s\n",print);
    afterprint=atof(print);
    fprintf(stdout,"atof 20f - %.20f\n",afterprint);

    snprintf(print,255,"%.9g",z);
    fprintf(stdout,"string 9g - %s\n",print);
    afterprint=atof(print);
    fprintf(stdout,"atof 20f - %.20f\n",afterprint);
    
            
    return(0);
}
