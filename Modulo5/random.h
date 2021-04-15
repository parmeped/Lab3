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

// se le pasa otro nro para sumar al time ya que si se realizan llamadas contiguas devuelve el mismo nro.
int randomNumber(int min, int max, int prevRandSeed)

{
  srand(time(NULL) + prevRandSeed);
  return (rand() % (max - min + 1)) + min;
}

