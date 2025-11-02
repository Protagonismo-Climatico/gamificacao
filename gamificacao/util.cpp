#include "util.h"

void Util::escreverDado(uint8_t device, uint8_t byte) {
    Wire.beginTransmission(device);
    Wire.write(byte);
    Wire.endTransmission();
    delay(1);
}

uint8_t Util::lerBotao(uint8_t device, uint8_t count, uint8_t mask) {
    Wire.requestFrom(device, count);
    uint8_t byte = Wire.read();
    byte = byte & mask;
    return byte;
}

bool Util::botaoSegurado(uint8_t device, uint8_t botao, unsigned long tempoSegurar) {
    static unsigned long tempoInicio = 0;
    uint8_t botaoPressionado = lerBotao(device, 1, MASCARA_BOTOES);

    if (botaoPressionado == botao) {
        if (tempoInicio == 0) tempoInicio = millis();
        if (millis() - tempoInicio >= tempoSegurar) {
            tempoInicio = 0;
            return true;
        }
    } else {
        tempoInicio = 0;
    }
    return false;
}