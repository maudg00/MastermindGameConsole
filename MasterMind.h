//
//  Mastermind.h
//
//
//  Creado por Mauricio de Garay, Bernardo García and Leonardo Morales el 20/11/2020.
//
/* El modulo Mastermind.h se encarga de definir el header necesario para que main.cpp pueda llamar a la clase Mastermind.cpp*/

//Definir el header si no está definido.

#ifndef MASTERMIND_H
#define MASTERMIND_H
#include <string>
#include "mbed.h"
#include "Jugador.h"

using namespace std;
//Prototipo de la clase.
class Mastermind
{
    // ATRIBUTOS PÚBLICOS:
    public:
        // STRINGS:
            string dificultadJuego;
            string respuestaCorrecta;
            string respuestaIngresada;
            string historialRespuestas[20];
        //ENTEROS:
            int turnosTotales;
            int turnoActual;
            int tiempoPorTurnos;
            int tiempoTurnoActual;
        //BOOLEANOS:
            bool hizoTrampa;
            bool ganoJuego;
            bool seRindio;
            bool enTurno;
        //TIMERS:
            Timer timerTotal;
        //TICKER:
            Ticker tickerVibrar;
        //TIMEOUT:
            Timeout timeoutTurno;
        //JUGADOR:
            Jugador jugadorNuevo;
    // Métodos
            /*
                El constructor va a inicializar todas las variables
            */
            Mastermind(string dificultad);
            /*
                iniciarJuego() va a consistir en empezar el juego y continuarlo 
                hasta que termine la partida. Considerar todos los casos
                de cómo terminar una partida
                @params
                @return
            */
            void iniciarJuego();
             /*
                randomizarRespuesta() va a crear la combinación de colores
                de forma aleatoria
                @params
                @return
            */
            void randomizarRespuesta();
             /*
               iniciarTurno() hace todas las consideraciones a hacer cuando
               se inicia un nuevo turno
               @params
                @return
            */
            void iniciarTurno();
            /*
               finlizarTurnoTimeout() finaliza el juego debido a que el tiempo
               del turno se acabó
               @params
                @return
            */
            void finalizarTurnoTimeout();
            /*
               finlizarTurnoJugada() finaliza el juego debido a que el usuario
               ingresó su intento de combincación
               @params
                @return
            */
            void finalizarTurnoJugada();
            /*
                hacerTrampa() revela la clave en la terminal BT
                @params
                @return
            */
            void hacerTrampa();
             /*
                guardarJugadaEnHistorial() va guardando la clave de intentos
                en un arreglo de strings
                @params
                @return
            */
            void guardarJugadaEnHistorial();
             /*
                verHistorial() despliega en terminal BT tu historial de jugadas
            */
            void verHistorial();
             /*
                verTiempoTranscurrido() despliega en terminal BT el tiempo
                transcurrido y la ronda en la que vas
                @params
                @return
            */
            void verTiempoTranscurrido();
             /*
                rendirJuego() termina la partida de forma abrupta
                @params
                @return
            */
            void rendirJuego();
             /*
                finalizarJuego() te avisa que acabó la partida y te lleva a
                terminal si no hiciste trampa para ingresar tu nombre y entrar
                en leaderboards
                @params
                @return
            */
            void finalizarJuego();
             /*
                vibrarTiempo() vibra el motor en proporción al tiempo
                transcurrido de la ronda/turno
                @params
                @return
            */
            void vibrarTiempo();
            /*
                desplegarTurno() despliega turno en display de 7 segmentos
                en comunicación en paralelo
                @params
                @return
            */
            void desplegarTurno();
};
#endif