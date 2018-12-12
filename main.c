#include "aventura3.h"

//CONFIGURACIÓN
int const NUMERO_DE_NODOS = 10; 
void *VALOR_INICIALIZACION = 0;
int const SIZE_DE_LA_PILA = sizeof(int);



int main(int argc, char *argv[]) {

    //Declaraciones
    struct my_stack_node *node = NULL;
    struct my_stack *stack = my_stack_init(SIZE_DE_LA_PILA);
    int numberOfNodes = 0;
    char *fileName = argv[1];

    if (fileName == NULL) {
        imprime_error("Se debe pasar por parámetro el nombre del fichero de pila.\nPrograma detenido.");
        return 0;
    }

//Se lee la pila del fichero pasado por parámetro.
    stack = my_stack_read(fileName);      
//Se contabilizan los nodos de la pila leída.     
    numberOfNodes = my_stack_len(stack);

//En caso de que sea = -1 (pila NULL) le asignamos el valor 0 a numero de nodos. 
    if (numberOfNodes==-1) {
        numberOfNodes = 0;
    }

    //Se crean los nodos hasta llegar a 10. 
         while (numberOfNodes<NUMERO_DE_NODOS) {

             my_stack_push(stack, VALOR_INICIALIZACION);
             numberOfNodes++;

         }

    //Volcamos la pila en el fichero. 
     if ((my_stack_write(stack, fileName))==-1) {

         imprime_error("Error al guardar la pila en el fichero.");

     }

     //Liberamos la memoria utilizada por la pila
     my_stack_purge(stack);


    return 1;

}