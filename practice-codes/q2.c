#include <stdio.h>
#include<omp.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
int convert(long long n) {
    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}
long long bconvert(int n) {
    long long bin = 0;
    int rem, i = 1, step = 1;
    while (n != 0) {
        rem = n % 2;
        printf("Step %d: %d/2, Remainder = %d, Quotient = %d\n", step++, n, rem, n / 2);
        n /= 2;
        bin += rem * i;
        i *= 10;
    }
    return bin;
}
int main() {
    int number, temp, digit1, digit2, digit3;


    #pragma omp sections 
    {
        #pragma omp selection
        {
            printf("Print all Armstrong numbers between 1 and 1000:\n");
            number = 001;
            while (number <= 900)
            {
        digit1 = number - ((number / 10) * 10);
        digit2 = (number / 10) - ((number / 100) * 10);
        digit3 = (number / 100) - ((number / 1000) * 10);
        temp = (digit1 * digit1 * digit1) + (digit2 * digit2 * digit2) + (digit3 * digit3 * digit3);
        if (temp == number)
        {
            printf("\n Armstrong no is:%d", temp);
        }
        number++;
        }
        }
        #pragma omp selection
        {
            printf("THREAD2 \n");
            long long n1=10000111;
            printf("%lld in binary = %d in decimal", n1, convert(n1));
        }
        #pragma omp selection
        {
            int n2=213;
            printf("%d in decimal = %lld in binary", n2, bconvert(n2));
        }
    }
return 0;
}

