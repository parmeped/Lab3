#define CLAVE_BASE 33 
#define ROJO 0
#define VERDE 1
#define RANDOM_MIN 1
#define RANDOM_MAX 99
#define LARGO_NOMBRE 50

struct juego {
    char nombre_jugador[LARGO_NOMBRE];
    int numero_pensado; // 0 = undefined; 0 > n < 100 a verificar
    int estado_acierto; // 0 = false; 1 = true
};