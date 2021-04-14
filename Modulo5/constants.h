#define CANTIDAD_PARTIDA 11
#define CANTIDAD_ALEATORIA 100
#define INTERVALO_PRODUCTO 100
#define INTERVALO_PARTIDA 5000
#define ROJO 0
#define VERDE 1
#define LARGO 1000

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