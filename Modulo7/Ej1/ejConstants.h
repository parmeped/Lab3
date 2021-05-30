#define INTERVALO_PEDIDOS 2000
#define CLIENT_AMOUNT 100
#define CLIENT_NAME_TEMPLATE "NombreCliente"
#define MIN_BALANCE 10
#define MAX_BALANCE 10000

#define CODE_SEPARATOR = ";"
#define CODE_CLI_ID "[ClientCode]:"
#define CODE_BALANCE "[Balance]:"
#define CODE_AMOUNT "[Amount]:"
#define CODE_ERROR "[Error]:"


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