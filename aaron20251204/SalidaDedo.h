
#ifndef SALIDA_DEDO_H
#define SALIDA_DEDO_H

#include <Arduino.h>
#include <Servo.h>

class SalidaDedo {

public:

  // constructor
  SalidaDedo();

  // destructor
  ~SalidaDedo();

  void configurar();

  void levantar();

  void bajar();

  // numero de pin donde va conectado el servomotor
  int patitaServo = 13;

  Servo servo;
};

#endif