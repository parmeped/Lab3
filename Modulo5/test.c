#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "shared.h"
#include "random.h"

#define CAP 10
#define MIN 0
#define MAX 100


int main(int argc, char *argv[])

{

  int *arrayPtr;
  arrayPtr = randomNumbers(vuelos[0].vuelo, vuelos[CANTIDAD_PARTIDA - 1].vuelo);
  printf("%d", *arrayPtr);

  for (int i = 0; i < CANTIDAD_ALEATORIA; i++ ) {
      printf( "*(p + %d) : %d\n", i, *(arrayPtr + i));
   }  return 0;
}


