#ifndef UTIL_H
#define UTIL_H
#include "./header.h"

class Util
{
public:
    Util() {}

    static void escreverDado(uint8_t device, uint8_t byte);
    static uint8_t lerBotao(uint8_t device, uint8_t count, uint8_t mask);
};
#endif