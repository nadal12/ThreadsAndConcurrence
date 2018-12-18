#include "aventura3.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

    //Declaraciones
    int total = 0;
    int max = 0;
    int min = 99999999;
    int *value;
    int media; 
    struct my_stack *stack;
    stack = my_stack_read(argv[1]);

    for (int i=0;i<10;i++) {
    
        if (my_stack_len(stack)>0) {

         value = my_stack_pop(stack);

        if (i=0) {
            min = *value;
            max = *value;
        }

        if (*value>max) {
            max = *value;
        }

        if (*value<min) {
            min = *value;
        }
        
        }

       total = total + *value;
       
    }

    media = total/10;

    printf("\nTotal: %d\n Min: %d\n Max: %d\n Media: %d", total, min, max, media);

}