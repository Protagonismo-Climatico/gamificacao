#include "jogo.h"

Jogo::Jogo()
    : resposta_certa(BOTAO_INVALIDO), ativo(false), 
      estado_atual(LCD_MENU_INICIAL), 
      todos_jogadores_responderam(false), 
      tempo_esgotado(false), 
      jogador_atual_resultado(0),
      round_atual(0) {}

Botao Jogo::definir_resposta_certa(Botao resposta) {
    Serial.print("Resposta correta definida: ");
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

void Jogo::ordenar_jogadores_por_pontuacao() {
    for (int i = 0; i < MAX_JOGADORES - 1; i++) {
        for (int j = 0; j < MAX_JOGADORES - i - 1; j++) {
            if (jogador[j].obterPontuacao() < jogador[j + 1].obterPontuacao()) {
                Jogador temp = jogador[j];
                jogador[j] = jogador[j + 1];
                jogador[j + 1] = temp;
            }
        }
    }
}

void Jogo::iniciar_jogo() {
    Serial.println("Iniciou o jogo!");
    this->ativo = true;
    this->round_atual = 1;
    
    for (int i = 0; i < MAX_JOGADORES; i++) {
        jogador[i].definirPontuacao(0);
    }
}

void Jogo::finalizarJogo() {
    Serial.println("Acabou o jogo!");
    this->ativo = false;
}