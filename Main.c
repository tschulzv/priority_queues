#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "pq.h"

int main(int argc, char* argv[]) {
    //revisar que se paso el nombre del archivo via parametros 
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
    
    // arreglo de caracteres ascii, indices inicializados a 0 
    int ascii[256] = {0};

    // leer el contenido del archivo caracter por caracter
    FILE* f = fopen(argv[1], "r");
    while (1) {
        char c = fgetc(f);
        if (c == EOF) {
            break;
        }
        // aumentar el conteo del caracter correspondiente en el array de ascii
        // castear a unsigned char para asegurar que los chars sean del 0 a 255
        ascii[(unsigned char)c]++;
    }
    fclose(f);
    
    // crear la pq y verificar su creacion correcta
    PQ* pq = pq_create();
    if (pq == NULL) { return 1; }
    
    // recorrer array de ascii y agregar a pq los caracteres con frecuencia > 0
    for (int i = 0; i < 256; i++) {
        if (ascii[i] > 0) {
            char* ch = malloc(sizeof(char));
            if (ch == NULL) { return 1;}
            *ch = (char)i;
            pq_add(pq, ch, ascii[i]);
        }
    }
    
    /*
    PQ* pq = pq_create();
    if (pq == NULL) { return 0; }
    // agregar algunos nodos
    char* valor1 = malloc(sizeof(char));
    *valor1 = 'A';
    pq_add(pq, valor1, 3);
    char* valor2 = malloc(sizeof(char));
    *valor2 = 'B';
    pq_add(pq, valor2, 4);

    //imprimir, debería ordenar: c, a
    print_pq(pq);


    char* valor3 = malloc(sizeof(char));
    *valor3 = 'C';
    pq_add(pq, valor3, 9);

    //imprimir, debería ordenar: c, a, b
    print_pq(pq);

    char* valor4 = malloc(sizeof(char));
    *valor4 = 'D';
    pq_add(pq, valor3, 8);


    char* valor5 = malloc(sizeof(char));
    *valor5 = 'E';
    pq_add(pq, valor5, 2);

    char* valor6 = malloc(sizeof(char));
    *valor6 = 'F';
    pq_add(pq, valor6, 5);

    char* valor7 = malloc(sizeof(char));
    *valor7 = 'G';
    pq_add(pq, valor7, 7);

    
    PrioValue pv = NULL;
    if (pq_remove(pq, (void**)&pv)) {
        if (pv != NULL) {
            printf("%c\n", *(char*)(pv->value));
            free(pv->value); 
            free(pv);         
        }
    }*/
    printf("Frecuencias de menor a mayor\nCaracter | Frecuencia");

    // sacar los valores en orden de menor a mayor hasta vaciar pq
    PrioValue pv = NULL;
    char ch;
    while (pq->size > 0) {
        // llamar a remove y si no es null (error) imprimir
        if (pq_remove(pq, (void**)&pv)) {
            if (pv != NULL) {
                // acceder al valor del puntero value como un char
                ch = *(char*)(pv->value);
                if (ch == ' ') { 
                    printf("\nespacio = %d", pv->prio);
                }
                else if (ch == '\n') {
                    printf("\nnewline = %d", pv->prio);
                }
                else {
                    printf("\n%c = %d", ch, pv->prio);
                }
            }
        }
    }
    free(pv->value);
    free(pv);
    pq_destroy(pq);
    system("PAUSE");
    return 0;
}