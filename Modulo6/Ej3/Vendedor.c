#include "../helpers/shared.h"

int main() {

    col *colchones = NULL;
    int id_memoria, valido = -1, codigo_seleccionado = -1, cantidad, salir = 0;
    char cadena[CADENA_S];

    int id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    colchones = (col*)creo_memoria(sizeof(col)*CANTIDAD_COLCHONES, &id_memoria, CLAVE_BASE); 

    while(salir != -1) {
        espera_semaforo(id_semaforo);
        while(valido == 0) {
            printf("Ingresar código del colchon.  \n");
            for (int i = 0; i < CANTIDAD_COLCHONES; i++) {
                printf("Nombre: %s, Stock: %d, codigo: %d \n", colchones[i].nombre, colchones[i].cantidad, colchones[i].codigo);
            }

            // Levanto semaforo para que la fabrica puede stockear mientras se decide.
            levanta_semaforo(id_semaforo);
            scanf("%d", &codigo_seleccionado);
            espera_semaforo(id_semaforo);
            if (codigo_seleccionado < 1 || codigo_seleccionado > CANTIDAD_COLCHONES) {
                printf("Error, el codigo seleccionado no existe! \n");
                break;
            }
            codigo_seleccionado = codigo_seleccionado - 1;
            printf("Ingrese la cantidad deseada. \n");

            // Idem punto anterior.
            levanta_semaforo(id_semaforo);
            scanf("%d", &cantidad);
            espera_semaforo(id_semaforo);

            if (cantidad < 1 || cantidad > 5 || colchones[codigo_seleccionado].cantidad - cantidad < 0) {
                printf("Error, no hay suficiente stock, o vender minimo %d y maximo %d colchones. Elija otra cantidad. \n", VENTA_MIN, VENTA_MAX);
                break;
            }
            colchones[codigo_seleccionado].cantidad = colchones[codigo_seleccionado].cantidad - cantidad;
            valido++;
        }
        valido = 0;
        salir++;
        levanta_semaforo(id_semaforo);

        // Este codigo fue implementado simplemente para permitir liberar la memoria al final, ya que en el resto de los ejercicios todos tienen while 
        // infinitos y por ende todas las salidas han de ser abruptas, sin poder liberar la memoria compartida. 
        if (salir > 10) {
            printf("Desea salir del programa? (Y) \n");
            scanf("%s", cadena);
            if (strcmp(CONST_SALIDA, cadena) == 0) {
                salir = -1;
            } 
        }
    }
    shmdt ((char *)colchones);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}