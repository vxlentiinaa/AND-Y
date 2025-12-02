#include "EntradaUltrasonico.h"
#include "SalidaDedo.h"
#include "SalidaMotorVibracion.h"
#include "SalidaVoz.h"

// instancias de las clases
EntradaUltrasonico ultrasonico;
SalidaDedo dedo;
SalidaMotorVibracion motor;
// salidaVoz voz;

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

  ultrasonico.medirDistancia();
  ultrasonico.decidirCercania();

  Serial.println(ultrasonico.dondeEsta);
  
  // si esta cerca, levantar dedo
  if (ultrasonico.dondeEsta == 0) {
    dedo.levantar();
  }
  // si esta mediano o lejano, bajar
  else {
    dedo.bajar();
  }

  // pausa para estabilidad DE QUE???
  //delay(pausa);

  // vibrar segun ultrasonico
  motor.vibrar(ultrasonico.dondeEsta);
}

// reproducir los audios 
// 1: lejano audio 1
  //if (ultrasonico.dondeEsta == 1) {
    //reproducirAudioDistancia(ultrasonico.distanciaCm);
 //   reproducirAudioDirecto(1);
 //   Serial.println("Reproduce audio 1 (Lejana)");
 // }

 // else if (ultrasonico.dondeEsta == 2) {
  //  reproducirAudioDirecto(2);
 //   Serial.println("Reproduce audio 2 (Mediana)");
 // }

  //else if (ultrasonico.dondeEsta == 0) {
 //   reproducirAudioDirecto(3);
 //   Serial.println("Reproduce audio 3 (Cercana)");
 // }

 // delay(pausa);

 if (ultrasonico.dondeEsta != estadoAnterior) {
    estadoAnterior = ultrasonico.dondeEsta;

    if (ultrasonico.dondeEsta == 2) {
      reproducirAudioDirecto(1);
      Serial.println("Audio 1 lejano");
    }
    else if (ultrasonico.dondeEsta == 1) {
      reproducirAudioDirecto(2);
      Serial.println("Audio 2 mediana");
    }
    else if (ultrasonico.dondeEsta == 0) {
      reproducirAudioDirecto(3);
      Serial.println("Audio 3 cercana");
    }
    
  }
  delay(200);
}