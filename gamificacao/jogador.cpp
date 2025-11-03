#include "jogador.h"

char Jogador::obterNome() {
  return this->nome_;
}

uint8_t Jogador::obterPontuacao() {
  return this->pontuacao_;
}


Botao Jogador::obterResposta() {
  return this->resposta_;
}

void Jogador::definirResposta(Botao resposta) {
  this->resposta_ = resposta;
}
uint8_t Jogador::obterEndereco() {
  return this->endereco_;
}

unsigned long Jogador::obterTempoAnterior() {
  return this->tempo_anterior_;
}

void Jogador::definirTempoAnterior(unsigned long tempo) {
  this->tempo_anterior_ = tempo;
}

void Jogador::definirPontuacao(uint8_t ponto) {
  this->pontuacao_ = ponto;
}

void Jogador::verificarBotaoPressionado() {
    uint8_t botao = Util::lerBotao(this->obterEndereco(), 1, MASCARA_BOTOES);

    switch (botao) {
        case BOTAO_A: this->definirResposta(BOTAO_A); break;
        case BOTAO_B: this->definirResposta(BOTAO_B); break;
        case BOTAO_C: this->definirResposta(BOTAO_C); break;
        case BOTAO_D: this->definirResposta(BOTAO_D); break;
        default: break; 
    }
}


void Jogador::marcar_ponto(uint8_t ponto) {
  uint8_t pontuacao = this->obterPontuacao() + ponto;
  this->definirPontuacao(pontuacao);
}

void Jogador::reiniciar_jogador() {
  Util::escreverDado(this->obterEndereco(), 0b11111111);
}