#include "aventura3.h"

//CONFIGURACIÓN
int const NUMBER_OF_NODES = 10; 
int const NUMBER_OF_THREADS = 10;
int const N = 1000000;
int const SIZE_DE_LA_PILA = sizeof(int);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    //Declaraciones
    struct my_stack_node *node = NULL;
    int numberOfNodes = 0;
    struct my_stack *stack;

int main(int argc, char *argv[]) {
    
    //Declaraciones
    char *fileName = argv[1];

    if ((fileName == NULL) || (argv[2]!=NULL))  {
        imprime_error("Se debe pasar un solo parámetro con el nombre del fichero de pila.\nPrograma detenido.");
        return 0;
    }

//Se lee la pila del fichero pasado por parámetro.
    stack = my_stack_read(fileName);  

    if (!stack) {

        stack = my_stack_init(SIZE_DE_LA_PILA);

    }    

//Se contabilizan los nodos de la pila leída.     
    numberOfNodes = my_stack_len(stack);
    printf("Número de nodos: %d\n", numberOfNodes);

//En caso de que sea = -1 (pila NULL) le asignamos el valor 0 a numero de nodos. 
    if (numberOfNodes==-1) {
        numberOfNodes = 0;
    }

 printf("Número de nodos: %d\n", numberOfNodes);
    
    //Se crean los nodos hasta llegar a 10. 
         while (numberOfNodes<NUMBER_OF_NODES) {
            int *data = malloc(SIZE_DE_LA_PILA);
            *data = 0;
            my_stack_push(stack, data);
            numberOfNodes++;
         }

    numberOfNodes = my_stack_len(stack);
    printf("Número de nodos: %d\n", numberOfNodes);


    puts("Hilos");
    //Se crea el array de hilos. 
     pthread_t hilos[NUMBER_OF_THREADS];

    for (int i=0; i<NUMBER_OF_THREADS;i++) {

        pthread_create(&hilos[i], NULL, function, NULL);
    
    }

    //Se esperan todos los hilos.
    for (int i=0; i<NUMBER_OF_THREADS;i++)  {
    pthread_join(hilos[i], NULL);
    }
    //Se escribe la pila en el fichero.
    my_stack_write(stack, fileName);

    my_stack_purge(stack);
    return 1;

}

    void *function() {

        //Declaraciones
        int *value; 

        for (int i=0;i<N;i++) {
            pthread_mutex_lock(&mutex);
            value = my_stack_pop(stack);
            pthread_mutex_unlock(&mutex);
            *value = *value+1;
            pthread_mutex_lock(&mutex);
            my_stack_push(stack, value);
            pthread_mutex_unlock(&mutex);
        }

        pthread_exit(NULL);

    }