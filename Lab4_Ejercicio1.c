#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t recurso1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t recurso2 = PTHREAD_MUTEX_INITIALIZER;

void *proceso1(void *arg) {
    while (1) {
        printf("Proceso 1 intentando adquirir recurso 1\n");
        pthread_mutex_lock(&recurso1);
        printf("Proceso 1 adquirió recurso 1\n");
        sleep(1);
        printf("Proceso 1 intentando adquirir recurso 2\n");
        pthread_mutex_lock(&recurso2);
        printf("Proceso 1 adquirió recurso 2\n");
        pthread_mutex_unlock(&recurso1);
        pthread_mutex_unlock(&recurso2);
    }
}


void *proceso2(void *arg) {
    while (1) {
        printf("Proceso 2 intentando adquirir recurso 2\n");
        pthread_mutex_lock(&recurso2);
        printf("Proceso 2 adquirió recurso 2\n");
        sleep(1);
        printf("Proceso 2 intentando adquirir recurso 1\n");
        pthread_mutex_lock(&recurso1);
        printf("Proceso 2 adquirió recurso 1\n");
        pthread_mutex_unlock(&recurso2);
        pthread_mutex_unlock(&recurso1);
    }
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, proceso1, NULL);
    pthread_create(&thread2, NULL, proceso2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}

