/*
Autór: Sergio Hernandez Castillo
Matrícula: A01025210
Descripción: Actividad 2 - Apuntadores a funciones
*/

#include <stdio.h>
#include <stdlib.h>

#define N 5

struct Libro {
    char * titulo;
    int paginas;
};

int main(){
    int * enteros = (int *) malloc(sizeof(int) * N);
    struct Libro * libros = (struct Libro *) malloc(sizeof(struct Libro) * N);

    printf("\nLlenando el arreglo dinámico de enteros...");

    int * e = enteros;
    int * finEnteros = enteros + N;

    for (; e < finEnteros; ++e){
        *e = rand() % 100;
    }

    printf("\nSe há llenado el arreglo dinámico de enteros.");
    printf("\n\nProporcione los datos de los 5 libros:");

    struct Libro * finLibros = libros + N;

    for (struct Libro * l = libros; l < finLibros; ++l){
        l->titulo = (char *) malloc(sizeof(char) * 25);
        printf("\nProporcione el título del libro: ");
        scanf("%s", l->titulo);

        printf("Proporcione la cantidad de páginas que tiene el libro: ");
        scanf("%d", &l->paginas);
    }

    printf("\nSe há llenado el arreglo dinámico de libros.\n");

    for (struct Libro * l = libros; l < finLibros; ++l){
        free(l->titulo);
    }

    free(libros);
    free(enteros);

    return 0;
}