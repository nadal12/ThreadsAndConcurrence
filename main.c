#include "aventura3.h"

//CONFIGURACIÓN
int const NUMBER_OF_NODES = 10; 
int const NUMBER_OF_THREADS = 10;
int const N = 1000;
int const SIZE_DE_LA_PILA = sizeof(int);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


struct my_data {
   int val;
   char name[8];
};

struct my_data *data1;



int main(int argc, char *argv[]) {

    //Declaraciones
    struct my_stack_node *node = NULL;
    struct my_stack *stack = my_stack_init(SIZE_DE_LA_PILA);
    int numberOfNodes = 0;
    char *fileName = argv[1];

    if ((fileName == NULL) || (argv[2]!=NULL))  {
        imprime_error("Se debe pasar un solo parámetro con el nombre del fichero de pila.\nPrograma detenido.");
        return 0;
    }

//Se lee la pila del fichero pasado por parámetro.
    stack = my_stack_read(fileName);      
//Se contabilizan los nodos de la pila leída.     
    numberOfNodes = my_stack_len(stack);
    printf("Número de nodos: %d\n", numberOfNodes);
//En caso de que sea = -1 (pila NULL) le asignamos el valor 0 a numero de nodos. 
    if (numberOfNodes==-1) {
        numberOfNodes = 0;
    }

    //Se crean los nodos hasta llegar a 10. 
         while (numberOfNodes<NUMBER_OF_NODES) {
            data1 = malloc(sizeof(struct my_data));
            data1->val=0;
             my_stack_push(stack, data1);
             numberOfNodes++;

         }

    numberOfNodes = my_stack_len(stack);
        printf("Número de nodos: %d\n", numberOfNodes);

    //Volcamos la pila en el fichero. 
     if ((my_stack_write(stack, fileName))==-1) {

         imprime_error("Error al guardar la pila en el fichero.");

     }

     //Liberamos la memoria utilizada por la pila.
     my_stack_purge(stack);

    //Se crea el array de hilos. 
     pthread_t hilos[NUMBER_OF_THREADS];

    for (int i=0; i<NUMBER_OF_THREADS;i++) {

        pthread_create(hilos[i], NULL, function, NULL);
    
    }



    return 1;

}

    void *function() {

        for (int i=0;i<N;i++) {

            my_stack_pop();
            
            my_stack_push();

        }

    }