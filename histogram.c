#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include <math.h>
float max_array(float A[],int n)
{
    int i;
    float max_val=A[0];

    #pragma omp parallel for
    for (i = 1; i < n; i++)
    {
       max_val = max_val > A[i] ? max_val:A[i];
    }
    


	return max_val;  
}
float min_array(float A[],int n)
{
    int i;
    float min_val=A[0];

    #pragma omp parallel for
    for (i = 1; i < n; i++)
    {
       min_val = min_val < A[i] ? min_val:A[i]; 
    }
   

    return min_val;
}

int main()
{
	int val_max,n;
	float a[500];
	int max_val,min_val,sd;
    printf("Enter the max value to be present in the array:");
    scanf("%d",&val_max);
    printf("Enter the number of elements in the array\n");
    scanf("%d",&n);
    #pragma omp parallel for
    for (int i=0;i<n;i++)
        a[i]=(((float)rand()/(float)(RAND_MAX)) * val_max);
    //printing the array elements
    for (int i=0;i<n;i++)
        printf("%f\n",a[i]);
    
    max_val=max_array(a,n)+1;
    min_val=min_array(a,n)+1;
    printf("The max value in the given array is:%d\n",max_val);
    printf("The min value in the given array is:%d\n",min_val);
    int count[100];
    int s;
    int num[10];
    #pragma omp parallel for
    for (int i=0;i<12; i++)
    {
    	num[i]=0;

    }
    #pragma omp parallel for
    for (int i=0;i<101; i=i+10)
    {
    	count[i/10]=i;

    }
    // for (int i = 0; i < 11; ++i)
    // {
    // 	printf("%d\n",count[i]);
    // }

    #pragma omp parallel for
    for (int z=1;z<11; z++)
    {	

    	#pragma omp parallel for
    	for (int j = 0; j < n; j++)
    	{
    		if(a[j]>count[z-1] && a[j]<count[z])
    			num[z-1]++;

    	}
    }
    //printing number of elements in each rannge 
    // #pragma omp parallal for
    // for (int i = 0; i < 10; ++i)
    // {
    // 	printf("%d\n",num[i]);
    // }

    // display the table header...

	printf("%s%13s%17s\n","the given", "histogram", "values");

	// do the iteration, outer for loop, read row by row...

	for(int i=1; i <11; i++)

	{

	printf("%9d to %9d %15d ",count[i-1],count[i], num[i]);

 

	// inner for loop, for every row, read column by column and print the bar...

	for(int j = 0;j< num[i];j++)

	// print the 'bar', and repeat...

	printf("*");

	// go to new line for new row, and repeats...

	printf("\n");

	}	
    
    return 0;



}
