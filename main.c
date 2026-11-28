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
    struct mapa miMapa = {0};    
    struct banda miBanda;    
    miMapa.densidadDePortales = 10;
    miMapa.cantidadDeLugares = 200;
    crearLugares(&miMapa);

    if(miMapa.cantidadDeLugares > 0){
        miMapa.posicionBanda = rand() % miMapa.cantidadDeLugares;
    }else{
        printf("No hay mundo, no se puede iniciar la banda.\n");
        return 1;
    }

    asignarActores(&miMapa);
    asignarProyectos(&miMapa);
    miMapa.pesoTotalProyectos = calcularPesoTotalMundo(&miMapa);
    generarMapa(&miMapa);
    asegurarComponenteConexa(&miMapa);
    crearBanda(&miBanda);
    
    printf("\nPRUEBA: posicion inicial\n");
    printf("La banda nacio en el lugar %d\n", miMapa.posicionBanda);

    printf("\nPRUEBA: obtenerLugar \n");
    struct lugar* lugar0 = obtenerLugar(&miMapa, 0);
    if(lugar0 != NULL) printf("Lugar 0: %s\n", lugar0->nombre);

    struct lugar* lUltimo = obtenerLugar(&miMapa, miMapa.cantidadDeLugares - 1);
    if(lUltimo != NULL) printf("Ultimo lugar (%d): %s\n", miMapa.cantidadDeLugares-1, lUltimo->nombre);

    struct lugar* lMalo = obtenerLugar(&miMapa, miMapa.cantidadDeLugares + 10);
    if(lMalo == NULL) printf("Posicion invalida -> NULL (correcto!) \n");

    printf("\nPRUEBA: llegar al Lugar (lugar de la banda)\n");
    llegarAlLugar(&miMapa, &miBanda);

    printf("\nPRUEBA: bienestar\n");
    mostrarBienestarMundo(&miMapa);
    if(obtenerLugar(&miMapa, miMapa.posicionBanda) != NULL){   // ← guard
        mostrarBienestarLugar(obtenerLugar(&miMapa, miMapa.posicionBanda));
    }

    //mostrarResumenMundo(&miMapa);
    //mostrarActores(&miMapa);
    //mostrarProyectos(&miMapa);
    return 0;
}