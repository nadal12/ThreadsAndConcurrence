/*
Aventura 3
Asignatura: Sistemas Operativos.
Grupo: Los tres mosqueteros.
Participantes: 
                + Eugenio Doñaque
                + Nadal Llabrés
                + Alvaro Pons
*/

#include <pthread.h>   /* Funcionalidades de threads*/
#include "my_lib.h"

//CONFIGURACIÓN
#define NUM_HILOS 10
#define NUMERO_DE_NODOS 10
#define SIZE_DE_LA_PILA sizeof(int)
#define N 1000000

int thread_counter = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {

    //Declaraciones
    struct my_stack *stack;
    int numberOfNodes = 0;
    char *fileName = argv[1];
    pthread_t threads[NUM_HILOS];

    if (fileName == NULL) {
        imprime_error("Se debe pasar por parámetro el nombre del fichero de pila.\nPrograma detenido.");
        return 0;
    }

    //Se lee la pila del fichero pasado por parámetro.
    stack = my_stack_read(fileName);

    //Check por errores leyendo desde fichero
    if (!stack) {
        /*En caso de haber error leyendo desde fichero*/

        puts("Fichero inexistente.\nGenerando pila.");

        stack = my_stack_init(SIZE_DE_LA_PILA);

        for (int i = 0;i<NUMERO_DE_NODOS;i++) {

            int *initval = malloc(SIZE_DE_LA_PILA);
            *initval = 0;

            my_stack_push(stack, initval);
        }

    } else {
        /*En caso contrario, si faltan elementos en la pila, añadir restantes*/

        //Se contabilizan los nodos de la pila leída.     
        numberOfNodes = my_stack_len(stack);

        //Se crean los nodos hasta llegar a 10. 
        while (numberOfNodes<NUMERO_DE_NODOS) {
            int *initval = malloc(SIZE_DE_LA_PILA);
            *initval = 0;

            my_stack_push(stack, initval);
            numberOfNodes++;
        }
    }

    //Stack lista para ser utilizada. Creación de hilos:
    printf("Número de hilos: %d\nNúmero de iteraciones: %d\n", NUM_HILOS, N);

    //Creación de los 10 hilos que se ejecutaran concurrentemente.
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_create(&threads[i], NULL, popAddPush, stack);
    }
    //Esperar por la ejecución de los diez hilos.
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(threads[i], NULL);
    }

    puts("Hilos terminados.. Guardando fichero en disco.");
    //Volcamos la pila en el fichero. 
    
    if ((my_stack_write(stack, fileName))==-1) {
        imprime_error("Error al guardar la pila en el fichero.");
    }


    //Liberamos la memoria utilizada por la pila
    my_stack_purge(stack);

    puts("Completado.\nCerrando programa.");
    
    return 1;

}

void *popAddPush(void *parametro) {

    struct my_stack *stack = (struct my_stack*)parametro;

        pthread_mutex_lock(&mutex);
        printf("Comenzando hilo %d\n", thread_counter);
        thread_counter++;
        pthread_mutex_unlock(&mutex);

    for (int i = 0; i < N; i++) {
        /*Sección crítica para el pop*/
        pthread_mutex_lock(&mutex);
        int *pvalue = (int *) my_stack_pop(stack);
        pthread_mutex_unlock(&mutex);

        (*pvalue)++;

        /*Sección crítica para el push*/
        pthread_mutex_lock(&mutex);
        my_stack_push(stack, pvalue);
        pthread_mutex_unlock(&mutex);
    }

    return 0;
}