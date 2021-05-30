#include "../../helpers/shared.h"
#include "ejConstants.h"

cli findClient(int clientCode, cli *client)
{
    cli cliente = {.cod_client = -1};
    if (clientCode < 1 || clientCode > CLIENT_AMOUNT)
    {
        return cliente;
    }

    return client[clientCode - 1];
}

void procesarConsultaSaldo(char *response, mensaje msg, cli *clients, int id_cola_mensajes)
{
    printf("Consulta Saldo\n");
    cli cliente = findClient(atoi(msg.char_mensaje), clients);

    if (cliente.cod_client == -1)
    {
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_SALDO_NOK, ERROR_CLI_NOT_FOUND);
        return;
    }

    sprintf(response, "El saldo del cliente %s (id:%d), es:%d", cliente.name, cliente.cod_client, cliente.balance);
    enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_SALDO, response);
}

void procesarDeposito(char *response, mensaje msg, cli *clients, int id_cola_mensajes, bool deposito)
{
    printf("Deposito u extraccion\n");
    char *e;
    e = strchr(msg.char_mensaje, '|');
    int index = (int)(e - msg.char_mensaje);

    substring(response, msg.char_mensaje, 0, index);
    int cliCode = atoi(response);

    substring(response, msg.char_mensaje, index + 1, strlen(msg.char_mensaje));
    int amount = atoi(response);
    cli cliente = findClient(cliCode, clients);

    if (cliente.cod_client == -1)
    {
        if (deposito)
        {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_DEPOSITO_NOK, ERROR_CLI_NOT_FOUND);
        }
        else
        {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_NOK, ERROR_CLI_NOT_FOUND);
        }
        return;
    }
    if (amount <= 0)
    {
        if (deposito)
        {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_DEPOSITO_NOK, ERROR_AMOUNT_LOWER_ZERO);
        }
        else
        {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_NOK, ERROR_AMOUNT_LOWER_ZERO);
        }
        return;
    }

    cliCode--;
    if (!deposito)
    {
        if ((clients[cliCode].balance - amount) < 0)
        {
            enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_NOK, ERROR_INSUFFICIENT_BALANCE);
            return;
        }
    }

    if (deposito)
    {
        clients[cliCode].balance += amount;
        sprintf(response, "Deposito de cliente %s (id:%d), realizado con exito. Saldo: %d", clients[cliCode].name, cliCode + 1, clients[cliCode].balance);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_DEPOSITO_OK, response);
    }
    else
    {
        clients[cliCode].balance -= amount;
        sprintf(response, "Extraccion de cliente %s (id:%d), realizada con exito. Saldo: %d", clients[cliCode].name, cliCode + 1, clients[cliCode].balance);
        enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_OK, response);
    }
    return;
}
