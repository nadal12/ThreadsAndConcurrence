#include <fcntl.h>     /* Modos de apertura de función open()*/
#include <stdlib.h>    /* Funciones malloc(), free(), y valor NULL */
#include <sys/stat.h>  /* Permisos función open() */
#include <sys/types.h> /* Definiciones de tipos de datos como size_t*/
#include <unistd.h>    /* Funciones read(), write(), close()*/

/*
    ESTRUCTURAS DE DATOS DE LA AVENTRA
*/
struct my_stack_node {
    void *data;
    struct my_stack_node *next;
};

struct my_stack {
    int size;
    struct my_stack_node *first;
};