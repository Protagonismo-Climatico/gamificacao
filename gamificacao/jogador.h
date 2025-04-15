
#ifndef JOGADOR_H
#define JOGADOR_H
#include "header.h"
#include "util.h"

class Jogador
{
private:
    char nome_;
    uint8_t pontuacao_;
    uint8_t resposta_;
    uint8_t endereco_;
    unsigned long tempo_anterior_;

public:

    Jogador(char nome, uint8_t endereco)
        : nome_(nome), pontuacao_(0), resposta_(0x0), endereco_(endereco),  tempo_anterior_(0) {}

    Jogador() : nome_(' '), pontuacao_(0), resposta_(0x0), endereco_(0),  tempo_anterior_(0) {}

    void verificarBotaoPressionado();
    void marcar_ponto(uint8_t ponto);
    void reiniciar_jogador();
    char obterNome();
    uint8_t obterPontuacao();
    void definirPontuacao(uint8_t ponto);
    uint8_t obterResposta();
    void definirResposta(uint8_t resposta);
    uint8_t obterEndereco();
    unsigned long obterTempoAnterior();
    void definirTempoAnterior(unsigned long tempo);



};

#endif