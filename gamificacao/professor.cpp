#include "professor.h"

uint8_t Professor::obterEndereco(){
    return this->endereco_;
}
char Professor::obterNome(){
    return this->nome_;
}

Botao Professor::verificarBotaoPressionado() {
    uint8_t botao_pressionado = Util::lerBotao(this->obterEndereco(), 1, MASCARA_BOTOES);
    
    switch (botao_pressionado) {
        case BOTAO_A:  return BOTAO_A;
        case BOTAO_B: return BOTAO_B;
        case BOTAO_C:  return BOTAO_C;
        case BOTAO_D:  return BOTAO_D;
    }

    return BOTAO_INVALIDO;
}
