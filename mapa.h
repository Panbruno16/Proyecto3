/**
 * PROYECTO: PORTALCRAFT
 * Autores: Emmanuel Matarrita Pineda, Maria Paula Ureña Azofeifa y Carlos Bruno Diaz Cordoba.
 * Fecha de creacion: 25/11/26
*/

#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>

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
    int profesion;
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


    

#endif // MAPA_H