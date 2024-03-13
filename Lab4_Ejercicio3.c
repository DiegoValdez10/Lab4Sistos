#include <stdio.h>
#include <stdbool.h>

#define NUM_RESOURCES 3
#define NUM_PROCESSES 5

int available[NUM_RESOURCES];
int max_resources[NUM_PROCESSES][NUM_RESOURCES];
int allocation[NUM_PROCESSES][NUM_RESOURCES];
int need[NUM_PROCESSES][NUM_RESOURCES];
bool finish[NUM_PROCESSES];

bool is_safe_state() {
    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        work[i] = available[i];
    }

    bool finish[NUM_PROCESSES] = {false};

    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < NUM_RESOURCES; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    ++count;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; 
        }
    }
    return true; 
}

bool request_resources(int process, int request[]) {
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false; 
        }
    }

    for (int i = 0; i < NUM_RESOURCES; ++i) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (!is_safe_state()) {
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false; 
    }

    return true; 
}

void release_resources(int process, int release[]) {
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        available[i] += release[i];
        allocation[process][i] -= release[i];
        need[process][i] += release[i];
    }
}

void simulate_processes() {
    printf("Ingresa los recursos disponibles: ");
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        scanf("%d", &available[i]);
    }


    printf("Ingresa el maximo de recursos para un proceso:\n");
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        printf("Process %d: ", i);
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            scanf("%d", &max_resources[i][j]);
        }
    }


    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            allocation[i][j] = 0;
            need[i][j] = max_resources[i][j];
        }
    }

    while (true) {
        int process;
        printf("Ingrasa el proceso (0-%d) o -1 para salir: ", NUM_PROCESSES - 1);
        scanf("%d", &process);
        if (process == -1) {
            break;
        }
        
        int request[NUM_RESOURCES];
        printf("Ingresa el pedido de recursos para el proceso %d: ", process);
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            scanf("%d", &request[i]);
        }

        if (request_resources(process, request)) {
            printf("Recursos puestos correctamente.\n");
        } else {
            printf("No se ha podido colocar el recurso\n");
        }

        printf("Recursos disponibles: ");
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            printf("%d ", available[i]);
        }
        printf("\n\n");
    }
}

int main() {
    simulate_processes();
    return 0;
}

