#include <omp.h>
#include <stdio.h>

#define RNG_MOD 0x80000000
int state;

int rng_int(void);
double rng_doub(double range);

int main() {
    int i, numIn, n;
    double x, y, pi,x1,y1;

    n = 1<<30;
    numIn = 0;
	x=omp_get_wtime();
    #pragma omp threadprivate(state)
    #pragma omp parallel private(x, y) reduction(+:numIn) 
    {

        state = 25234 + 17 * omp_get_thread_num();
        #pragma omp for
        for (i = 0; i <= n; i++) {
            x = (double)rng_doub(1.0);
            y = (double)rng_doub(1.0);
            if (x*x + y*y <= 1) numIn++;
        }
    }
    y1=omp_get_wtime();
    pi = 4.*numIn / n;
    printf("BY MALLA JYOTSNA SHREE MAHIMA \n");
    printf("18BCE0912 \n");
    printf("The value of pi with monti carlo method is: %f\n", pi);
    printf("The time taken to calculate value of pi with monti carlo method is: %f\n", y1-x1);
    return 0;
}

int rng_int(void) {
   return (state = (state * 1103515245 + 12345) & 0x7fffffff);
}

double rng_doub(double range) {
    return ((double)rng_int()) / (((double)RNG_MOD)/range);
}
