#include<stdio.h>
#include<omp.h>
long int multiplyNumbers(int n);
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int a[n]; 
     for(int i=0; i<n; ++i)
     {
          printf("Enter number%d: ",i+1);
          scanf("%d", &a[i]);
     }
    #pragma omp for
    for(int i=0;i<n;i++)
    printf("Factorial of %d = %ld \n \n",a[i],multiplyNumbers(a[i]));
    return 0;
}

long int multiplyNumbers(int n) {
    
    int i=1;
    #pragma omp for
    for(int j=1;j<=n;j++)
    i=i*j;
    return i;
}

