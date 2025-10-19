#include "jogador.h"

char Jogador::obterNome() {
  return this->nome_;
}

uint8_t Jogador::obterPontuacao() {
  return this->pontuacao_;
}


uint8_t Jogador::obterResposta() {
  return this->resposta_;
}

void Jogador::definirResposta(uint8_t resposta) {
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

}

void Jogador::marcar_ponto(uint8_t ponto) {
  uint8_t pontuacao = this->obterPontuacao() + ponto;
  this->definirPontuacao(ponto);
}

void Jogador::reiniciar_jogador() {
  Util::escreverDado(this->obterEndereco(), 0b11111111);
}