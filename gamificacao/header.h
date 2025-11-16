#ifndef HEADER_H
#define HEADER_H


#include <Wire.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "TCA9548.h"

#define DEBOUNCE  50
#define TEMPO_LIMITE  10000
#define MAX_ROUNDS 2
#define NUM_CONTROLES 3
#define NUM_JOGADORES (NUM_CONTROLES - 1)


extern LiquidCrystal_I2C lcd;
extern TCA9548 MP;


enum EnderecosI2C
{
    PARTICIPANTE = 0x20,
    LCD = 0x27
};

enum Botao
{
    BOTAO_A = 0b11111110,
    BOTAO_B = 0b11111101,
    BOTAO_C = 0b11111011,
    BOTAO_D = 0b11110111,
    BOTAO_INVALIDO = 0b11111111

};

enum Mascara
{
    MASCARA_BOTOES = 0b11111111
};



enum EstadoJogo {
    LCD_MENU_INICIAL,
    ACAO_MENU_INICIAL,
    LCD_DEF_RESPOSTA,
    ACAO_DEF_RESPOSTA,
    LCD_AGUARDAR_RESPOSTAS,
    ACAO_AGUARDAR_RESPOSTAS,
    LCD_MOSTRAR_RESULTADOS,
    ACAO_MOSTRAR_RESULTADOS,
    LCD_PLACAR_FINAL,
    ACAO_PLACAR_FINAL,
    ACAO_ENCERRAR_JOGO
};
#endif