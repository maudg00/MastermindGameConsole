//
//  main.cpp
//
//
//  Creado por Mauricio de Garay, Bernardo Garcia and Leonardo Morales el 20/11/2020.
/*Se encargará de controlar el flujo general de la consola e instanciar las variables estáticas de hardware */

#include "mbed.h"
#include "MasterMind.h"
#include "TextLCD.h"
#include "Hardware.h"
#include "Jugador.h"
#include "Leaderboards.h"
DigitalIn Hardware::RED(PTC11);
DigitalIn Hardware::GREEN(PTC10);
DigitalIn Hardware::BLUE(PTC6);
DigitalIn Hardware::YELLOW(PTC5);
DigitalIn Hardware::BLACK(PTC4);
DigitalIn Hardware::BROWN(PTC3);
DigitalIn Hardware::WHITE(PTC0);
DigitalIn Hardware::PURPLE(PTC7);
//SALIDAS DIGITALES:
DigitalOut Hardware::LED_ON(PTC9);    
//ENTRADAS ANALÓGICAS:
AnalogIn Hardware::LUZ(PTB0);
//SALIDAS PWM:
PwmOut Hardware::MOTOR(PTA1);
PwmOut Hardware::LEDLUZ(PTB1);
//PwmOut Hardware::MOTOR2(PTA13);
//INTERRUPCIONES:     
InterruptIn Hardware::TRAMPA(PTA5);
InterruptIn Hardware::HISTORIAL(PTA4);
InterruptIn Hardware::TIEMPO(PTA12);
InterruptIn Hardware::RENDIR(PTD4);
//COMUNICACIÓN:
I2C Hardware::I2C_LCD(PTE0,PTE1);
TextLCD_I2C Hardware::LCD(&I2C_LCD, 0x4E, TextLCD::LCD16x2);
Serial Hardware::BT(PTE22, PTE23);
BusOut Hardware::SEGMENTOS(PTE31, PTA17, PTA16, PTC17, PTC16, PTC13, PTC12);

Ticker tickerIluminacion;

//PROTOTIPO DE FUNCIONES A USAR
/*
La función intro se encarga de desplegar la introducción al usuario, tanto en terminal de celular como LCD.
Parámetros: ninguno
Returns: void
*/

void intro();
/*
La función pedirDificultad pide dificultad al usuario y explica en el celular qué hace cada dificultad. Además, retorna la que fue seleccionada.
Parámetros: ninguno
Returns: string con dificultad seleccionada
*/

string pedirDificultad();
/*
La función revisarIluminacion lee la entrada analógica del fotoresistor y en función a eso, ajusta con PWM los leds laterales. Es attached a un ticker que checa constantemente la iluminación.
Parámetros: ninguno
Returns: void
*/

void revisarIluminacion();
int juegosJugados=0;

// DECLARACIÓN DE VARIABLES GLOBALES DE LA CLASE LEADERBOARDS
 string Leaderboards::leaderboards[0];
    int Leaderboards::jugadoresTotales;
    
// FUNCIÓN MAIN
int main()
{
     Hardware::LEDLUZ.period_ms(100);
    Hardware::MOTOR.period_ms(0);
    Hardware::MOTOR.pulsewidth_ms(0);
    Hardware::SEGMENTOS=0;
    Leaderboards::jugadoresTotales=0;
    Hardware::LED_ON=1;
    
    tickerIluminacion.attach(&revisarIluminacion,1);
    string dificultad;
    while(1)
    {
    intro();
    int opcion=0;
    do
    {
        opcion=Hardware::BLUE.read();
        if((opcion)==1)
        {
            Hardware::MOTOR.period_ms(15);
            Hardware::LCD.cls();
             Hardware::limpiarBT();
            break;
        }
        Hardware::MOTOR.period_ms(10);
    }
    while ((opcion)==0);
    dificultad=pedirDificultad();
    Mastermind *MasterMindJuego=new Mastermind(dificultad);
    MasterMindJuego->iniciarJuego();
    MasterMindJuego->timerTotal.stop();
    Hardware::HISTORIAL.rise(NULL);
    Hardware::RENDIR.rise(NULL);
    Hardware::TIEMPO.rise(NULL);
    Hardware::TRAMPA.rise(NULL);
    free(MasterMindJuego);
    }
}


/*
La función intro se encarga de desplegar la introducción al usuario, tanto en terminal de celular como LCD.
Parámetros: ninguno
Returns: void
*/
void intro()
{
        Hardware::LCD.cls();
        Hardware::limpiarBT();
        Hardware::LCD.printf("MASTERMIND\nPresiona azul!");
        Hardware::BT.printf("Bienvenidx a la interfaz por celular de MASTERMIND.\nEste juego fue creado por Mauricio de Garay y Bernardo Garcia.\nAqui podras ver los resultados de tu historial, trampa, tiempo y leaderboards.\nAdemas, para ingresar tu usuario si es que ganas de forma limpia, se hara desde esta terminal.\n");
}
/*
La función pedirDificultad pide dificultad al usuario y explica en el celular qué hace cada dificultad. Además, retorna la que fue seleccionada.
Parámetros: ninguno
Returns: string con dificultad seleccionada
*/

string pedirDificultad()
    {
        string facil="Facil";
        string dificil="Dificil";
        Hardware::LCD.printf("Azul: facil.\nRojo: dificil.");
        Hardware::BT.printf("Facil:\n     Combinacion de 4 colores.\n     10 intentos.\n     15 segundos por intento.\n");
        Hardware::BT.printf("Dificil:\n     Combinacion de 6 colores.\n     12 intentos.\n     Solamente 10 segundos por intento.\n");
        int opcionAzul=0, opcionRojo=0;
        wait(1);
        do
        {
            opcionAzul=Hardware::BLUE.read();
            opcionRojo=Hardware::RED.read();
        }
        while ((opcionAzul!=1) && (opcionRojo!=1));
        Hardware::LCD.cls();
        //Hardware::BT.cls();
        if(opcionAzul==1)
        {
            return facil;
        }
        return dificil;
    }
/*
La función revisarIluminacion lee la entrada analógica del fotoresistor y en función a eso, ajusta con PWM los leds laterales. Es attached a un ticker que checa constantemente la iluminación.
Parámetros: ninguno
Returns: void
*/
void revisarIluminacion()
{
    Hardware::LEDLUZ.write(0.5-(10*(Hardware::LUZ.read())));
}
