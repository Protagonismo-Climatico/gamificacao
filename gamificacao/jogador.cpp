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
  this->tempo_anterior_;
}

void Jogador::definirTempoAnterior(unsigned long tempo) {
  this->tempo_anterior_ = tempo;
}

void Jogador::definirPontuacao(uint8_t ponto) {
  this->pontuacao_ = ponto;
}

void Jogador::verificarBotaoPressionado() {
  uint8_t botao_pressionado_atual = Util::lerBotao(this->obterEndereco(), 1, 0b11111111);

  if (botao_pressionado_atual != BOTAO_INVALIDO && millis() - this->obterTempoAnterior() > 50) {
    this->definirTempoAnterior(millis());
    switch (botao_pressionado_atual) {
      case BOTAO_A:
        Serial.println("O jogador apertou a opcao 'A'");
        this->definirResposta(BOTAO_A);
        break;
      case BOTAO_B:
        Serial.println("O jogador apertou a opcao 'B'");
        this->definirResposta(BOTAO_B);
        break;
      case BOTAO_C:
        Serial.println("O jogador apertou a opcao 'C'");
        this->definirResposta(BOTAO_C);
        break;
      case BOTAO_D:
        Serial.println("O jogador apertou a opcao 'D'");
        this->definirResposta(BOTAO_D);
        break;
      default:
        this->definirResposta(BOTAO_INVALIDO);
        break;
    }
  }
}

void Jogador::marcar_ponto(uint8_t ponto) {
  uint8_t pontuacao = this->obterPontuacao() + ponto;
  this->definirPontuacao(ponto);
}

void Jogador::reiniciar_jogador() {
  Util::escreverDado(this->obterEndereco(), 0b11111111);
  this->definirResposta(BOTAO_INVALIDO);
}