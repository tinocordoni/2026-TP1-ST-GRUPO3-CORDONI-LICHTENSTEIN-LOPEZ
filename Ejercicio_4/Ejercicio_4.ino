/*
Grupo 3
Cordoni
Lichtenstein
López

Ejercicio 4
*/

//tipos de variables
typedef enum {
  P1,
  P2,
  espera1,
  espera2,
  esperaAumento,
  esperaDsiminucion
} tipoEstado;

//funciones
void maquinaDeEstados();

//defines e includes
#include <TimerOne.h>

#define SWITCH_1  //pin
#define SWITCH_2  //pin

//variables
tipoEstado estado = P1;

int SW1;
int SW2;

float umbralGrados = 28.0;

void setup() {
  //inicio
  Serial.begin(9600);
  Serial.println();
  Serial.println("Inicio \n________");
  Serial.println();

  //setup
  pinMode(SWITCH_1, INPUT /*_PULLUP*/);
  pinMode(SWITCH_2, INPUT /*_PULLUP*/);

  //máquina de estados
  estado = P1;
}

void loop() {
  SW1 = digitalRead(SWITCH_1);
  SW2 = digitalRead(SWITCH_2);
  maquinaDeEstados();
}



void maquinaDeEstados() {
  switch (estado) {
    case P1:
      //
      if (SW1 == LOW && SW2 == LOW) {
        estado = espera1;
      }
      break;
    case espera1:
      //
      if (SW1 == HIGH && SW2 == HIGH) {
        estado = P2;
      }
      break;
    case P2:
      //
      if (SW1 == LOW && SW2 == LOW) {
        estado = espera2;
      }
      if (SW1 == LOW && SW2 == HIGH) {
        estado = esperaAumento;
      }
      if (SW1 == HIGH && SW2 == LOW) {
        estado = esperaDisminucion;
      }
      break;
    case espera2:
      //
      if (SW1 == HIGH && SW2 == HIGH) {
        estado = P1;
      }
      break;
    case esperaAumento:
      //
      if (SW1 == HIGH && SW2 == HIGH) {
        estado = espera2;
      }
      if (SW1 == LOW && SW2 == LOW) {
        umbralGrados++;
        estado = P2;
      }
      break;
    case esperaDisminucion:
      //
      if (SW1 == HIGH && SW2 == HIGH) {
        estado = espera2;
      }
      if (SW1 == LOW && SW2 == LOW) {
        umbralGrados--;
        estado = P2;
      }
      break;
  }
}