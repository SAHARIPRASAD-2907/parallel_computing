#include <stdio.h>
 #include <stdlib.h>
 #include <omp.h> 
 #include <time.h>
int main (int argc, char *argv[])
 {
 	int  nthreads, tid, procs, maxt;
 	clock_t start, finish,i;
scanf("Enter number of threads = %d",&i); 
/* Start parallel region */
 #pragma omp parallel private(nthreads, tid) 
{ 
/* Obtain thread number */ 
tid = omp_get_thread_num();
printf("The obtained thread number is = %d\n",tid);
 /* Only master thread does this */ 
if (tid == 0)
 { 
 start=clock();
printf("Thread %d getting environment info...\n", tid); 
/* Print environment information */ 
printf("Number of processors = %d\n", procs);
printf("Thread number = %d \n", tid) 
printf("Max threads = %d\n", maxt);
printf("Number of threads = %d\n", nthreads);

finish=clock();
int processing_time =(double(finish-start)/CLOCKS_PER_SEC);
printf("Time taken is = %d\n",processing_time);
}
}
getch();
return 0;
 }

