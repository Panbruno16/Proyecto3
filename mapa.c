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

    printf("Primeros 20 lugares y sus portales de salida:\n");
    struct lugar* lugarActual= mapa->listaLugares;
    int i=0;
    while(lugarActual != NULL && i < 20){
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

void recorrerMapa(struct mapa* mapa, int nodoInicio, int* visitados){
    int n= mapa->cantidadDeLugares;
    int cola[200];
    int frente=0; 
    int final=0;

    visitados[nodoInicio]=1;
    cola[final]= nodoInicio;
    final++;

    while(frente < final){
        int w= cola[frente];
        frente++;

        for(int j=0; j<n; j++){
            if(mapa->matrizPortales[w][j] > 0 && visitados[j]==0){
                visitados[j]=1;
                cola[final]= j;
                final++;
            }
        }
    }
}

void asegurarComponenteConexa(struct mapa* mapa){
    int n= mapa->cantidadDeLugares;
    int* visitados= calloc(n, sizeof(int));
    int portalesCreados=0;

    recorrerMapa(mapa, 0, visitados);
    for(int i = 1; i<n; i++){
        if(visitados[i]==0){
            mapa->matrizPortales[0][i] = 1 + rand() % 50;
            portalesCreados++;
        }
    }
    for(int i =1; i<n; i++){
        for(int k=0; k<n; k++){
            visitados[k]=0;
        }
        recorrerMapa(mapa, i, visitados);
        if(visitados[0]==0){
            mapa->matrizPortales[i][0] = 1 + rand() % 50;
            portalesCreados++;
        }
    }
    free(visitados);
    /**
     if(portalesCreados>0){
        printf("Se crearon %d portales adicionales para asegurar que el mapa sea conexo.\n", portalesCreados);
    } else {
        printf("El mapa ya era conexo. No se crearon portales adicionales.\n");
    }*/
}

void crearBanda(struct banda* banda){
    char nombreProfesion[10][50];
    int totalProfesiones=0;

    FILE* archivo= fopen("profesiones.txt", "r");
    if(archivo==NULL){
        printf("Error al abrir el archivo profesiones.txt");
        printf("No se puede crear una banda sin profesiones\n");
        banda->integrantes= NULL;
        return;
    }else{
        char linea[50];
        while(fgets(linea, 50, archivo) != NULL && totalProfesiones<10){
            linea[strcspn(linea, "\n")] = 0;
            if(strlen(linea)>0){
                strcpy(nombreProfesion[totalProfesiones], linea);
                totalProfesiones++;
            }
        }
        fclose(archivo);
    }

    if(totalProfesiones==0){
        printf("No se encontraron profesiones validas en el archivo profesiones.txt\n");
        banda->integrantes= NULL;
        return;
    }
    if(totalProfesiones<3){
        printf("Error: No hay suficientes profesiones para crear una banda completa.");
        banda->integrantes= NULL;
        return;
    }


    int profesionesUsadas[10] = {0};
    banda->integrantes= NULL;
    struct persona* ultimo= NULL;
    for(int i = 0; i<3; i++){
        struct persona* nuevo= calloc(1, sizeof(struct persona));
        sprintf(nuevo->nombre, "Integrante %d", i+1);
        int indiceProfesion;
        do{
            indiceProfesion= rand() % totalProfesiones;
        }while(profesionesUsadas[indiceProfesion]==1);

        profesionesUsadas[indiceProfesion]=1;
        strcpy(nuevo->profesion, nombreProfesion[indiceProfesion]);

        nuevo->saludMental= 50 + rand() % 51;
        nuevo->saludFisica= 50 + rand() % 51;
        nuevo->listaEmociones= NULL;
        nuevo->siguiente= NULL;

        asignarEmociones(nuevo);



        if(banda->integrantes==NULL){
            banda->integrantes= nuevo;
            ultimo= nuevo;
        } else {
            ultimo->siguiente= nuevo;
            ultimo= nuevo;
        }
    }
    banda->saludMentalBanda= 0;
    banda->saludFisicaBanda= 0;
    banda->misionActual= 0;
    banda->listaSecundarias= NULL;

    printf("Banda creada con 3 integrantes:\n");
    struct persona* actual= banda->integrantes;
    while(actual != NULL){
        printf(" - %s (Profesión: %s)\n", actual->nombre, actual->profesion);
        printf("Emociones: ");
        mostrarEmociones(actual);
        printf("\n");
        actual= actual->siguiente;
    }
}

void asignarEmociones(struct persona* persona){
    if(persona==NULL){
        return;
    }
    char nombreEmocion[5][30];
    int totalEmociones=0;

    FILE* archivo= fopen("emociones.txt", "r");
    if(archivo==NULL){
        printf("Error al abrir el archivo emociones.txt");
        printf("No se pueden asignar emociones sin el archivo\n");
        return;
    }
    char linea[30];
    while(fgets(linea, 30, archivo) != NULL && totalEmociones <5){
        linea[strcspn(linea, "\n")]=0;
        if(strlen(linea)>0){
            strcpy(nombreEmocion[totalEmociones], linea);
            totalEmociones++;
        }
    }
    fclose(archivo);

    if(totalEmociones==0){
        printf("No se encontraron emociones validas en el archivo emociones.txt\n");
        return;
    }
    int emocionesAsignadas= 0;
    int emocionesUsadas[5] = {0};

    for(int i=0; i <totalEmociones; i++){
        struct emocion* nueva= calloc(1, sizeof(struct emocion));
        strcpy(nueva->nombre, nombreEmocion[i]);
        nueva->valor= 5 + rand() % 16;
        if (strcmp(nueva->nombre, "Felicidad")==0 || strcmp(nueva->nombre, "Disciplina")==0){
            nueva->esNegativa= 0;
        } else {
            nueva->esNegativa= 1;
        }
        nueva->siguiente= persona->listaEmociones;
        persona->listaEmociones= nueva;
    }
}

void mostrarEmociones(struct persona* persona){
    struct emocion* actual = persona->listaEmociones;
    if(actual==NULL){
        printf("No hay emociones asignadas a %s\n", persona->nombre);
        return;
    }
    while(actual != NULL){
        printf("[%s: %d, %s]",
        actual->nombre,
        actual->valor,
        actual->esNegativa == 1 ? "Negativa" : "Positiva");
        actual=actual->siguiente;
    }
}

int calcularDijkstra(struct mapa* mapa, int origen, int destino){
    int n  = mapa->cantidadDeLugares;
    int distancia[200];
    int visitado[200];
    int anteriores[200];
    
    for(int i=0; i<n; i++){
        distancia[i]= INT_MAX;
        visitado[i]= 0;
        anteriores[i]= -1;
    }
    distancia[origen]= 0;

    for(int i=0; i<n; i++){
        int W = -1;
        int minDistancia = INT_MAX;
        for(int j=0; j<n; j++){
            if(visitado[j]==0 && distancia[j]<minDistancia){
                minDistancia= distancia[j];
                W= j;
            }
        }
        if (W==-1 || distancia[W]== INT_MAX){
            break;
        }
        visitado[W]= 1;
        for(int V=0; V<n; V++){
            if(mapa->matrizPortales[W][V]>0 && visitado[V]==0){
                int nuevaDistancia= distancia[W] + mapa->matrizPortales[W][V];
                if(nuevaDistancia<distancia[V]){
                    distancia[V]= nuevaDistancia;
                    anteriores[V]= W;
                }
            }
        }
    }

    if(distancia[destino]== INT_MAX){
        printf("No hay ruta desde %d hasta %d\n", origen, destino);
        return -1;
    }

    int ruta[200];
    int pasos=0;
    int actual= destino;

    while(actual != -1){
        ruta[pasos]= actual;
        pasos++;
        actual= anteriores[actual];
    }


    //Verficiar
    printf("Ruta desde %d hasta %d| \n", origen, destino);
    printf("Costo total de salud: %d\n", distancia[destino]);
    printf("Ruta: ");
    for(int i=pasos-1; i>=0; i--){
        printf("%d", ruta[i]);
        if(i>0){
            printf(" -> ");
        }
    }
    printf("\n");
    

    return distancia[destino];
}

int leerCatalogoActores(struct actor catalogo[], int capacidad){
    FILE* archivo = fopen("actores.txt", "r");
    if(archivo==NULL){
        printf("Error, no se pudo cargar actores. Se necesitan actores para poder crear el mapa.\n");
        return 0;
    }
    int total=0;
    char linea[100];
    while(fgets(linea, 100, archivo)!= NULL){
        linea[strcspn(linea, "\n")]= 0;
        if (strlen(linea)==0){
            continue;
        }
        if(total>=capacidad){
            break;
        }        
            
        if(sscanf(linea, "%49[^,], %d, %d",
            catalogo[total].nombre,
            &catalogo[total].dannoMental,
            &catalogo[total].dannoFisico
        )==3){
            total++;
        }
    }
    fclose(archivo);
    if(total==0){
        printf("No se encontraron actores validos.\n");
    }
    return total;
}

void asignarActores(struct mapa* mapa){
    struct actor catalogo[100];
    int total=leerCatalogoActores(catalogo, 100);
    if(total==0){
        printf("Sin catalogo, no se puede asignar los actores\n");
        return;
    }
    struct lugar* lugarActual=mapa->listaLugares;
    while(lugarActual!=NULL){
        int cantidad= (rand()%100<65) ? 1:0;
        for(int k=0; k<cantidad; k++){
            struct actor* elegido =&catalogo[rand()%total];
            struct actor* nuevo =calloc(1, sizeof(struct actor));
            strcpy(nuevo->nombre, elegido->nombre);
            nuevo->dannoMental=elegido->dannoMental;
            nuevo->dannoFisico=elegido->dannoFisico;
            nuevo->siguiente=lugarActual->listaDeActores;
            lugarActual->listaDeActores=nuevo;
        }    
        lugarActual=lugarActual->siguiente;
    }
}

void mostrarActores(struct mapa* mapa){
    if(mapa==NULL){
        printf("No hay mundo disponible\n");
        return;
    }
    struct lugar* lugarActual=mapa->listaLugares;
    int indice=0;
    while(lugarActual!=NULL){
       struct actor* actual=lugarActual->listaDeActores;
       if(actual!=NULL){
        printf("lugar %d (%s)\n", indice, lugarActual->nombre);
        while(actual!=NULL){
            printf("   - %s (M:%d F:%d)\n",
            actual->nombre, actual->dannoMental, actual->dannoFisico);
            actual=actual->siguiente;
            }
        }else{
            printf("Lugar %d (%s)    - no tiene actor\n", indice, lugarActual->nombre);
        }
        lugarActual=lugarActual->siguiente;
        indice++;
    }
}

int leerCatalogoProyectos(struct proyecto catalogo[], int capacidad){
    FILE* archivo=fopen("proyectos.txt", "r");
    if (archivo==NULL){
        printf("Error al abrir los proyectos, no se pudo crear el mundo\n");
        return 0;
    }
    int total=0;
    char linea[100];
    while(fgets(linea, 100, archivo)!=NULL){
        linea[strcspn(linea, "\n")]=0;
        if(strlen(linea)==0){
            continue;
        }
        if(total>= capacidad){
            break;
        }
        if(sscanf(linea,"%49[^,], %d, %d, %d", 
            catalogo[total].nombre,
            &catalogo[total].dannoBienestar,
            &catalogo[total].saludMentalRequerida,
            &catalogo[total].lugarDestino
        )==4){
            total++; 
        }
    }
    fclose(archivo);
    if(total==0){
        printf("No se encontraron proyectos validos.\n");
    }
    return total; 
}

void asignarProyectos(struct mapa* mapa){
    struct proyecto catalogo[100];
    int total= leerCatalogoProyectos(catalogo, 100);
    if (total==0){
        printf("Sin catalogo de proyectos, no se pudo crear el mundo\n");
        return;
    }
    struct lugar* lugarActual= mapa->listaLugares;
    while(lugarActual!=NULL){
        if(rand()%100<40){
            struct proyecto* elegido=&catalogo[rand()%total];
            if(elegido->lugarDestino<0 || elegido->lugarDestino>=mapa->cantidadDeLugares){
                printf("Proyecto %s tiene destino invalido, se omite.\n", elegido->nombre);
            }else{
                struct proyecto* nuevo=calloc(1, sizeof(struct proyecto));
                strcpy(nuevo->nombre, elegido->nombre);
                nuevo->dannoBienestar=elegido->dannoBienestar;
                nuevo->saludMentalRequerida=elegido->saludMentalRequerida;
                nuevo->lugarDestino=elegido->lugarDestino;

                nuevo->siguiente=lugarActual->listaDeProyectos;
                lugarActual->listaDeProyectos=nuevo;
            }
        }
        lugarActual=lugarActual->siguiente;
    }
}

void mostrarProyectos(struct mapa* mapa){
    if(mapa==NULL){
        printf("No hay mundo disponible\n");
        return;
    }
    struct lugar* lugarActual=mapa->listaLugares;
    int indice=0;
    while(lugarActual!=NULL){
       struct proyecto* actual=lugarActual->listaDeProyectos;
       if(actual!=NULL){
        printf("lugar %d (%s)\n", indice, lugarActual->nombre);
        while(actual!=NULL){
            printf("   - %s (DB:%d S:%d Destino: %d)\n",
            actual->nombre, actual->dannoBienestar, actual->saludMentalRequerida, actual->lugarDestino);
            actual=actual->siguiente;
            }
        }else{
            printf("Lugar %d (%s)    - no tiene proyectos\n", indice, lugarActual->nombre);
        }
        lugarActual=lugarActual->siguiente;
        indice++;
    }
}




