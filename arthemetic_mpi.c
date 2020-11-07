#include <mpi.h>
#include<stdio.h>
int fib(int n) 
{ 
    if (n <= 1) 
        return n; 
    return fib(n-1) + fib(n-2); 
} 
   int main(int argc, char **argv)
   {
      int node,a,b,c1,c2,c3,c4;
      int a,b,c,d;
      long int s1,s2,s3,s4;
      printf("Enter the sum to be calculated-");
      scanf("%d",&n);
      a=(n/4);
      b=(n/4)*2;
      c=(n/4)*3;
      d=n
      d=20200;
      MPI_Init(&argc,&argv);
      MPI_Comm_rank(MPI_COMM_WORLD, &node);
      

      if( node == 0 ) {

         /* do some work as process 0 */
        for(int i=0;i<a;i++)
        {
        s1=s1+fib(i);
        }
        
      }
      else if( node == 1 ) {

         /* do some work as process 1 */
         for(int i=a;i<b;i++)
        {
        s2=s2+fib(i);
        }
      }
      else if( node == 2 ) {

          //do some work as process 2  
        for(int i=b;i<c;i++)
        {
        s3=s3+fib(i);
        }
      } 
      else if(node==3){

         /* do this work in any remaining processes */
        for(int i=c;i<d;i++)
        {
        s4=s4+fib(i);
        }
      }
      
      /* Stop this process */
      long int s=s1+s2+s3+s4;
	printf("The sum is %lu",&s);
      MPI_Finalize();
      return 0;
   }
