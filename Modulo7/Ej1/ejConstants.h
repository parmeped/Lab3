#define INTERVALO_PEDIDOS 2000
#define CLIENT_AMOUNT 20 // TODO: pasar a 100 luego
#define CLIENT_NAME_TEMPLATE "NombreCliente"
#define MIN_BALANCE 10
#define MAX_BALANCE 10000

#define CODE_SEPARATOR ";"

#define ERROR_CLI_NOT_FOUND "El cliente solicitado no existe."
#define ERROR_AMOUNT_LOWER_ZERO "El monto no puede ser menor o igual a 0."
#define ERROR_INSUFFICIENT_BALANCE "No hay saldo suficiente para realizar la operacion."

// Eventos
typedef enum
{
    EVT_NINGUNO,
    EVT_CONSULTA_SALDO,
    EVT_DEPOSITO,
    EVT_EXTRACCION,
    EVT_RTA_SALDO,
    EVT_RTA_SALDO_NOK,
    EVT_RTA_DEPOSITO_OK,
    EVT_RTA_DEPOSITO_NOK,
    EVT_RTA_EXTRACCION_OK,
    EVT_RTA_EXTRACCION_NOK
} Eventos;

// Destino mensaje
typedef enum
{
    MSG_NADIE,
    MSG_BANCO,
    MSG_CAJERO,
    MSG_CLIENTE
} Destinos;

typedef struct cliente cli;
struct cliente
{
    int cod_client;
    int balance; // int para simplificar
    char name[CADENA_S];
};