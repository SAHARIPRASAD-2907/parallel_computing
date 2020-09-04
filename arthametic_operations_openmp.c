#include<stdio.h>
#include<omp.h>
#include<time.h>
int main()
{
int tid,a,b,c,y;
double tt1,tt2,tt3,tt4,tt5;
clock_t t1_sta,t2_sta,t3_sta,t4_sta,t5_sta,t1_stp,t2_stp,t3_stp,t4_stp,t5_stp;
printf("ENTER NUMBER 1:");
scanf("%d",&a);
printf("ENTER NUMBER 2:");
scanf("%d",&b);
omp_set_num_threads(5);
#pragma omp parallel
{
tid=omp_get_thread_num();
if(tid==0)
{
t1_sta=clock();
printf("----HEY I AM THREAD ONE I AM GOING TO PERFORM ADDITION \n");
c=a+b;
printf("THE SUM FO 2  NUMBERS IS: %d \n",c);
t1_stp=clock();
 tt1 = (((double) (t1_stp - t1_sta)) / CLOCKS_PER_SEC);
 printf("TOTAL TIME TAKEN TO PERFORM ADDITION = %lf \n",tt1);
}
else if(tid==1)
{
t2_sta=clock();
printf("----HEY I AM THREAD TWO I AM GOING TO PERFORM SUBTRACTION \n");
c=a-b;
printf("THE DIFFERENCE FO 2 NUMBERS IS: %d \n",c);
t2_stp=clock();
 tt2 = (((double) (t2_stp - t2_sta)) / CLOCKS_PER_SEC);
 printf("TOTAL TIME TAKEN TO PERFORM SUBTRACTION = %lf \n",tt2);
 }
else if(tid==2){
t3_sta=clock();
printf("----HEY I AM THREAD THREE I AM GOING TO PERFORM MULTIPLICATION \n");
c=a*b;
printf("THE PRODUCT FO 2  NUMBERS IS: %d \n",c);
t3_stp=clock();
 tt3 = (((double) (t3_stp - t3_sta)) / CLOCKS_PER_SEC);
 printf("TOTAL TIME TAKEN TO PERFORM MULTIPLICATION = %lf \n",tt3);
}
else if(tid==3)
{
t4_sta=clock();
printf("----HEY I AM THREAD FOUR I AM GOING TO PERFORM DIVISION \n");
c=a/b;
printf("THE DIVISION FO 2  NUMBERS IS: %d \n",c);
t4_stp=clock();
 tt4 = (((double) (t4_stp - t4_sta)) / CLOCKS_PER_SEC);
 printf("TOTAL TIME TAKEN TO PERFORM DIVISION = %lf \n",tt4);
}
else 
{
t5_sta=clock();
printf("----HEY I AM THREAD FIVE I AM GOING TO PERFORM MODULO OPERATION \n");
c=a%b;
printf("THE MODULO FO 2  NUMBERS IS: %d \n",c);
t5_stp=clock();
 tt5 = (((double) (t5_stp - t5_sta)) / CLOCKS_PER_SEC);
 printf("TOTAL TIME TAKEN TO PERFORM MODULO = %lf \n",tt5);
}
}

printf("TIME TAKEN TO FINISH THE WHOLE COMPUTATION : ");
y=omp_get_wtime();
printf("%d\n",y);
return(0);
}


