#include <Adafruit_LiquidCrystal.h>

#include <LiquidCrystal_I2C.h>

#include "Wire.h"
#include <LiquidCrystal_I2C.h>

#define MAX_JOGADORES 6

void writeData(uint8_t device, uint8_t byte)
{
    Wire.beginTransmission(device);
    Wire.write(byte);       // Envia o byte ao dispositivo
    Wire.endTransmission(); // Finaliza a comunicacao com o dispositivo i2c
    delay(1);
}

uint8_t readData(uint8_t device, uint8_t count, uint8_t mask)
{
    Wire.requestFrom(device, count); // Solicita o estado das portas do dispositivo
    uint8_t byte = Wire.read();      // Salva na variavel o byte enviado pelo dispositivo
    byte = byte & mask;

    return byte;
}

enum EnderecosI2C
{
    PLAYER_A = 0x20,
    PLAYER_B = 0x21,
    PLAYER_C = 0x22,
    PLAYER_D = 0x23,
    PLAYER_E = 0x24,
    PLAYER_F = 0x26,
    PROFESSOR = 0x25
};

enum Botoes
{
    BOTAO_INICIAR = 0b11011111,
    BOTAO_FINALIZAR = 0b11101111,
    BOTAO_A = 0b11110111,
    BOTAO_B = 0b11111011,
    BOTAO_C = 0b11111101,
    BOTAO_D = 0b11111110,
    BOTOES_JOGADOR = 0b00001111,
    BOTOES_MESTRE = 0b11111111
};

LiquidCrystal_I2C lcd(0x27,16,2);

uint8_t reset_leds;
uint8_t iniciar_rodada;
uint8_t finalizar_rodada;

class Jogador
{
public:
    char nome;
    uint8_t pontuacao;
    uint8_t resposta;
    uint8_t endereco;
    uint8_t botao_pressionado;

    Jogador(char nome, uint8_t endereco)
        : nome(nome), pontuacao(0), resposta(0x0), endereco(endereco), botao_pressionado(0) {}

    Jogador() : nome(' '), pontuacao(0), resposta(0x0), endereco(0), botao_pressionado(0) {}

    void verificar_botao_pressionado();
    void marcar_ponto(uint8_t ponto);
    void reiniciar_jogador();
};

class Professor
{
public:
    char nome;
    uint8_t endereco;
    uint8_t botao_pressionado;

    Professor(char nome, uint8_t endereco) : nome(nome), endereco(endereco), botao_pressionado(0) {}

    void verificar_botao_pressionado();
};

class Jogo
{
public:
    uint8_t rodadas;
    uint8_t rodadas_restantes;
    uint8_t resposta_certa;
    bool iniciar_jogo;
    Jogador jogador[MAX_JOGADORES];
    Professor professor;

    Jogo(uint8_t rodadas, Professor professor)
        : rodadas(rodadas), rodadas_restantes(rodadas), resposta_certa(0x0), professor(professor)
    {
        this->iniciar_jogo = false;
    }

    void definir_resposta_certa();
    void finalizarRodada();
    void finalizarJogo();
    void cronometro(int tempo);
    void definir_quantidade_rodadas();
    void exibir_menu();
    void reiniciar_jogador();
    void verificar_botoes_jogadores();
    void pontuar_jogadores();
    void redefinir_respostas_jogadores();
};

void Professor::verificar_botao_pressionado()
{
    uint8_t botao_pressionado_atual = readData(this->endereco, 1, 0b11111111);
    uint8_t botao_pressionado_anterior = this->botao_pressionado;

    if (botao_pressionado_atual != 0b11111111 && botao_pressionado_atual != botao_pressionado_anterior)
    {
        switch (botao_pressionado_atual)
        {
        case BOTAO_A:
            Serial.println("O Professor apertou a opcao 'A'");
            this->botao_pressionado = BOTAO_A;
            break;
        case BOTAO_B:
            Serial.println("O Professor apertou a opcao 'B'");
            this->botao_pressionado = BOTAO_B;
            break;
        case BOTAO_C:
            Serial.println("O Professor apertou a opcao 'C'");
            this->botao_pressionado = BOTAO_C;
            break;
        case BOTAO_D:
            Serial.println("O Professor apertou a opcao 'D'");
            this->botao_pressionado = BOTAO_D;
            break;
        case BOTAO_INICIAR:
            iniciar_rodada = 1;
            Serial.println("Iniciar rodada");
            this->botao_pressionado = BOTAO_INICIAR;
            break;
        case BOTAO_FINALIZAR:
            this->botao_pressionado = BOTAO_FINALIZAR;
            iniciar_rodada = 0;
            finalizar_rodada = 1;
            break;
        default:
            break;
        }
    }
}

void Jogador::verificar_botao_pressionado()
{
    uint8_t botao_pressionado_atual = readData(this->endereco, 1, 0b11111111);
    uint8_t botao_pressionado_anterior = this->botao_pressionado;

    if (botao_pressionado_atual != 0b11111111 && botao_pressionado_atual != botao_pressionado_anterior && this->resposta == 0x0)
    {
        switch (botao_pressionado_atual)
        {
        case BOTAO_A:
            Serial.println("O jogador apertou a opcao 'A'");
            this->resposta = BOTAO_A;
            break;
        case BOTAO_B:
            Serial.println("O jogador apertou a opcao 'B'");
            this->resposta = BOTAO_B;
            break;
        case BOTAO_C:
            Serial.println("O jogador apertou a opcao 'C'");
            this->resposta = BOTAO_C;
            break;
        case BOTAO_D:
            Serial.println("O jogador apertou a opcao 'D'");
            this->resposta = BOTAO_D;
            break;
        default:
            break;
        }
    }
}

