#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <stdint.h>


typedef unsigned long ulong;
typedef unsigned char uchar;

uint32_t uint32_reverse_byteorder(uint32_t in)
{
    uint32_t out = in;
    uint32_t mask[4] = {0xff000000,0x00ff0000,0x0000ff00,0x000000ff};
    int i = 0;
    for (i=0;i< 4;i++)
    {
        fprintf(stdout, "%u = %.4x\t",mask[i],mask[i]);
    }
    out = (((out << 24) & mask[0])   | /* byte0 */
           ((out << 8 ) & mask[1])   | /* byte1 */
           ((out >> 8 ) & mask[2])   | /* byte2 */
           ((out >> 24) & mask[3]));   /* byte3 */

    
        
    /* out = (((out &0xff) << 24)   | /\* byte0 *\/ */
    /*        ((out & 0xff00)<<8)   | /\* byte1 *\/ */
    /*        ((out >> 8) & 0xff00) | /\* byte2 *\/ */
    /*        ((out >> 24) & 0xff));  /\* byte3 *\/ */
    fprintf (stdout, "\n%u = %.4u\n", in, out);
    return out;
    

}

uint32_t print_net_order_int(uint32_t in)
{
    uint32_t in_htonl = htonl(in);
    uint32_t htonl_ntohl = ntohl(in_htonl);
    
    fprintf (stdout, "%u = %.4u\n",in,in_htonl );
    fprintf (stdout, "%u = %.4u\n",in,htonl_ntohl );
    return htonl_ntohl;
    
}



int
main(int argc, char *argv[])
{
    const uint32_t magic = 2000;
    uint32_t after = print_net_order_int(magic);
    FILE* out_be;
    FILE* out_le;
    out_be = fopen("out_be.io","w");
    out_le = fopen("out_le.io","w");
    
    after= uint32_reverse_byteorder(magic);
    fwrite(&after,sizeof(uint32_t),1, out_be);
    after= uint32_reverse_byteorder(after);
    fwrite(&after,sizeof(uint32_t),1,  out_le);
    fclose(out_be);
    fclose(out_le);
    /**
     * out_be.io and out_le.io are written out as binary data
     * we can then hexdump the results and inspect the values
     * to see they match whats been output from fprintf
     * we can also read the same binary file into java or lisp
     * and perform similar byteorder operations.
     * 
     * hexdump -e '1/4 "%d" "\n" ' out_le.io ====> 2000
     * hexdump -e '1/4 "%d" "\n" ' out_be.io ====> -804847616
     *
     * */
    return (after == magic);
    

}
