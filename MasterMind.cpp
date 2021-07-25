//
//  Mastermind.cpp
//
//
//  Creado por Mauricio de Garay, Bernardo Garcia and Leonardo Morales el 20/11/2020.
//
/* El modulo Mastermind.cpp se encarga de desarrollar los metodos de la clase Mastermind que fue prototipada en Mastermind.h*/
#include "MasterMind.h"
/* Mastermind() es el constructor de la clase, se encarga de instanciar un objeto tipo Mastermind
inicializando los atributos de este.
@params
@returns
*/
Mastermind::Mastermind(string dificultad){
    Mastermind::dificultadJuego=dificultad;
    Mastermind::hizoTrampa=false;
    Mastermind::ganoJuego=false;
    Mastermind::seRindio=false;
    Mastermind::enTurno=false;
    Mastermind::respuestaIngresada="";
    Mastermind::turnoActual=0;
    Mastermind::tiempoTurnoActual=0;
    Mastermind::respuestaCorrecta[0]=0;
    if(dificultad=="Facil")
    {
         Mastermind::turnosTotales=10;
         Mastermind::tiempoPorTurnos=15;
     }
    else
     {
            Mastermind::turnosTotales=12;
            Mastermind::tiempoPorTurnos=10;
     }
    Mastermind::historialRespuestas[0]="";
}
  /*
    iniciarJuego() va a consistir en empezar el juego y continuarlo 
    hasta que termine la partida. Considerar todos los casos
    de cómo terminar una partida
    @params
    @return
 */

void Mastermind::iniciarJuego(){
            Mastermind::timerTotal.start();
            Mastermind::randomizarRespuesta();
	//interrupts rise
            Hardware::HISTORIAL.rise(callback(this,&Mastermind::verHistorial));
            Hardware::TRAMPA.rise(callback(this,&Mastermind::hacerTrampa));
            Hardware::TIEMPO.rise(callback(this,&Mastermind::verTiempoTranscurrido));
            Hardware::RENDIR.rise(callback(this,&Mastermind::rendirJuego));
	//Loop que controla juego
            do
            {
	//cada turno es una iteracion
                Mastermind::desplegarTurno();
                Hardware::LCD.cls();
                Hardware::LCD.printf("Iniciando turno\n");
                wait(2);
                Mastermind::turnoActual++;
                wait(1);
                Hardware::LCD.cls();
                Mastermind::iniciarTurno();
                if(Mastermind::seRindio==true)
                {
                    Hardware::MOTOR.pulsewidth_ms(0);
                    //Hardware::MOTOR2.pulsewidth_ms(0);
                    break;
                }
                if(Mastermind::ganoJuego==true)
                {
                    Hardware::MOTOR.pulsewidth_ms(0);
                    //Hardware::MOTOR2.pulsewidth_ms(0);
                    break;
                }
                Hardware::LCD.cls();
                Hardware::LCD.printf("Finalizar turno\n");
                wait(2);
            }
            while((Mastermind::turnoActual<=turnosTotales));
            Hardware::SEGMENTOS=0;
            Mastermind::finalizarJuego();
            Hardware::MOTOR.pulsewidth_ms(0);
            //Hardware::MOTOR2.pulsewidth_ms(0);
}
 /*
    randomizarRespuesta() va a crear la combinación de colores
    de forma aleatoria
    @params
    @return
*/
void Mastermind::randomizarRespuesta(){
	//numero de colores, depende de dificultad.
            int tamano;
            if(Mastermind::dificultadJuego=="Facil")
            {
                tamano=4;
            }
            else
            {
                tamano=6;
            }
            Mastermind::respuestaCorrecta="";
            char respuestaCorrecta[10];
            respuestaCorrecta[0]=0;
            int random;
            int sensor;
	        /*Hacemos un loop donde obtenemos colores aleatorios y nos aseguramos que no se repitan
             hasta llenar nuestro arreglo respuestaCorrecta*/
            for(int i=0; i<tamano; i++)
            {
                sensor=(int)10000*(0.85-(10*(Hardware::LUZ.read())));
                int bandera=0;
                char letra;
                do
                    {
                    bandera=0;
                    random=(rand()%100)+1;
                    random=((random%sensor)-rand()%100);
                    random=(random%9)+1;
                    if(random==1)
                    {
                        letra='R';
                    }
                    if(random==2)
                    {
                        letra='V';
                    }
                    if(random==3)
                    {
                        letra='A';
                    }
                    if(random==4)
                    {
                        letra='Y';
                    }
                    if(random==5)
                    {
                        letra='N';
                    }
                    if(random==6)
                    {
                        letra='C';
                    }
                    if(random==7)
                    {
                        letra='B';
                    }
                    if(random==8)
                    {
                        letra='M';
                    }
                    if(random>8||random<1){
                        letra='M';
                    }
                    for(int j=0; j<i; j++)
                    {
                        if(letra==respuestaCorrecta[j])
                        {
                            bandera=1;
                        }
                    }
                    
                }
                while(bandera==1);
                respuestaCorrecta[i]=letra;
	//Finalizamos el arreglo
                respuestaCorrecta[i+1]=0;
            }
            
            string aux(respuestaCorrecta);
            Mastermind::respuestaCorrecta=aux;
}
  /*
    iniciarTurno() hace todas las consideraciones a hacer cuando
    se inicia un nuevo turno
    @params
    @return
*/

