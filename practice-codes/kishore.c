#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define CHUNKSIZE 10
#define N  10

int main (int argc, char *argv[]) 
{

int tid;
int i,j,k,sum=0;
int rows,cols;

printf("Enter Number of Rows of matrices\n");
scanf("%d",&rows);
printf("Enter Number of Columns of matrices\n");
scanf("%d",&cols);

int a[rows][cols];
int b[rows][cols];
int c[rows][cols];

int *d,*e,*f1,*f2;

printf("Enter %d elements of first matrix\n",rows*cols);
for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
    {
       a[i][j]=(rand() % (10)) + 1; 
    }

printf("Enter %d elements of second matrix\n",rows*cols);
for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
    {
       b[i][j]=(rand() % (10)) + 1;
    }
#pragma omp parallel shared(a,b,c) private(i,j,k) 
   {
#pragma omp for  schedule(static)
   for (i=0; i<rows; i=i+1){
      for (j=0; j<rows; j=j+1){
         c[i][j]=0.;
         for (k=0; k<rows; k=k+1){
            c[i][j]=(c[i][j])+((a[i][k])*(b[k][j]));
         }
      }
   }
}

printf("Values of Resultant Matrix MULTIPLICATION are as follows:\n");

for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
    {
       printf("Value of C[%d][%d]=%d\n",i,j,c[i][j]);
    }

}