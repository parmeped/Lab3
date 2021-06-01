#define MIN_RANDOM 1
#define MAX_RANDOM 99

typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int 	nro_jugador;	
	int*	bolillas;						
	int  	cantidad_intentos;
};