#include "jogo.h"
#include "Adafruit_LiquidCrystal.h"

Adafruit_LiquidCrystal lcd(0x27);

uint8_t reset_leds;
uint8_t iniciar_rodada;
uint8_t finalizar_rodada;

Jogo jogo(3);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
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
  jogo.iniciar_jogo();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jogo iniciado!");
}

void loop()
{

  if (jogo.ativo)
  {
    Serial.print("Definindo resposta...");
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Prestem atencao");
    jogo.definir_resposta_certa();
    jogo.verificar_botoes_jogadores();
    jogo.pontuar_jogadores();
    jogo.redefinir_respostas_jogadores();

    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("PLA|");
    lcd.setCursor(0, 1);
    lcd.print("CAR|");
    
    uint8_t index_jogador = 0;
    for (uint8_t i = 5; i <= 15 && index_jogador < 6; i += 2)
    {
      lcd.setCursor(i, 0); // Coluna, Linha
      lcd.print(jogo.jogador[index_jogador].nome);
      lcd.setCursor(i, 1); // Coluna, Linha
      lcd.print(jogo.jogador[index_jogador].pontuacao);
      index_jogador++;
    }
    jogo.ativo = false;
  }
}
