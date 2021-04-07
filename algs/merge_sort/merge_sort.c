#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<math.h>
int merge(int *arr,int p, int q, int r);
int merge_sort(int *arr, int p, int r);
int fill_array(int arr[],int cnt);
void show_array(int arr[],int cnt);


int main(int argc, char ** argv)
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
        /* show_array(ex_arr,n_ex); */
        merge_sort(ex_arr,0,n_ex-1);
        show_array(ex_arr,n_ex);
    }
    else
    {
        fprintf(stderr,"Unmatched size: fill_size=%d \n",
                fill_size);
    }
    
        
    return (0);
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


int merge(int *arr,int p, int q, int r)
{
    int sentinel=9999999;
    
    
    int n1,n2;
    n1 = q - p ;
    n2 = r - q;
    int *L=(int*)malloc(( n1 + 1) * sizeof(int));
    int *R=(int*)malloc(( n2 + 1) * sizeof(int));
    int i,j;
    for (i = 0; i <= n1; i++)
    {
        // fprintf(stdout,"p+i: arr[%d]:%d\n",p+i,arr[p+i]);
        
        L[i]=arr[p+i];
    }
    for (j = 0; j < n2; j++)
    {
        // fprintf(stdout,"q+j: arr[%d]:%d\n",q+j+1,arr[q+j+1]);
        R[j] = arr[q+j+1];
    }
    L[i]=sentinel;
    R[j]=sentinel;
    i = 0;
    j = 0;
    int k;
    for (k = p; (k <= r) && (i <=n1) && (j<=n2);k++)
    {
        /* fprintf(stdout,"L[%d]:%d - R[%d]:%d\n", */
        /*         i,L[i],j,R[j]); */
        
        if (L[i] <= R[j])
        {
            arr[k]=L[i++];
        }
        else
        {
            arr[k] = R[j++];
            
        }
    }
    /* fprintf(stdout,"p:%d,q:%d,r:%d,k:%d,n1:%d,n2:%d\n", */
    /*         p,q,r,k,n1,n2); */
    
    return (0);
}

int merge_sort(int *arr, int p, int r)
{
    if (p < r)
    {
        int q = floor((p+r)/2);
        /* fprintf(stdout,"p:%d,q:%d,r:%d\n", */
        /*         p,q,r); */
        merge_sort(arr,p,q);
        merge_sort(arr,q+1,r);
        merge(arr,p,q,r);
    }
    
    return (0);
}

