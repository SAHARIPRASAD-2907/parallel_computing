#include<omp.h>
#include<stdio.h>
int main()
{
	int no_proc,no_thread,x,y,z,c;
	printf("No of Processor in the system : ");
	no_proc=omp_get_num_procs();
	printf("%d\n",no_proc);
	printf("Thread number in the system : ");
	no_thread=omp_get_thread_num();
	printf("%d\n",no_thread);
	printf("Maximum no of threads in the system : ");
	c=omp_get_max_threads();
	printf("%d\n",c);
	printf("No of threads in the system : ");
	x=omp_get_num_threads();
	printf("%d\n",x);
	printf("Time taken for the given computation : ");
	y=omp_get_wtime();
	printf("%d\n",y);
	omp_set_num_threads(2);
	z=omp_get_num_threads();
	printf("Set no of threads in the system : ");
	printf("%d\n",z);


return 0;	
}


