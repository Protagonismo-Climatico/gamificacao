#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define ENDERECO_PCF8574_PLAYER_A 0x20  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_B 0x21  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_C 0x22  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_D 0x23  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_E 0x24  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_0 0x25  // Endereco I2C para o PCF8574

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


//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);  // O endereco de fabrica do LCD geralmente é 0x27 ou 0x7F

void setup() {
  // Resetando os leds
  Wire.begin();        // Inicializa a comunicacao i2c
  Serial.begin(9600);  // start serial for output
  // Escrevendo no LCD os caracteres que nao se alteram
  lcd.init();
  // Visor do LCD: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
  //               0x40 0x41 0x42 0x43 0x44 0x45 0x46 0x47 0x48 0x49 0x4A 0x4B 0x4C 0x4D 0x4E 0x4F
  lcd.setBacklight(HIGH);  // Luz de fundo acesa
  lcd.setCursor(0, 0);
  //         XXXXXXXXXXXXXXXX
  lcd.print("PLAYER A B C D E");
  lcd.setCursor(0, 4);
  lcd.print("POINTS 0 0 0 0 0");
  Serial.println("Setup");
  reset_leds = 1;  // Variavel para acionar o reset dos Leds
  iniciar_rodada = 0;
  finalizar_rodada = 0;
  pontuacao_player_A = 0;
  pontuacao_player_B = 0;
  pontuacao_player_C = 0;
  pontuacao_player_D = 0;
  pontuacao_player_E = 0;
}

