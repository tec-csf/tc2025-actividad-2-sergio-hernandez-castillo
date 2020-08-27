/*
Autór: Sergio Hernandez Castillo
Matrícula: A01025210
Descripción: Actividad 2 - Apuntadores a funciones
*/

#include <stdio.h>
#include <stdlib.h>

#define N 5

/* Tipos de funciones */

typedef void (*t_dato)(void *);
typedef void (*t_iterador)(void *, void *, size_t, size_t);
typedef void (*t_recorre)(t_dato, void *, size_t, size_t);

/* Funciones callback para los iteradores */

void * begin(void * arreglo){
    return arreglo;
}

void * end(void * arreglo, size_t conteo, size_t tamanio){
    return (arreglo + (conteo * tamanio));
}

void * next(void * arreglo, void * posicion, size_t conteo, size_t tamanio){
    if ((posicion + tamanio) == (arreglo + (conteo * tamanio))){
        return NULL;
    }

    else {
        return posicion + tamanio;
    }
}

void * prev(void * arreglo, void * posicion, size_t conteo, size_t tamanio){
    if (arreglo == posicion){
        return NULL;
    }

    else {
        return arreglo - tamanio;
    }
}

/* Funciones para imprimir */

void imprimirArreglo(t_dato tipoDeDato, void * posicion){
    (*tipoDeDato)(posicion);
}

void imprimirEntero(void * posicion){
    int * i = (int *)posicion;

    printf("%d ", *i);
}

/* Funciones genéricas */

void recorre(t_recorre iterador, t_dato tipoDeDato, void * arreglo, size_t conteo, size_t tamanio){
    (*iterador)(tipoDeDato, arreglo, conteo, tamanio);
}

void forwardIterator(t_dato tipoDeDato, void * arreglo, size_t conteo, size_t tamanio){
    void * forwardBegin = begin(arreglo);
    void * posicion = forwardBegin; 

    while (posicion != NULL){
        imprimirArreglo(tipoDeDato, posicion);
        posicion = next(arreglo, posicion, conteo, tamanio);
    }
}

typedef struct {
    char * titulo;
    int paginas;
} Libro;

int main(){
    int * enteros = (int *) malloc(sizeof(int) * N);
    Libro * libros = (Libro *) malloc(sizeof(Libro) * N);

    printf("\nLlenando el arreglo dinámico de enteros...");

    int * e = enteros;
    int * finEnteros = enteros + N;

    for (; e < finEnteros; ++e){
        *e = rand() % 100;
    }

    printf("\nSe há llenado el arreglo dinámico de enteros.");
    printf("\n\nProporcione los datos de los 5 libros:");

    Libro * finLibros = libros + N;

    for (Libro * l = libros; l < finLibros; ++l){
        l->titulo = (char *) malloc(sizeof(char) * 25);
        printf("\nProporcione el título del libro: ");
        scanf("%s", l->titulo);

        printf("Proporcione la cantidad de páginas que tiene el libro: ");
        scanf("%d", &l->paginas);
    }

    printf("\nSe há llenado el arreglo dinámico de libros.\n\n");

    printf("Ahora se va a recorrer el arreglo dinámico de enteros usando un forward iterator: ");
    recorre(&forwardIterator, &imprimirEntero, enteros, N, sizeof(enteros));

    for (Libro * l = libros; l < finLibros; ++l){
        free(l->titulo);
    }

    free(libros);
    free(enteros);

    return 0;
}