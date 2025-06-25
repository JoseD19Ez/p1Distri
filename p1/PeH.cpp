#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//Trabaja en un hilo
void* contador(void* arg) {
    for (int i = 1; i <= 10; i++) {
        printf("Contador: %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t hilo;

    //Creamos el hilo
    if (pthread_create(&hilo, NULL, contador, NULL) != 0) {
        perror("Error al crear el hilo");
        return 1;
    }

    //Ejecutamos el ping
    printf("Iniciando ping: ping\n");
    FILE* salida = popen("ping -n 5 google.com", "r");

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), salida) != NULL) {
        printf("[PING] %s", buffer);
    }

    pclose(salida); //Cierre del proceso
    printf("Proceso terminado.\n");

    //Esperando el hilo
    // hilo = false;
    pthread_join(hilo, NULL);

    return 0;
}
