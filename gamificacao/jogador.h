#ifndef JOGADOR_H
#define JOGADOR_H

#include "header.h"

class Jogador {
private:
    char nome_;
    uint8_t pontuacao_;
    Botao resposta_;
    uint8_t endereco_;
    unsigned long tempo_anterior_;

public:
    Jogador(char nome, uint8_t endereco);
    Jogador();

    void verificarBotaoPressionado();
    void marcar_ponto(uint8_t ponto);
    void reiniciar_jogador();
    
    char obterNome();
    uint8_t obterPontuacao();
    void definirPontuacao(uint8_t ponto);
    Botao obterResposta();
    void definirResposta(Botao resposta);
    uint8_t obterEndereco();
    unsigned long obterTempoAnterior();
    void definirTempoAnterior(unsigned long tempo);
};

#endif