#include "../../helpers/shared.h"
#include "ejConstants.h"

cli findClient(int clientCode, cli *client)
{
    cli cliente = {.cod_client = -1};
    if (clientCode < 1 || clientCode > CLIENT_AMOUNT - 1)
    {
        return cliente;
    }

    return client[clientCode - 1];
}



void procesar_evento(int id_cola_mensajes, mensaje msg, cli *clients)
{
    char response[100];
    static int cantidad = 0; //es inicializada solo una vez, mantiene el valor en las sucesivas llamadas.
    printf("Destino   %d\n", (int)msg.long_dest);
    printf("Remitente %d\n", msg.int_rte);
    printf("Evento    %d\n", msg.int_evento);
    printf("Mensaje   %s\n", msg.char_mensaje);
    switch (msg.int_evento)
    {
    case EVT_CONSULTA_SALDO:
        printf("Consulta Saldo\n");
        cli cliente = findClient(atoi(msg.char_mensaje), clients);

        if (cliente.cod_client == -1) {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_CAJERO, EVT_RTA_SALDO_NOK, "El cliente solicitado no existe.");
            break;    
        }

        sprintf(response, "El saldo del cliente %s (id:%d), es:%d", cliente.name, cliente.cod_client, cliente.balance);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_CAJERO, EVT_RTA_SALDO, response);
        break;
    
    case EVT_DEPOSITO:
        printf("Depositando...");
        int index = strchr(msg.char_mensaje, CODE_CLI_ID);
        int separator = strchr(msg.char_mensaje, CODE_SEPARATOR);


        // o si saldo a depositar es < 1
        if (cliente.cod_client == -1) {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_CAJERO, EVT_RTA_DEPOSITO_NOK, "El cliente solicitado no existe.");
            break;    
        }

        clients[atoi(msg.char_mensaje)].balance += 0; // el deposito
        sprintf(response, "Deposito de cliente %s (id:%d), realizado con exito. Saldo: %d", cliente.name, cliente.cod_client, cliente.balance);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_CAJERO, EVT_RTA_DEPOSITO_OK, response);
        break;

    default:
        printf("\n Evento sin definir \n");
        break;
    }
    printf("------------------------------\n");
}

int main()
{
    int id_cola_mensajes, initialRandom = 0;
    mensaje msg;
    cli clients[CLIENT_AMOUNT];

    // fill clients
    for (int i = 0; i < CLIENT_AMOUNT; i++)
    {
        clients[i].cod_client = i + 1;
        strcpy(clients[i].name, CLIENT_NAME_TEMPLATE); // TODO: add clientId to name.
        clients[i].balance = randomNumberPrevSeed(MIN_BALANCE, MAX_BALANCE, initialRandom);
        initialRandom = clients[i].balance;
        printf("codCliente:%d nombreCliente:%s balance:%d \n", clients[i].cod_client, clients[i].name, clients[i].balance);
        usleep(TIEMPO_ESPERA_XS * 300);
    }

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    while (1)
    {
        recibir_mensaje(id_cola_mensajes, MSG_BANCO, &msg);
        procesar_evento(id_cola_mensajes, msg, clients);
    };

    borrar_cola(id_cola_mensajes);
    return 0;
}
