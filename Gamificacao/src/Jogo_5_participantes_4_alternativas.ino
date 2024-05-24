#include "Adafruit_LiquidCrystal.h"

#define ENDERECO_PCF8574_PLAYER_A 0x20 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_B 0x21 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_C 0x22 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_D 0x23 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_E 0x24 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_0 0x25 // Endereco I2C para o PCF8574

uint8_t byte_player_0;
uint8_t byte_player_A;
uint8_t byte_player_B;
uint8_t byte_player_C;
uint8_t byte_player_D;
uint8_t byte_player_E;

uint8_t botoes_player_0;
uint8_t botoes_player_A;
uint8_t botoes_player_B;
uint8_t botoes_player_C;
uint8_t botoes_player_D;
uint8_t botoes_player_E;

uint8_t resposta_player_A;
uint8_t resposta_player_B;
uint8_t resposta_player_C;
uint8_t resposta_player_D;
uint8_t resposta_player_E;

uint8_t pontuacao_player_A;
uint8_t pontuacao_player_B;
uint8_t pontuacao_player_C;
uint8_t pontuacao_player_D;
uint8_t pontuacao_player_E;

uint8_t reset_leds;
uint8_t iniciar_rodada;
uint8_t finalizar_rodada;
uint8_t resposta_certa;

#define botao_A 0b111110
#define botao_B 0b111101
#define botao_C 0b111011
#define botao_D 0b110111
#define botao_INICIAR 0b011111
#define botao_FINALIZAR 0b101111

// Inicializa o display no endereco 0x27
Adafruit_LiquidCrystal lcd(0x27); // O endereco de fabrica do LCD geralmente é 0x27 ou 0x7F

void setup()
{
  // Resetando os leds
  Wire.begin();       // Inicializa a comunicacao i2c
  Serial.begin(9600); // start serial for output
  // Escrevendo no LCD os caracteres que nao se alteram
  lcd.begin(16, 2);
  // Visor do LCD: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
  //               0x40 0x41 0x42 0x43 0x44 0x45 0x46 0x47 0x48 0x49 0x4A 0x4B 0x4C 0x4D 0x4E 0x4F
  lcd.setBacklight(HIGH); // Luz de fundo acesa
  lcd.setCursor(0, 0);
  //         XXXXXXXXXXXXXXXX
  lcd.print("PLAYER A B C D E");
  lcd.setCursor(0, 4);
  lcd.print("POINTS 0 0 0 0 0");
  Serial.println("Setup");
  reset_leds = 1; // Variavel para acionar o reset dos Leds
  iniciar_rodada = 0;
  finalizar_rodada = 0;
  pontuacao_player_A = 0;
  pontuacao_player_B = 0;
  pontuacao_player_C = 0;
  pontuacao_player_D = 0;
  pontuacao_player_E = 0;
}

void writeData(uint8_t device, uint8_t byte)
{
  Wire.beginTransmission(device);
  Wire.write(byte);       // Envia o byte ao dispositivo
  Wire.endTransmission(); // Finaliza a comunicacao com o dispositivo i2c
}

uint8_t readData(uint8_t device, uint8_t count, uint8_t mask)
{
  Wire.requestFrom(device, count); // Solicita o estado das portas do dispositivo
  uint8_t byte = Wire.read();      // Salva na variavel o byte enviado pelo dispositivo
  byte = byte & mask;

  return byte;
}

uint8_t verify_buttons_players(uint8_t device)
{
  uint8_t botoes_player = readData(device, 1, 0b00001111);
  uint8_t resposta_player = botoes_player;

  Serial.println(botoes_player);

  switch (botoes_player)
  {
  case botao_A << 2:
    writeData(device, 0b11101111);
    Serial.println("Jogador apertou a opcao 'A'"); // Imprime no terminal
    break;

  case botao_B << 2:
    writeData(device, 0b11011111);
    Serial.println("Jogador apertou a opcao 'B'"); // Imprime no terminal
    break;
  case botao_C << 2:
    writeData(device, 0b10111111);
    Serial.println("Jogador apertou a opcao 'C'"); // Imprime no terminal
    break;
  case botao_D << 2:
    writeData(device, 0b01111111);
    Serial.println("Jogador apertou a opcao 'D'"); // Imprime no terminal
    break;

  default:
    break;
  }

  return resposta_player;
}

uint8_t verify_answer_players(uint8_t answer_player, uint8_t answer_correct)
{
  if (answer_player == answer_correct)
  {
    return (uint8_t)1;
  }
  else
  {
    return (uint8_t)0;
  }
}

