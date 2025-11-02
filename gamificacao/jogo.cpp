#include "./jogo.h"

Botao Jogo::definir_resposta_certa(Botao resposta) {
  Serial.println(resposta);
  return this->resposta_certa = resposta;
}



void Jogo::redefinir_respostas_jogadores() {
  for (int i = 0; i < MAX_JOGADORES; i++) {
    this->jogador[i].definirResposta(BOTAO_INVALIDO);
  }
}

void Jogo::reiniciar_jogadores() {
  for (int i = 0; i < MAX_JOGADORES; i++) {
    jogador[i].reiniciar_jogador();
  }
}

void Jogo::verificar_botoes_jogadores() {
    this->todos_jogadores_responderam = true;
    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (jogador[i].obterResposta() == BOTAO_INVALIDO) {
            jogador[i].verificarBotaoPressionado();
            if (jogador[i].obterResposta() == BOTAO_INVALIDO) {
                this->todos_jogadores_responderam = false;
            }
        }
    }
}

void Jogo::pontuar_jogadores(Botao resposta, uint8_t pontos) {
  for (uint8_t i = 0; i < MAX_JOGADORES; i++) {
    if (this->jogador[i].obterResposta() == resposta) {
      this->jogador[i].marcar_ponto(pontos);
    }
  }
}

void Jogo::iniciar_jogo() {
  Serial.print("Iniciou o jogo!");
  this->ativo = true;
}

void Jogo::finalizarJogo() {
  Serial.print("Acabou o jogo!");
  this->ativo = false;
}