void loop() {
  if (reset_leds == 1)  // Se o jogo foi resetado
  {
    Serial.println("Resetando players");
    //Resetando players
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_0);
    Wire.write(0b11111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_A);
    Wire.write(0b11111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_B);
    Wire.write(0b11111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_C);
    Wire.write(0b11111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_D);
    Wire.write(0b11111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_E);
    Wire.write(0b11111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();
    reset_leds = 0;
    Serial.println("playes resetados");
  }
  // Player 0, o que define qual eh a alternativa correta
  Wire.requestFrom(ENDERECO_PCF8574_PLAYER_0, 1);  // Solicita o estado das portas do dispositivo
  byte_player_0 = Wire.read();                     // Salva na variavel o byte enviado pelo dispositivo
  botoes_player_0 = byte_player_0 & 0b00111111;
  // Resposta a:
  if (botoes_player_0 == 0b111110) {
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_0);
    Wire.write(0b01111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();  // Finaliza a comunicacao com o dispositivo i2c
    resposta_certa = byte_player_0 & 0b00001111;
  }
  // Resposta b:
  if (botoes_player_0 == 0b111101) {
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_0);
    Wire.write(0b01111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();  // Finaliza a comunicacao com o dispositivo i2c
    resposta_certa = byte_player_0 & 0b00001111;
  }
  // Resposta c:
  if (botoes_player_0 == 0b111011) {
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_0);
    Wire.write(0b10111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();  // Finaliza a comunicacao com o dispositivo i2c
    resposta_certa = byte_player_0 & 0b00001111;
  }
  // Resposta d:
  if (botoes_player_0 == 0b110111) {
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_0);
    Wire.write(0b01111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();  // Finaliza a comunicacao com o dispositivo i2c
    resposta_certa = byte_player_0 & 0b00001111;
  }
  // Finaliza rodada:
  if (botoes_player_0 == 0b101111)  // Se pressionou o botao que finaliza a rodada
  {
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_0);
    Wire.write(0b10111111);  // Acende no controle do player 0 o LED que indica que a rodada foi finalizada
    Wire.endTransmission();  // Finaliza a comunicacao com o dispositivo i2c
    iniciar_rodada = 0;
    finalizar_rodada = 1;
  }
  if (botoes_player_0 == 0b011111)  // Se pressionou o botao que inicia a rodada
  {
    Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_0);
    Wire.write(0b11111111);  // Envia o byte ao dispositivo
    Wire.endTransmission();  // Finaliza a comunicacao com o dispositivo i2c
    iniciar_rodada = 1;
    Serial.println("Iniciar rodada");  // Imprime no terminal
  }

  // Inicia a leiura periodica dos botoes dos jogadores
  if (iniciar_rodada == 1) {
    // Player A
    Wire.requestFrom(ENDERECO_PCF8574_PLAYER_A, 1);  // Solicita o estado das portas do dispositivo
    byte_player_A = Wire.read();                     // Salva na variavel o byte enviado pelo dispositivo
    botoes_player_A = byte_player_A & 0b00001111;
    if (botoes_player_A == 0b1110) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_A);
      Wire.write(0b11101111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_A);                    // Imprime no terminal
      Serial.println("Jogador A apertou a opcao 'a'");  // Imprime no terminal
      resposta_player_A = botoes_player_A;
    } else if (botoes_player_A == 0b1101) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_A);
      Wire.write(0b11011111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_A);                    // Imprime no terminal
      Serial.println("Jogador A apertou a opcao 'b'");  // Imprime no terminal
      resposta_player_A = botoes_player_A;
    } else if (botoes_player_A == 0b1011) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_A);
      Wire.write(0b10111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_A);                    // Imprime no terminal
      Serial.println("Jogador A apertou a opcao 'c'");  // Imprime no terminal
      resposta_player_A = botoes_player_A;
    } else if (botoes_player_A == 0b0111) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_A);
      Wire.write(0b01111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_A);                    // Imprime no terminal
      Serial.println("Jogador A apertou a opcao 'd'");  // Imprime no terminal
      resposta_player_A = botoes_player_A;
    }
    // player 2
    Wire.requestFrom(ENDERECO_PCF8574_PLAYER_B, 1);  // Solicita o estado das portas do dispositivo
    byte_player_B = Wire.read();                     // Salva na variavel o byte enviado pelo dispositivo
    botoes_player_B = byte_player_B & 0b00001111;
    if (botoes_player_B == 0b1110) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_B);
      Wire.write(0b11101111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_B);                    // Imprime no terminal
      Serial.println("Jogador B apertou a opcao 'a'");  // Imprime no terminal
      resposta_player_B = botoes_player_B;
    } else if (botoes_player_B == 0b1101) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_B);
      Wire.write(0b11011111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_B);                    // Imprime no terminal
      Serial.println("Jogador B apertou a opcao 'b'");  // Imprime no terminal
      resposta_player_B = botoes_player_B;
    } else if (botoes_player_B == 0b1011) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_B);
      Wire.write(0b10111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_B);                    // Imprime no terminal
      Serial.println("Jogador B apertou a opcao 'c'");  // Imprime no terminal
      resposta_player_B = botoes_player_B;
    } else if (botoes_player_B == 0b0111) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_B);
      Wire.write(0b01111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_B);                    // Imprime no terminal
      Serial.println("Jogador B apertou a opcao 'd'");  // Imprime no terminal
      resposta_player_B = botoes_player_B;
    }
    // player C
    Wire.requestFrom(ENDERECO_PCF8574_PLAYER_C, 1);  // Solicita o estado das portas do dispositivo
    byte_player_C = Wire.read();                     // Salva na variavel o byte enviado pelo dispositivo
    botoes_player_C = byte_player_C & 0b00001111;
    if (botoes_player_C == 0b1110) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_C);
      Wire.write(0b11101111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_C);                    // Imprime no terminal
      Serial.println("Jogador C apertou a opcao 'a'");  // Imprime no terminal
      resposta_player_C = botoes_player_C;
    } else if (botoes_player_C == 0b1101) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_C);
      Wire.write(0b11011111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_C);                    // Imprime no terminal
      Serial.println("Jogador C apertou a opcao 'b'");  // Imprime no terminal
      resposta_player_C = botoes_player_C;
    } else if (botoes_player_C == 0b1011) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_C);
      Wire.write(0b10111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_C);                    // Imprime no terminal
      Serial.println("Jogador C apertou a opcao 'c'");  // Imprime no terminal
      resposta_player_C = botoes_player_C;
    } else if (botoes_player_C == 0b0111) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_C);
      Wire.write(0b01111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_C);                    // Imprime no terminal
      Serial.println("Jogador C apertou a opcao 'd'");  // Imprime no terminal
      resposta_player_C = botoes_player_C;
    }
    // player D
    Wire.requestFrom(ENDERECO_PCF8574_PLAYER_D, 1);  // Solicita o estado das portas do dispositivo
    byte_player_D = Wire.read();                     // Salva na variavel o byte enviado pelo dispositivo
    botoes_player_D = byte_player_D & 0b00001111;
    if (botoes_player_D == 0b1110) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_D);
      Wire.write(0b11101111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_D);                    // Imprime no terminal
      Serial.println("Jogador D apertou a opcao 'a'");  // Imprime no terminal
      resposta_player_D = botoes_player_D;
    } else if (botoes_player_D == 0b1101) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_D);
      Wire.write(0b11011111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_D);                    // Imprime no terminal
      Serial.println("Jogador D apertou a opcao 'b'");  // Imprime no terminal
      resposta_player_D = botoes_player_D;
    } else if (botoes_player_D == 0b1011) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_D);
      Wire.write(0b10111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_D);                    // Imprime no terminal
      Serial.println("Jogador D apertou a opcao 'c'");  // Imprime no terminal
      resposta_player_D = botoes_player_D;
    } else if (botoes_player_D == 0b0111) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_D);
      Wire.write(0b01111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_D);                    // Imprime no terminal
      Serial.println("Jogador D apertou a opcao 'd'");  // Imprime no terminal
      resposta_player_D = botoes_player_D;
    }
    // player E
    Wire.requestFrom(ENDERECO_PCF8574_PLAYER_E, 1);  // Solicita o estado das portas do dispositivo
    byte_player_E = Wire.read();                     // Salva na variavel o byte enviado pelo dispositivo
    botoes_player_E = byte_player_E & 0b00001111;
    if (botoes_player_E == 0b1110) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_E);
      Wire.write(0b11101111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_E);                    // Imprime no terminal
      Serial.println("Jogador E apertou a opcao 'a'");  // Imprime no terminal
      resposta_player_E = botoes_player_E;
    } else if (botoes_player_E == 0b1101) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_E);
      Wire.write(0b11011111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_E);                    // Imprime no terminal
      Serial.println("Jogador E apertou a opcao 'b'");  // Imprime no terminal
      resposta_player_E = botoes_player_E;
    } else if (botoes_player_E == 0b1011) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_E);
      Wire.write(0b10111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_E);                    // Imprime no terminal
      Serial.println("Jogador E apertou a opcao 'c'");  // Imprime no terminal
      resposta_player_E = botoes_player_D;
    } else if (botoes_player_E == 0b0111) {
      Wire.beginTransmission(ENDERECO_PCF8574_PLAYER_E);
      Wire.write(0b01111111);                           // Envia o byte ao dispositivo
      Wire.endTransmission();                           // Finaliza a comunicacao com o dispositivo i2c
      Serial.println(byte_player_E);                    // Imprime no terminal
      Serial.println("Jogador E apertou a opcao 'd'");  // Imprime no terminal
      resposta_player_E = botoes_player_E;
    }
  }
  if (finalizar_rodada == 1) {
    // ***********************************************************************************************************
    // Visor do LCD: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
    //               0x40 0x41 0x42 0x43 0x44 0x45 0x46 0x47 0x48 0x49 0x4A 0x4B 0x4C 0x4D 0x4E 0x4F
    //
    //              ("P    L    A    Y    E    R         A         B         C          D         E");
    //              ("P    O    I    N    T    S         0         0         0          0         0");
    // ***********************************************************************************************************
    if (resposta_player_A == resposta_certa) {

      pontuacao_player_A += 1;
      lcd.setCursor(7, 4);  // Coluna, Linha
      lcd.print(pontuacao_player_A);
      resposta_player_A = 0;
    }
    if (resposta_player_B == resposta_certa) {

      pontuacao_player_B += 1;
      lcd.setCursor(9, 4);  // Coluna, Linha
      lcd.print(pontuacao_player_B);
      resposta_player_B = 0;
    }
    if (resposta_player_C == resposta_certa) {

      pontuacao_player_C += 1;
      lcd.setCursor(11, 4);  // Coluna, Linha
      lcd.print(pontuacao_player_C);
      resposta_player_C = 0;
    }
    if (resposta_player_D == resposta_certa) {

      pontuacao_player_D += 1;
      lcd.setCursor(13, 4);  // Coluna, Linha
      lcd.print(pontuacao_player_D);
      resposta_player_D = 0;
    }
    if (resposta_player_E == resposta_certa) {

      pontuacao_player_E += 1;
      lcd.setCursor(15, 4);  // Coluna, Linha
      lcd.print(pontuacao_player_E);
      resposta_player_E = 0;
    }
    reset_leds = 1;
    finalizar_rodada = 0;
  }
}