void Jogador::marcar_ponto(uint8_t ponto)
{
    this->pontuacao += ponto;
}

void Jogador::reiniciar_jogador()
{
    writeData(this->endereco, 0b11111111);
    this->resposta = 0;
    this->botao_pressionado = 0;
}

void Jogo::definir_resposta_certa()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("DEFINIR RESPOSTA");
    bool continuar = true;
    uint8_t resposta_anterior = this->resposta_certa;
    uint8_t botao_pressionado = readData(PROFESSOR, 1, 0b11111111);

    while (continuar)
    {
        if (botao_pressionado == BOTAO_A || botao_pressionado == BOTAO_B || botao_pressionado == BOTAO_C || botao_pressionado == BOTAO_D)
        {
            this->resposta_certa = botao_pressionado;
            continuar = false;
        }
        botao_pressionado = readData(PROFESSOR, 1, 0b11111111);
    }
    lcd.clear();
}

void Jogo::finalizarRodada()
{
    this->rodadas_restantes -= 1;
    this->resposta_certa = 0x0;
    if (this->rodadas_restantes <= 0)
    {
        finalizarJogo();
    }
}

void Jogo::redefinir_respostas_jogadores()
{
    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        this->jogador[i].resposta = 0x0;
    }
}

void Jogo::finalizarJogo()
{
    Serial.print("Acabou o jogo!");
}

void Jogo::cronometro(int tempo)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando em...");
    lcd.setCursor(0, 4);

    for (int i = tempo; i > 0; i--)
    {
        lcd.setCursor(5, 4);
        lcd.print(i);
        lcd.print(" segundos");
        delay(tempo * 1000);
    }
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Vai!");
}

void Jogo::definir_quantidade_rodadas()
{
    bool continuar = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Quant. de rodadas:");

    uint8_t botao = 0b11111111;
    while (continuar)
    {
        switch (botao)
        {
        case BOTAO_FINALIZAR:
            continuar = false;
            break;
        case BOTAO_A:
            this->rodadas += 1;
            lcd.setCursor(7, 1);
            lcd.print(this->rodadas);
            break;
        case BOTAO_B:
            this->rodadas -= 1;
            lcd.setCursor(7, 1);
            lcd.print(this->rodadas);
            break;
        }
    }
    this->rodadas_restantes = this->rodadas;
}

void Jogo::exibir_menu()
{
    bool continuar = true;

    String opcao[2] = {"Iniciar jogo", "Nr. de rodadas"};
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println(">");
    lcd.setCursor(2, 0);
    lcd.print(opcao[0]);
    lcd.setCursor(2, 1);
    lcd.print(opcao[1]);

    uint8_t botao = 0b11111111;
    while (continuar)
    {
        switch (botao)
        {
        case BOTAO_INICIAR:
            this->iniciar_jogo = true;
            continuar = false;
            break;
        case BOTAO_A:
            Serial.print("ENTROU AQUI E NAO DEVERIA?");
            String primeiro_elemento = opcao[0];
            for (int i = 0; i < sizeof(opcao) / sizeof(opcao[0]) - 1; i++)
            {
                Serial.print("FOR 1");
                opcao[i] = opcao[i + 1];
            }
            opcao[sizeof(opcao) / sizeof(opcao[0]) - 1] = primeiro_elemento;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.println(">");
            lcd.setCursor(2, 0);
            lcd.print(opcao[0]);
            lcd.setCursor(2, 1);
            lcd.print(opcao[1]);
            break;
        }
        botao = readData(PROFESSOR, 1, 0b11111111);
    }
}

void Jogo::reiniciar_jogador()
{
    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        jogador[i].reiniciar_jogador();
    }
}

void Jogo::verificar_botoes_jogadores()
{
    bool continuar = true;

    while (continuar)
    {
        for (int i = 0; i < MAX_JOGADORES; i++)
        {
            this->jogador[i].verificar_botao_pressionado();
        } 
        if (this->jogador[0].resposta)
        {
            continuar = false;
        }
    }
}

void Jogo::pontuar_jogadores()
{
    for (uint8_t i = 0; i < MAX_JOGADORES; i++)
    {
        if (this->jogador[i].resposta == this->resposta_certa)
        {
            this->jogador[i].marcar_ponto(1);
        }
    }
}

Professor professor('P', PROFESSOR);
Jogo jogo(3, professor);

void setup()
{
    Serial.begin(9600);
    lcd.init(); 
      lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Setup completed");

    jogo.jogador[0] = Jogador('A', PLAYER_A);
    jogo.jogador[1] = Jogador('B', PLAYER_B);
    jogo.jogador[2] = Jogador('C', PLAYER_C);
    jogo.jogador[3] = Jogador('D', PLAYER_D);
    jogo.jogador[4] = Jogador('E', PLAYER_E);
    jogo.jogador[5] = Jogador('F', PLAYER_F);

    iniciar_rodada = 0;
    finalizar_rodada = 0;
    reset_leds = 1;

    jogo.reiniciar_jogador();

    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Setup finalizado!");
}



void loop()
{
    Serial.print(jogo.jogador[0].pontuacao);
    jogo.exibir_menu();

    while (jogo.iniciar_jogo)
    {
        Serial.print("Jogo Iniciado!");
        jogo.definir_resposta_certa();
        // jogo.cronometro(2);

        jogo.verificar_botoes_jogadores();
        jogo.pontuar_jogadores();
        jogo.redefinir_respostas_jogadores();

        Serial.print(jogo.jogador[0].pontuacao);

        uint8_t index = 0;
        for (uint8_t i = 7; i < 15; i += 2)
        {
            lcd.setCursor(i, 4); // Coluna, Linha
            lcd.print(jogo.jogador[index].pontuacao);
            index++;
        }
        // jogo.iniciar_jogo = 0;
    }
}
