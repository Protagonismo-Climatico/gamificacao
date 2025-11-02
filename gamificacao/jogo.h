#ifndef JOGO_H
#define JOGO_H

#include "header.h"
#include "jogador.h"
#include "professor.h"

class Jogo {
public:
    Botao resposta_certa;
    bool ativo;
    Jogador jogador[MAX_JOGADORES];
    Professor professor;
    EstadoJogo estado_atual;
    bool todos_jogadores_responderam;
    bool tempo_esgotado;
    int jogador_atual_resultado;
    int round_atual;

    Jogo();

    void iniciar_jogo();
    void finalizarJogo();
    Botao definir_resposta_certa(Botao);
    void verificar_botoes_jogadores();
    void reiniciar_jogadores();
    void pontuar_jogadores(Botao, uint8_t);
    void redefinir_respostas_jogadores();
    void ordenar_jogadores_por_pontuacao();
};

#endif