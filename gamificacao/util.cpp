#include "util.h"

static void Util::escreverDado(uint8_t device, uint8_t byte)
{
    Wire.beginTransmission(device);
    Wire.write(byte);
    Wire.endTransmission();
    delay(1);
}

static uint8_t Util::lerBotao(uint8_t device, uint8_t count, uint8_t mask)
{
    Wire.requestFrom(device, count);
    uint8_t byte = Wire.read();
    byte = byte & mask;

    return byte;
}