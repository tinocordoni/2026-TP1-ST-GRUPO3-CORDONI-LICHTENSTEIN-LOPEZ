/*
Grupo 3
Cordoni
Lichtenstein
López
*/

//Ejercicio 2
#include <DHT.h>

#define DATA_DHT 23    // pin del dht
#define DHTTYPE DHT11  // tipo de DHT

DHT dht(DATA_DHT, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temperatura = dht.readTemperature();

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  delay(2000);  // 2 segundos mínimo
}