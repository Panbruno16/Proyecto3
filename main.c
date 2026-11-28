/**
 * PROYECTO: PORTALCRAFT
 * Autores: Emmanuel Matarrita Pineda, Maria Paula Ureña Azofeifa y Carlos Bruno Diaz Cordoba.
 * Fecha de creacion: 25/11/26
*/

#include "mapa.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int main() {
    srand(time(NULL)); 
    struct mapa miMapa;
    struct banda miBanda;
    miMapa.densidadDePortales = 10; // Establecer la densidad de portales deseada
    miMapa.cantidadDeLugares = 200; // Establecer la cantidad de lugares deseada
    crearLugares(&miMapa);
    
    if(miMapa.cantidadDeLugares > 0){
    miMapa.posicionBanda = rand() % miMapa.cantidadDeLugares;
    }else{
    printf("No hay mundo, no se puede iniciar la banda.\n");
    return 1;
    }

    asignarActores(&miMapa);
    asignarProyectos(&miMapa);
    generarMapa(&miMapa);
    asegurarComponenteConexa(&miMapa);
    crearBanda(&miBanda);

    calcularDijkstra(&miMapa, 0, 5); 

    mostrarResumenMundo(&miMapa);
    mostrarActores(&miMapa);
    mostrarProyectos(&miMapa);
    return 0;
}