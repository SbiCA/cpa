#include <stdio.h>
#include <math.h>
#include <omp.h>

typedef unsigned long long Entero_grande;
//#define N 100000000ULL
#define N 10000000ULL

int primo(Entero_grande n)
{
  int p;
  Entero_grande i, s;

  p = (n % 2 != 0 || n == 2);

  if (p) {
    s = sqrt(n);

    for (i = 3; p && i <= s; i += 2)
      if (n % i == 0) p = 0;
  }

  return p;
}

int main()
{
  Entero_grande i, n;
  int numberOfThreads;
  #pragma omp parallel
  numberOfThreads = omp_get_num_threads();
  n = 2; /* Por el 1 y el 2 */
  int threadFoundPrimes = 0;
  #pragma omp parallel  for private(i,threadFoundPrimes) //reduction(+:n)
  for (i = 3; i <= N; i += 2){

      if (primo(i))
      {
        int threadId = omp_get_thread_num();
        threadFoundPrimes++;
        printf("thread %i found %i primes\n",threadId,threadFoundPrimes);
         #pragma omp atomic
         n++;
      }
  }
  
  printf("Entre el 1 y el %llu hay %llu numeros primos.\n",
         N, n);

  return 0;
}
