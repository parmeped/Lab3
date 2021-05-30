#include "banco_helpers.c"

void procesar_evento(int id_cola_mensajes, mensaje msg, cli *clients)
{
    char response[CADENA_M];
    static int cantidad = 0; //es inicializada solo una vez, mantiene el valor en las sucesivas llamadas.
    imprimir_msg(msg);
    cli cliente;

    switch (msg.int_evento)
    {
    case EVT_CONSULTA_SALDO:
        procesarConsultaSaldo(response, msg, clients, id_cola_mensajes);
        break;

    case EVT_DEPOSITO:
        procesarDeposito(response, msg, clients, id_cola_mensajes, 1);
        break;

    case EVT_EXTRACCION:
        procesarDeposito(response, msg, clients, id_cola_mensajes, 0);
        break;

    default:
        printf("\n Evento sin definir \n");
        usleep(TIEMPO_ESPERA_M * 1000);
        break;
    }
    printSeparator();
}

int main()
{
    int id_cola_mensajes, initialRandom = 0;
    mensaje msg;
    cli clients[CLIENT_AMOUNT];
    char name[CADENA_S];

    // fill clients
    for (int i = 0; i < CLIENT_AMOUNT; i++)
    {
        clients[i].cod_client = i + 1;
        sprintf(name, "%s%d", CLIENT_NAME_TEMPLATE, i + 1);
        strcpy(clients[i].name, name);
        clients[i].balance = randomNumberPrevSeed(MIN_BALANCE, MAX_BALANCE, initialRandom);
        initialRandom = clients[i].balance;
        printf("codCliente:%d nombreCliente:%s balance:%d \n", clients[i].cod_client, clients[i].name, clients[i].balance);
        usleep(TIEMPO_ESPERA_XS * 150);
    }
    printSeparator();

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    while (1)
    {
        recibir_mensaje(id_cola_mensajes, MSG_BANCO, &msg);
        procesar_evento(id_cola_mensajes, msg, clients);
    };

    borrar_cola(id_cola_mensajes);
    return 0;
}
