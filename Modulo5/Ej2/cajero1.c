#include "../random.h" // ya incluye constants.h
#include "../shared.h"

#define NRO_CAJERO "1"

int main() {

    FILE *productor;
    int nro_lote = 0, importe, es_efectivo, depositos, tiempo_espera;
    int rand_previo = randomNumber(RANDOM_MIN, RANDOM_MAX, 0);
    int id_semaforo = creo_semaforo();
    char nombre_archivo[CADENA_S] = "";
    inicia_semaforo(id_semaforo, VERDE);
    espera_semaforo(id_semaforo);
    strcat(strcat(strcat(nombre_archivo, NOMBRE_ARCHIVO), NRO_CAJERO), EXTENSION_ARCHIVO);

    while (1)
    {
        depositos = randomNumber(DEPOSITOS_MIN, DEPOSITOS_MAX, rand_previo);

        // Abro archivo, guardo depositos.
        productor = fopen(nombre_archivo, "a");    
        if (productor != NULL)
        {
            printf("depositos: %d \n", depositos);
            for (int i = 0; i < depositos; i++) {
                importe = randomNumber(DEPOSITO_MIN, DEPOSITO_MAX, rand_previo);
                es_efectivo = randomNumber(0, 1, rand_previo);
                rand_previo = importe;

                printf("IMPORTE:%d ES_EFECTIVO:%d LOTE:%d \n", importe, es_efectivo, nro_lote);
                fprintf(productor, "IMPORTE:%d ES_EFECTIVO:%d LOTE:%d\n", importe, es_efectivo, nro_lote);
            }
            nro_lote++;
            fclose(productor);      
        }
        else
        {
            perror("Error al abrir archivo");
        }
        tiempo_espera = randomNumber(TIEMPO_MIN, TIEMPO_MAX, rand_previo);
        usleep(tiempo_espera * 1000);
        levanta_semaforo(id_semaforo);
        espera_semaforo(id_semaforo);
    };
  return 0;
}