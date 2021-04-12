#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define CANTIDAD_PARTIDA 11
#define INTERVALO_PRODUCTO 100
#define INTERVALO_PARTIDA 5000
#define ROJO 0
#define VERDE 1
#define LARGO 1000

key_t creo_clave()
{
  // Igual que en cualquier recurso compartido (memoria compartida, semaforos
  // o colas) se obtien una clave a partir de un fichero existente cualquiera
  // y de un entero cualquiera. Todos los procesos que quieran compartir este
  // semaforo, deben usar el mismo fichero y el mismo entero.
  key_t clave;
  clave = ftok("/bin/ls", 33);
  if (clave == (key_t)-1)
  {
    printf("No puedo conseguir clave de semaforo\n");
    exit(0);
  }
  return clave;
}

//funcion que crea el semaforo
int creo_semaforo()
{
  key_t clave = creo_clave();
  //PRIMER PARAMETRO ES LA CLAVE, EL SEGUNDO CANT SEMAFORO, EL TERCERO 0600 LO UTILIZA CUALQUIERA, IPC ES CONSTANTE (VEA SEMAFORO)
  int id_semaforo = semget(clave, 1, 0600 | IPC_CREAT);
  if (id_semaforo == -1)
  {
    printf("Error: no puedo crear semaforo\n");
    exit(0);
  }
  return id_semaforo;
}

//inicia el semaforo
void inicia_semaforo(int id_semaforo, int valor)
{
  semctl(id_semaforo, 0, SETVAL, valor);
}

//levanta el semaforo
void levanta_semaforo(int id_semaforo)
{
  struct sembuf operacion;
  printf("Levanta SEMAFORO \n");
  operacion.sem_num = 0;
  operacion.sem_op = 1;
  operacion.sem_flg = 0;
  semop(id_semaforo, &operacion, 1);
}

//espera semaforo
void espera_semaforo(int id_semaforo)
{
  struct sembuf operacion;
  printf("Espera SEMAFORO \n");
  operacion.sem_num = 0;
  operacion.sem_op = -1;
  operacion.sem_flg = 0;
  semop(id_semaforo, &operacion, 1);
}

struct flight {
  int vuelo;  
  int pasajeros;
  char destino[30];
};

int main()
{
  char cadena[LARGO];

  // Lo ideal sería un diccionario o una hashtable pero requiere una implementacion mas compleja.
  struct flight vuelos[CANTIDAD_PARTIDA] =
  {
    {1000, 0, "Caracas"},
    {1001, 0, "Brasil"},
    {1002, 0, "España"},
    {1003, 0, "Italia"},
    {1004, 0, "Egipto"},
    {1005, 0, "Mexico"},
    {1006, 0, "Mongolia"},
    {1007, 0, "China"},
    {1008, 0, "Japon"},
    {1009, 0, "Peru"},
    {1010, 0, "India"}
  };

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
    usleep(INTERVALO_PARTIDA * 1000);
  };
  return 0;
}
