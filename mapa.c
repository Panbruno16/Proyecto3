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

void menu() {
    printf("Bienvenido al juego PortalCraft!\n");
    printf("Seleccione una opcion:\n");
    printf("1. Iniciar juego\n");
    printf("2. Cargar juego\n");
    printf("3. Salir\n");
};

void generarMapa(struct mapa* mapa){
    //mapa->cantidadDeLugares= 100 + rand() % 101;
    int n=mapa->cantidadDeLugares;
    for(int i=0; i<mapa->cantidadDeLugares; i++){
        for (int j=0; j<mapa->cantidadDeLugares; j++){
            mapa->matrizPortales[i][j] = 0;
        }
    }
    for(int i=0; i<mapa->cantidadDeLugares; i++){
        for (int j=0; j<mapa->cantidadDeLugares; j++){
            if(i!=j){
                int probabilidad = rand() % 100;
                if(probabilidad < mapa->densidadDePortales){
                    mapa->matrizPortales[i][j] = 1 + rand() % 50;
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        int tieneSalida = 0;
        int tieneLlegada = 0;
        for(int j=0; j<n; j++){
            if(mapa->matrizPortales[i][j] > 0){
                tieneSalida = 1;
            }
            if(mapa->matrizPortales[j][i] > 0){
                tieneLlegada = 1;
            }
        }

        if(tieneSalida==0){
            int destinoAzar= rand()%n;
            while(destinoAzar==i){
                destinoAzar= rand()%n;
        }
        //printf("DEBUG: El lugar %d no tenia salida. Creando portal al lugar %d\n", i, destinoAzar);

        mapa->matrizPortales[i][destinoAzar] = 1 + rand() % 50;
        }
        if(tieneLlegada==0){
            int origenAzar= rand()%n;
            while(origenAzar==i){
                origenAzar= rand()%n;
            }
            mapa->matrizPortales[origenAzar][i] = 1 + rand() % 50;
        }
    }
}

void crearLugares(struct mapa* mapa){

    FILE* archivo= fopen("lugares.txt", "r");
    if(archivo==NULL){
        printf("Error al abrir el archivo lugares.txt");
        printf("No se puede crear un mundo sin los lugares\n");
        mapa->cantidadDeLugares= 0;
        return;
    }


    mapa->listaLugares= NULL;
    struct lugar* ultimoLugar= NULL;
    char nombreLeido[50];
    int contador=0;

    while(fgets(nombreLeido, sizeof(nombreLeido), archivo) != NULL && contador < mapa->cantidadDeLugares){
        nombreLeido[strcspn(nombreLeido, "\n")] = 0;
        if(strlen(nombreLeido)==0){
            continue;
        } 
        struct lugar* nuevoLugar= calloc(1, sizeof(struct lugar));
        strcpy(nuevoLugar->nombre, nombreLeido);

        nuevoLugar->listaDeActores= NULL;
        nuevoLugar->listaDeProyectos= NULL;
        nuevoLugar->siguiente= NULL;

        if(mapa->listaLugares==NULL){
            mapa->listaLugares= nuevoLugar;
            ultimoLugar= nuevoLugar;
        } else {
            ultimoLugar->siguiente= nuevoLugar;
            ultimoLugar= nuevoLugar;
        }
        contador++;
    }
    fclose(archivo);
    if(contador < mapa->cantidadDeLugares){
        printf("Advertencia: No se encontraron suficientes lugares en el archivo lugares.txt. Ajustando cantidad a %d.\n", contador);
        mapa->cantidadDeLugares= contador;
    }
}


void mostrarResumenMundo(struct mapa* mapa){
    printf("Resumen del mundo generado:\n");
    printf("Cantidad de lugares: %d\n", mapa->cantidadDeLugares);
    printf("Densidad de portales: %d%%\n", mapa->densidadDePortales);

    printf("Primeros 5 lugares y sus portales de salida:\n");
    struct lugar* lugarActual= mapa->listaLugares;
    int i=0;
    while(lugarActual != NULL && i < 5){
        printf("Lugar %d: %s-> ", i, lugarActual->nombre);
        int portales=0;
        for(int j=0; j<mapa->cantidadDeLugares; j++){
            if(mapa->matrizPortales[i][j] > 0){
                printf("[Portal al indice %d, peso %d]", j, mapa->matrizPortales[i][j]);
                portales++;
            }
        }
        if(portales==0){
            printf("No hay portales de salida desde este lugar.");
        }
        printf("\n");
        lugarActual= lugarActual->siguiente;
        i++;
    }
    printf("... (y más lugares no mostrados)\n");
}