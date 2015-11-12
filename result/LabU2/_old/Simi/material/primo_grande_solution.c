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
    #pragma omp parallel
    numberOfThreads = omp_get_num_threads();
    // do not know when to stop
    #pragma omp parallel private(i)
    {
     
      //iteration: 3,5,7,9,11,13,15,17,19 ....
      //thread:    0,1,2,0,1, ,2, 0,1, 2
      int threadId = omp_get_thread_num();
      int startIndex = (threadId*2)+3;
      int offset = 2* numberOfThreads;
      for (i = startIndex; p && i <= s; i += offset)
        if (n % i == 0) p = 0;
    }
   
  }

  return p;
}

int main()
{
  int t1 = omp_get_wtime();
  Entero_grande n;

  for (n = ENTERO_MAS_GRANDE; !primo(n); n -= 2) {
    /* NADA */
  }

  int t2 = omp_get_wtime();
  printf("El mayor primo que cabe en %d bytes es %llu.\n",
         sizeof(Entero_grande), n);
  printf("took %i seconds",t2-t1);

  return 0;
}
