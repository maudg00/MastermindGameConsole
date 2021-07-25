///
//  Hardware.h
//
//
//  Creado por Mauricio de Garay, Bernardo García and Leonardo Morales el 20/11/2020.
//
/* El módulo Hardware.h se encarga de definir una clase de variables estáticas con todo el hardware cuyos atributos pueden ser accedidos fácilmente en cualquier momento.*/


//Definir el header si no está definido.

#ifndef HARDWARE_H
#define HARDWARE_H
#include <string>
#include "TextLCD.h"

using namespace std;

class Hardware{
    public:
    //ATRIBUTOS ESTÁTICOS:
      //  BOTONES:
            static DigitalIn RED;
            static DigitalIn GREEN;
            static DigitalIn BLUE;
            static DigitalIn YELLOW;
            static DigitalIn BLACK;
            static DigitalIn BROWN;
            static DigitalIn WHITE;
            static DigitalIn PURPLE;
       // SALIDAS DIGITALES:
            static DigitalOut LED_ON;

       // ENTRADAS ANALÓGICAS:
            static AnalogIn LUZ;
       // SALIDAS PWM:
            static PwmOut MOTOR;
            static PwmOut LEDLUZ;
            static PwmOut MOTOR2;
       // INTERRUPCIONES:     
            static  InterruptIn TRAMPA;
            static InterruptIn HISTORIAL;
            static InterruptIn TIEMPO;
            static InterruptIn RENDIR;
       // COMUNICACIÓN:
            static I2C I2C_LCD;
            static TextLCD_I2C LCD;
            static Serial BT;
            static BusOut SEGMENTOS;
        // EXTRA:
            /*
                limpiarBT() hace un clear de la pantalla en terminal BT a través
                de múltiples saltos de línea
                @params
                @return
            */
            static void limpiarBT();
};
#endif
