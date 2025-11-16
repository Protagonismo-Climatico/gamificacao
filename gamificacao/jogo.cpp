#include "./jogo.h"

Botao Jogo::definir_resposta_certa(Botao resposta) {
  Serial.println(resposta);
  return this->resposta_certa = resposta;
}

void Jogo::redefinir_respostas_jogadores() {
  for (int i = 0; i < NUM_JOGADORES; i++) {
    this->jogador[i].definirResposta(BOTAO_INVALIDO);
  }
}

void Jogo::reiniciar_jogadores() {
  for (int i = 0; i < NUM_JOGADORES; i++) {
    jogador[i].definirPontuacao(0);
    
  }
}

void Jogo::verificar_botoes_jogadores() {
    this->todos_jogadores_responderam = true;
    for (int i = 0; i < NUM_JOGADORES; i++) {
        if (jogador[i].obterResposta() == BOTAO_INVALIDO) {
            jogador[i].verificarBotaoPressionado();
            if (jogador[i].obterResposta() == BOTAO_INVALIDO) {
                this->todos_jogadores_responderam = false;
            }
        }
    }
}

void Jogo::pontuar_jogadores(Botao resposta, uint8_t pontos) {
  for (uint8_t i = 0; i < NUM_JOGADORES; i++) {
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


/*Inicio de refatoração*/

void Jogo::iniciarLCDS() {  
  for (int canal = 0; canal < NUM_CONTROLES; canal++) {
    MP.selectChannel(canal);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bem vindo ao");
    lcd.setCursor(0, 1);
    lcd.print("Futuro Quizz!");
    Serial.println(canal);
  }
  MP.selectChannel(0);
}

void Jogo::verificarBotoesJogadores() {
  this->todos_jogadores_responderam = true;

  for (int canal = 0; canal < NUM_JOGADORES; canal++) {
    MP.selectChannel(canal + 1);
    this->jogador[canal].verificarBotaoPressionado(); 
    if (this->jogador[canal].obterResposta() == BOTAO_INVALIDO) {
      this->todos_jogadores_responderam = false;
    }
  }
  MP.selectChannel(0);
}

void Jogo::verificarExistenciaResposta() {
  Botao resposta;

  for (int canal = 0; canal < NUM_JOGADORES; canal++) {
    MP.selectChannel(canal + 1);
    resposta = this->jogador[canal].obterResposta();
    if (resposta != BOTAO_INVALIDO) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sua resposta:");
      lcd.setCursor(0, 1);
      lcd.print("Letra ");

      if(resposta == BOTAO_A){
      lcd.print("A");
      }else if(resposta == BOTAO_B){
        lcd.print("B");
      }else if(resposta == BOTAO_C){
        lcd.print("C");
      }else if(resposta == BOTAO_D){
        lcd.print("D");
      }
    }
  }
  MP.selectChannel(0);
}


void Jogo::iniciarPcfs(){
  for (int canal = 0; canal < NUM_CONTROLES; canal++) { 
    MP.selectChannel(canal);
    Util::escreverDado(PARTICIPANTE, 0b11111111);
  }
  MP.selectChannel(0);
}

void Jogo::lcdRespondam(){
  for (int canal = 1; canal <= NUM_JOGADORES; canal++) {
    MP.selectChannel(canal);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Qual a resposta?");
    lcd.setCursor(0, 1);
    lcd.print("A/B/C/D");
    Serial.println(canal);
  }
  MP.selectChannel(0);
}
void Jogo::lcdEsperem(){
  for (int canal = 1; canal <= NUM_CONTROLES; canal++) {
    MP.selectChannel(canal);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Espere o");
    lcd.setCursor(0, 1);
    lcd.print("professor");
  }
  MP.selectChannel(0);
}

void Jogo::lcdAguardarJogadores(){
  MP.selectChannel(0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aguardando");
  lcd.setCursor(0, 1);
  lcd.print("Jogadores...");
}

void Jogo::lcdDefinirResposta(){
  MP.selectChannel(0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Definir Resposta:");
  lcd.setCursor(0, 1);
  lcd.print("A/B/C/D");
}

void Jogo::lcdPlacarFinal(){
  for (int canal = 0; canal < NUM_CONTROLES; canal++) {
    MP.selectChannel(canal);

    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("PLA|");
    lcd.setCursor(0, 1);
    lcd.print("CAR|");
    
    uint8_t index_jogador = 0;
    for (uint8_t i = 5; i <= 15 && index_jogador < NUM_JOGADORES; i += 2)
    {
      lcd.setCursor(i, 0); 
      lcd.print(this->jogador[index_jogador].obterNome());
      lcd.setCursor(i, 1);
      lcd.print(this->jogador[index_jogador].obterPontuacao());
      index_jogador++;
    }
  }
  MP.selectChannel(0);

}


void Jogo::mostrarAcertos(){

  for (uint8_t i = 0; i < NUM_JOGADORES; i++){
    bool acertou = (this->jogador[i].obterResposta() == this->resposta_certa);
    for (int canal = 0; canal < NUM_CONTROLES; canal++) {
      MP.selectChannel(canal);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Jogador ");
      lcd.print(this->jogador[i].obterNome());
      lcd.setCursor(0, 1);
      if (acertou) {
        lcd.print("Acertou! ");
      } else {
        lcd.print("Errou!   ");
      }
      lcd.print("Pts:");
      lcd.print(this->jogador[i].obterPontuacao());
      delay(1000);
      }
    }
  MP.selectChannel(0);
}
