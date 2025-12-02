#include "SalidaMotorVibracion.h"

// constructor
SalidaMotorVibracion::SalidaMotorVibracion() {}

// destructor
SalidaMotorVibracion::~SalidaMotorVibracion() {}

// configuración inicial
void SalidaMotorVibracion::configurar() {
  pinMode(SalidaMotorVibracion::TRIG_PIN,
          OUTPUT);
  pinMode(SalidaMotorVibracion::ECHO_PIN, INPUT);
  pinMode(SalidaMotorVibracion::MOTOR_PIN, OUTPUT);
  Serial.begin(9600);
}

// funcion para actualizar NO SE QUE
void SalidaMotorVibracion::actualizar() {
  digitalWrite(SalidaMotorVibracion::TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SalidaMotorVibracion::TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SalidaMotorVibracion::TRIG_PIN, LOW);

  SalidaMotorVibracion::duracion = pulseIn(
    SalidaMotorVibracion::ECHO_PIN,
    HIGH);
}

// actualiza la vibración según la distancia
void SalidaMotorVibracion::vibrar(int cuantoVibrar) {

  // si es cercana, el numero es 0
  if (cuantoVibrar == 0) {
    // No vibra
    SalidaMotorVibracion::intensidad = 0;
  }
  // si es mediana, el numero es 1
  else if (cuantoVibrar == 1) {
    // vibra mucho
    SalidaMotorVibracion::intensidad = 255;
  }
  // si es lejana, el numero es 2
  else if (cuantoVibrar == 2) {
    // Vibra poco
    SalidaMotorVibracion::intensidad = 150;
  }
  // fuera de rango
  else {
    SalidaMotorVibracion::intensidad = 0;
  }

  analogWrite(SalidaMotorVibracion::MOTOR_PIN,
              SalidaMotorVibracion::intensidad);

  delay(100);
}