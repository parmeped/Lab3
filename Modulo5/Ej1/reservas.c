#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "../constants.h"
#include "../shared.h"

int main()
{
  char cadena[LARGO];
  int cant_producto = 0;
  FILE *consumidor;

  int id_semaforo = creo_semaforo();  
  char *e;
  char destino[50], part_char[50], test[100], buffer[50];
  int index, delimiter, partida, vuelo, i = 0;

  while (1)
  {    
    espera_semaforo(id_semaforo);

    consumidor = fopen("lote.dat", "r");
    if (consumidor != NULL)
    {
      printf("\nCONSUMIMOS!!\n");
      while (!feof(consumidor))
      {

        fscanf(consumidor, "PARTIDA:%04d VUELO:%04d DESTINO:%s \n", &partida, &vuelo, destino);
        printf("PARTIDA:%04d VUELO:%04d DESTINO:%s \n", partida, vuelo, destino);
        
        switch(vuelo) {
          case(1000):
            i = 0;
            vuelos[i].pasajeros++;
            break;
          case (1001):
            i = 1;
            vuelos[i].pasajeros++;
            break;
          case (1002):
            i = 2;
            vuelos[i].pasajeros++;
            break;
          case (1003):
            i = 3;
            vuelos[i].pasajeros++;
            break;
          case (1004):
            i = 4;
            vuelos[i].pasajeros++;
            break;
          case (1005):
            i = 5;
            vuelos[i].pasajeros++;
            break;
          case (1006):
            i = 6;
            vuelos[i].pasajeros++;
            break;
          case (1007):
            i = 7;
            vuelos[i].pasajeros++;
            break;
          case (1008):
            i = 8;
            vuelos[i].pasajeros++;
            break;
          case (1009):
            i = 9;
            vuelos[i].pasajeros++;
            break;
          case (1010):
            i = 10;
            vuelos[i].pasajeros++;
            break;
          default:
            break;
        }
        i = 0;
      
        usleep(INTERVALO_PRODUCTO * 1000);
        cant_producto++;
      }
      fclose(consumidor);
      if (cant_producto > 0)
      {
        printf("\nBORRAMOS\n");
        sprintf(part_char, "%04d", partida);
        strcpy(buffer, "lote");
        strcat(buffer, part_char);
        rename("lote.dat", strcat(buffer, ".dat"));
        cant_producto = 0;
      }
      for(int j = 0; j < 11; j++) {
        printf("Vuelo: %d, Destino: %s, Pasajeros: %d \n", vuelos[j].vuelo, vuelos[j].destino, vuelos[j].pasajeros);
      }
    }
    else
    {
      perror("Error al abrir lote.dat");
    }

    printf("\nESPERAMOS\n");

    levanta_semaforo(id_semaforo);
    usleep(300);
  };
  return 0;
}
