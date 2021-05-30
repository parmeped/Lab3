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
    case EVT_RTA_EXTRACCION_OK:
        printf("Extraccion ok!\n");
        imprimir_msg(msg);
        break;
    case EVT_RTA_EXTRACCION_NOK:
        printf("Error extraccion!\n");
        imprimir_msg(msg);
        break;
    default:
        printf("\nEvento sin definir\n");
        break;
    }
    printSeparator();
}

int main(int argc, char *argv[])
{
    int cajeroId = atoi(argv[1]);
    if (cajeroId < 1)
    {
        printf("Error, el Id del cajero debe ser mayor o igual a 1.");
        return 1;
    }

    int id_cola_mensajes;
    mensaje msg;
    char cadena[CADENA_S];
    int client = 0, respuesta, cliCode, amount;
    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    bool salir = false;

    while (!salir)
    {
        printf("Seleccione una operacion: [1] consulta, [2] deposito, [3] extraccion, [4] salir.\n");
        scanf("%d", &respuesta); // TODO: validar que la respuesta existe...

        if (respuesta == 1)
        {
            printf("Ingrese codigo de cliente..\n");
            scanf("%d", &cliCode);
            sprintf(cadena, "%d", cliCode);
            enviar_mensaje(id_cola_mensajes, MSG_BANCO, cajeroId, EVT_CONSULTA_SALDO, cadena);
        }
        else if (respuesta == 2)
        {
            printf("Ingrese codigo de cliente..\n");
            scanf("%d", &cliCode);
            printf("Ingrese monto a depositar..\n");
            scanf("%d", &amount);
            sprintf(cadena, "%d|%d", cliCode, amount);
            enviar_mensaje(id_cola_mensajes, MSG_BANCO, cajeroId, EVT_DEPOSITO, cadena);
        }
        else if (respuesta == 3)
        {
            printf("Ingrese codigo de cliente..\n");
            scanf("%d", &cliCode);
            printf("Ingrese monto a extraer..\n");
            scanf("%d", &amount);
            sprintf(cadena, "%d|%d", cliCode, amount);
            enviar_mensaje(id_cola_mensajes, MSG_BANCO, cajeroId, EVT_EXTRACCION, cadena);
        }
        else
        {
            salir = true;
            break;
        }
        recibir_mensaje(id_cola_mensajes, cajeroId, &msg);
        procesar_evento(id_cola_mensajes, msg);
        usleep(TIEMPO_ESPERA_M * 1000);
    };

    printf("Gracias, vuelvas prontos!");
    borrar_cola(id_cola_mensajes);
    return 0;
}
