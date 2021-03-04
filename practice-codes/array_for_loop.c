#include<stdio.h>
#include<omp.h>
#include <math.h>
#include <time.h>
int isprime(int n)
{	int flag;
	for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
void prime_sum_array(int a[],int n)
{
	int sum=0;
	#pragma omp parallel for 
	for(int i = 0; i < n; ++i)
	{
		if(isprime(a[i]) && a[i]!=1)
			sum=sum+a[i];
	}
	printf("Sum of prime numbers in the array is: %d\n",sum);

}

void print_arr(int a[],int count)
{
	printf("The resultant array is \n");
	#pragma omp parallel for 
	for (int i = 0; i < count; ++i)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}
void square_arr(int a[],int count)
{
	printf("The resultant array is \n");
	#pragma omp parallel for 
	for (int i = 0; i < count; ++i)
	{
		printf("%d ",a[i]*a[i]);
	}
	printf("\n");
}
void cube_arr(int a[],int count)
{
	printf("The resultant array is \n");
	#pragma omp parallel for 
	for (int i = 0; i < count; ++i)
	{
		printf("%d ",a[i]*a[i]*a[i]);
	}
	printf("\n");
}
void add_arr(int a[],int count)
{
	int n;
	printf("Enter a number to add:\n"); 
    scanf("%d",&n);
	printf("The resultant array is \n");
	#pragma omp parallel for 
	for (int i = 0; i < count; ++i)
	{
		printf("%d ",a[i]+n);
	}
	printf("\n");
}
void mlp_arr(int a[],int count)
{
	int n;
	printf("Enter a number to multiply:\n"); 
    scanf("%d",&n);
	printf("The resultant array is \n");
	#pragma omp parallel for 
	for (int i = 0; i < count; ++i)
	{
		printf("%d ",a[i]*n);
	}
	printf("\n");
}
void print_sum(int a[],int n)
{	int sum=0;
	#pragma omp parallel for shared(sum)
	for (int i = 0; i < n; i++) 
	{
	#pragma omp critical
		sum = sum + a[i];

	}
	printf("The sum of array is:%d",sum);
	printf("\n");
}
void print_oddsum(int a[],int n)
{	int sum=0;
	#pragma omp parallel for shared(sum)
	for (int i = 0; i <n; i=i+2) 
	{
	#pragma omp critical
		sum = sum + a[i];

	}
	printf("The oddsum of array is:%d",sum);
	printf("\n");
}
void print_evensum(int a[],int n)
{	int sum=0;
	#pragma omp parallel for shared(sum)
	for (int i =1; i <n; i=i+2) 
	{
	#pragma omp critical
		sum = sum + a[i];

	}
	printf("The evensum of array is:%d",sum);
	printf("\n");
}
void print_oddnum(int a[],int count)
{
	printf("The odd numbers from array is \n");
	#pragma omp parallel for 
	for (int i = 0; i < count; ++i)
	{
		if(a[i]%2!=0)
		printf("%d ",a[i]);
	}
	printf("\n");
}
void print_evennum(int a[],int count)
{
	printf("The even numbers from the array is \n");
	#pragma omp parallel for 
	for (int i = 0; i < count; ++i)
	{
		if(a[i]%2==0)
		printf("%d ",a[i]);
	}
	printf("\n");
}
void max_array(int A[],int n)
{
    int i;
    int max_val=A[0];

    #pragma omp parallel for  
    for (i = 1; i < n; i++)
       max_val = max_val > A[i] ? max_val : A[i];

	printf("The max value in the given array is:%d\n",max_val) ;   
}
void min_array(int A[],int n)
{
    int i;
    int min_val=A[0];

    #pragma omp parallel for  
    for (i = 1; i < n; i++)
       min_val = min_val < A[i] ? min_val : A[i];

    printf("The min value in the given array is:%d\n",min_val);
}
int main() 
{ 	

    clock_t s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12;
    clock_t e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,e11,e12; 
    int a[1000],b[1000]; 
    int i,number_of_digits;
    printf("Enter the number of elements of an array:\n"); 
    scanf("%d",&number_of_digits);
    printf("Enter %d elements in the array\n",number_of_digits);  
    for (i = 0; i < number_of_digits; i++) { 
  
      
        scanf("%d",&a[i]); 
    } 
   
    //To print the array elements-
    s1=clock(); print_arr(a,number_of_digits); e1=clock();
    
     //To find the sum / odd sum / even sum of the array elements
    s2=clock();  print_oddsum(a,number_of_digits); e2=clock();
    s3=clock(); print_evensum(a,number_of_digits); e3=clock();
   //To add /multiply a value to each element and print the sum
    s4=clock(); add_arr(a,number_of_digits); e4=clock();
    s5=clock(); mlp_arr(a,number_of_digits); e5=clock();
    //To count the odd and even elements in the array
    s6=clock(); print_evennum(a,number_of_digits);e6=clock();
    s7=clock(); print_oddnum(a,number_of_digits);e7=clock();
    //To find the sum of square’sand cubesof array elements//
    s8=clock(); square_arr(a,number_of_digits);e8=clock();
    s9=clock(); cube_arr(a,number_of_digits);e9=clock();
    //To find the maximum and minimum in an array
    s10=clock(); max_array(a,number_of_digits);e10=clock();
    s11=clock(); min_array(a,number_of_digits);e11=clock();
    //To count the prime numbers and their sum in the array
    s12=clock(); prime_sum_array(a,number_of_digits);e12=clock();
    printf("The time take to print array using open mp:%ld seconds\n",e1-s1);
    printf("The time take to print odd sum of array using open mp:%ld seconds\n",e2-s2);
    printf("The time take to print even sum of array using open mp:%ld seconds\n",e3-s3);
    printf("The time take to add a element to all elements in array using open mp:%ld seconds\n",e4-s4);
    printf("The time take to multiply a element to all elemnts in array using open mp:%ld seconds\n",e5-s5);
    printf("The time take to print even numbers in a array using open mp:%ld seconds \n",e6-s6);
    printf("The time take to print odd  umbers in a array using open mp:%ld seconds\n",e7-s7);
    printf("The time take to print aquare of array elements using open mp:%ld seconds\n",e8-s8);
    printf("The time take to print cube of array elements using open mp:%ld seconds\n",e9-s9);
    printf("The time take to print max element from array using open mp:%ld seconds\n",e10-s10);
    printf("The time take to print min elemeny from array array using open mp:%ld seconds\n",e11-s11);
    printf("The time take to print prime sum of array using open mp:%ld seconds\n",e12-s12);
    return 0; 
} 