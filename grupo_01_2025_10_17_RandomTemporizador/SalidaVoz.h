#ifndef SALIDA_VOZ_H
#define SALIDA_VOZ_H

// esta clase no la separamos porque fue nuestro límite, tenía mucha información
// mandar issue al profe para ver si se puede cambiar pero no es necesario
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

class SalidaVoz {
  SalidaVoz();
  ~SalidaVoz();
};

void configurarMP3();
void reproducirAudioDistancia(float distancia);
void reproducirAudioDirecto(int numeroAudio);

#endif