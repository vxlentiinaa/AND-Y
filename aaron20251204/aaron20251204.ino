
//
#include "EntradaUltrasonico.h"
#include "SalidaDedo.h"
#include "SalidaMotorVibracion.h"
#include "SalidaVoz.h"

// instancias de las clases
EntradaUltrasonico ultrasonico;
SalidaDedo dedo;
SalidaMotorVibracion motor;


int pausa = 500;
int estadoAnterior = -1;

void setup() {
  // configurar entrada
  ultrasonico.configurar();

  // configurar salidas
  dedo.configurar();
  motor.configurar();

  // inicializamos el reproductor
  configurarMP3();
}

void loop() {

  detectarEstado();


  ultrasonico.medirDistancia();
  ultrasonico.decidirCercania();

  Serial.println(ultrasonico.dondeEsta);

  // si esta cerca, levantar dedo
  if (ultrasonico.dondeEsta == 0) {
    dedo.levantar();
  }
  // si esta mediano o lejano, bajar dedo
  else {
    dedo.bajar();
  }

  // vibrar segun ultrasonico
  motor.vibrar(ultrasonico.dondeEsta);

  // reproducir los audios, segun distancia
  if (ultrasonico.dondeEsta != estadoAnterior) {
    estadoAnterior = ultrasonico.dondeEsta;

    if (ultrasonico.dondeEsta == 2) {
      reproducirAudioDirecto(1);
      Serial.println("Audio 1 lejano");
    } else if (ultrasonico.dondeEsta == 1) {
      reproducirAudioDirecto(2);
      Serial.println("Audio 2 mediana");
    } else if (ultrasonico.dondeEsta == 0) {
      reproducirAudioDirecto(random(3, 10));
      Serial.println("Audio 3 cercana");
    }
  }
  delay(200);
}