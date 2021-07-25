//
//  Leaderboards.h
//
//
//  Creado por Mauricio de Garay, Bernardo García and Leonardo Morales el 20/11/2020.
//
/* El modulo Leaderboards.h se encarga de definir el header necesario para que main.cpp pueda llamar a la clase Leaderboards.cpp*/

//Definir el header si no está definido.

#ifndef LEADERBOARDS_H
#define LEADERBOARDS_H
#include <string>
#include "mbed.h"
#include "TextLCD.h"

using namespace std;

class Leaderboards{
    public:
    //ATRIBUTOS ESTÁTICOS:
     static string leaderboards[50];
     static int jugadoresTotales;
};
#endif