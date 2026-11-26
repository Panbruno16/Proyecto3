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
    miMapa.densidadDePortales = 20; // Establecer la densidad de portales deseada
    miMapa.cantidadDeLugares = 200; // Establecer la cantidad de lugares deseada
    crearLugares(&miMapa);
    generarMapa(&miMapa);


    mostrarResumenMundo(&miMapa);

    // Liberar memoria y realizar otras operaciones necesarias

    return 0;
}