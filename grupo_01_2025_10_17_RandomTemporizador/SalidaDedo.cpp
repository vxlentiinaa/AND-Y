#include "SalidaDedo.h"

SalidaDedo::SalidaDedo() {}

SalidaDedo::~SalidaDedo() {}

void SalidaDedo::configurar() {
  SalidaDedo::servo.attach(SalidaDedo::patitaServo);
  // posicion inicial 0 grados
  SalidaDedo::servo.write(0);
}

void SalidaDedo::levantar() {
  // 180 grados
  SalidaDedo::servo.write(180);
}

void SalidaDedo::bajar() {
  //0 grados
  SalidaDedo::servo.write(0);
}