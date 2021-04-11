#include <stdio.h>
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

struct flight
{
  int vuelo;
  int pasajeros;
  char destino[30];
};

int main()
{
  char cadena[LARGO]; 
  int nro_producto = 0, nro_partida = 0;
  FILE *productor;

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

  int id_semaforo;

  id_semaforo = creo_semaforo();
  inicia_semaforo(id_semaforo, VERDE);

  while (1)
  {
    espera_semaforo(id_semaforo);

    printf("\nPRODUCIMOS-PARTIDA-%04d\n", nro_partida);
    productor = fopen("lote.dat", "a");
    if (productor != NULL)
    {
      for (nro_producto = 0; nro_producto < CANTIDAD_PARTIDA; nro_producto++)
      {
         printf("PARTIDA:%04d VUELO:%04d DESTINO:%s \n", nro_partida, vuelos[nro_producto].vuelo, vuelos[nro_producto].destino);
         fprintf(productor, "PARTIDA:%04d VUELO:%04d DESTINO:%s \n", nro_partida, vuelos[nro_producto].vuelo, vuelos[nro_producto].destino);
         usleep(INTERVALO_PRODUCTO * 1000);
      }
      fclose(productor);
      nro_partida++;
      printf("\nESPERAMOS\n");
    }
    else
    {
      perror("Error al abrir lote.dat");
    }

    levanta_semaforo(id_semaforo);
    usleep(INTERVALO_PARTIDA * 1000);
  };
  return 0;
}
