#include "EntradaUltrasonico.h"

EntradaUltrasonico::EntradaUltrasonico() {}

EntradaUltrasonico::~EntradaUltrasonico() {}

void EntradaUltrasonico::configurar() {
  pinMode(patitaTrigger, OUTPUT);
  pinMode(patitaEcho, INPUT);
  Serial.begin(9600);
}

float EntradaUltrasonico::medirDistancia() {
  // Enviar pulso
  digitalWrite(patitaTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(patitaTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(patitaTrigger, LOW);

  // Leer eco
  duracion = pulseIn(patitaEcho, HIGH);

  // Convertir a cm (velocidad del sonido = 343 m/s)
  distanciaCm = int(float(duracion) * 0.0343 / 2.0);

  return distanciaCm;
}

void EntradaUltrasonico::decidirCercania() {
  int nuevoEstado = -1;

  // Determinar en qué zona está la distancia
  if (distanciaCm >= minCercana && distanciaCm <= maxCercana) {
    nuevoEstado = 0; // cercana
  } 
  else if (distanciaCm >= minMediana && distanciaCm <= maxMediana) {
    nuevoEstado = 1; // mediana
  } 
  else if (distanciaCm >= minLejana && distanciaCm <= maxLejana) {
    nuevoEstado = 2; // lejana
  }

  //Cambia solo si ha pasado tiempo suficiente desde el último cambio
  if (nuevoEstado != ultimoEstado && (millis() - ultimoCambio > tiempoEstabilidad)) {
    ultimoCambio = millis();
    ultimoEstado = nuevoEstado;
    dondeEsta = nuevoEstado;
  } 
  else {
    dondeEsta = ultimoEstado;
  }
}