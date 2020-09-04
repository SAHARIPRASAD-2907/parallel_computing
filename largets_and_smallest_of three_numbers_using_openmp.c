#include<stdio.h>
#include<omp.h>
#include<time.h>
int main()
{
int tid,a,b,c,d,y;
clock_t t1_sta,t2_sta,t1_stp,t2_stp;
double tt1,tt2;
printf("ENTER NUMBER 1:");
scanf("%d",&a);
printf("ENTER NUMBER 2:");
scanf("%d",&b);
printf("ENTER NUMBER 3:");
scanf("%d",&c);
omp_set_num_threads(2);
#pragma omp parallel
{
tid=omp_get_thread_num();
if(tid==0)
{
t1_sta=clock();
printf("-----HELLO I AM THREAD ONE I AM GOING TO CALCULATE THE GREATEST OF 3 NUMBERS--- \n");
if (a >= b && a >= c) 
printf("THE LARGEST NUMBER = %d \n", a); 
if (b >= a && b >= c) 
printf("THE LARGEST NUMBER = %d \n", b); 
if(c >= a && c >= b) 
printf("THE LARGEST NUMBER = %d \n", c); 
t1_stp=clock();
tt1 = (((double) (t1_stp - t1_sta)) / CLOCKS_PER_SEC);
printf("TOTAL TIME TAKEN TO FIND LARGEST OF 3 NUMBERS = %lf \n",tt1);
}
else{
t2_sta=clock();
printf("-----HELLO I AM THREAD TWO I AM GOING TO CALCULATE THE SMALLEST OF 3 NUMBERS--- \n");
if (a <= b && a <= c) 
printf("THE SMALLEST NUMBER = %d \n", a); 
if (b <= a && b <= c) 
printf("THE SMALLEST NUMBER = %d \n", b); 
if (c <= a && c <= b) 
printf("THE SMALLEST NUMBER = %d \n", c);
t2_stp=clock();
tt2 = (((double) (t2_stp - t2_sta)) / CLOCKS_PER_SEC);
printf("TOTAL TIME TAKEN TO FIND SMALLEST OF 3 NUMBERS = %lf \n",tt2);
}
}
printf("TIME TAKEN TO FINISH THE WHOLE COMPUTATION : ");
y=omp_get_wtime();
printf("%d\n",y);
return(0);
}


