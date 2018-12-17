Práctica Nº3 de la asignatura Sistemas Operativos I.
Asignatura del cuatrimestre de invierno del segundo año de la carrera de Ingeniería Informática @ Universitat de les Illes Balears.

Desarrolladores:
	Nadal Llabrés	(nadal12@hotmail.com)
	Alvaro Pons	(varopons@gmail.com)
	Eugenio Doñaque	(eugeniodonaque@gmail.com)

La práctica consiste en realizar dos programas: 'main' y 'reader'

El programa main ha de recibir como argumento el nombre o ruta de un fichero dentro del directorio donde se ejecuta.

El main intentará leer un my_stack (de la librería av3.c). Si el fichero indicado no tiene el contenido de ningún struct my_stack, o no existe, deberá crear uno nuevo.

El programa trabajará siempre con un my_stack de al menos 10 nodos. En caso de obtener uno mayor desde el fichero, se utilizarán solo las 10 posiciones en agregarse de último.

El mismo creará 10 hilos que de forma concurrente accederán al contenido de la pila (struct my_stack) y aumentar en 1 unidad su valor. Por instrucciones del enunciado de la práctica, deben haber dos secciones críticas: Una en el pop y otra en el push del dato.

Una vez finalizada la ejecución de todos los hilos, se volcará el contenido del stack en el fichero indicado por argumento del programa.


El programa reader realiza estadísticas básicas sobre la estructura de tipo pilo generada. Incluyendo: acumulado, valor máximo, valor mínimo y promedio.


Cada hilo realiza un bucle de N iteraciones (indicado al ejecutar el programa). Por tanto, el funcionamiento correcto del programa se ve cuando el acumulado encontrado en la pila es igual a N*Num_hilos, y el valor promedio igual a acumulado/num_hilos
