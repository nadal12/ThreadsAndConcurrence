#include "aventura3.h"



int main(int argc, char *argv[]) {

    //Declaraciones
    int file; 

    if (argv[1] == NULL) {
        imprime_error("Se debe pasar por parámetro el nombre del fichero de pila\n Saliendo.");
        return 0;
    }

    file = open(argv[1],  O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);

    if (file == -1) {
        imprime_error("Error en llamada de sistema open()");
        return 0;
    }

    fseek(file, 0, SEEK_END);


    if (ftell(file)==0) || (numero de elementos <10) {

        rellenar_fichero();
        process();

    }else{

        process();

    }

    return 1;
}