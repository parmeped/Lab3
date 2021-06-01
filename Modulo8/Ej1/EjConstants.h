#define MIN_RANDOM 1
#define MAX_RANDOM 99
#define TIEMPO_MIN 500
#define TIEMPO_MAX 5000


typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int 	nro_jugador;	
	int		nro_a_adivinar;
	int  	cantidad_intentos;
	int 	ganador;
};