#include <stdio.h>
#include <stdlib.h>
int fill_array(int arr[],int cnt);
void show_array(int arr[],int cnt);
int insertion_sort(int arr[],int cnt);

int main (int argc, char**argv)
{
    int n_ex=30;
    fprintf(stdout, "argc:%d\n",argc);
    
    if (argc == 2)
    {
        n_ex = atoi(argv[1]);
        fprintf(stdout, "n_ex: %d\n", n_ex);
        
    }
    else
    {
        fprintf(stderr,"INVALID ARGUMENTS\n");
        fprintf(stderr,"USAGE:\n\t ./main.out <array_size integer>\n\n");
        exit(-1);
    }
    
    
    int *ex_arr=(int*)malloc(n_ex * sizeof(int));
    if (!ex_arr)
    {
        fprintf(stderr,"Out of memory\n");
        exit(-1);
    }
    
    int fill_size = fill_array(ex_arr,n_ex);
    if (fill_size == (n_ex))
    {
        // show_array(ex_arr,n_ex);
        insertion_sort(ex_arr,n_ex);
        show_array(ex_arr,n_ex);
        
    }
    else
    {
        fprintf(stderr,"Unmatched size: fill_size=%d \n",
                fill_size);
    }
    
    
    
    return 0;
}

int fill_array(int arr[],int cnt)
{
    int ret=-1;
    if (cnt)
    {
        int i;
        for ( i  = 0; i < cnt; i++)
        {
            arr[i]=cnt % (i+1);
        }
        ret = i;
        
    }
    return (ret);
}

        
void show_array(int arr[],int cnt)
{
    if (  cnt)
    {
        int i;
        fprintf(stdout,"\n");
        for ( i = 0; i < cnt; i++)
        {
            fprintf(stdout, "%d ",
                    arr[i]);
            if ((i > 0) && (i %41 == 0))
            {
                fprintf(stdout,"\n");
            }
        }
        fprintf(stdout,"\n");
        
    }
}

int insertion_sort(int arr[],int cnt)
{
    int ret=-1;
    if (cnt)
    {
        int j;
        for (j=1; j < cnt; j++)
        {
            int i,key = arr[j];
            /* fprintf(stdout, "key = %d\n", */
            /*         key); */
            i = j-1;
            while ((i >= 0) && (arr[i] > key))
            {
                arr[i+1]=arr[i];
                i--;
            }
            arr[i+1]=key;
        }
        ret = j;
    }
    
    return(ret);
}

