#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//Find greatest common factor of a and b.
int gcd(int a, int b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

//Generate pseudorandom number based on function f(x) = (x^2 + random) mod N.
int pseudorandom(int x, int N){
    int random;
    int result;
    random = rand();
    result = ((int)pow(x, 2) + rand()) % N;
    return result;
}

//Check if the given value is prime.
bool isPrime(int num){
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
        
    }
    return true;
}

//find a prime factor of N using Pollard's Rho method
int findPrimeFactor(int N){
    int a = 2;
    int b = 2;
    int diff;
    int p;

    a = pseudorandom(a, N);
    b = pseudorandom(pseudorandom(b, N), N);
    while (b != a)
    {
        a = pseudorandom(a, N);
        b = pseudorandom(pseudorandom(b, N), N);    //Floyd cycle detection scheme
        diff = abs(a - b);
        p = gcd(diff, N);
        if (p > 1 && isPrime(p))
        {
            return p;
        }
        
    }

    return NULL;
}

//print all prime factors of N.
void printAllPF(int N){
    int f1, f2, nonPrime;

    f1 = findPrimeFactor(N);
    
    if (f1 == 0)
    {
        printf("failure\n");
    } else {
        printf("%d", f1);
        f2 = N / f1;
        while (!isPrime(f2))            //check if f2 is prime, if not 
        {                               //then find prime factors for f2
            nonPrime = f2;
            f2 = findPrimeFactor(f2);
            printf(", %d", f2);
            f2 = nonPrime/f2;
        }
        printf(", %d\n", f2);
    }
}


int main(){
    int num;
    printf("Number to be factorized:");
    scanf("%d", &num);
    getchar();
    printf("N = %d\n", num);
    printf("Prime factors of N: ");
    printAllPF(num);
}
