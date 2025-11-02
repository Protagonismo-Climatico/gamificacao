#include <Wire.h>
#include "Adafruit_LiquidCrystal.h"
#include "util.h"
#include "jogador.h"
#include "professor.h"
#include "jogo.h"

// ========== VARIÁVEIS GLOBAIS ==========
Adafruit_LiquidCrystal lcd(0x27);
Jogo jogo;

unsigned long t_ultima_mudanca = 0;
unsigned long t_inicio_resposta = 0;
unsigned long t_mostra_resultado = 0;
unsigned long t_placar_final = 0;

Botao botaoPressionado = BOTAO_INVALIDO;
Botao botaoAnterior = BOTAO_INVALIDO;

// ========== SETUP ==========
void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    
    jogo.professor = Professor('P', PROFESSOR);
    
    jogo.jogador[0] = Jogador('A', PLAYER_A);
    jogo.jogador[1] = Jogador('B', PLAYER_B);
    jogo.jogador[2] = Jogador('C', PLAYER_C);
    jogo.jogador[3] = Jogador('D', PLAYER_D);
    jogo.jogador[4] = Jogador('E', PLAYER_E);
    
    jogo.reiniciar_jogadores();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bem vindo ao");
    lcd.setCursor(0, 1);
    lcd.print("Futuro Quizz!");
    delay(2000);
}

// ========== LOOP PRINCIPAL ==========
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
                    jogo.iniciar_jogo();
                    jogo.estado_atual = LCD_DEF_RESPOSTA;
                } else if (botaoPressionado == BOTAO_B) {
                    Serial.println("Finalizar jogo pressionado.");
                    jogo.estado_atual = ACAO_ENCERRAR_JOGO;
                }
                break;

            case LCD_DEF_RESPOSTA:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Qual a resposta?");
                lcd.setCursor(0, 1);
                lcd.print("A / B / C / D");
                jogo.estado_atual = ACAO_DEF_RESPOSTA;
                break;

            case ACAO_DEF_RESPOSTA:
                if (botaoPressionado != botaoAnterior) {
                    botaoAnterior = botaoPressionado;
                    
                    if (botaoPressionado != BOTAO_INVALIDO) {
                        jogo.definir_resposta_certa(botaoPressionado);
                        jogo.estado_atual = LCD_AGUARDAR_RESPOSTAS;
                    }
                }
                break;

            case LCD_AGUARDAR_RESPOSTAS:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Aguardando...");
                lcd.setCursor(0, 1);
                lcd.print("Jogadores");
                
                jogo.redefinir_respostas_jogadores();
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
                    
                    int i = jogo.jogador_atual_resultado;
                    bool acertou = (jogo.jogador[i].obterResposta() == jogo.resposta_certa);
                    
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Jogador ");
                    lcd.print(jogo.jogador[i].obterNome());
                    
                    lcd.setCursor(0, 1);
                    if (acertou) {
                        lcd.print("Acertou! ");
                    } else {
                        lcd.print("Errou!   ");
                    }
                    lcd.print("Pts:");
                    lcd.print(jogo.jogador[i].obterPontuacao());
                }
                
                jogo.estado_atual = ACAO_MOSTRAR_RESULTADOS;
                break;

            case ACAO_MOSTRAR_RESULTADOS:
                if (millis() - t_mostra_resultado >= 500) {
                    jogo.jogador_atual_resultado++;
                    
                    if (jogo.jogador_atual_resultado >= MAX_JOGADORES) {
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
                }
                break;

            case LCD_PLACAR_FINAL:
                jogo.ordenar_jogadores_por_pontuacao();
                
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("TOP 3:");
                lcd.setCursor(0, 1);
                
                for (int i = 0; i < 3 && i < MAX_JOGADORES; i++) {
                    lcd.print(jogo.jogador[i].obterNome());
                    lcd.print(":");
                    lcd.print(jogo.jogador[i].obterPontuacao());
                    if (i < 2) lcd.print(" ");
                }
                
                t_placar_final = millis();
                jogo.estado_atual = ACAO_PLACAR_FINAL;
                break;

            case ACAO_PLACAR_FINAL:
                if (millis() - t_placar_final >= 10000) {
                    jogo.estado_atual = ACAO_ENCERRAR_JOGO;
                }
                break;

            case ACAO_ENCERRAR_JOGO:
                Serial.println("Jogo encerrado.");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Jogo");
                lcd.setCursor(0, 1);
                lcd.print("Encerrado!");
                delay(2000);
                
                jogo.round_atual = 0;
                jogo.estado_atual = LCD_MENU_INICIAL;
                break;
        }
    }
}