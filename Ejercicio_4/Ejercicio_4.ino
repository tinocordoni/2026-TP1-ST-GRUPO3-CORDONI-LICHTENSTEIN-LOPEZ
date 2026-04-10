/*
Grupo 3
Cordoni
Lichtenstein
López

Ejercicio 4
*/

//defines e includes
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <U8g2lib.h>

#define SWITCH_1 35
#define SWITCH_2 34

#define LED 25
#define DHTPIN 23
#define DHTTYPE DHT11

//tipos de variables
typedef enum {
  P1,
  P2,
  espera1,
  espera2,
  esperaAumento,
  esperaDisminucion
} tipoEstado;

//funciones
void maquinaDeEstados();
void imprimirTemperaturaYUmbral();
void imprimirUmbral();
void controlLed();

//config
DHT dht(DHTPIN, DHTTYPE);
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /*reset*/ U8X8_PIN_NONE);

//variables
tipoEstado estado = P1;

int SW1;
int SW2;

float umbralGrados = 28.0;

float hic;

void setup() {
  //inicio
  Serial.begin(9600);
  Serial.println();
  Serial.println("Inicio \n________");
  Serial.println();

  //setup
  pinMode(SWITCH_1, INPUT);
  pinMode(SWITCH_2, INPUT);

  pinMode(LED, OUTPUT);

  dht.begin();
  u8g2.begin();
  u8g2.clearBuffer();

  //máquina de estados
  estado = P1;
}

void loop() {
  SW1 = digitalRead(SWITCH_1);
  SW2 = digitalRead(SWITCH_2);

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)){
    return;
  }
  hic = dht.computeHeatIndex(t, h, false);
  maquinaDeEstados();
  controlLed();
}

void maquinaDeEstados() {
  switch (estado) {
    case P1:
      imprimirTemperaturaYUmbral();
      //
      if (SW1 == LOW && SW2 == LOW) {
        estado = espera1;
      }
      break;
    case espera1:
      imprimirTemperaturaYUmbral();
      //
      if (SW1 == HIGH && SW2 == HIGH) {
        estado = P2;
      }
      break;
    case P2:
      imprimirUmbral();
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
      imprimirUmbral();
      //
      if (SW1 == HIGH && SW2 == HIGH) {
        estado = P1;
      }
      break;
    case esperaAumento:
      imprimirUmbral();
      //
      if (SW1 == LOW && SW2 == LOW) {
        estado = espera2;
      }
      if (SW1 == HIGH && SW2 == HIGH) {
        umbralGrados++;
        estado = P2;
      }
      break;
    case esperaDisminucion:
      imprimirUmbral();
      //
      if (SW1 == LOW && SW2 == LOW) {
        estado = espera2;
      }
      if (SW1 == HIGH && SW2 == HIGH) {
        umbralGrados--;
        estado = P2;
      }
      break;
  }
}

void imprimirTemperaturaYUmbral() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2.drawStr(0, 20, "Actual:");
  char stringTemp[10];
  sprintf(stringTemp, "%.1f", hic);
  u8g2.drawStr(80, 20, stringTemp);

  u8g2.drawStr(0, 40, "Umbral:");
  char stringUmb[10];
  sprintf(stringUmb, "%.1f", umbralGrados);
  u8g2.drawStr(80, 40, stringUmb);

  u8g2.sendBuffer();
}

void imprimirUmbral() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2.drawStr(0, 40, "Umbral:");
  char stringUmb[10];
  sprintf(stringUmb, "%.1f", umbralGrados);
  u8g2.drawStr(80, 40, stringUmb);  // alineado igual

  u8g2.sendBuffer();
}

void controlLed() {
  if (hic >= umbralGrados) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}