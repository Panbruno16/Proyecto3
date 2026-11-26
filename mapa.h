/**
 * PROYECTO: PORTALCRAFT
 * Autores: Emmanuel Matarrita Pineda, Maria Paula Ureña Azofeifa y Carlos Bruno Diaz Cordoba.
 * Fecha de creacion: 25/11/26
*/

#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Structs y datos
 */

struct mapa {
    int cantidadDeLugares;
    int matrizPortales[200][200];    
    int densidadDePortales;
    int posicionBanda;
    struct lugar* listaLugares;
};

struct lugar {
    char nombre[50];
    struct actor* listaDeActores;
    struct proyectos* listaDeProyectos;
    struct secundarias* listaDeSecundarias;
    struct lugar* siguiente;
};


struct banda {
    struct persona* integrantes;
    int saludMentalBanda;
    int saludFisicaBanda;
    int misionActual;
    struct secundarias* listaSecundarias;
};

struct persona {
    char nombre[50];
    char profesion[50];
    int saludMental;
    int saludFisica;
    struct emocion* listaEmociones;
    struct persona* siguiente;
};

struct emocion{
    char nombre[30];
    int valor;
    int esNegativa;
    struct emocion* siguiente;
};

struct actor {
    char nombre[50];
    int dannoMental;
    int dannoFisico;
    struct actor* siguiente;

};

struct proyectos {
    char nombre[50];
    int dannoBienestar;
    int saludMentalRequerida;
    int lugarDestino;
    struct proyectos* siguiente;
};

struct secundarias {
    char nombre[50];
    int profesionRequerida;
    int recompensaMental;
    int recompensaFisica;
    int lugarDestino;
    struct secundarias* siguiente;
};

//Funciones


/**
 * Genera la matriz de adyacencia aleatoria con los portales y sus pesos.
 */
void generarMapa(struct mapa* mapa);

/**
 * Lee el archivo lugares.txt y crea la lista enlazada de lugares.
 */
void crearLugares(struct mapa* mapa);

/**
 * Muestra un resumen de los primeros lugares y sus portales (para pruebas).
 */
void mostrarResumenMundo(struct mapa* mapa);

/**
 * Asegura que el mapa sea conexo creando portales adicionales si es necesario.
 */
void asegurarComponenteConexa(struct mapa* mapa);

/**
 * Recorre el mapa desde un nodo inicial y marca los nodos visitados.
 */
void recorrerMapa(struct mapa* mapa, int nodoInicio, int* visitados);

/**
 * Crea una banda con 3 integrantes y asigna profesiones aleatorias desde el archivo profesiones.txt.
 */
void crearBanda(struct banda* banda);


#endif // MAPA_H