void Mastermind::iniciarTurno(){
	//Para que vibre cada vez más en un turno, cada segundo se checa
            Mastermind::tickerVibrar.attach(callback(this, &Mastermind::vibrarTiempo), 1);
            int hayBlanco=0;
            int hayRojo=0;
            int hayAzul=0;
            int hayVerde=0;
            int hayAmarillo=0;
            int hayMorado=0;
            int hayNegro=0;
            int hayCafe=0;
            Mastermind::enTurno=true;
	//Si se acaba el tiempo, pierde el turno.
            Mastermind::timeoutTurno.attach( callback(this, &Mastermind::finalizarTurnoTimeout), Mastermind::tiempoPorTurnos);
            Mastermind::respuestaIngresada="";
	//Loop en lo que ingresa valores
            while(Mastermind::enTurno==true)
            {
                if(Mastermind::seRindio==true)
                {
                    break;
                }
                if(Mastermind::enTurno==false)
                {
                    break;
                }
                else if(Mastermind::respuestaIngresada.length()==Mastermind::respuestaCorrecta.length())
                {
                    Mastermind::timeoutTurno.detach();
                    Mastermind::finalizarTurnoJugada();
                    break;
                }

                else if(Hardware::RED.read()==1 && hayRojo==0)
                {
                    Mastermind::respuestaIngresada= Mastermind::respuestaIngresada + "R";
                    hayRojo=1;
                    Hardware::LCD.cls();
                    Hardware::LCD.printf("%s", Mastermind::respuestaIngresada.c_str());
                }
                else if(Hardware::GREEN.read()==1 && hayVerde==0)
                {
                    Mastermind::respuestaIngresada= Mastermind::respuestaIngresada + "V";
                    hayVerde=1;
                    Hardware::LCD.cls();
                    Hardware::LCD.printf("%s", Mastermind::respuestaIngresada.c_str());
                }
                else if(Hardware::BLUE.read()==1 && hayAzul==0)
                {
                    Mastermind::respuestaIngresada= Mastermind::respuestaIngresada + "A";
                    hayAzul=1;
                    Hardware::LCD.cls();
                    Hardware::LCD.printf("%s", Mastermind::respuestaIngresada.c_str());
                }
                else if(Hardware::YELLOW.read()==1 && hayAmarillo==0)
                {
                    Mastermind::respuestaIngresada= Mastermind::respuestaIngresada + "Y";
                    hayAmarillo=1;
                    Hardware::LCD.cls();
                    Hardware::LCD.printf("%s", Mastermind::respuestaIngresada.c_str());
                }
                else if(Hardware::BLACK.read()==1 && hayNegro==0)
                {
                    Mastermind::respuestaIngresada= Mastermind::respuestaIngresada + "N";
                    hayNegro=1;
                   Hardware::LCD.cls();
                    Hardware::LCD.printf("%s", Mastermind::respuestaIngresada.c_str());
                }
                else if(Hardware::BROWN.read()==1 && hayCafe==0)
                {
                    Mastermind::respuestaIngresada= Mastermind::respuestaIngresada + "C";
                    hayCafe=1;
                    Hardware::LCD.cls();
                    Hardware::LCD.printf("%s", Mastermind::respuestaIngresada.c_str());

                }
                else if(Hardware::WHITE.read()==1 && hayBlanco==0)
                {
                    Mastermind::respuestaIngresada= Mastermind::respuestaIngresada + "B";
                    hayBlanco=1;
                   Hardware::LCD.cls();
                    Hardware::LCD.printf("%s", Mastermind::respuestaIngresada.c_str());
                }
                else if(Hardware::PURPLE.read()==1 && hayMorado==0)
                {
                    Mastermind::respuestaIngresada= Mastermind::respuestaIngresada + "M";
                    hayMorado=1;
                    Hardware::LCD.cls();
                    Hardware::LCD.printf("%s", Mastermind::respuestaIngresada.c_str());
                }
            }
            Mastermind::timeoutTurno.detach();
            Mastermind::tickerVibrar.detach();
            Mastermind::tiempoTurnoActual=0;
            Hardware::MOTOR.pulsewidth_ms(0);
            //Hardware::MOTOR2.pulsewidth_ms(0);
            Hardware::MOTOR.write(0);
            //Hardware::MOTOR2.write(0);
}
/*
    finlizarTurnoTimeout() finaliza el juego debido a que el tiempo
    del turno se acabó
    @params
    @return
*/
void Mastermind::finalizarTurnoTimeout(){
      Mastermind::enTurno=false;
}
/*
    finalizarTurnoJugada() finaliza el juego debido a que el usuario
    ingresó su intento de combincación
    @params
    @return
*/
void Mastermind::finalizarTurnoJugada(){
            Hardware::LCD.cls();
            if(Mastermind::seRindio==true)
            {
                return;
            }
            if((Mastermind::respuestaIngresada.length())!=(Mastermind::respuestaCorrecta.length()))
            {
                return;
            }
            Mastermind::enTurno=false;
            int contadorColor=0;
            int contadorPosicion=0;
	        //comparamos para ver posiciones y colores correctos.
            for(int i=0; i<(Mastermind::respuestaCorrecta.length()); i++)
            {
                if(Mastermind::respuestaIngresada[i]==Mastermind::respuestaCorrecta[i])
                {
                    contadorPosicion++;
                }
                for(int j=0; j<(Mastermind::respuestaCorrecta.length()); j++)
                {
                    if(Mastermind::respuestaIngresada[i]==Mastermind::respuestaCorrecta[j])
                    {
                        contadorColor++;
                    }
                }
            }
	        //por si se gana.
            if(contadorPosicion==(Mastermind::respuestaCorrecta.length()))
            {
                Mastermind::ganoJuego=true;
                Hardware::LCD.printf("Acertaste todo.\nFelicidades!");
                return;
            }
            Hardware::LCD.cls();
            Hardware::MOTOR.pulsewidth_ms(0);
            //Hardware::MOTOR2.pulsewidth_ms(0);
            Hardware::LCD.printf("\n%d Color.\n%d Posicion.", contadorColor, contadorPosicion);
            guardarJugadaEnHistorial();
            wait(5);
}
/*
    hacerTrampa() revela la clave en la terminal BT
    @params
    @return
*/
void Mastermind::hacerTrampa(){
             Hardware::limpiarBT();
            Mastermind::hizoTrampa=true;
            Hardware::BT.printf("La respuesta es %s.\n", Mastermind::respuestaCorrecta.c_str());
}
/*
    guardarJugadaEnHistorial() va guardando la clave de intentos
    en un arreglo de strings
    @params
    @return
*/
void Mastermind::guardarJugadaEnHistorial(){
    Mastermind::historialRespuestas[Mastermind::turnoActual-1]=Mastermind::respuestaIngresada;
} 
/*
    verHistorial() despliega en terminal BT tu historial de jugadas
*/
void Mastermind::verHistorial(){
             Hardware::limpiarBT();
            if((Mastermind::historialRespuestas[0].length())<2)
            {
                Hardware::BT.printf("Tu historial esta vacio.\n");
                return;
            }
            for(int i=0; i<Mastermind::turnoActual;i++)
            {
                Hardware::BT.printf("%s\n", Mastermind::historialRespuestas[i].c_str());
            }
}
/*
    verTiempoTranscurrido() despliega en terminal BT el tiempo
    transcurrido y la ronda en la que vas
    @params
    @return
*/
void Mastermind::verTiempoTranscurrido(){
             Hardware::limpiarBT();
            Hardware::BT.printf("Han transcurrido %f segundos.\n", Mastermind::timerTotal.read());
            Hardware::BT.printf("Vas en el turno %d de %d.\n", Mastermind::turnoActual, Mastermind::turnosTotales);
}
/*
    rendirJuego() termina la partida de forma abrupta
    @params
    @return
*/
void Mastermind::rendirJuego(){
    Mastermind::seRindio=true;
}
/*
    finalizarJuego() te avisa que acabó la partida y te lleva a
    terminal si no hiciste trampa para ingresar tu nombre y entrar
    en leaderboards
    @params
    @return
*/
void Mastermind::finalizarJuego(){
            if(Mastermind::seRindio==true || Mastermind::hizoTrampa==true || Mastermind::ganoJuego==false)
            {
                Hardware::LCD.cls();
                Hardware::LCD.printf("Gracias por jugar.\n");
                wait(1);
            }
            else if(Mastermind::ganoJuego==true)
            {
                char nombre[50];
                Hardware::LCD.cls();
                Hardware::LCD.printf("Ve tu terminal.\n");
                Hardware::BT.printf("Dime tu nombre: ");
                Hardware::BT.scanf("%s", nombre);
                string nombreS(nombre);
                Mastermind::jugadorNuevo= Jugador(nombreS, Mastermind::dificultadJuego, (Mastermind::turnosTotales-Mastermind::turnoActual));
                Mastermind::jugadorNuevo.insertarJugadorEnLeaderboard();
                Mastermind::jugadorNuevo.verLeaderboardJugadores();
            }
}
/*
    vibrarTiempo() vibra el motor en proporción al tiempo
    transcurrido de la ronda/turno
    @params
    @return
*/
void Mastermind::vibrarTiempo(){
            Mastermind::tiempoTurnoActual++;
            Hardware::MOTOR.pulsewidth_ms(Mastermind::tiempoTurnoActual);    
            //Hardware::MOTOR2.pulsewidth_ms(Mastermind::tiempoTurnoActual);            
}
/*
    desplegarTurno() despliega turno en display de 7 segmentos
    en comunicación en paralelo
    @params
    @return
*/
void Mastermind::desplegarTurno(){
    int valor;
    switch(Mastermind::turnosTotales - Mastermind::turnoActual){
        case 0:
            valor=63;
            break;
        case 1:
            valor=12;
            break;
        case 2:
            valor=91;
            break;
        case 3:
            valor=94;
            break;
        case 4:
            valor=108;
            break;
        case 5:
            valor=118;
            break;
        case 6:
            valor=119;
            break;
        case 7:
            valor=28;
            break;
        case 8:
            valor=127;
            break;
        case 9:
            valor=124;
            break;
        case 10:
            valor=125;
            break;
        case 11:
            valor=103;
            break;
        case 12:
            valor=51;
            break;
        case 13:
            valor=79;
            break;
        case 14:
            valor=115;
            break;
        case 15:
            valor=113;
            break;
            
        
    }
    Hardware::SEGMENTOS=valor;
}
