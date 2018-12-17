#include <stdio.h>
#include <limits.h>
#include "aventura3.h"

#define MAX_ITERATIONS 10

int main(int argc, char *argv[]) {

    //Declaraciones
    struct my_stack *stack;
    int *data, stack_size;
    int it = 0;
    int max = 0, min = INT_MAX, acum = 0, prom;

    if (!argv[1]) {
        imprime_error("Se debe pasar por parámetro el nombre del fichero de pila.\nPrograma detenido.");
        return 0;
    }

    //Generar pila
    stack = my_stack_read(argv[1]);

    if (!stack) { //Comprobar por errores
        imprime_error("Error generando pila desde el fichero especificado.");
        return 0;
    }

    //Obtener tamaño de la pila
    stack_size = my_stack_len(stack);
    if (stack_size == -1) {
        imprime_error("Error en lectura desde fichero.");
        return 0;
    }
    
    //Impresión por pantalla del número de elementos
    printf("Tamaño del stack: %d\n",stack_size);
    while(stack->first && it < MAX_ITERATIONS) {
        data = (int *) my_stack_pop(stack);

        printf("data: %d\n", *data);
        
        acum += *data; //Calcular sumatorio
        
        if (*data < min) min = *data; //Calcular minimo
        if (*data > max) max = *data; //Calcular maximo

        it++;
    }

    prom = acum/stack_size;

    printf("Items: %d | Suma: %d | Min: %d | Max: %d | Promedio: %d\n", stack_size, acum, min, max, prom);
}