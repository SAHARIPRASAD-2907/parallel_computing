#include <stdio.h>
#include <omp.h>
void work1() 
{
	printf("Work1 processing\n");
}
void work2() 
{
	printf("work2processing\n");
}
void single_example()
{  
#pragma omp parallel  
	{    
	#pragma omp single      
		printf("Beginning work1.\n");    
		work1();    
		#pragma omp single      
		printf("Finishing work1.\n");    
		#pragma omp single nowait      
		printf("Finished work1 and beginning work2.\n");    
		work2();  
	}
}
float w1(int i)
{  return 1.0 * i;}
float w2(int i)
{   return 2.0 * i;}
void atomic_example(float *x, float *y, int *index, int n)
{  int i;  
#pragma omp parallel for shared(x, y, index, n)    
	for (i=0; i<n; i++) 
		{      
		#pragma omp atomic update      
			x[index[i]] += w1(i);      
			y[i] += w2(i);
		}
		printf("work done through automic contruct value of y:\n");
		for (i = 0; i < 10; ++i)
		{
			printf("%f ",y[i]);
		}
}
void sharing_section_directive()
{
	int N=10;
	int i, nthreads, tid;
	float a[N], b[N], c[N], d[N];

/* Some initializations */
	for (i=0; i<N; i++) {
	a[i] = i * 1.5;
	b[i] = i + 22.35;
	c[i] = d[i] = 0.0;
						}

	#pragma omp parallel shared(a,b,c,d,nthreads) private(i,tid)
	{
	tid = omp_get_thread_num();
	if (tid == 0)
	{
	nthreads = omp_get_num_threads();
	printf("Number of threads = %d\n", nthreads);
	}
	printf("Thread %d starting...\n",tid);

	#pragma omp sections 
	{
	#pragma omp section
	{
	printf("Thread %d doing section 1\n",tid);
	for (i=0; i<N; i++)
	{
	c[i] = a[i] + b[i];
	printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
	}
	}

	#pragma omp section
	{
	printf("Thread %d doing section 2\n",tid);
	for (i=0; i<N; i++)
	{
	d[i] = a[i] * b[i];
	printf("Thread %d: d[%d]= %f\n",tid,i,d[i]);
	}
	}

	}  /* end of sections */

	printf("Thread %d done.\n",tid); 

	}  /* end of parallel section */

}
void for_loop_sharing()
{
	int CHUNKSIZE=10;
	int N=10;
	int nthreads, tid, i, chunk;
	float a[N], b[N], c[N];

/* Some initializations */
for (i=0; i < N; i++)
a[i] = b[i] = i * 1.0;
chunk = CHUNKSIZE;

#pragma omp parallel shared(a,b,c,nthreads,chunk) private(i,tid)
{
tid = omp_get_thread_num();
if (tid == 0)
{
nthreads = omp_get_num_threads();
printf("Number of threads = %d\n", nthreads);
}
printf("Thread %d starting...\n",tid);

#pragma omp for schedule(dynamic,chunk)
for (i=0; i<N; i++)
{
c[i] = a[i] + b[i];
printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
}

}  /* end of parallel section */

}
int main (void)
{
    int i = 10;
    printf("using privrte in openmp\n\n");
    //to elobrate the private variable using openMP
    #pragma omp parallel private(i)
    {
        printf("thread %d: i = %d\n", omp_get_thread_num(), i);
        i = 1000 + omp_get_thread_num();
    }

    printf("i = %d\n", i);
    int section_count = 0;    
    omp_set_dynamic(0);    
    omp_set_num_threads(4);
    printf("using first privrte in openmp\n\n"); 
    //to elobrate the first private variable in openMP
    #pragma omp parallel
    #pragma omp sections firstprivate( section_count )
    {
    #pragma omp section    
    {        
    section_count++;        
    /* may print the number one or two */        
    printf( "section_count %d\n", section_count );    
    }
    //to elobrate about section directive in OpenMP
    #pragma omp section    
    {        
    section_count++;        
    /* may print the number one or two */        
    printf( "section_count %d\n", section_count );    
	}
	}
	printf("using last private in openmp\n\n");
	//to elobrate last private using openMP
	int val = 123456789;
 
    printf("Value of \"val\" before the OpenMP parallel region: %d.\n", val);
	#pragma omp parallel for lastprivate(val)
    for(int i = 0; i < omp_get_num_threads(); i++)
    {
        val = omp_get_thread_num();
    }
 
    // Value after the parallel region; unchanged.
    printf("Value of \"val\" after the OpenMP parallel region: %d. Thread %d was therefore the last one to modify it.\n", val, val);
    printf("using single work contruct in openmp\n\n");
    //elobrating single work construce
    single_example();
    float x[1000];  
    float y[10000];  
    int index[10000];    
  
    for (i = 0; i < 10000; i++) 
    	{    
    		index[i] = i % 1000;    
    		y[i]=0.0;
    	}  
    	for (i = 0; i < 1000; i++)    
    		x[i] = 0.0;
    printf("using atopmic in openmp\n\n");

    //elobrating atomic contruct  
    atomic_example(x, y, index, 10000);
    printf("using for loop sharing in openmp\n\n");
 	//for loop sharing
 	for_loop_sharing();
    printf("using section loop sharing in openmp\n\n");	
 	//section loop sharing()
 	sharing_section_directive();

    return 0;
}
