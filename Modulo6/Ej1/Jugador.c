#include "../helpers/shared.h"

int main() {
    
    ju *memoria = NULL;
    int acierto = 0, intentos = 0, buscar_nro = 1, id_memoria, nro_pensado;
    int array[RANDOM_MAX + 1];

    // Inicializo todos los valores del array en 0. (No utilizado aun). La pos 0 queda sin utilizar.
    for (int i = 1; i < RANDOM_MAX + 1; i++) {
        array[i] = 0;
    }
    
    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    memoria = (ju*)creo_memoria(sizeof(ju)*CANTIDAD, &id_memoria, CLAVE_BASE); 
    
    printf("Es peligroso continuar sin un nombre! Por favor escribe uno: \n");
    scanf("%s", memoria[0].nombre_jugador);

    while(acierto == 0) {
        espera_semaforo(id_semaforo);

        if (memoria[0].numero_pensado == 0 && memoria[0].estado_acierto == 0) {
            while(buscar_nro == 1) {
                nro_pensado = randomNumber(RANDOM_MIN, RANDOM_MAX);
                printf("Intentando con %d... \n", nro_pensado);
                if (array[nro_pensado] == 0) {
                    array[nro_pensado] = nro_pensado;
                    memoria[0].numero_pensado = nro_pensado;
                    buscar_nro = 0;
                }
            }
            buscar_nro = 1;
            intentos++;
        } else if (memoria[0].numero_pensado != 0 && memoria[0].estado_acierto == 1) {
            acierto++;
        }
        levanta_semaforo(id_semaforo);
        // Agrego tiempo espera para evitar tantas llamadas
        usleep(TIEMPO_ESPERA * 1000);
    }
    
    printf("Felicidades %s, encontraste el número luego de %d intentos! \n", memoria[0].nombre_jugador, intentos);
    shmdt ((char *)memoria);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}