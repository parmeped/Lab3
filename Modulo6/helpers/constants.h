#define CLAVE_BASE 33 
#define ROJO 0
#define VERDE 1
#define RANDOM_MIN 1
#define RANDOM_MAX 99
#define LARGO_NOMBRE 50
#define CANTIDAD 1
#define TIEMPO_ESPERA 500
#define TIEMPO_ESPERAx2 1000

// Ej 1
typedef struct juego ju;

struct juego {
    char nombre_jugador[LARGO_NOMBRE];
    int numero_pensado; // 0 = undefined; 0 > n < 100 a verificar
    int estado_acierto; // 0 = false; 1 = true
};

// Ej 2
#define PEAJE_MIN 100
#define PEAJE_MAX 5000
#define AUTOS_MIN 400
#define AUTOS_MAX 600
#define ARCHIVO_PEAJE "peajes.dat"
 


// Ej 3

const char* NOMBRES_COLCHONES[] = {"PIERO", "SUAVESTAR", "CANNON", "SIMMONS", "BELMO"};
#define CANTIDAD_COLCHONES 5
#define TIEMPO_ESPERA_COLCHON 500
#define VENTA_MIN 1
#define VENTA_MAX 5

typedef struct colchon col;

struct colchon {
    char nombre[LARGO_NOMBRE];
    int codigo;
    int cantidad;
};

