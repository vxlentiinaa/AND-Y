#ifndef MOTOR_VIBRACION_H
#define MOTOR_VIBRACION_H

#include <Arduino.h>

class SalidaMotorVibracion {
public:
  // constructor
  SalidaMotorVibracion();
  // destructor
  ~SalidaMotorVibracion();

  // configura los pines
  void configurar();
  // actualiza los datos de los pines para que queden en 0
  void actualizar();
  // función auxiliar
  void vibrar(int cuantoVibrar);

  // pines
  int TRIG_PIN = 11;
  int ECHO_PIN = 12;
  int MOTOR_PIN = 9;

  // variables internas
  unsigned long duracion = 0;
  int intensidad = 0;
};

#endif