# include <getopt.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include "bv.h"
# include "sieve.h"

void primeFactorization(int num, int primeCount, int *prime) 
{
    while (num > 1) 
    {
        if (num % prime[primeCount] == 0) 
        {
            num = num/prime[primeCount];
            printf("%d ", prime[primeCount]);
        } else 
        {
            primeCount++;
        }
    }
    printf("\n");
}

void findPrime(int numNumbers) 
{
    int isPrime = 0;
    int numPrime = 0;
    int primeCount = 0;
    int prime[numNumbers];
    
    bitV *bitV = newVec(numNumbers);
    oneVec(bitV);
    sieve(bitV);
    
    for (int count = 2; count <= numNumbers; count++) 
    { 
        isPrime = valBit(bitV , count);
        if (isPrime == 1) //If it's prime 
        {  
            prime[numPrime] = count; //Insert prime numbers into array so it's easier to access
            printf("%d Prime \n" , count);
            numPrime++;
        } else 
        {  
            printf("%d Composite: ", count);
            primeFactorization(count, primeCount, prime);
        } 
    }
    free(bitV->v);
}

int main(int argc, char * const argv[]) 
{
    int c;
    int numNumbers = 100; //Run up to 100 by default
    
    while ((c = getopt(argc, argv, "n:")) != -1) 
    {
        switch (c) {
            case 'n' : numNumbers = atoi(optarg); //Specify number to run until
            break;
        }
    }
    findPrime(numNumbers);
}
