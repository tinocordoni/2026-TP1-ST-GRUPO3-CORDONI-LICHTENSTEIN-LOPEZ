/*
Ejercicio 1
Cordoni
Laist
*/

//tipos de variables
typedef enum {
  Espera1,
  Espera2,
  P1,
  P2,
  EsperaAumento,
  EsperaDsiminucion
} tipoEstado;

//funciones

//defines e includes
#include <TimerOne.h>

#define BOT1 3
#define BOT2 4

//variables
tipoEstado estado = P1;

int timerSeg = 0;

void setup() {
  //inicio
  Serial.begin(9600);
  Serial.println();
  Serial.println("Inicio \n________");
  Serial.println();

  //setup

  //timerOne
  Timer1.initialize(1000000);  //cada 1s
  Timer1.attachInterrupt(timer);

  //máquina de estados
  estado = ;
}

void loop() {

  switch (estado) {
    case :
      break;
  }
}

void timer() {
  timerSeg++;
}