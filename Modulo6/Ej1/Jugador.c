#include "../helpers/random.h"
#include "../helpers/sem.h"
#include "../helpers/memory.h"


int main() {
    
    struct juego Juego;
    int acierto = 0, intentos = 0;
    int array[RANDOM_MAX + 1];

    // Inicializo todos los valores del array en 0. (No utilizado aun). La pos 0 queda sin utilizar.
    for (int i = 1; i < RANDOM_MAX + 1; i++) {
        array[i] = 0;
    }
    
    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while(acierto == 0) {
        espera_semaforo(id_semaforo);

        if (Juego.numero_pensado == 0 && Juego.estado_acierto == 0) {
            Juego.numero_pensado = randomNumber(RANDOM_MIN, RANDOM_MAX);
            intentos++;
        } else if (Juego.numero_pensado != 0 && Juego.estado_acierto == 1) {
            printf("Felicidades, acertaste! cantidad intentos: %d", intentos);
        }
        levanta_semaforo(id_semaforo);
    }
    
    printf("Felicidades, has ganado %s!", Juego.nombre_jugador);
    return 0;
}