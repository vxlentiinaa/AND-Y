#ifndef ENTRADA_ULTRASONICO_H
#define ENTRADA_ULTRASONICO_H

#include <Arduino.h>

class EntradaUltrasonico {

public:

  EntradaUltrasonico();

  ~EntradaUltrasonico();

  void configurar();

  float medirDistancia();

  void mostrarConsola();

  void decidirCercania();

  // pin digital 11 para el Trigger del sensor
  int patitaTrigger = 11;

  // pin digital 12 para el Echo del sensor
  int patitaEcho = 12;

  long duracion;

  int distanciaCm;

  // rangos de distancia (en cm)
  float minCercana = 2;
  float maxCercana = 15;

  float minMediana = 70;
  float maxMediana = 90;
  float minLejana = 130;
  float maxLejana = 150;

  // 0 esta cercano
  // 1 esta mediano
  // 2 esta lejano
  int dondeEsta = 0;
  // inicializar en valor -1
  // porque -1 no es un valor correcto
  int dondeEstaAnterior = -1;

  bool cambioEstado = false;
};

#endif