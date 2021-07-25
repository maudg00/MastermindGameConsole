//
//  Jugador.cpp
//
//
//  Creado por Mauricio de Garay, Bernardo García and Leonardo Morales el 20/11/2020.
//
/* El modulo Jugador.cpp se encarga de desarrollar los métodos de la clase Jugador que fue prototipada en Jugador.h*/
#include "Jugador.h"
/*
            El constructor va a crear al jugador e inicializar sus respectivas
            variables
        */
Jugador::Jugador(string nombre, string dificultad, int turnosRestantes){
            Jugador::nombreUsuario=nombre;
            Jugador::dificultadJuego=dificultad;
            Jugador::turnosRestantes=turnosRestantes;
}
  /*
            insertarJugadorEnLeaderboard() ingresa tu nombre y puntaje
            en leaderboards
            @params
            @return
        */

void  Jugador::insertarJugadorEnLeaderboard()
{
            char palabra[100];
            sprintf(palabra, "Nombre: %s, Dificultad: %s, Turnos restantes: %d\n", Jugador::nombreUsuario.c_str(), Jugador::dificultadJuego.c_str(), Jugador::turnosRestantes);
            string aux(palabra);
            Leaderboards::leaderboards[Leaderboards::jugadoresTotales]=aux;
            Leaderboards::jugadoresTotales++;
}
/*
            verLeaderboardJugadores() te permite ver Leaderboards en terminal BT
            @params
                @return
        */

void Jugador::verLeaderboardJugadores()
{
            Hardware::limpiarBT();
            Hardware::BT.printf("LEADERBOARDS:\n");
            for(int i=0; i<Leaderboards::jugadoresTotales;i++){
                Hardware::BT.printf("%s\n", Leaderboards::leaderboards[i].c_str());
            }
           
}

