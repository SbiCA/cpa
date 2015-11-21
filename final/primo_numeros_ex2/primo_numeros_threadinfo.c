#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <omp.h>

typedef unsigned long long Entero_grande;
//#define N 100000000ULL
#define N 100000000ULL

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
  int* primesFoundPerThread = (int*) calloc(numberOfThreads, sizeof(int));
  for(i = 0; i < numberOfThreads; i++){
    primesFoundPerThread[i] = 0;
  }
  
  #pragma omp parallel for
  for (i = 3; i <= N; i += 2){

      if (primo(i))
      {
        int threadId = omp_get_thread_num();
        primesFoundPerThread[threadId]++;
         #pragma omp atomic
         n++;
      }
  }
  
  for(i = 0; i < numberOfThreads; i++){
    printf("thread %i found %i primes\n",i,primesFoundPerThread[i]);
  }
  
  printf("Entre el 1 y el %llu hay %llu numeros primos.\n",
         N, n);

  return 0;
}
