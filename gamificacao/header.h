#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>

// ========== CONFIGURAÇÕES GERAIS ==========
#define MAX_JOGADORES 5
#define DEBOUNCE 50
#define TEMPO_LIMITE 10000
#define MAX_ROUNDS 5

// ========== ENDEREÇOS I2C DOS CONTROLES ==========
enum EnderecosI2C {
    PLAYER_A = 0x20,
    PLAYER_B = 0x21,
    PLAYER_C = 0x22,
    PLAYER_D = 0x23,
    PLAYER_E = 0x24,
    PROFESSOR = 0x26
};

// ========== BOTÕES ==========
enum Botao {
    BOTAO_A = 0b11110111,
    BOTAO_B = 0b11111011,
    BOTAO_C = 0b11111101,
    BOTAO_D = 0b11111110,
    BOTAO_INVALIDO = 0b11111111
};

// ========== MÁSCARAS ==========
enum Mascara {
    MASCARA_BOTOES = 0b11111111
};

// ========== ESTADOS DO JOGO ==========
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