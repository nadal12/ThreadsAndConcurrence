#include "my_lib.h"

/*******************************************************************************
 *                        FUNCIONALIDADES DE LA PILA
*******************************************************************************/
/*
    Crea instancias de estructuras my_stack en la memoria y devuelve un
    puntero al stack.

    Parametros:
        +size: Entero que representa el tamaño de los datos a ser guardados
               en el stack.
    Devuelve:
        +NULL: En caso de error.
        +stack: Puntero al stack recien instanciado.
*/
struct my_stack *my_stack_init (int size){
    
    struct my_stack_node *node = NULL;
    struct my_stack *stack = malloc(sizeof(size)+sizeof(node));
    if (stack == NULL) return NULL; //Comprobación de errores

    stack->size = size;
    stack->first = node;
    return stack;
}

/*
    Metodo para agregar nuevos nodos al stack.
    Parametros:
        +stack: Puntero al my_stack donde añadir data.
        +data: Puntero al dato a añadir al stack.
    Devuelve:
        +(-1): En caso de error.
        +0: Si operacion ha sido exitosa.
*/
int my_stack_push(struct my_stack *stack, void *data) {

    //Check si el stack existe y si el tamaño de los datos es mayor a 0:
    if (stack == NULL || stack -> size <= 0) return -1;

    //Reservar espacio para estructura my_stack_node:
    struct my_stack_node *node = malloc(sizeof(struct my_stack_node));
    if (node == NULL) return -1; //Comprobar por errores de Malloc.

    //Asignar dato y dirección del siguiente nodo:
    node->data = data;
    node->next = stack->first;
    
    //Actualizar dirección del primer nodo del stack:
    stack->first = node;
    
    return 0;
}


/*
    Metodo que retira el último dato en entrar al stack.
    Parametros:
        +stack: Puntero al stack de donde recuperar el dato.
    Devuelve: 
        +Puntero al dato obtenido del stack.
*/
void *my_stack_pop(struct my_stack *stack) {

    //Declarations
    struct my_stack_node *oldFirst = NULL;
    void *data;

    //Check if the stack is empty.
    if (stack->first == NULL) return NULL;
    
    //Save node data into variable. 
    data = stack->first->data;
    
    //Save the old "first" value.
    oldFirst = stack->first;
    stack->first = stack->first->next;

    //Free the unused space.
    free(oldFirst);

    return data;
}


/*
    Recorre la pila y retorna el número de nodos totales que hay en la pila.
    Parametros:
        +stack: Puntero al stack del cual contar nodos.
    Devuelve:
        +(-1): En caso de error
        +contador: Valor entero del número de nodos existentes en el stack.
                   >= 0
*/
int my_stack_len(struct my_stack *stack) {

    //Check si stack existe
    if (stack == NULL) return -1;

    //Declaraciones
    int contador = 0;
    struct my_stack_node *crnt;
    
    //Asignacion del nodo actual
    crnt = stack->first;

    while (crnt != NULL){
        contador++;
        crnt = crnt->next;
    }
    
    return contador;
}


/*
    my_stack_read
    Metodo que recupera desde un fichero la informacion volcada de una pila.
    El primer dato en ser leido representa el tamaño de los datos de la pila.

    Parametros:
        +filename: Puntero a la cadena de caracteres que contiene la 
                   direccion del fichero a ser leido.
    +Devuelve: 
        +stack: Puntero al stack generado.
        +NULL: Si ocurre algún error.
    
*/
struct my_stack *my_stack_read(char *filename) {

    //Declaraciones
    int file;
    int rd;

    //Declaraciones para tratar con datos de la pila
    int *size;
    int sizeofint = sizeof(int);
    struct my_stack *stack;
    void *data;

    //Check si la direccion del fichero es válida:
    file = open(filename, O_RDONLY);
    if (file == -1) return NULL;     //Comprobación de errores

    /*
        Lectura de la pila desde fichero
    */

    //Recuperacion del tamaño de los datos:
    size = malloc(sizeof(int));
    if (size == NULL) return NULL; //Comprobación de errores

    rd = read(file, size, sizeofint);
    if (rd != sizeofint) return NULL;   //Comprobación de errores

    //Instanciacion de estructura my_stack
    stack = my_stack_init(*size);
    if (stack == NULL) return NULL;    //Comprobación de errores

    //Recuperacion de datos desde el fichero.
    data = malloc(stack->size);
    if (data == NULL) return NULL; //Comprobación de errores

