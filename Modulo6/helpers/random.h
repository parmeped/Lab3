#include "shared.h"

// se le pasa otro nro para sumar al time ya que si se realizan llamadas contiguas devuelve el mismo nro.
int randomNumber(int min, int max)

{
  srand(time(NULL));
  return (rand() % (max - min + 1)) + min;
}

