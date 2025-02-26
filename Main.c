#include <stdlib.h>
#include <stdio.h>
#include "pq.h"

int main(int argc, char* argv[]) {

    /* revisar que se paso el nombre del archivo via parametros */
    if (argc != 2) {
        printf("Forma de uso:\n");
        printf("\tProyecto1.exe nombre_de_archivo.txt\n");
        return 1;
    }
    /*
    REEMPLACE SU CODIGO AQUI
    deben abrir el archivo, leer cada caracter y guardarlo en una tabla con la cantidad de
    veces que se encuentra cada letra.
    (o sea contar cuantas veces se repite cada letra,o sea su frecuencia de repeticion)
    Luego cerrar el archivo.
    Luego agregar cada uno de los caracteres a la cola de prioridad PQ usando su frecuencia
    de repeticion como prioridad
    Por ultimo deben sacar todos los elementos de la cola de prioridad e imprimir los valores
    en pantalla (caracter y frecuencia). Esto nos dara un resultado ordenado de menor
    a mayor frecuencia
    Ejemplo de funcionamiento, al ejecutar el .exe del proyecto compilado:
        >Proyecto1.exe test1.txt
        donde test1.txt contenga el siguiente texto: Debo terminar mi proyecto hoy!
        El resultado a imprimir debe ser
        >Frecuencias de menor a mayor
        >Caracter | frecuencia
        >D = 1
        >a = 1
        >p = 1
        >h = 1
        >! = 1
        >b = 1
        >t = 2
        >m = 2
        >i = 2
        >y = 2
        >e = 3
        >o = 3
        >r = 3
        >  = 4

    Obs. deberan poder manejar archivos de texto grandes, por ej libros completos en txt
    mirar proyecto gutenberg
    https://www.gutenberg.org/cache/epub/10506/pg10506.txt
    */
    // ej. leer el contenido del archivo caracter por caracter:s
    FILE* f = fopen(argv[1], "r");
    while (1) {
        char c = fgetc(f);
        if (feof(f)) {
            break;
        }
        // imprime en pantalla el caracter
        printf("%c", c);
    }
    fclose(f);

    return 0;
}