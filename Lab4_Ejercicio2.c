#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_FILOSOFOS 5

sem_t tenedores[NUM_FILOSOFOS];
sem_t mutex;

void *filosofo(void *arg) {
    int id = *((int *)arg);
    int tenedor_izq = id;
    int tenedor_der = (id + 1) % NUM_FILOSOFOS;

    while (1) {
        printf("Filósofo %d pensando...\n", id);

        sem_wait(&mutex);
        sem_wait(&tenedores[tenedor_izq]);
        sem_wait(&tenedores[tenedor_der]);
        sem_post(&mutex);

        printf("Filósofo %d comiendo...\n", id);
        sleep(rand() % 3); 

        sem_post(&tenedores[tenedor_izq]);
        sem_post(&tenedores[tenedor_der]);
    }
}

int main() {
    pthread_t filosofos[NUM_FILOSOFOS];
    int ids[NUM_FILOSOFOS];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_FILOSOFOS; i++)
        sem_init(&tenedores[i], 0, 1);

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }


    for (int i = 0; i < NUM_FILOSOFOS; i++)
        pthread_join(filosofos[i], NULL);

    sem_destroy(&mutex);
    for (int i = 0; i < NUM_FILOSOFOS; i++)
        sem_destroy(&tenedores[i]);

    return 0;
}

