#include "../helpers/shared.h"


int main() {
    
    ju *memoria = NULL;
    int pienso_nro_local, acierto = 0, id_memoria;
    
    pienso_nro_local = randomNumber(RANDOM_MIN, RANDOM_MAX);
    printf("Numero elegido: %d \n", pienso_nro_local);
    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    memoria = (ju*)creo_memoria(sizeof(ju)*CANTIDAD, &id_memoria, CLAVE_BASE); 

    while(acierto == 0) {
        espera_semaforo(id_semaforo);

        if (memoria[0].numero_pensado != 0 && memoria[0].estado_acierto == 0) {
            printf("Pensaste en %d... \n", memoria[0].numero_pensado);
            if (memoria[0].numero_pensado == pienso_nro_local) {
                printf("Acertaste! \n");
                memoria[0].estado_acierto = 1;
                acierto++;
            } else {
                printf("No acertaste! \n");
                memoria[0].numero_pensado = 0;
                memoria[0].estado_acierto = 0;
            }
        }
        levanta_semaforo(id_semaforo);
        // Agrego tiempo espera para evitar tantas llamadas
        usleep(TIEMPO_ESPERA * 1000);
    }
    
    printf("Felicidades, has ganado %s! \n", memoria[0].nombre_jugador);

    shmdt ((char *)memoria);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}