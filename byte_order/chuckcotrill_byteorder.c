/** 
 * From Chuck's answer to the following question:
 * https://softwareengineering.stackexchange.com/questions/215535/regarding-little-endian-and-big-endian-conversion
 * */
#include <stdio.h>
#include <string.h>
typedef unsigned long ulong;
typedef unsigned char uchar;
int
main(int argc, char *argv[])
{
    uchar word[4] = {(uchar)0x01,(uchar)0x23,(uchar)0x45,(uchar)0x67};
    ulong be = 0x01234567;
    ulong le = 0x67452301;
    ulong me = 0x23016745;
    ulong we; ulong ue;
    memcpy(&we,word,4);
    if( we == be ) printf("Big-endian\n");
    if( we == le ) printf("Little-endian\n");
    if( we == me ) printf("Middle-endian\n");

    char UNIX[4+1]="UNIX";
    ue  = ((ulong)'U'); ue<<=8;
    ue += ((ulong)'N'); ue<<=8;
    ue += ((ulong)'I'); ue<<=8;
    ue += ((ulong)'X');
    printf("%s = %.4s\n",UNIX,(char*)&ue);

    int ndx;
    uchar *p = word;
    printf("@%x:\n", p );
    for( ndx=0; ndx<sizeof(we); ndx++ )
    {
        printf("[%02x] %03d:%02x\n", ndx, p[ndx], p[ndx] );
    }

}
