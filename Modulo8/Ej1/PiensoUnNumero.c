#include "../../helpers/shared.h"
#include "EjConstants.h"

pthread_mutex_t mutex;
bool g_acertaron = false;

void *ThreadJugadores(void *parametro)
{
    bool buscarNro = true;
    tjugador *datos_thread = (tjugador *)parametro;
    int nro_jugador = datos_thread->nro_jugador;
    int nro_a_adivinar = datos_thread->nro_a_adivinar;
    int cantidad_intentos = datos_thread->cantidad_intentos;
    int nro_pensado = 0;

    int tiempoEspera = randomNumber(TIEMPO_MIN, TIEMPO_MAX);

    int array[MAX_RANDOM + 1];

    // Inicializo todos los valores del array en 0. (No utilizado aun). La pos 0 queda sin utilizar.
    for (int i = 1; i < MAX_RANDOM + 1; i++)
    {
        array[i] = 0;
    }

    while (!g_acertaron)
    {
        pthread_mutex_lock(&mutex);
        printf("\nSoy el jugador %d\n", nro_jugador + 1);

        while (buscarNro)
        {
            nro_pensado = randomNumberPrevSeed(MIN_RANDOM, MAX_RANDOM, tiempoEspera);
            printf("Intentando con %d... \n", nro_pensado);
            if (array[nro_pensado] == 0)
            {
                array[nro_pensado] = nro_pensado;
                buscarNro = false;
            }
            else
            {
                printf("(Jugador %d)Numero ya usado! Buscando otro... \n", nro_jugador + 1);
                usleep(TIEMPO_ESPERA_XS * 1000);
            }
        }
        buscarNro = true;
        cantidad_intentos++;
        printf("Intentos=%d \n", cantidad_intentos);
        if (nro_pensado == nro_a_adivinar) {
            printf("Acerte! Jugador: %d \n", nro_jugador + 1);
            datos_thread->ganador = 1;
            g_acertaron = true;
        }
        pthread_mutex_unlock(&mutex);

        usleep(tiempoEspera * 1000);
    };

    datos_thread->cantidad_intentos = cantidad_intentos;
    pthread_exit((void *)"Listo");
}

int main(int argc, char *argv[])
{
    int cantJugadores = atoi(argv[1]);
    if (cantJugadores < 1)
    {
        printf("Error, la cantidad de jugadores debe ser mayor o igual a 1.\n");
        return 1;
    }

    printf("Cantidad de jugadores ingresada: %d \n", cantJugadores);
    int numeroPensado = randomNumberPrevSeed(MIN_RANDOM, MAX_RANDOM, 1);
    printf("Numero a acertar: %d \n", numeroPensado);

    tjugador *datos_thread;

    // Thread initiation.
    pthread_t *idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantJugadores);
    pthread_attr_t atributos;
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    pthread_mutex_init(&mutex, NULL);

    datos_thread = (tjugador *)malloc(sizeof(tjugador) * cantJugadores);

    for (int i = 0; i < cantJugadores; i++)
    {
        datos_thread[i].nro_jugador = i;
        datos_thread[i].cantidad_intentos = 0;
        datos_thread[i].nro_a_adivinar = numeroPensado;
        pthread_create(&idHilo[i], &atributos, ThreadJugadores, &datos_thread[i]);
        usleep(TIEMPO_ESPERA_M * 1000);
    }

    while (!g_acertaron)
    {
        // No necesario, para mostrar que main sigue.
        // pthread_mutex_lock(&mutex);
        // printf("Proceso main esperando \n");
        // pthread_mutex_unlock(&mutex);
        usleep(TIEMPO_ESPERA_M * 1000);
    };

    for (int i = 0; i < cantJugadores; i++)
    {
        pthread_join(idHilo[i], NULL);
        printf("TERMINO\n");
        printf("PPAL: Jugador %d: %d intentos. Ganador? %d \n", i + 1, datos_thread[i].cantidad_intentos, datos_thread[i].ganador);
    }

    return 0;
}
