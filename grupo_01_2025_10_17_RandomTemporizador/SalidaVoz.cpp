#include "SalidaVoz.h"

#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))  // para placas tipo UNO o ESP8266
#include <SoftwareSerial.h>
SoftwareSerial mp3Serial(4, 5);  // RX, TX
#define MP3_SERIAL mp3Serial
#else
#define MP3_SERIAL Serial1
#endif

DFRobotDFPlayerMini mp3Player;

// condicionar el sonido para que no se repita como loro
// es decir, si detecta distancia x, reproducir es verdadero
bool reproduciendo = false;

// prueba de la aplicacion de millis
int tiempoActual = millis();

// tiempo el cual ha pasado desde la ultima actualizacion del temporizador
int tiempoNuevoTemporizador = 0;

// cuantos milisegundos durara un segundo
int intervaloSegundo = 6500;

int distancia = 0;

// inicializar el reproductor MP3
void configurarMP3() {
  MP3_SERIAL.begin(9600);
  Serial.println(F("Inicializando DFPlayer..."));

  if (!mp3Player.begin(MP3_SERIAL, true, true)) {
    Serial.println(F("Error: No se pudo iniciar el DFPlayer."));
    Serial.println(F("1. Revisa las conexiones (RX/TX)."));
    Serial.println(F("2. Asegúrate de que la SD esté insertada."));
    while (true) { delay(100); }
  }

  Serial.println(F("🎶 DFPlayer Mini listo."));
  mp3Player.volume(30);  // volumen 0–30
}

// reproducir audio según distancia medida
void reproducirAudioDistancia(float distancia) {
  static int ultimoAudio = 0;  // evita repetir el mismo audio constantemente

  // definir la distancia minima de 0 a 20 cm
  // definir distancia media de 50 a 90 cm
  // definir la distancia maxima de 100 a 140 cm
  // tiempo de reposo cuando no siente presencia
  if (distancia >= 5 && distancia <= 30) {
    // rango cercano(carpeta 3): audios 002-010
    if (ultimoAudio != 3 && !reproduciendo) {
      int numeroAudio = random(2, 11);       // random entre 2 y 10 inclusive
      mp3Player.playFolder(3, numeroAudio);  // Carpeta 3, archivos 002-010
      reproduciendo = true;
      Serial.print("Reproduciendo audio ");
      Serial.println(numeroAudio);
      ultimoAudio = 3;
    }
  } else if (distancia >= 50 && distancia <= 80) {
    // rango medio(carpeta 2): audio 2
    if (ultimoAudio != 2 && !reproduciendo) {
      mp3Player.playFolder(2, 1);
      reproduciendo = true;
      Serial.println("Reproduciendo audio 2");
      ultimoAudio = 2;
    } else if (distancia >= 90 && distancia <= 120) {
      // rango largo(carpeta 1): audio 1
      if (ultimoAudio != 1 && !reproduciendo) {
        mp3Player.playFolder(1, 1);
        reproduciendo = true;
        Serial.println("Reproduciendo audio 1");
        ultimoAudio = 1;
      } else {
        // fuera de rango: reinicia estado
        ultimoAudio = 0;
        reproduciendo = false;
      }
    }
  }
}

void reproducirAudioDirecto(int numeroAudio) {
    mp3Player.play(numeroAudio);
    Serial.print("Reproduciendo audio ");
    Serial.println(numeroAudio);
    tiempoNuevoTemporizador = tiempoActual;
}
