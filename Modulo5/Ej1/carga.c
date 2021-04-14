#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../random.h" // ya incluye constants.h
#include "../shared.h"

int main()
{
  char cadena[LARGO], nombre[LARGO]; 
  int nro_producto = 0, nro_partida = 0, vuelo = CANTIDAD_PARTIDA + 1, j, partida_anterior = 0, *arrayPtr, rand_aux;
  FILE *productor;

  int id_semaforo = creo_semaforo();
  inicia_semaforo(id_semaforo, VERDE);

  while (vuelo != 0 && vuelo != -1 && (vuelo < 1 || vuelo > CANTIDAD_PARTIDA)) {
    printf("Ingrese el numero de vuelo de entre los disponibles (-1 para aleatorio, 0 para salir): \n");
    j = 1;
    for (int i = 0; i < CANTIDAD_PARTIDA; i++) {      
      printf("Id: %d, Vuelo: %d, Destino: %s \n", j, vuelos[i].vuelo, vuelos[i].destino);
      j++;
    }
    scanf("%s", cadena);
    vuelo = atoi(cadena);    
    if (vuelo == 0) {
      break;
    } else if (vuelo != -1) {
      printf("Ingrese el nombre del pasajero \n");
      scanf("%s", nombre);
    }
  }

  if (vuelo > 0) {
    espera_semaforo(id_semaforo);
  }
  
  // TODO: Producir aleatoriamente
  while (vuelo == -1) {
    espera_semaforo(id_semaforo);
    productor = fopen("lote.dat", "a");
    if (productor != NULL)
    {
      arrayPtr = randomNumbers(0, CANTIDAD_PARTIDA - 1);

      for (nro_producto = 0; nro_producto < CANTIDAD_ALEATORIA; nro_producto++)
      {
        rand_aux = *(arrayPtr + nro_producto);
        printf("PARTIDA:%04d VUELO:%04d DESTINO:%s AUX:%d \n", nro_partida, vuelos[rand_aux].vuelo, vuelos[rand_aux].destino, rand_aux);
        fprintf(productor, "PARTIDA:%04d VUELO:%04d DESTINO:%s \n", nro_partida, vuelos[rand_aux].vuelo, vuelos[rand_aux].destino);
      }
      usleep(INTERVALO_PRODUCTO * 500);
      fclose(productor);
    }
    else
    {
      perror("Error al abrir lote.dat");
    }
    usleep(INTERVALO_PARTIDA * 500);
    printf("\n Finalizó la carga aleatoria de %d vuelos. Desea cargar una nueva partida? (Y) \n", CANTIDAD_ALEATORIA);
    scanf("%s", cadena);
    if (strcmp("Y", cadena) == 0) {
      nro_partida++;
      levanta_semaforo(id_semaforo);
    } else {
      vuelo = 0;
    }
  }

  // Producir normal
  while (vuelo != 0)
  {
    // Abro archivo, guardo vuelo.
    productor = fopen("lote.dat", "a");    
    if (productor != NULL)
    {
      printf("PARTIDA:%04d VUELO:%04d DESTINO:%s NOMBRE:%s \n", nro_partida, vuelos[vuelo - 1].vuelo, vuelos[vuelo - 1].destino, nombre);
      
      // no se guarda el nombre ya que no es requisito.
      fprintf(productor, "PARTIDA:%04d VUELO:%04d DESTINO:%s \n", nro_partida, vuelos[vuelo - 1].vuelo, vuelos[vuelo - 1].destino);
      usleep(INTERVALO_PRODUCTO * 1000);
      vuelo = CANTIDAD_PARTIDA + 1;
      fclose(productor);      
    }
    else
    {
      perror("Error al abrir lote.dat");
    }

    // Chequeo partida
    while (vuelo != 0 && strcmp("Y", cadena) != 0 && strcmp("N", cadena) != 0) {
      printf("Desea generar una nueva partida? (Y/N) \n");
      scanf("%s", cadena);
      if (strcmp("Y", cadena) == 0) {
        nro_partida++;
      }
    }    
    if (vuelo != 0 && nro_partida != partida_anterior) {      
      partida_anterior = nro_partida;
      usleep(INTERVALO_PARTIDA * 1000);
      levanta_semaforo(id_semaforo);
      espera_semaforo(id_semaforo);
    }

    while (vuelo != 0 && (vuelo < 1 || vuelo > CANTIDAD_PARTIDA)) {
      printf("Ingrese el numero de vuelo de entre los disponibles (0 para salir): \n");
      j = 1;
      for (int i = 0; i < CANTIDAD_PARTIDA; i++) {      
        printf("Id: %d, Vuelo: %d, Destino: %s \n", j, vuelos[i].vuelo, vuelos[i].destino);
        j++;
      }
      scanf("%s", cadena);
      vuelo = atoi(cadena);      
      if (vuelo == 0) {
        break;
      }
      printf("Ingrese el nombre del pasajero \n");
      scanf("%s", nombre);
    }    
  };
  return 0;
}
