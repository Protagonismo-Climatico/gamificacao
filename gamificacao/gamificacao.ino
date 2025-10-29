#include "jogo.h"
#include "Adafruit_LiquidCrystal.h"

Adafruit_LiquidCrystal lcd(0x27);
Jogo jogo;
unsigned long t_ultima_mudanca = 0;    
unsigned long t_inicio_resposta = 0;

Botao botaoPressionado = BOTAO_INVALIDO;
Botao botaoAnterior = BOTAO_INVALIDO;



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  jogo.professor = Professor('P', PROFESSOR);
  jogo.jogador[0] = Jogador('A', PLAYER_A);
  jogo.jogador[1] = Jogador('B', PLAYER_B);
  jogo.jogador[2] = Jogador('C', PLAYER_C);
  jogo.jogador[3] = Jogador('D', PLAYER_D);
  jogo.jogador[4] = Jogador('E', PLAYER_E);
  jogo.jogador[5] = Jogador('F', PLAYER_F);
  
  jogo.reiniciar_jogadores();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Configurado.");
}

void loop() {
   botaoPressionado = jogo.professor.verificarBotaoPressionado();

  if (millis() - t_ultima_mudanca > DEBOUNCE) {
    t_ultima_mudanca = millis();
    switch (jogo.estado_atual) {
      case LCD_MENU_INICIAL:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("A - Iniciar");
        lcd.setCursor(0, 1);
        lcd.print("B - Finalizar");
        jogo.estado_atual = ACAO_MENU_INICIAL;
      break;

      case ACAO_MENU_INICIAL:
        if (botaoPressionado == BOTAO_A) {
          Serial.println("Iniciar jogo pressionado.");
          botaoAnterior = BOTAO_A;
          jogo.estado_atual = LCD_DEF_RESPOSTA;
        }else if (botaoPressionado == BOTAO_B) {
          Serial.println("Finalizar jogo pressionado.");
          jogo.estado_atual = ACAO_ENCERRAR_JOGO;
        }
      break;

      case LCD_DEF_RESPOSTA:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Definir Resposta:");
        lcd.setCursor(0, 1);
        lcd.print("A/B/C/D");
        jogo.estado_atual = ACAO_DEF_RESPOSTA;
      break;

      case ACAO_DEF_RESPOSTA:
        if (botaoPressionado != botaoAnterior) {
          botaoAnterior = botaoPressionado;
          if(botaoPressionado != BOTAO_INVALIDO){
            jogo.definir_resposta_certa(botaoPressionado);
            Serial.print("Resposta correta definida: ");
            jogo.estado_atual = LCD_AGUARDAR_RESPOSTAS;
          }
        }
      break;
      case LCD_AGUARDAR_RESPOSTAS:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Aguardando jog...");
        jogo.estado_atual = ACAO_AGUARDAR_RESPOSTAS;
      break;
      case ACAO_AGUARDAR_RESPOSTAS:
        if (t_inicio_resposta == 0) {
         t_inicio_resposta = millis();
        }

        jogo.verificar_botoes_jogadores();

        if (millis() - t_inicio_resposta >= TEMPO_LIMITE) {
          jogo.tempo_esgotado = true;
        }

        if (jogo.todos_jogadores_responderam || jogo.tempo_esgotado) {
          jogo.estado_atual = LCD_MOSTRAR_RESULTADOS;
          t_inicio_resposta = 0;
          jogo.tempo_esgotado = false; 
        }
      break;
      case LCD_MOSTRAR_RESULTADOS:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mostrando result");
        jogo.estado_atual = ACAO_MOSTRAR_RESULTADOS;
      break;
      case ACAO_MOSTRAR_RESULTADOS:
        jogo.pontuar_jogadores(jogo.resposta_certa, 1);
        jogo.estado_atual = ACAO_ENCERRAR_JOGO;
      break;
      case ACAO_ENCERRAR_JOGO:
        Serial.println("Jogo encerrado.");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Jogo encerrado");
        jogo.finalizarJogo();
        jogo.estado_atual = LCD_MENU_INICIAL;
      break;
    }
  }
}