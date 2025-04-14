#ifndef JOGO_H
#define JOGO_H
#include "./jogador.h"
#include "./professor.h"
#include "./header.h"
#include "util.h"
class Jogo
{
public:
    uint8_t rodadas;
    uint8_t rodadas_restantes;
    uint8_t resposta_certa;
    bool ativo;
    Jogador jogador[MAX_JOGADORES];
    Professor professor;

    Jogo(uint8_t rodadas)
        : rodadas(rodadas), rodadas_restantes(rodadas), resposta_certa(0x0)
    {
        this->ativo = false;
    }
    void iniciar_jogo();
    void definir_resposta_certa();
    void finalizarRodada();
    void finalizarJogo();
    void definir_quantidade_rodadas();
    void reiniciar_jogadores();
    void verificar_botoes_jogadores();
    void pontuar_jogadores();
    void redefinir_respostas_jogadores();
};

#endif