#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>
#include "Arduino.h"
#include <Wire.h>

#define MAX_JOGADORES 6

enum EnderecosI2C
{
    PLAYER_A = 0x20,
    PLAYER_B = 0x21,
    PLAYER_C = 0x22,
    PLAYER_D = 0x23,
    PLAYER_E = 0x24,
    PLAYER_F = 0x25,
    PROFESSOR = 0x26
};

enum Botoes
{
    BOTAO_INICIAR = 0b11011111,
    BOTAO_FINALIZAR = 0b11101111,
    BOTAO_A = 0b11110111,
    BOTAO_B = 0b11111011,
    BOTAO_C = 0b11111101,
    BOTAO_D = 0b11111110,
    BOTOES_JOGADOR = 0b00001111,
    BOTOES_MESTRE = 0b11111111
};



#endif