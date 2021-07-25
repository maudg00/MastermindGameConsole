//
//  Jugador.h
//
//
//  Creado por Mauricio de Garay, Bernardo García and Leonardo Morales el 20/11/2020.
//
/* El modulo Jugador.h se encarga de definir el header necesario para que main.cpp pueda llamar a la clase Jugador.cpp*/

//Definir el header si no está definido.

#ifndef JUGADOR_H
#define JUGADOR_H

#include "Hardware.h"
#include <string>
#include "Leaderboards.h"

using namespace std;
//Prototipo de la clase.
class Jugador
{
    public:
        //STRINGS:
        string nombreUsuario;
        string dificultadJuego;
        //INTEGERS:
        int turnosRestantes;
        //MÉTODOS:
        /*
            El constructor va a crear al jugador e inicializar sus respectivas
            variables
        */
        Jugador(string nombre="default", string dificultad="Facil", int turnosRestantes=15);
        /*
            insertarJugadorEnLeaderboard() ingresa tu nombre y puntaje
            en leaderboards
            @params
            @return
        */
        void insertarJugadorEnLeaderboard();
         /*
            verLeaderboardJugadores() te permite ver Leaderboards en terminal BT
            @params
                @return
        */
        void verLeaderboardJugadores();
    
};

#endif