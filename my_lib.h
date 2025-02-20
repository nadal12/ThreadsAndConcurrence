/*
Aventura 3
Asignatura: Sistemas Operativos.
Grupo: Los tres mosqueteros.
Participantes: 
                + Eugenio Doñaque
                + Nadal Llabrés
                + Alvaro Pons
*/
#include <fcntl.h>     /* Modos de apertura de función open()*/
#include <stdlib.h>    /* Funciones malloc(), free(), y valor NULL */
#include <sys/stat.h>  /* Permisos función open() */
#include <sys/types.h> /* Definiciones de tipos de datos como size_t*/
#include <unistd.h>    /* Funciones read(), write(), close()*/
#include <stdio.h>  
#include <errno.h>
#include <string.h>

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

/*******************************************************************************
 *                        FUNCIONALIDADES DE LA PILA
*******************************************************************************/

struct my_stack *my_stack_init(int size);
int my_stack_push(struct my_stack *stack, void *data);
void *my_stack_pop(struct my_stack *stack);
int my_stack_len(struct my_stack *stack);
struct my_stack *my_stack_read(char *filename);
int my_stack_write(struct my_stack *stack, char *filename);
int my_stack_purge(struct my_stack *stack);

/*******************************************************************************
 *                        FUNCIONALIDADES PARA PROGRAMA
*******************************************************************************/
void *popAddPush(void *parametro);

/******************************************************************************
                             FUNCIONES DE APOYO
******************************************************************************/
void imprime_error(char *mensaje_error);