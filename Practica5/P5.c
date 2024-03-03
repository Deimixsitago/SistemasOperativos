#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#define THREAD_NUM 20

void *fibonacci(void *args)
{
    char *msg = (char *)args;
    int a = 1, b = 1, i, e = 1;
    for (i = 0; i != 25; i++)
    {
        printf("%s fib(%d) = %d\n", msg, e, a);
        //usleep(10000);
        sleep(1);
        a = a + b;
        e++;
        printf("%s fib(%d) = %d\n", msg, e, b);
        //usleep(10000);
        sleep(1);
        b = a + b;
        e++;
    }
}
void *potencia(void *args)
{
    char *msg = (char *)args;
    int pot, i = 0;
    for (i = 0; i != 50; i++)
    {
        pot = (int)pow(2, i);
        printf("%s pot(%d) = %d\n", msg, i + 1, pot);
        //usleep(10000);
        sleep(1);
    }
}
void *acumulada(void *args)
{
    char *msg = (char *)args;
    int i, acu = 0;
    for (i = 0; i != 50; i++)
    {
        acu += i;
        printf("%s acu(%d) = %d\n", msg, i + 1, acu);
        //usleep(10000);
        sleep(1);
    }
}
void *multiplicacion(void *args)
{
    char *msg = (char *)args;
    int i, acu = 1;
    for (i = 1; i != 51; i++)
    {
        acu *= i;
        printf("%s prod(%d) = %d\n", msg, i, acu);
        //usleep(10000);
        sleep(1);
    }
}
int main()
{
        printf("\nPID = [%d]\n", getpid());
    char *msg1 = "Hilo Acumulada [0]", *msg2 = "Hilo Multiplicación [1]", *msg3 = "Hilo Potencia [2]", *msg4 = "Hilo Fibonacci [3]";
    int ret1, ret2, ret3, ret4;
    pthread_t acumu, mult, pot, fib;
    ret1 = pthread_create(&acumu, NULL, acumulada, (void *)msg1);
    ret2 = pthread_create(&mult, NULL, multiplicacion, (void *)msg2);
    ret3 = pthread_create(&pot, NULL, potencia, (void *)msg3);
    ret4 = pthread_create(&fib, NULL, fibonacci, (void *)msg4);

    pthread_join(acumu, NULL);
    pthread_join(mult, NULL);
    pthread_join(pot, NULL);
    pthread_join(fib, NULL);

    printf("Hilo acumulativo ret1 = %d\n", ret1);
    printf("Hilo Multiplicativo ret2 = %d\n", ret2);
    printf("Hilo Potenciador ret3 = %d\n", ret3);
    printf("Hilo Fibonacci ret4 = %d\n", ret4);

}