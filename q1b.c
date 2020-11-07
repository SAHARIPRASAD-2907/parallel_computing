#include <stdio.h>
#include<omp.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
int convert(long long n);
long long convertOctalToDecimal(int octalNumber);
int main() {
    long long n;
    printf("Enter a binary number: ");
    scanf("%lld", &n);
    int octalNumber;
    printf("Enter an octal number: ");
    scanf("%d", &octalNumber);
    int decnum=0, rem, i=0, len=0;
    char hexnum[20];
    printf("Enter any Hexadecimal Number: ");
    scanf("%s", hexnum);
    #pragma omp selection
    {
    #pragma omp slection
    {
    printf("%lld in binary = %d in decimal \n \n", n, convert(n));
    }
    #pragma omp selection
    {
    printf("%d in octal = %lld in decimal \n \n", octalNumber, convertOctalToDecimal(octalNumber));
    }
    #pragma omp selection
    {
    while(hexnum[i]!='\0')
    {
        len++;
        i++;
    }
    len--;
    i=0;
    while(len>=0)
    {
        rem = hexnum[len];
        if(rem>=48 && rem<=57)
            rem = rem-48;
        else if(rem>=65 && rem<=90)
            rem = rem-55;
        else
        {
            printf("\nYou've entered an invalid Hexadecimal digit");
            return 0;
        }
        decnum = decnum + (rem*pow(16, i));
        len--;
        i++;
    }
    printf("\nEquivalent Decimal Value = %d", decnum);
    }
    }
    return 0;
}

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
long long convertOctalToDecimal(int octalNumber)
{
    int decimalNumber = 0, i = 0;

    while(octalNumber != 0)
    {
        decimalNumber += (octalNumber%10) * pow(8,i);
        ++i;
        octalNumber/=10;
    }

    i = 1;

    return decimalNumber;
}