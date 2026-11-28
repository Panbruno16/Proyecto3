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
    struct proyecto* listaDeProyectos;
    struct secundaria* listaDeSecundarias;
    struct lugar* siguiente;
};


struct banda {
    struct persona* integrantes;
    int saludMentalBanda;
    int saludFisicaBanda;
    int misionActual;
    struct secundaria* listaSecundarias;
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

struct proyecto {
    char nombre[50];
    int dannoBienestar;
    int saludMentalRequerida;
    int lugarDestino;
    struct proyecto* siguiente;
};

struct secundaria {
    char nombre[50];
    int profesionRequerida;
    int recompensaMental;
    int recompensaFisica;
    int lugarDestino;
    struct secundaria* siguiente;
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

/**
 * Calcula la distancia mínima entre dos lugares usando el algoritmo de Dijkstra.
 */
int calcularDijkstra(struct mapa* mapa, int origen, int destino);

/**
 * Asigna las emociones a cada Integrante de la banda de manera enlistada. 
 */

void asignarEmociones(struct persona* persona);

/**
 * Mostrar emociones de cada persona integrante en la banda. 
 */
void mostrarEmociones(struct persona* persona);

/**
 * Lee el catalogo de actores para poder determinar el catalogo del mismo y usarse para asignar con una probabilidad en cada lugar. 
 */
int leerCatalogoActores(struct actor catalogo[], int capacidad);

/**
 * Hace la asignacion de los actores en lugar con una probabilidad que haya 1 o 0 actores en cada lugar. 
 */
void asignarActores(struct mapa* mapa);

/**
 * funcion momentanea que muestra los actores de un lugar.
 */
void mostrarActores(struct mapa* mapa);

/**
 * funcion para leer un catalogo de proyectos y asi poder usarlos despues en asignarProyectos.
 */
int leerCatalogoProyectos(struct proyecto catalogo[], int capacidad);

/**
 * Funcion para poder asignar los proyectos en distintos lugares, tienen nombre, dañobienestar, saludrequerida y destino. 
 */
void asignarProyectos(struct mapa* mapa);

/**
 * Funcion para mostrar los proyectos y sus asiganciones.
 */
void mostrarProyectos(struct mapa* mapa);
#endif // MAPA_H