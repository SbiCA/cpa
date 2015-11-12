#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <omp.h>

typedef unsigned long long Entero_grande;
#define ENTERO_MAS_GRANDE  ULLONG_MAX

int primo(Entero_grande n)
{
  int p;

  Entero_grande i, s;

  p = (n % 2 != 0 || n == 2);

  if (p) {
    s = sqrt(n);

   int numberOfThreads;
   int offset;
   #ifdef _OPENMP
   #pragma omp parallel
   numberOfThreads = omp_get_num_threads();
   offset = 2 * numberOfThreads;
   #else
   numberOfThreads = 1;
   offset = 2;
   #endif
    
    #pragma omp parallel private(i)
    {
      #ifdef _OPENMP
      int threadIndex =  omp_get_thread_num();
      int startIndex = (2 * threadIndex) + 3;
      #else
      int startIndex = 3;
      #endif
      for (i = startIndex; p && i <= s; i += offset)
        if (n % i == 0) p = 0;          
    }
  }

  return p;
}

int main()
{
  Entero_grande n;

  #ifdef _OPENMP
  double t1 = omp_get_wtime();
  #endif

  for (n = ENTERO_MAS_GRANDE; !primo(n); n -= 2) {
    /* NADA */
  }
  
  #ifdef _OPENMP
  double t2 = omp_get_wtime();
  printf("looptime: %f \n", t2-t1);
  #endif

  printf("El mayor primo que cabe en %d bytes es %llu.\n",
         sizeof(Entero_grande), n);

  return 0;
}
