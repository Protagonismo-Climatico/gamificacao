#include "jogo.h"
#include <LiquidCrystal_I2C.h>
#include "TCA9548.h"

LiquidCrystal_I2C lcd(LCD, 16, 2);
TCA9548 MP(0x70);

Jogo jogo;
unsigned long t_ultima_mudanca = 0;    
unsigned long t_inicio_resposta = 0;
unsigned long t_mostra_resultado = 0;
unsigned long t_placar_final = 0;


Botao botaoPressionado = BOTAO_INVALIDO;
Botao botaoAnterior = BOTAO_INVALIDO;

void setup() {    
  Serial.begin(9600);
  Serial.println("🔹 Iniciando setup...");

  Wire.begin();
  Serial.println("🔹 Wire iniciado.");

  if (!MP.begin()) {
    Serial.println("⚠ Erro ao inicializar o multiplexador!");
  } else {
    Serial.println("Multiplexador iniciado!");
  }
  
  jogo.professor = Professor('P', PARTICIPANTE);
  jogo.jogador[0] = Jogador('A', PARTICIPANTE);
  jogo.jogador[1] = Jogador('B', PARTICIPANTE);

  jogo.iniciarPcfs();
  jogo.iniciarLCDS();
}

void loop() {
   botaoPressionado = jogo.professor.verificarBotaoPressionado();

  if (millis() - t_ultima_mudanca > DEBOUNCE) {
    t_ultima_mudanca = millis();
    switch (jogo.estado_atual) {
      case LCD_MENU_INICIAL:
        MP.selectChannel(0);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("A - Iniciar");
        lcd.setCursor(0, 1);
        lcd.print("B - Finalizar");
        jogo.estado_atual = ACAO_MENU_INICIAL;
        jogo.lcdEsperem();
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
        jogo.lcdDefinirResposta();
        jogo.lcdEsperem();
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
        jogo.lcdAguardarJogadores();
        jogo.lcdRespondam();
        jogo.redefinir_respostas_jogadores();

        jogo.estado_atual = ACAO_AGUARDAR_RESPOSTAS;
      break;

      case ACAO_AGUARDAR_RESPOSTAS:
        if (t_inicio_resposta == 0) {
            t_inicio_resposta = millis();
        }

        jogo.verificarBotoesJogadores();
        jogo.verificarExistenciaResposta();

        if (millis() - t_inicio_resposta >= TEMPO_LIMITE) {
            jogo.tempo_esgotado = true;
        }

        if (jogo.todos_jogadores_responderam || jogo.tempo_esgotado) {
            jogo.pontuar_jogadores(jogo.resposta_certa, 1);
            jogo.jogador_atual_resultado = 0;
            jogo.estado_atual = LCD_MOSTRAR_RESULTADOS;
            t_inicio_resposta = 0;
            t_mostra_resultado = 0;
            jogo.tempo_esgotado = false;
        }
        break;

        case LCD_MOSTRAR_RESULTADOS:
          if (t_mostra_resultado == 0) {
              t_mostra_resultado = millis();
              jogo.mostrarAcertos();
          }
          
          jogo.estado_atual = ACAO_MOSTRAR_RESULTADOS;
          break;
        case ACAO_MOSTRAR_RESULTADOS:
          jogo.jogador_atual_resultado++;
          
          if (jogo.jogador_atual_resultado >= NUM_JOGADORES) {
            if (jogo.round_atual >= MAX_ROUNDS) {
              jogo.estado_atual = LCD_PLACAR_FINAL;
            } else {
              jogo.round_atual++;
              jogo.estado_atual = LCD_DEF_RESPOSTA;
            }
          } else {
              t_mostra_resultado = 0;
              jogo.estado_atual = LCD_MOSTRAR_RESULTADOS;
          }
          break;
          case LCD_PLACAR_FINAL:
            jogo.lcdPlacarFinal();
                
            t_placar_final = millis();
            jogo.estado_atual = ACAO_PLACAR_FINAL;
            break;
          case ACAO_PLACAR_FINAL:
            if (millis() - t_placar_final >= 10000) {
              jogo.estado_atual = ACAO_ENCERRAR_JOGO;
              }
            break;
          case ACAO_ENCERRAR_JOGO:
            for (int canal = 1; canal <= NUM_CONTROLES; canal++) {
              MP.selectChannel(canal);
              jogo.lcdEsperem();
            }
            delay(2000);
            jogo.round_atual = 0;
            jogo.reiniciar_jogadores();
            jogo.estado_atual = LCD_MENU_INICIAL;
            break;
            
     
    }
  }
}