    rd = read(file, data, stack->size);
    if (rd == -1) {    //Comprobación de errores
        return NULL;
    }

    //Bucle de recuperacion
    while (rd > 0) {
        if (rd != stack->size) return NULL;    //Comprobación de errores

        int push = my_stack_push(stack, data);
        if (push == -1) return NULL; //Comprobación de errores
        

        data = malloc(stack->size);
        if (data == NULL) return NULL; //Comprobación de errores

        rd = read(file, data, stack->size);
        if (rd == -1) return NULL;   //Comprobación de errores

    }

    close(file);

    return stack;
}


/*
    Metodo que vuelca todos los datos de una pila en un fichero.
    Parametros:
        +stack: La pila a ser volcada.
        +filename: Puntero al String que contiene la ruta del archivo.
    Devuelve: 
        +(-1): En caso de errores
        +counter: Contador de la cantidad de nodos escritos
    
*/
int my_stack_write(struct my_stack *stack, char *filename) {

    //Comprobación inicial de la pila. 
    if (stack == NULL) return -1;
    
    //Declaraciones
    struct my_stack *aux_stack = my_stack_init(stack->size); 
    int counter = 0; //Para contar el número de datos escritos en el fichero. 
    int writtenBytes; 

    //Comprobación de la funcion "my_stack_init". 
    if (aux_stack==NULL) return -1;

    struct my_stack_node *aux_node = NULL;  

    //Índice para recorrer la pila principal. 
    struct my_stack_node *index = stack->first; 
    aux_stack-> size = stack->size;
    

    //Copia de la pila principal a la pila auxiliar. 
    while (index!=NULL) {
    
        //Reserva de memoria para un nuevo nodo. 
        aux_node = malloc(stack->size);
        
        //Comprobación de la instrucción "malloc". 
        if (aux_node == NULL) return -1;
        
        aux_node->next = aux_stack->first;         
        aux_stack->first = aux_node; 
        aux_node->data = index->data; 

        //Actualizar valor de "index".       
        index = index->next;
    
    }

    //Abrir fichero. 
    mode_t mode = S_IRUSR | S_IWUSR;
    int file = open(filename, O_CREAT | O_WRONLY | O_TRUNC , mode); 
    
    //Comprobación del fichero abierto. 
    if (file==-1) return -1;

    writtenBytes = write(file, &(stack->size), sizeof(int));

    //Proceso de escritura al fichero. 
    while (aux_stack->first != NULL) {

        writtenBytes = write(file, my_stack_pop(aux_stack), stack->size);

        //Comprobación de la función "write". 
        if ((writtenBytes == -1) || (writtenBytes != stack->size)) return -1;

        counter++;
    }

    close(file);
    return counter;
}


/*
    Metodo que libera la memoria utilizada por la pila y sus nodos.
    Parametros:
        +stack: Stack del cual liberar.
    Devuelve:
        +(-1): En caso de error.
        +counter: Número de nodos borrados del stack.
*/
int my_stack_purge(struct my_stack *stack) {

    //Declarations
    struct my_stack_node *oldFirst = NULL; 
    int counter = 0;

    //Recorrido de la pila
    while (stack->first!=NULL)  {

        // Save the "first" value. 
        oldFirst = stack->first; 

        //Change the "first" value.
        stack->first = stack->first->next; 
        
        //Free the unused space. 
        free(oldFirst); 
        counter++; 

    }

    free(stack);

    //Return the number of deleted nodes. 
    return counter;
}

/******************************************************************************
                             FUNCIONES DE APOYO
******************************************************************************/
/**
 * Metodo que imprime a través de la salida estandar de errores un mensaje
 * indicando:
 *      Número de error (errno): mensaje de error.
 * En caso de que el parámetro mensaje_error == NULL, mensaje de error será el
 * String devuelto por strerror(errno) -el error correspondiente a errno.
 * 
 * En caso contrario, se imprime el mensaje_error recibido.
 * 
 * Parámetros:
 *          +mensaje_error: String con el mensaje de error correspondiente.
 * 
 * Return: void method. Returns nothing.
 */
void imprime_error(char *mensaje_error) {
    if (mensaje_error == NULL) {
        fprintf(stderr, "Error %d: %s\n", errno, strerror(errno));
    
    } else {
        fprintf(stderr, "%s\n", mensaje_error);
    }
}