void loop()
{
  if (reset_leds == 1) // Se o jogo foi resetado
  {
    Serial.println("Resetando players");
    // Resetando players

    writeData(ENDERECO_PCF8574_PLAYER_0, 0b11111111);
    writeData(ENDERECO_PCF8574_PLAYER_A, 0b11111111);
    writeData(ENDERECO_PCF8574_PLAYER_B, 0b11111111);
    writeData(ENDERECO_PCF8574_PLAYER_C, 0b11111111);
    writeData(ENDERECO_PCF8574_PLAYER_D, 0b11111111);
    writeData(ENDERECO_PCF8574_PLAYER_E, 0b11111111);

    reset_leds = 0;
    Serial.println("Playes Resetados.");
  }
  // Player 0, o que define qual eh a alternativa correta
  botoes_player_0 = readData(ENDERECO_PCF8574_PLAYER_0, 1, 0b00111111);


  switch (botoes_player_0)
  {
  case botao_A:
    Serial.println("Apertou o botao A");
    writeData(ENDERECO_PCF8574_PLAYER_0, 0b01111111);
    resposta_certa = byte_player_0 & 0b00001111;
    break;
  case botao_B:
    Serial.println("Apertou o botao B");
    writeData(ENDERECO_PCF8574_PLAYER_0, 0b01111111);
    resposta_certa = byte_player_0 & 0b00001111;
    break;
  case botao_C:
    Serial.println("Apertou o botao C");
    writeData(ENDERECO_PCF8574_PLAYER_0, 0b10111111);
    resposta_certa = byte_player_0 & 0b00001111;
    break;
  case botao_D:
    Serial.println("Apertou o botao D");
    writeData(ENDERECO_PCF8574_PLAYER_0, 0b01111111);
    resposta_certa = byte_player_0 & 0b00001111;
    break;
  case botao_INICIAR:
    writeData(ENDERECO_PCF8574_PLAYER_0, 0b11111111);
    iniciar_rodada = 1;
    Serial.println("Iniciar rodada"); // Imprime no terminal
    break;

  case botao_FINALIZAR:
    writeData(ENDERECO_PCF8574_PLAYER_0, 0b10111111);
    iniciar_rodada = 0;
    finalizar_rodada = 1;
    break;
  default:
    break;
  }

  // Inicia a leiura periodica dos botoes dos jogadores
  if (iniciar_rodada == 1)
  {
    botoes_player_A = verify_buttons_players(ENDERECO_PCF8574_PLAYER_A);
    resposta_player_A = botoes_player_A;
    botoes_player_B = verify_buttons_players(ENDERECO_PCF8574_PLAYER_B);
    resposta_player_B = botoes_player_B;
    botoes_player_C = verify_buttons_players(ENDERECO_PCF8574_PLAYER_C);
    resposta_player_C = botoes_player_C;
    botoes_player_D = verify_buttons_players(ENDERECO_PCF8574_PLAYER_D);
    resposta_player_D = botoes_player_D;
    botoes_player_E = verify_buttons_players(ENDERECO_PCF8574_PLAYER_E);
    resposta_player_E = botoes_player_E;
  }
  if (finalizar_rodada == 1)
  {
    // ***********************************************************************************************************
    // Visor do LCD: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
    //               0x40 0x41 0x42 0x43 0x44 0x45 0x46 0x47 0x48 0x49 0x4A 0x4B 0x4C 0x4D 0x4E 0x4F
    //
    //              ("P    L    A    Y    E    R         A         B         C          D         E");
    //              ("P    O    I    N    T    S         0         0         0          0         0");
    // ***********************************************************************************************************

    // pontuacao_player_A += verify_answer_players(resposta_player_A, resposta_certa);
    // pontuacao_player_B += verify_answer_players(resposta_player_B, resposta_certa);
    // pontuacao_player_C += verify_answer_players(resposta_player_C, resposta_certa);
    // pontuacao_player_D += verify_answer_players(resposta_player_D, resposta_certa);
    // pontuacao_player_E += verify_answer_players(resposta_player_E, resposta_certa);

    if (resposta_player_A == resposta_certa)
    {

      pontuacao_player_A += 1;
      lcd.setCursor(7, 4); // Coluna, Linha
      lcd.print(pontuacao_player_A);
      resposta_player_A = 0;
    }
    if (resposta_player_B == resposta_certa)
    {

      pontuacao_player_B += 1;
      lcd.setCursor(9, 4); // Coluna, Linha
      lcd.print(pontuacao_player_B);
      resposta_player_B = 0;
    }
    if (resposta_player_C == resposta_certa)
    {

      pontuacao_player_C += 1;
      lcd.setCursor(11, 4); // Coluna, Linha
      lcd.print(pontuacao_player_C);
      resposta_player_C = 0;
    }
    if (resposta_player_D == resposta_certa)
    {

      pontuacao_player_D += 1;
      lcd.setCursor(13, 4); // Coluna, Linha
      lcd.print(pontuacao_player_D);
      resposta_player_D = 0;
    }
    if (resposta_player_E == resposta_certa)
    {

      pontuacao_player_E += 1;
      lcd.setCursor(15, 4); // Coluna, Linha
      lcd.print(pontuacao_player_E);
      resposta_player_E = 0;
    }
    reset_leds = 1;
    finalizar_rodada = 0;
  }
}