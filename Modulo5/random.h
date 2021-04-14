#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "constants.h"

int * randomNumbers(int min, int max)

{
  static int array[CANTIDAD_ALEATORIA];
  srand(time(NULL));

  for(int i = 0; i < CANTIDAD_ALEATORIA; i++) {
    array[i] = (rand() % (max - min + 1)) + min;
  }    
  
  return array;
}


