#include "professor.h"

uint8_t Professor::obterEndereco(){
    return this->endereco_;
}
char Professor::obterNome(){
    return this->nome_;
}

Botao Professor::verificarBotaoPressionado()
{
    uint8_t atual = Util::lerBotao(this->obterEndereco(), 1, 0b11111111);

    static uint8_t anterior = BOTAO_INVALIDO;        // último botão lido
    static unsigned long t_ultima_mudanca = 0;       // para debounce
    unsigned long agora = millis();

    // Se não mudou, não há evento
    if (atual == anterior) return BOTAO_INVALIDO;

    // Mudou: aplica debounce (~50 ms)
    if (agora - t_ultima_mudanca < 50) return BOTAO_INVALIDO;

    // Confirma a mudança
    t_ultima_mudanca = agora;
    anterior = atual;

    // Dispara evento **só** na transição solto -> pressionado
    if (atual != BOTAO_INVALIDO) {
        switch (atual) {
            case BOTAO_A: Serial.println("O Professor apertou a opcao 'A'"); return BOTAO_A;
            case BOTAO_B: Serial.println("O Professor apertou a opcao 'B'"); return BOTAO_B;
            case BOTAO_C: Serial.println("O Professor apertou a opcao 'C'"); return BOTAO_C;
            case BOTAO_D: Serial.println("O Professor apertou a opcao 'D'"); return BOTAO_D;
        }
    }
    return BOTAO_INVALIDO; // transição pressionado->solto não gera evento
}
