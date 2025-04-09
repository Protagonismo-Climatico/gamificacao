#include "./jogo.h"
#include "Wire.h"
#include <stdint.h>
#include "Arduino.h"

void Jogo::definir_resposta_certa()
{
    bool continuar = true;
    uint8_t resposta_anterior = this->resposta_certa;
    uint8_t botao_pressionado = Util::lerBotao(PROFESSOR, 1, 0b11111111);

    while (continuar)
    {
        if (botao_pressionado == BOTAO_A || botao_pressionado == BOTAO_B || botao_pressionado == BOTAO_C || botao_pressionado == BOTAO_D)
        {
            this->resposta_certa = botao_pressionado;
            continuar = false;
        }
        botao_pressionado = Util::lerBotao(PROFESSOR, 1, 0b11111111);
    }
}

void Jogo::finalizarRodada()
{
    this->rodadas_restantes -= 1;
    this->resposta_certa = 0x0;
    if (this->rodadas_restantes <= 0)
    {
        finalizarJogo();
    }
}

void Jogo::redefinir_respostas_jogadores()
{
    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        this->jogador[i].resposta = 0x0;
    }
}

void Jogo::finalizarJogo()
{
    Serial.print("Acabou o jogo!");
}


void Jogo::reiniciar_jogadores()
{
    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        jogador[i].reiniciar_jogador();
    }
}

void Jogo::verificar_botoes_jogadores()
{
    bool continuar = true;

    while (continuar)
    {
        for (int i = 0; i < MAX_JOGADORES; i++)
        {
            this->jogador[i].verificar_botao_pressionado();
        } 
        if (this->jogador[0].resposta)
        {
            continuar = false;
        }
        // TODO tempo de resposta dos usuarios
    }
}

void Jogo::pontuar_jogadores()
{
    for (uint8_t i = 0; i < MAX_JOGADORES; i++)
    {
        if (this->jogador[i].resposta == this->resposta_certa)
        {
            this->jogador[i].marcar_ponto(1);
        }
    }
}