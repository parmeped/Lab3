#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// Shared
#define CADENA_L 1000
#define CADENA_S 50

// Ej 1
#define CANTIDAD_PARTIDA 11
#define CANTIDAD_ALEATORIA 100
#define INTERVALO_PRODUCTO 100
#define INTERVALO_PARTIDA 5000
#define INTERVALO_RESERVAS 300
#define ROJO 0
#define VERDE 1

struct flight {
  int vuelo;  
  int pasajeros;
  char destino[30];
};

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

// Ej 2

#define DEPOSITO_MIN 100
#define DEPOSITO_MAX 500
#define DEPOSITOS_MIN 10
#define DEPOSITOS_MAX 20
#define TIEMPO_MIN 1000
#define TIEMPO_MAX 2500
#define CONTROL_TESORERO 2500
#define RANDOM_MIN 1
#define RANDOM_MAX 10000
#define NOMBRE_ARCHIVO "cajero"
#define EXTENSION_ARCHIVO ".dat"
#define CANTIDAD_CAJEROS 3

#define CAMPO_CNT_EFT "TC-EFEC"
#define CAMPO_CNT_CHQ "TC-CHEQ"
#define CAMPO_TOT_EFT "T$-EFEC"
#define CAMPO_TOT_CHQ "T$-CHEQ"
#define LARGO_COLUMNA 10


struct cajero {
  char nombre[20];
  int cajero_id;
  int depositos_efectivo;
  int depositos_cheque;
  int total_efectivo;
  int total_cheque;
};

struct cajero cajeros[CANTIDAD_CAJEROS] = 
{
  {"Matilde", 1, 0, 0, 0, 0},
  {"Esteban", 2, 0, 0, 0, 0},
  {"Soy1Cajero", 3, 0, 0, 0, 0}
};