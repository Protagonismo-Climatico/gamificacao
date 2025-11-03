#include "jogo.h"
#include <LiquidCrystal_I2C.h>
#include "TCA9548.h"
#define NUM_LCDS 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
TCA9548 MP(0x70);

Jogo jogo;
unsigned long t_ultima_mudanca = 0;    
unsigned long t_inicio_resposta = 0;
unsigned long t_mostra_resultado = 0;
unsigned long t_placar_final = 0;


Botao botaoPressionado = BOTAO_INVALIDO;
Botao botaoAnterior = BOTAO_INVALIDO;


void iniciarLCDS() {
  Serial.println("Iniciando LCDs (Canal 0 e 1)...");
  
  for (int canal = 0; canal < NUM_LCDS; canal++) { // Loop para canal=0 e canal=1
    MP.selectChannel(canal);
    delay(50);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bem vindo ao");
    lcd.setCursor(0, 1);
    lcd.print("Futuro Quizz!");
    Serial.print("✅ LCD no Canal ");
    Serial.println(canal);
  }

  MP.selectChannel(0);
  Serial.println("LCD do Professor (Canal 0) re-selecionado.");
}

void iniciarPcfs(){

  for (int canal = 0; canal < NUM_LCDS; canal++) { // Loop para canal=0 e canal=1
    MP.selectChannel(canal);
    delay(50);
    Util::escreverDado(PROFESSOR, 0b11111111);
    Serial.println("Botões Professor (Ch 0) inicializados.");
  }
  MP.selectChannel(0);
}

void lcdAguardarJogadores(){
    MP.selectChannel(0);
    delay(50);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Aguardando");
      lcd.setCursor(0, 1);
      lcd.print("Jogadores...");
  }

void lcdRespondam(){
  for (int canal = 1; canal <= MAX_JOGADORES; canal++) {
    MP.selectChannel(canal);
    delay(50);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Qual a resposta?");
    lcd.setCursor(0, 1);
    lcd.print("A/B/C/D");
    Serial.println(canal);
  }

  MP.selectChannel(0);
}
void lcdEsperem(){
  for (int canal = 1; canal <= MAX_JOGADORES; canal++) {
    MP.selectChannel(canal);
    delay(50);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Espere o");
    lcd.setCursor(0, 1);
    lcd.print("professor");
    Serial.println(canal);
  }

  MP.selectChannel(0);
}

void verificar_botoes_jogadores() {

  jogo.todos_jogadores_responderam = true;
  for (int canal = 0; canal < MAX_JOGADORES; canal++) { // Loop para canal=0 e canal=1
    MP.selectChannel(canal+1);
    delay(50);

    if (jogo.jogador[canal].obterResposta() == BOTAO_INVALIDO) {
      jogo.jogador[canal].verificarBotaoPressionado();
      if (jogo.jogador[canal].obterResposta() == BOTAO_INVALIDO) {
        jogo.todos_jogadores_responderam = false;
     }
    }
  }
  MP.selectChannel(0);
}

void setup() {    
  Serial.begin(9600);
  delay(1000);
  Serial.println("🔹 Iniciando setup...");

  Wire.begin();
  Serial.println("🔹 Wire iniciado.");

  if (!MP.begin()) {
    Serial.println("⚠ Erro ao inicializar o multiplexador!");
  } else {
    Serial.println("Multiplexador iniciado!");
  }

  
  jogo.professor = Professor('P', PROFESSOR);
  jogo.jogador[0] = Jogador('A', PLAYER_A);
  
  MP.selectChannel(0);
  iniciarPcfs();
  iniciarLCDS();
  Serial.println("LCD inicializado!");
}
void mostrarAcertos(){

   for (int canal = 0; canal < NUM_LCDS; canal++) {

    int i = jogo.jogador_atual_resultado;

    bool acertou = (jogo.jogador[i].obterResposta() == jogo.resposta_certa);

    MP.selectChannel(canal);

    delay(50);        

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

  MP.selectChannel(0);

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
        //lcd.print("B - Finalizar");
        jogo.estado_atual = ACAO_MENU_INICIAL;
        lcdEsperem();
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
        lcdEsperem();
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
        lcdAguardarJogadores();
        lcdRespondam();
        jogo.redefinir_respostas_jogadores();

        jogo.estado_atual = ACAO_AGUARDAR_RESPOSTAS;
      break;

      case ACAO_AGUARDAR_RESPOSTAS:
        if (t_inicio_resposta == 0) {
            t_inicio_resposta = millis();
        }

        verificar_botoes_jogadores();

        if (millis() - t_inicio_resposta >= TEMPO_LIMITE) {
            jogo.tempo_esgotado = true;
        }

        if (jogo.todos_jogadores_responderam ) {
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
             mostrarAcertos();
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
           
                
                for (int canal = 0; canal < NUM_LCDS; canal++) {
                  MP.selectChannel(canal);

                  lcd.clear();
                  lcd.setCursor(0, 0); 
                  lcd.print("PLA|");
                  lcd.setCursor(0, 1);
                  lcd.print("CAR|");
                  
                  uint8_t index_jogador = 0;
                  for (uint8_t i = 5; i <= 15 && index_jogador < MAX_JOGADORES; i += 2)
                  {
                    lcd.setCursor(i, 0); // Coluna, Linha
                    lcd.print(jogo.jogador[index_jogador].obterNome());
                    lcd.setCursor(i, 1); // Coluna, Linha
                    lcd.print(jogo.jogador[index_jogador].obterPontuacao());
                    index_jogador++;
                  }
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

               for (int canal = 1; canal <= NUM_LCDS; canal++) {
                  MP.selectChannel(canal);
                  lcdEsperem();
                }
                delay(2000);
                jogo.round_atual = 0;
                jogo.reiniciar_jogadores();
                jogo.estado_atual = LCD_MENU_INICIAL;
                break;
            
     
    }
  }
}