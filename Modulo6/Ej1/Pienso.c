#include "../helpers/random.h"
#include "../helpers/sem.h"
#include "../helpers/memory.h"


int main() {
    
    struct juego Juego;
    int pienso_nro_local, acierto = 0;
    
    pienso_nro_local = randomNumber(RANDOM_MIN, RANDOM_MAX);
    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while(acierto == 0) {
        espera_semaforo(id_semaforo);

        if (Juego.numero_pensado != 0 && Juego.estado_acierto == 0) {
            if (Juego.numero_pensado == pienso_nro_local) {
                printf("Acertaste!");
                Juego.estado_acierto = 1;
                acierto++;
            } else {
                printf("No acertaste!");
                Juego.numero_pensado = 0;
                Juego.estado_acierto = 0;
            }
        }
        levanta_semaforo(id_semaforo);
    }
    
    printf("Felicidades, has ganado %s!", Juego.nombre_jugador);
    return 0;
}