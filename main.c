/*
Autór: Sergio Hernandez Castillo
Matrícula: A01025210
Descripción: Actividad 2 - Apuntadores a funciones
*/

#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef struct {
    char * titulo;
    int paginas;
} Libro;

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
        return posicion - tamanio;
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

void imprimirLibro(void * posicion){
    Libro * l = (Libro *)posicion;

    printf("Título: %s\n", l->titulo);
    printf("Páginas: %d\n\n", l->paginas);
}

/* Funciones genéricas */

void forwardIterator(t_dato tipoDeDato, void * arreglo, size_t conteo, size_t tamanio){
    void * posicion = begin(arreglo);

    while (posicion != NULL){
        imprimirArreglo(tipoDeDato, posicion);
        posicion = next(arreglo, posicion, conteo, tamanio);
    }
}

void reverseIterator(t_dato tipoDeDato, void * arreglo, size_t conteo, size_t tamanio){
    void * posicion = end(arreglo, conteo, tamanio) - tamanio;

    while (posicion != NULL){
        imprimirArreglo(tipoDeDato, posicion);
        posicion = prev(arreglo, posicion, conteo, tamanio);
    }
}

void bidirectionalIterator(t_dato tipoDeDato, void * arreglo, size_t conteo, size_t tamanio){
    void * posicion = begin(arreglo);

    while (posicion != NULL){
        imprimirArreglo(tipoDeDato, posicion);
        posicion = next(arreglo, posicion, conteo, tamanio);
    }

    printf("\n");

    posicion = end(arreglo, conteo, tamanio) - tamanio;

    while(posicion != NULL){
        imprimirArreglo(tipoDeDato, posicion);
        posicion = prev(arreglo, posicion, conteo, tamanio);
    }
}

void recorre(t_recorre iterador, t_dato tipoDeDato, void * arreglo, size_t conteo, size_t tamanio){
    (*iterador)(tipoDeDato, arreglo, conteo, tamanio);
}

int main(){
    int * enteros = (int *) malloc(sizeof(int) * N);
    Libro * libros = (Libro *) malloc(sizeof(Libro) * N);

    printf("\nLlenando el arreglo dinámico de enteros...");

    int * e = enteros;
    int * finEnteros = enteros + N;

    for (; e < finEnteros; ++e){
        *e = rand() % 50;
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

    printf("Ahora se va a recorrer el arreglo dinámico de enteros usando un forward iterator:\n");
    recorre(&forwardIterator, &imprimirEntero, enteros, N, sizeof(int));

    // printf("\n\nAhora se va a recorrer el arreglo dinámico de enteros usando un reverse iterator:\n");
    // recorre(&reverseIterator, &imprimirEntero, enteros, N, sizeof(int));

    // printf("\n\nAhora se va a recorrer el arreglo dinámico de enteros usando un bidirectional iterator:\n");
    // recorre(&bidirectionalIterator, &imprimirEntero, enteros, N, sizeof(int));

    printf("\n\nAhora se va a recorrer el arreglo dinámico de libros usando un bidirectional iterator:\n");
    recorre(&bidirectionalIterator, &imprimirLibro, libros, N, sizeof(Libro));

    // printf("\nAhora se va a recorrer el arreglo dinámico de libros usando un forward iterator:\n");
    // recorre(&forwardIterator, &imprimirLibro, libros, N, sizeof(Libro));

    // printf("\nAhora se va a recorrer el arreglo dinámico de libros usando un reverse iterator:\n");
    // recorre(&reverseIterator, &imprimirLibro, libros, N, sizeof(Libro));

    for (Libro * l = libros; l < finLibros; ++l){
        free(l->titulo);
    }

    free(libros);
    free(enteros);

    return 0;
}