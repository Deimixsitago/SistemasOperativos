#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

//Declarar Macros para crear vectores globales
#define N 5
//Estados
#define COMEN 0
#define HAMBRE 1
#define PIENSAN 2
#define DERECHA (fil_num + 4) % N
#define IZQUIERDA (fil_num + 1) % N

int Estado[N];
int phil[N] = {0, 1, 2, 3, 4};

sem_t semaforo;
sem_t S[N];

void Comer(int fil_num)
{
    //Come si los cubiertos están desocupados y tiene hambre
    if (Estado[fil_num] == HAMBRE && Estado[IZQUIERDA] != COMEN && Estado[DERECHA] != COMEN)
    {
        // Estado comen
        Estado[fil_num] = COMEN;

        sleep(2);

        printf("Filósofo %d toma cubiertos(%d, %d)\n",
               fil_num + 1, IZQUIERDA + 1, fil_num + 1);

        printf("Filósofo %d está comiendo...\n", fil_num + 1);

        sem_post(&S[fil_num]);
    }
}

void tomar_Cubiertos(int fil_num)
{

    sem_wait(&semaforo);

    // Estado Hambre
    Estado[fil_num] = HAMBRE;

    printf("Filósofo %d tiene hambre\n", fil_num + 1);

    // Come si sus vecinos no comen
    Comer(fil_num);

    sem_post(&semaforo);

    // Si no puede comer espera
    sem_wait(&S[fil_num]);

    sleep(1);
}

void DejarCubierto(int fil_num)
{

    sem_wait(&semaforo);

    // Estado Piensan
    Estado[fil_num] = PIENSAN;

    printf("Filósofo %d deja cubiertos(%d, %d)\n",
           fil_num + 1, IZQUIERDA + 1, fil_num + 1);
    printf("Filósofo %d está pensando...\n", fil_num + 1);

    //Vecinos comen si pueden
    Comer(IZQUIERDA);
    Comer(DERECHA);

    sem_post(&semaforo);
}

//Crear Filosofos
void *Filósofo(void *num)
{

    while (1)
    {

        int *i = num;

        sleep(1);

        tomar_Cubiertos(*i);

        sleep(0);

        DejarCubierto(*i);
    }
}

int main()
{

    int i;
    pthread_t hilo_Fil[N];

    // inicializar semáforo
    sem_init(&semaforo, 0, 1);

    for (i = 0; i < N; i++)

        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++)
    {

        // Crear hilos de Filósofo
        pthread_create(&hilo_Fil[i], NULL, Filósofo, &phil[i]);

        printf("Filosofo %d está pensando\n", i + 1);
    }

    for (i = 0; i < N; i++)

        pthread_join(hilo_Fil[i], NULL);
}