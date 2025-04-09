#include "jogador.h"

void Jogador::verificar_botao_pressionado()
{
    uint8_t botao_pressionado_atual = Util::lerBotao(this->endereco, 1, 0b11111111);
    uint8_t botao_pressionado_anterior = this->botao_pressionado;

    if (botao_pressionado_atual != 0b11111111 && botao_pressionado_atual != botao_pressionado_anterior && this->resposta == 0x0)
    {
        switch (botao_pressionado_atual)
        {
        case BOTAO_A:
            Serial.println("O jogador apertou a opcao 'A'");
            this->resposta = BOTAO_A;
            break;
        case BOTAO_B:
            Serial.println("O jogador apertou a opcao 'B'");
            this->resposta = BOTAO_B;
            break;
        case BOTAO_C:
            Serial.println("O jogador apertou a opcao 'C'");
            this->resposta = BOTAO_C;
            break;
        case BOTAO_D:
            Serial.println("O jogador apertou a opcao 'D'");
            this->resposta = BOTAO_D;
            break;
        default:
            break;
        }
    }
}

void Jogador::marcar_ponto(uint8_t ponto)
{
    this->pontuacao += ponto;
}

void Jogador::reiniciar_jogador()
{
    Util::escreverDado(this->endereco, 0b11111111);
    this->resposta = 0;
    this->botao_pressionado = 0;
}