#include "jogo.h"
#include "Adafruit_LiquidCrystal.h"

Adafruit_LiquidCrystal lcd(0x27);

unsigned long tempo_segundos = 0;

Jogo jogo(3);
unsigned long tempo_anterior = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Configurado.");

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
  lcd.print("Jogo iniciado!");
}

void loop() {
  if (jogo.ativo) {
    Serial.print("Definindo resposta...");
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Gerando");
    lcd.setCursor(3, 1);
    lcd.print("Pergunta...");
    Botao resposta_certa = jogo.definir_resposta_certa();



    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando em...");
    lcd.setCursor(0, 4);

    for (uint8_t i = 3; i > 0; i--) {
      lcd.setCursor(5, 4);
      lcd.print(i);
      lcd.print(" segundos");
      delay(3 * 1000);
    }
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Vai!");



    jogo.verificar_botoes_jogadores();
    jogo.pontuar_jogadores(resposta_certa, 1);
    jogo.redefinir_respostas_jogadores();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PLA|");
    lcd.setCursor(0, 1);
    lcd.print("CAR|");

    uint8_t index_jogador = 0;
    for (uint8_t i = 5; i <= 15 && index_jogador < 6; i += 2) {
      lcd.setCursor(i, 0);  // Coluna, Linha
      lcd.print(jogo.jogador[index_jogador].obterNome());
      lcd.setCursor(i, 1);  // Coluna, Linha
      lcd.print(jogo.jogador[index_jogador].obterPontuacao());
      index_jogador++;
    }
    jogo.finalizarJogo();
  }
  unsigned long tempo_atual = millis();
  Botao botao_pressionado = jogo.professor.verificarBotaoPressionado();

  if (botao_pressionado == BOTAO_A && tempo_atual - tempo_anterior >= 1000) {
    tempo_anterior = tempo_atual;
    tempo_segundos++;
    if (tempo_segundos >= 2) {
      jogo.iniciar_jogo();
      tempo_segundos = 0;
    }
  }
}
