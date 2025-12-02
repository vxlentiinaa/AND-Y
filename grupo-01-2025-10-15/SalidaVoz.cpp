#include "SalidaVoz.h"
#include "DFRobotDFPlayerMini.h"

#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))   // para placas tipo UNO o ESP8266
#include <SoftwareSerial.h>
SoftwareSerial mp3Serial(4, 5); // RX, TX
#define MP3_SERIAL mp3Serial
#else
#define MP3_SERIAL Serial1
#endif

DFRobotDFPlayerMini myDFPlayer;

// inicializar el reproductor MP3
void configurarMP3() {
  MP3_SERIAL.begin(9600);
  Serial.println(F("Inicializando DFPlayer..."));

  if (!myDFPlayer.begin(MP3_SERIAL, true, true)) {
    Serial.println(F("⚠️ Error: No se pudo iniciar el DFPlayer."));
    Serial.println(F("1. Revisa las conexiones (RX/TX)."));
    Serial.println(F("2. Asegúrate de que la SD esté insertada."));
    while (true) { delay(100); }
  }

  Serial.println(F("🎶 DFPlayer Mini listo."));
  myDFPlayer.volume(20); // volumen 0–30
}


// reproducir audio según distancia medida
void reproducirAudioDistancia(float distancia) {
  static int ultimoAudio = 0; // evita repetir el mismo audio constantemente

// definir la distancia minima de 2 a 15 cm
// definir distancia media de 70 a 90 cm
// definir la distancia maxima de 130 a 150 cm
// tiempo de reposo cuando no siente presencia 
 if (distancia >= 2 && distancia <= 18) {
    // rango largo: audio 1
    if (ultimoAudio != 3) {
      myDFPlayer.playFolder(3, 3);
      Serial.println("Reproduciendo audio 3");
      ultimoAudio = 3;
    }
  } 
  else if (distancia >= 70 && distancia <= 90) {
    // rango medio: audio 2
    if (ultimoAudio != 2) {
      myDFPlayer.playFolder(2, 2);
      Serial.println("Reproduciendo audio 2");
      ultimoAudio = 2;
    }
  } 
  else if (distancia >= 130 && distancia <= 150) {
    // rango largo: audio 1
    if (ultimoAudio != 1) {
      myDFPlayer.playFolder(1, 1);
      Serial.println("Reproduciendo audio 1");
      ultimoAudio = 1;
    }
  } 
  else {
    ultimoAudio = 0; // fuera de rango: reinicia estado
  }
}

  void reproducirAudioDirecto(int numeroAudio, int carpetaAudio) {
    myDFPlayer.Folder(carpetaAudio, numeroAudio);
    Serial.print("Reproduciendo carpeta ");
    Serial.print(carpetaAudio);
    Serial.print("Reproduciendo audio");
    Serial.println(numeroAudio);
  }