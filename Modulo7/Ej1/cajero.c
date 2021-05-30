#include "../../helpers/shared.h"
#include "ejConstants.h"

void procesar_evento(int id_cola_mensajes, mensaje msg)
{
    char cadena[100];
    static int cantidad = 0; //es inicializada solo una vez, mantiene el valor en las sucesivas llamadas.
    switch (msg.int_evento)
    {
    case EVT_RTA_SALDO:
        printf("Rta consulta saldo\n");
        imprimir_msg(msg);
        break;
    case EVT_RTA_SALDO_NOK:
        printf("Error consulta saldo!\n");
        imprimir_msg(msg);
        break;
    case EVT_RTA_DEPOSITO_OK:
        printf("Deposito ok!\n");
        imprimir_msg(msg);
        break;
    case EVT_RTA_DEPOSITO_NOK:
        printf("Error deposito saldo!\n");
        imprimir_msg(msg);
        break;
    default:
        printf("\nEvento sin definir\n");
        break;
    }
    printf("------------------------------\n");
}

int main()
{
    int id_cola_mensajes;
    mensaje msg;
    char cadena[CADENA_S];
    int client = 0;
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    while (1)
    {
        sprintf(cadena, "%d", client);
        printf("Consultando saldo para: %s \n", cadena);
        enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_DEPOSITO, cadena);
        recibir_mensaje(id_cola_mensajes, MSG_CAJERO, &msg);
        procesar_evento(id_cola_mensajes, msg);
        client++;
        usleep(TIEMPO_ESPERA_M * 1000);
    };

    borrar_cola(id_cola_mensajes);
    return 0;
}
