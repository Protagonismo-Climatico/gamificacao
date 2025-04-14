#include "jogo.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t reset_leds;
uint8_t iniciar_rodada;
uint8_t finalizar_rodada;

Jogo jogo(3);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setup completed");

  jogo.professor = Professor('P', PROFESSOR);
  jogo.jogador[0] = Jogador('A', PLAYER_A);
  jogo.jogador[1] = Jogador('B', PLAYER_B);
  jogo.jogador[2] = Jogador('C', PLAYER_C);
  jogo.jogador[3] = Jogador('D', PLAYER_D);
  jogo.jogador[4] = Jogador('E', PLAYER_E);
  jogo.jogador[5] = Jogador('F', PLAYER_F);

  iniciar_rodada = 0;
  finalizar_rodada = 0;
  reset_leds = 1;

  jogo.reiniciar_jogadores();

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setup finalizado!");
}

void loop() {
  Serial.print(jogo.jogador[0].pontuacao);

  while (jogo.iniciar_jogo) {
    Serial.print("Jogo Iniciado!");
    jogo.definir_resposta_certa();
    jogo.verificar_botoes_jogadores();
    jogo.pontuar_jogadores();
    jogo.redefinir_respostas_jogadores();

    Serial.print(jogo.jogador[0].pontuacao);

    uint8_t index = 0;
    for (uint8_t i = 7; i < 15; i += 2) {
      lcd.setCursor(i, 4);  // Coluna, Linha
      lcd.print(jogo.jogador[index].pontuacao);
      index++;
    }
    // jogo.iniciar_jogo = 0;
  }
}
