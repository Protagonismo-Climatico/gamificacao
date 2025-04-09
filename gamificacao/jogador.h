
#ifndef JOGADOR_H
#define JOGADOR_H
#include <stdint.h>
#include "header.h"
#include "Arduino.h"
#include "util.h"

class Jogador
{
public:
    char nome;
    uint8_t pontuacao;
    uint8_t resposta;
    uint8_t endereco;
    uint8_t botao_pressionado;

    Jogador(char nome, uint8_t endereco)
        : nome(nome), pontuacao(0), resposta(0x0), endereco(endereco), botao_pressionado(0) {}

    Jogador() : nome(' '), pontuacao(0), resposta(0x0), endereco(0), botao_pressionado(0) {}

    void verificar_botao_pressionado();
    void marcar_ponto(uint8_t ponto);
    void reiniciar_jogador();
};

#endif