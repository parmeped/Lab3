#define CADENA_S 50
#define CADENA_M 500
#define CADENA_L 2000

#define CONST_SALIDA "Y"

#define CLAVE_BASE 33 
#define ROJO 0
#define VERDE 1

#define TIEMPO_ESPERA_XXS 50
#define TIEMPO_ESPERA_XS 150
#define TIEMPO_ESPERA_S 500
#define TIEMPO_ESPERA_M 1000



typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
	long	long_dest; 						//Destinatario
	int 	int_rte;						//Remitente
	int 	int_evento;						//Numero de evento
	char 	char_mensaje[CADENA_L];			//mensaje
};