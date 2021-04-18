#include "../helpers/shared.h"

int main() {

    col *colchones = NULL;
    int id_memoria;

    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    colchones = (col*)creo_memoria(sizeof(col)*CANTIDAD_COLCHONES, &id_memoria, CLAVE_BASE); 

    for (int i = 0; i < CANTIDAD_COLCHONES; i++) {
        strcpy(colchones[i].nombre, NOMBRES_COLCHONES[i]);
        colchones[i].cantidad = 10;
        colchones[i].codigo = i + 1;
    }

    while(1) {
        for (int i = 0; i < CANTIDAD_COLCHONES; i++) {
            espera_semaforo(id_semaforo);
            if (colchones[i].cantidad < 10) {
                printf("Fabricando colchon para %s (codigo %d)... \n", colchones[i].nombre, colchones[i].codigo);
                colchones[i].cantidad = colchones[i].cantidad + 1;
            }
            levanta_semaforo(id_semaforo);
            usleep(TIEMPO_ESPERA_COLCHON * 1000);
        }
    }
    shmdt ((char *)colchones);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}