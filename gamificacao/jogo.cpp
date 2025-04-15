#include "./jogo.h"


void Jogo::definir_resposta_certa() {
  bool continuar = true;
  uint8_t resposta_anterior = this->resposta_certa;
  uint8_t botao_pressionado = Util::lerBotao(PROFESSOR, 1, 0b11111111);

  while (continuar) {
    if (botao_pressionado == BOTAO_A || botao_pressionado == BOTAO_B || botao_pressionado == BOTAO_C || botao_pressionado == BOTAO_D) {
      this->resposta_certa = botao_pressionado;
      continuar = false;
    }
    botao_pressionado = this->professor.verificarBotaoPressionado();
  }
}

void Jogo::finalizarRodada() {
  this->resposta_certa = 0x0;
  if (this->rodadas_restantes <= 0) {
    finalizarJogo();
  }
}

void Jogo::redefinir_respostas_jogadores() {
  for (int i = 0; i < MAX_JOGADORES; i++) {
    this->jogador[i].definirResposta(0x0);
  }
}

void Jogo::finalizarJogo() {
  Serial.print("Acabou o jogo!");
  this->ativo = false;
}


void Jogo::reiniciar_jogadores() {
  for (int i = 0; i < MAX_JOGADORES; i++) {
    jogador[i].reiniciar_jogador();
  }
}

void Jogo::verificar_botoes_jogadores() {
  bool continuar = true;

  while (continuar) {
    for (int i = 0; i < MAX_JOGADORES; i++) {
      this->jogador[i].verificarBotaoPressionado();
    }
    if (this->jogador[0].obterResposta()) {
      continuar = false;
    }
    // TODO tempo de resposta dos usuarios
  }
}

void Jogo::pontuar_jogadores() {
  for (uint8_t i = 0; i < MAX_JOGADORES; i++) {
    if (this->jogador[i].obterResposta() == this->resposta_certa) {
      this->jogador[i].marcar_ponto(1);
    }
  }
}

void Jogo::iniciar_jogo() {
  this->ativo = true;
}