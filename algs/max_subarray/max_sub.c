#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

enum {BRUTE,DIVIDE};

int brute_max_sub(int*arr,int nmem, int *left, int * right);
int brutetest(int*arr,int nmem,int*maxsub,int alen);


int main(int argc, char** argv)
{
    int err= -1;
    int arr1[] = { 2, 3, -12, 4, -6, 8, 13, 4, -7 , -22 };
    int arr1_len=sizeof(arr1)/sizeof(int);
    int arr1_maxsub[]={5,7,25};
    int arr2[] = {13, -3, -25, 20, -3, -16, -23,
                 18, 20, -7, 12, -5 , -22, 15, -4, 7};
    int arr2_len=sizeof(arr2)/sizeof(int);
    int arr2_maxsub[]={7,10,43};

    if (argc < 2)
    {
        fprintf(stderr,"INVALID_ARGUMENT - argc = %d\n",argc);
        exit(EXIT_FAILURE);
    }

    switch(atoi(argv[1]))
    {
        case BRUTE:
            err = brutetest(arr1,arr1_len,arr1_maxsub,3);
            err = brutetest(arr2,arr2_len,arr2_maxsub,3);
            break;
        case DIVIDE:
            err = 0;
            break;
    }
    //fprintf(stdout,"max sub array ([%d]%d,[%d]%d,%d)\n",
    //        left,arr[left],right,arr[right],max_val);
    
    return (err);
}



/**
 * find max subarray by finding the n choose 2 pairs of indices
 * with the highest value sum
 *
 * */
int brute_max_sub(int*arr,int nmem, int *left, int * right)
{
    int max_step = nmem-1;
    int max_val = -99999;
    
    int step=0;
    
    // n chooose 2
    while(step < max_step)
    {
        int i,j;


        
        for (i = 0;(i+step) < nmem;i++)
        {
            int temp_sum=0;
            for (j = 0 ; j <= step; j++)
            {

                temp_sum+=arr[i+j];
                /* fprintf(stdout,"++++++++> (%d,%d,%d)\n", */
                /*         i, i+j, temp_sum); */

            }
            if (temp_sum > max_val)
            {
                /* fprintf(stdout,"--> (%d,%d,%d)\n", */
                /*         i, i+j-1, temp_sum); */
                
                max_val = temp_sum;
                *left=i;
                *right=i+j-1;
            }
        }
        step++;
    }
    return (max_val);
    
}


int brutetest(int*arr,int nmem,int*maxsub,int alen)
{
    int err=0;
    int max_val= -1;
    int left,right;
    int arr_len=nmem;
    
    
    max_val = brute_max_sub( arr,arr_len, &left,&right );
    assert(maxsub[0] == left);
    assert(maxsub[1] == right);
    assert(maxsub[2] == max_val);
    
    fprintf(stdout,"max sub array ([%d]%d,[%d]%d,%d)\n",
            left,arr[left],right,arr[right],max_val);
    return (err);
}


