#include "EntradaUltrasonico.h"

EntradaUltrasonico::EntradaUltrasonico() {}

EntradaUltrasonico::~EntradaUltrasonico() {}

void EntradaUltrasonico::configurar() {
  pinMode(EntradaUltrasonico::patitaTrigger, OUTPUT);
  pinMode(EntradaUltrasonico::patitaEcho, INPUT);
  Serial.begin(9600);
}

float EntradaUltrasonico::medirDistancia() {

  // mide la distancia y despues la devuelve
  digitalWrite(EntradaUltrasonico::patitaTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(EntradaUltrasonico::patitaTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(EntradaUltrasonico::patitaTrigger, LOW);

  // lee la duración del pulso de retorno
  EntradaUltrasonico::duracion = pulseIn(EntradaUltrasonico::patitaEcho, HIGH);
  // calcula la distancia en cm (velocidad del sonido = 343 m/s)
  EntradaUltrasonico::distanciaCm = int(float(EntradaUltrasonico::duracion) * 0.0343 / 2.0);

  // mostrar distancia medida en el monitor serial
  // Serial.print("Distancia: ");
  // Serial.print(distanciaCm);
  // Serial.println(" cm");

  return distanciaCm;
}

void EntradaUltrasonico::decidirCercania() {

  EntradaUltrasonico::dondeEstaAnterior = EntradaUltrasonico::dondeEsta;

  // calcula nuevo estado de dondeEsta
if (EntradaUltrasonico::distanciaCm >= EntradaUltrasonico::minCercana
      && EntradaUltrasonico::distanciaCm <= EntradaUltrasonico::maxCercana) {
    EntradaUltrasonico::dondeEsta = 0;
  } else if (EntradaUltrasonico::distanciaCm >= EntradaUltrasonico::minMediana
             && EntradaUltrasonico::distanciaCm <= maxMediana) {
    EntradaUltrasonico::dondeEsta = 1;
  } else if (EntradaUltrasonico::distanciaCm >= EntradaUltrasonico::minLejana
             && EntradaUltrasonico::distanciaCm <= EntradaUltrasonico::maxLejana) {
    EntradaUltrasonico::dondeEsta = 2;
  } else {
    EntradaUltrasonico::dondeEsta = -1;
  }

   // decidir si dondeEsta cambio o no
  if (EntradaUltrasonico::dondeEsta == EntradaUltrasonico::dondeEstaAnterior) {
  EntradaUltrasonico::cambioEstado = false;
  } else {
    EntradaUltrasonico::cambioEstado = true;
  }

}