#ifndef ENTRADAULTRASONICO_H
#define ENTRADAULTRASONICO_H

#include <Arduino.h>

class EntradaUltrasonico {
public:
  EntradaUltrasonico();
  ~EntradaUltrasonico();

  void configurar();
  float medirDistancia();
  void decidirCercania();

  // valores actuales
  int dondeEsta;     // 0 = cercana, 1 = mediana, 2 = lejana, -1 = nada
  float distanciaCm; // distancia medida

  // pines del sensor
  const int patitaTrigger = 11;
  const int patitaEcho = 12;

  // rangos de distancia (puedes ajustarlos)
  const int minCercana = 5;
  const int maxCercana = 30;
  const int minMediana = 50;
  const int maxMediana = 80;
  const int minLejana = 90;
  const int maxLejana = 120;

  long duracion;

  // variables para evitar repeticiones de loro
  int ultimoEstado = -1;
  unsigned long ultimoCambio = 0;
  const unsigned long tiempoEstabilidad = 500; // milisegundos (0.5 seg)
};

#endif