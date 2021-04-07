#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int test12();
int test57();

int matrix_mult_cubed(int A[2][2],int B[2][2], int C[2][2]);
int matrix_eql(int C[2][2], int D[2][2]);
int main(int argc, char**argv)
{
    int ret = 0;
    ret = test12();
    if (ret==0)
    {
        fprintf(stdout,"Passed test12\n");
    }
    
    ret = test57();
    if (ret==0)
    {
        fprintf(stdout,"Passed test57\n");
    }
    
    return (ret);
}


int matrix_mult_cubed(int A[2][2],int B[2][2], int C[2][2])
{
    int err=0;
    int n= 2;
    int i,j,k;
    
    for (i=0; i < n; i++)
    {
        for (j=0;j<n;j++)
        {
            for (k = 0; k<n;k++)
            {
                C[i][j]=C[i][j] + (A[i][k] * B[k][i]);
            }
        }

    }
    for (i=0; i < n; i++)
    {
        for (j=0;j<n;j++)
        {
            fprintf(stdout," %d ",C[i][j]);
            
        }
        fprintf(stdout,"\n");
        
    }
    return (err);
}


int test12()
{
    int ret=0;
    int A[2][2] ={{1,1},
                  {2,2}};
    int B[2][2] ={{1,1},
                  {2,2}};
    int C[2][2] ={{0,0},
                  {0,0}};
    int D[2][2] ={{3,3},
                  {6,6}};
    
    ret = matrix_mult_cubed(A,B,C);
    ret = matrix_eql(C,D);
    
    
    return(ret);
}

int test57()
{
    int ret=0;
    int A[2][2] ={{5,5},
                  {7,7}};
    int B[2][2] ={{5,5},
                  {7,7}};
    int C[2][2] ={{0,0},
                  {0,0}};
    int D[2][2] ={{60,60},
                  {84,84}};
    
    ret = matrix_mult_cubed(A,B,C);
    ret = matrix_eql(C,D);

    return(ret);
}


int matrix_eql(int C[2][2], int D[2][2])
{
    int ret=0;
    int i,j;
    int n=2;
    
    for (i=0; i < n; i++)
    {
        for (j=0;j<n;j++)
        {
            if (C[i][j] != D[i][j])
            {
                ret = 1;
                return (ret);
            }
        }
    }
    return(ret);
}
