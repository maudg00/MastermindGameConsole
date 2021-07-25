//
//  Hardware.cpp
//
//
//  Creado por Mauricio de Garay, Bernardo Garcia and Leonardo Morales el 20/11/2020.
//
/* El modulo Hardware.cpp se encarga de desarrollar los metodos de la clase Hardware que fue prototipada en Hardware.h*/
#include "Hardware.h"
/*
                limpiarBT() hace un clear de la pantalla en terminal BT a través
                de múltiples saltos de línea
                @params
                @return
            */
void Hardware::limpiarBT(){
    for(int i=0; i<40; i++)
        Hardware::BT.printf("\n");
}