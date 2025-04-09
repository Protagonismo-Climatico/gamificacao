#include "professor.h"

void Professor::verificar_botao_pressionado()
{
    uint8_t botao_pressionado_atual = Util::lerBotao(this->endereco, 1, 0b11111111);
    uint8_t botao_pressionado_anterior = this->botao_pressionado;

    if (botao_pressionado_atual != 0b11111111 && botao_pressionado_atual != botao_pressionado_anterior)
    {
        switch (botao_pressionado_atual)
        {
        case BOTAO_A:
            Serial.println("O Professor apertou a opcao 'A'");
            this->botao_pressionado = BOTAO_A;
            break;
        case BOTAO_B:
            Serial.println("O Professor apertou a opcao 'B'");
            this->botao_pressionado = BOTAO_B;
            break;
        case BOTAO_C:
            Serial.println("O Professor apertou a opcao 'C'");
            this->botao_pressionado = BOTAO_C;
            break;
        case BOTAO_D:
            Serial.println("O Professor apertou a opcao 'D'");
            this->botao_pressionado = BOTAO_D;
            break;
        case BOTAO_INICIAR:
            Serial.println("Iniciar rodada");
            this->botao_pressionado = BOTAO_INICIAR;
            break;
        case BOTAO_FINALIZAR:
            this->botao_pressionado = BOTAO_FINALIZAR;
            break;
        default:
            break;
        }
    }
}