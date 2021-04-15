#include "../constants.h"
#include "../shared.h"

void revisarCajeros(int cajero_id, struct cajero *cajero_total) {
    
    FILE *consumidor;
    int importe, es_efectivo, nro_lote, cant_producto;
    char archivo_org[CADENA_S] = "", arch_renom[CADENA_S] = "", buffer[CADENA_S] = "";
    
    // buffer del cajero_id
    sprintf(buffer, "%d", cajeros[cajero_id].cajero_id);
    // nombre archivo original
    strcat(strcat(strcat(archivo_org, NOMBRE_ARCHIVO), buffer), EXTENSION_ARCHIVO);

    consumidor = fopen(archivo_org, "r");
    if (consumidor != NULL)
    {
        printf("\nCONSUMIMOS!!\n");
        
        while (!feof(consumidor))
        {

            fscanf(consumidor, "IMPORTE:%d ES_EFECTIVO:%d LOTE:%d \n", &importe, &es_efectivo, &nro_lote);
            printf("IMPORTE:%d ES_EFECTIVO:%d LOTE:%d \n", importe, es_efectivo, nro_lote);
            if (es_efectivo == 1) {
                cajeros[cajero_id].depositos_efectivo++;
                cajeros[cajero_id].total_efectivo += importe;
                cajero_total->depositos_efectivo++;
                cajero_total->total_efectivo += importe;
            } else {
                cajeros[cajero_id].depositos_cheque++;
                cajeros[cajero_id].total_cheque += importe;
                cajero_total->depositos_cheque++;
                cajero_total->total_cheque += importe;
            }
        }
      
        usleep(INTERVALO_PRODUCTO * 1000);
        cant_producto++;
      
        fclose(consumidor);
        if (cant_producto > 0)
        {
            printf("\n Renombramos \n");
            
            // Primer buffer arch_renom
            strcat(strcat(arch_renom, NOMBRE_ARCHIVO), buffer);
            // buffer del lote + agregar "." previo
            sprintf(buffer, ".%d", nro_lote);
            strcat(strcat(arch_renom, buffer), EXTENSION_ARCHIVO);

            rename(archivo_org, arch_renom);
            cant_producto = 0;
        }
    }
    else
    {
      perror("Error al abrir el archivo");
    }
}

void mostrarCajeros(struct cajero *cajero_total) {
    printf("%*s%*s%*s%*s \n",
        LARGO_COLUMNA ,CAMPO_CNT_EFT,
        LARGO_COLUMNA ,CAMPO_TOT_EFT,
        LARGO_COLUMNA ,CAMPO_CNT_CHQ,
        LARGO_COLUMNA ,CAMPO_TOT_CHQ
        );
    printf(
        "%*d%*d%*d%*d \n",
        LARGO_COLUMNA ,cajero_total->depositos_efectivo,
        LARGO_COLUMNA ,cajero_total->total_efectivo, 
        LARGO_COLUMNA ,cajero_total->depositos_cheque, 
        LARGO_COLUMNA ,cajero_total->total_cheque);

    for(int i = 0; i < CANTIDAD_CAJEROS; i++) {
        printf("\n %s \n", cajeros[i].nombre);
        printf("%*s%*s%*s%*s \n",
        LARGO_COLUMNA ,CAMPO_CNT_EFT,
        LARGO_COLUMNA ,CAMPO_TOT_EFT,
        LARGO_COLUMNA ,CAMPO_CNT_CHQ,
        LARGO_COLUMNA ,CAMPO_TOT_CHQ
        );
        printf(
            "%*d%*d%*d%*d \n",
            LARGO_COLUMNA ,cajeros[i].depositos_efectivo,
            LARGO_COLUMNA ,cajeros[i].total_efectivo, 
            LARGO_COLUMNA ,cajeros[i].depositos_cheque, 
            LARGO_COLUMNA ,cajeros[i].total_cheque);
    }   
}


int main()
{
    int id_semaforo = creo_semaforo();  
    struct cajero cajero_total = { .cajero_id = 0, .nombre = "Total" }; 

    while (1)
    {    

        for (int i = 0; i < CANTIDAD_CAJEROS; i++) {
            revisarCajeros(i, &cajero_total);
        }

        mostrarCajeros(&cajero_total);    
        printf("\nESPERAMOS\n");

        levanta_semaforo(id_semaforo);
        usleep(500 * 1000);
    };
    return 0;
}
