#include "professor.h"

uint8_t Professor::obterEndereco(){
    return this->endereco_;
}
char Professor::obterNome(){
    return this->nome_;
}

Botao Professor::verificarBotaoPressionado()
{
    uint8_t botao_pressionado_atual = Util::lerBotao(this->obterEndereco(), 1, 0b11111111);
    uint8_t botao_pressionado_anterior = BOTAO_INVALIDO;
    static unsigned long tempo_anterior = 0;

    if (botao_pressionado_atual != BOTAO_INVALIDO && millis() - tempo_anterior > 50)
    {
        tempo_anterior = millis();
        switch (botao_pressionado_atual)
        {
        case BOTAO_A:
            Serial.println("O Professor apertou a opcao 'A'");
            return BOTAO_A;
        case BOTAO_B:
            Serial.println("O Professor apertou a opcao 'B'");
            return BOTAO_B;
        case BOTAO_C:
            Serial.println("O Professor apertou a opcao 'C'");
            return BOTAO_C;
        case BOTAO_D:
            Serial.println("O Professor apertou a opcao 'D'");
            return BOTAO_D;
        default:
            return BOTAO_INVALIDO;
        }
    }
}