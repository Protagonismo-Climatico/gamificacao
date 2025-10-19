#ifndef JOGO_H
#define JOGO_H
#include "./jogador.h"
#include "./professor.h"
#include "./header.h"
#include "util.h"
class Jogo {
public:
  Botao resposta_certa;
  bool ativo;
  Jogador jogador[MAX_JOGADORES];
  Professor professor;
  EstadoJogo estado_atual;


  Jogo()
    : resposta_certa(BOTAO_INVALIDO), ativo(false), estado_atual(LCD_MENU_INICIAL) {
  }
  void iniciar_jogo();
  void finalizarJogo();
  Botao definir_resposta_certa();
  void verificar_botoes_jogadores();
  void reiniciar_jogadores();
  void pontuar_jogadores(Botao, uint8_t);
  void redefinir_respostas_jogadores();
};

#endif