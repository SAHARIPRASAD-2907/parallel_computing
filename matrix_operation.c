#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void main()
{
int tid;
int i,j,k,sum=0;
int rows,cols;
double s1,s2,s3,s4,s5,e1,e2,e3,e4,e5,d1,d2,d3,d4,d5;

printf("Enter Number of Rows of matrices\n");
scanf("%d",&rows);
printf("Enter Number of Columns of matrices\n");
scanf("%d",&cols);

int a[rows][cols];
int b[rows][cols];
int c1[rows][cols],c2[rows][cols],c3[rows][cols];

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

d=(int *)malloc(sizeof(int)*rows*cols);
e=(int *)malloc(sizeof(int)*rows*cols);
f1=(int *)malloc(sizeof(int)*rows*cols);
f2=(int *)malloc(sizeof(int)*rows*cols);

d=(int *)a;
e=(int *)b;
f1=(int *)c1;
f2=(int *)c2;
//Concurrent or parallel matrix addition
s1=omp_get_wtime( );
#pragma omp parallel num_threads(rows*cols)
  {
    tid=omp_get_thread_num();
    f1[tid]=d[tid]+e[tid];
  }
e1=omp_get_wtime( );
d1= e1-s1;

//Concurrent or parallel matrix subtraction
s2=omp_get_wtime( );
#pragma omp parallel num_threads(rows*cols)
  {
    tid=omp_get_thread_num();
    f2[tid]=d[tid]-e[tid];
  }
e2=omp_get_wtime( );
d2= e2-s2;

//Concrrent or parallel matrix multiplication
s3=omp_get_wtime( );
#pragma omp parallel shared(a,b,c3) private(i,j,k) 
   {
#pragma omp for  schedule(static)
   for (i=0; i<rows; i=i+1){
      for (j=0; j<rows; j=j+1){
         c3[i][j]=0.;
         for (k=0; k<rows; k=k+1){
            c3[i][j]=(c3[i][j])+((a[i][k])*(b[k][j]));
         }
      }
   }
}
e3=omp_get_wtime( );
d3= e3-s3;

//sum of rows of matrix A
printf("Values of sum of row elemnts of A are as follows:\n");
s4=omp_get_wtime( );
#pragma omp parallel shared(a) private(i,j) 
   {
#pragma omp for  schedule(static)
           for (i = 0; i < rows; ++i) 

        {

            for (j = 0; j < rows; ++j) 

            {

                sum = sum + a[i][j] ;

            }

 

       //     printf("Sum of the %d row is = %d\n", i, sum);

            sum = 0;}
}
e4=omp_get_wtime( );
d4= e4-s4;

sum=0;
printf("Values of sum of column elements of matrix B are as follows:\n");

//sum of columns of matrix B
s5=omp_get_wtime( );
#pragma omp parallel shared(b) private(i,j) 
   {
#pragma omp for  schedule(static)
                   for (j = 0; j < rows; ++j) 

        {

            for (i = 0; i < rows; ++i)

            {

                sum = sum + b[i][j];

            }

 

     //       printf("Sum of the %d column is = %d\n", j, sum);

            sum = 0;

 

        }

 
}
e5=omp_get_wtime( );
d5= e5-s5;
/*
printf("Values of Resultant Matrix ADDITION are as follows:\n");

for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
    {
       printf("Value of C1[%d][%d]=%d\n",i,j,c1[i][j]);
    }
   */
/*
printf("Values of Resultant Matrix SUBTRACTION are as follows:\n");

for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
    {
       printf("Value of C2[%d][%d]=%d\n",i,j,c2[i][j]);
    }
  */  
/*printf("Values of Resultant Matrix MULTIPLICATION are as follows:\n");

for(i=0;i<rows;i++)
  for(j=0;j<cols;j++)
    {
       printf("Value of C3[%d][%d]=%d\n",i,j,c3[i][j]);
    }*/
printf("the time taken to calulate matrix addition %f \n", d1);
printf("the time taken to calculate matrix subtraction %f \n", d2);
printf("the time taken to calculate matrix multiplication is %f \n", d3);
printf("the time taken to calculate the sum of rows of elements %f \n", d4);
printf("the time taken to perform sum of columns is %f \n", d5);


}






