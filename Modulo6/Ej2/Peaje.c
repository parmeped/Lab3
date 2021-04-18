#include "../helpers/shared.h"

void mostrarVias(int *array, int lenght) {
    for(int i = 0; i < lenght; i++) {
        printf("VIA[%d]: %d Vehiculos \n", i + 1, array[i]);
    }
}

void guardarLiberaciones(int liberaciones) {
    FILE *archivo;
    archivo = fopen(ARCHIVO_PEAJE, "w+");
    if (archivo != NULL) {
        fprintf(archivo, "Cantidad de liberaciones de vias: %d \n", liberaciones);
    }
    fclose(archivo);
}

int main(int argc, char *argv[]) {

    int cantVias = atoi(argv[1]);
    if (cantVias < 1) {
        printf("Error, la cantidad de vias no puede ser menor a 1.");
        return 1;
    }

    int *vehiculos_en_cola;
    int tiempo_espera = randomNumber(PEAJE_MIN, PEAJE_MAX);
    int liberaciones = 0, id_memoria;

    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    vehiculos_en_cola = (int*)creo_memoria(sizeof(int)*cantVias, &id_memoria, CLAVE_BASE); 
        
    while(1) {
        for (int i = 0; i < cantVias; i++) {
            espera_semaforo(id_semaforo);
            if (vehiculos_en_cola[i] > 9) {
                printf("Liberando via %d \n", i + 1);
                vehiculos_en_cola[i] = 0;
                liberaciones++;
                guardarLiberaciones(liberaciones);
            } else if (vehiculos_en_cola[i] > 0) {
                printf("Restando un vehiculo a via %d... \n", i + 1);
                vehiculos_en_cola[i] = vehiculos_en_cola[i] - 1;
            }
            levanta_semaforo(id_semaforo);
            usleep(tiempo_espera * 1000);
        }
        mostrarVias(vehiculos_en_cola, cantVias);
    }
    shmdt ((char *)vehiculos_en_cola);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}