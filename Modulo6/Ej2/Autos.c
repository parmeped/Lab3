#include "../helpers/shared.h"

int main(int argc, char *argv[]) {

    int cantVias = atoi(argv[1]);

    if (cantVias < 1) {
        printf("Error, la cantidad de vias no puede ser menor a 1.");
        return 1;
    }

    int *vehiculos_en_cola;
    int tiempo_espera = randomNumber(AUTOS_MIN, AUTOS_MAX);
    int viaSeleccionada, id_memoria;

    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    vehiculos_en_cola = (int*)creo_memoria(sizeof(int)*cantVias, &id_memoria, CLAVE_BASE); 
        
    while(1) {
        espera_semaforo(id_semaforo);
        viaSeleccionada = 0;
        for (int i = 0; i < cantVias; i++) {
            if (vehiculos_en_cola[i] < vehiculos_en_cola[viaSeleccionada]) {
                viaSeleccionada = i;
            }
        }
        printf("Se eligió la via %d! \n", viaSeleccionada + 1);
        vehiculos_en_cola[viaSeleccionada] = vehiculos_en_cola[viaSeleccionada] + 1;
        levanta_semaforo(id_semaforo);
        usleep(tiempo_espera * 1000);
    }
    shmdt ((char *)vehiculos_en_cola);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}