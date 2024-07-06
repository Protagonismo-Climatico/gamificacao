#include "Adafruit_LiquidCrystal.h"

#define ENDERECO_PCF8574_PLAYER_A 0x20  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_B 0x21  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_C 0x22  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_D 0x23  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_E 0x24  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_F 0x25  // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PROFESSOR 0x26 // Endereco I2C para o PCF8574

uint8_t byte_player_0;
uint8_t byte_player_A;
uint8_t byte_player_B;
uint8_t byte_player_C;
uint8_t byte_player_D;
uint8_t byte_player_E;
uint8_t byte_player_F;

uint8_t botoes_player_0;
uint8_t botoes_player_A;
uint8_t botoes_player_B;
uint8_t botoes_player_C;
uint8_t botoes_player_D;
uint8_t botoes_player_E;
uint8_t botoes_player_F;

uint8_t resposta_player_A;
uint8_t resposta_player_B;
uint8_t resposta_player_C;
uint8_t resposta_player_D;
uint8_t resposta_player_E;
uint8_t resposta_player_F;

uint8_t pontuacao_player_A;
uint8_t pontuacao_player_B;
uint8_t pontuacao_player_C;
uint8_t pontuacao_player_D;
uint8_t pontuacao_player_E;
uint8_t pontuacao_player_F;

uint8_t reset_leds;
uint8_t iniciar_rodada;
uint8_t finalizar_rodada;
uint8_t resposta_certa;
Adafruit_LiquidCrystal lcd(0x27); // O endereco de fabrica do LCD geralmente é 0x27 ou 0x7F

#define botao_INICIAR 0b11011111
#define botao_FINALIZAR 0b11101111
#define botao_A 0b11110111
#define botao_B 0b11111011
#define botao_C 0b11111101
#define botao_D 0b11111110
#define botoes_jogador 0b00001111
#define botoes_mestre 0b11111111
#define MAX_JOGADORES 6

class Professor
{
public:
    char nome;
    uint8_t endereco;
    uint8_t botao_pressionado;

    Professor(char nome, uint8_t endereco) : nome(nome), endereco(endereco)
    {
        this->botao_pressionado = 0;
    }

    void verificar_botao_pressionado()
    {
        uint8_t botao_pressionado_atual = readData(this->endereco, 1, 0b11111111);
        uint8_t botao_pressionado_anterior = this->botao_pressionado;

        if (botao_pressionado_atual != 0b11111111 & botao_pressionado_atual != botao_pressionado_anterior)
        {
            switch (botao_pressionado_atual)
            {
            case botao_A:
                Serial.println("O Professor apertou a opcao 'A'"); // Imprime no terminal
                this->botao_pressionado = botao_A;
                break;

            case botao_B:
                Serial.println("O Professor apertou a opcao 'B'"); // Imprime no terminal
                this->botao_pressionado = botao_B;
                break;
            case botao_C:
                Serial.println("O Professor apertou a opcao 'C'"); // Imprime no terminal
                this->botao_pressionado = botao_C;
                break;
            case botao_D:
                Serial.println("O Professor apertou a opcao 'D'"); // Imprime no terminal
                this->botao_pressionado = botao_D;
                break;
            case botao_INICIAR:
                iniciar_rodada = 1;
                Serial.println("Iniciar rodada"); // Imprime no terminal
                this->botao_pressionado = botao_INICIAR;
                // cronometro(2);
                break;

            case botao_FINALIZAR:
                this->botao_pressionado = botao_FINALIZAR;
                iniciar_rodada = 0;
                finalizar_rodada = 1;

                break;

            default:
                break;
            }
        }
    }
};

class Jogador
{
public:
    char nome;
    uint8_t pontuacao;
    uint8_t resposta;
    uint8_t endereco;
    uint8_t botao_pressionado;
    Jogador(char nome, uint8_t endereco)
    {
        this->nome = nome;
        this->pontuacao = 0;
        this->resposta = 0x0;
        this->endereco = endereco;
        this->botao_pressionado = 0;
    }
    Jogador()
    {
        this->nome = ' ';
        this->pontuacao = 0;
        this->resposta = 0x0;
        this->endereco = 0;
        this->botao_pressionado = 0;
    }
    void verificar_botao_pressionado()
    {
        uint8_t botao_pressionado_atual = readData(this->endereco, 1, 0b11111111);
        uint8_t botao_pressionado_anterior = this->botao_pressionado;

        if (botao_pressionado_atual != 0b11111111 & botao_pressionado_atual != botao_pressionado_anterior & this->resposta == 0x0)
        {
            switch (botao_pressionado_atual)
            {
            case botao_A:
                Serial.println("O jogador apertou a opcao 'A'"); // Imprime no terminal
                this->resposta = botao_A;
                break;

            case botao_B:
                Serial.println("O jogador apertou a opcao 'B'"); // Imprime no terminal
                this->resposta = botao_B;
                break;
            case botao_C:
                Serial.println("O jogador apertou a opcao 'C'"); // Imprime no terminal
                this->resposta = botao_C;
                break;
            case botao_D:
                Serial.println("O jogador apertou a opcao 'D'"); // Imprime no terminal
                this->resposta = botao_D;
                break;
            default:
                break;
            }
        }
    }

    void pontuar_jogador(uint8_t resposta_certa, uint8_t ponto)
    {
        if (resposta_certa == this->resposta)
        {
            this->pontuacao += ponto;
        }
    }

    void reiniciar_jogador()
    {
        writeData(this->endereco, 0b11111111);
        this->resposta = 0;
        this->botao_pressionado = 0;
    }
};

class Jogo
{
public:
    uint8_t rodadas;
    uint8_t rodadas_restantes;
    uint8_t resposta_certa;

    Jogo(uint8_t rodadas) : rodadas(rodadas)
    {
        this->resposta_certa = 0x0;
        this->rodadas_restantes = rodadas;
    }

    void definir_resposta_certa(uint8_t resposta_certa_nova)
    {
        if (resposta_certa_nova == 0x0)
        {
            this->resposta_certa = resposta_certa_nova;
        }
    }

    void finalizarRodada()
    {
        this->rodadas_restantes -= 1;
        this->resposta_certa = 0x0;
        if (this->rodadas_restantes <= 0)
        {
            finalizarJogo();
        }
    }

    void finalizarJogo()
    {
        Serial.print("Acabou o jogo more...");
    }

    void definir_quantidade_rodadas()
    {
        // ("P    L    A    Y    E    R         A         B         C          D         E");
        bool continuar = true;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.println("Quant. de rodadas:");

        uint8_t botao = 0b11111111;
        while (continuar)
        {
            switch (botao)
            {
            case botao_FINALIZAR:
                continuar = false;
                break;
            case botao_A:
                this->rodadas += 1; // VERIFICAR
                lcd.setCursor(7, 1);
                lcd.print(this->rodadas);
                break;
            case botao_B:
                this->rodadas -= 1; // TRATAR NUMERO NEGATIVO
                lcd.setCursor(7, 1);
                lcd.print(this->rodadas);
                break;
            }
            botao = readData(ENDERECO_PCF8574_PROFESSOR, 1, 0b11111111);
        }
    }

    void exibir_menu()
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
            case botao_INICIAR:
                definir_quantidade_rodadas();
                continuar = false;
                break;
            case botao_A:
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
            botao = readData(ENDERECO_PCF8574_PROFESSOR, 1, 0b11111111);
        }
    }
};

Jogo jogo(5);
Professor professor('P', ENDERECO_PCF8574_PROFESSOR);
Jogador jogador[MAX_JOGADORES];

void setup()
{
    jogador[0] = Jogador('A', ENDERECO_PCF8574_PLAYER_A);
    jogador[1] = Jogador('B', ENDERECO_PCF8574_PLAYER_B);
    jogador[2] = Jogador('C', ENDERECO_PCF8574_PLAYER_C);
    jogador[3] = Jogador('D', ENDERECO_PCF8574_PLAYER_D);
    jogador[4] = Jogador('E', ENDERECO_PCF8574_PLAYER_E);
    jogador[5] = Jogador('F', ENDERECO_PCF8574_PLAYER_F);

    Wire.begin();       // Inicializa a comunicacao i2c
    Serial.begin(9600); // start serial for output
    // Escrevendo no LCD os caracteres que nao se alteram
    lcd.begin(16, 2);
    // Visor do LCD: 0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
    //               0x40 0x41 0x42 0x43 0x44 0x45 0x46 0x47 0x48 0x49 0x4A 0x4B 0x4C 0x4D 0x4E 0x4F
    lcd.setBacklight(HIGH); // Luz de fundo acesa
    lcd.setCursor(0, 0);

    //         XXXXXXXXXXXXXXXX
    lcd.print("PLAYER A B C D E F");
    lcd.setCursor(0, 4);
    lcd.print("PONTOS 0 0 0 0 0 0");
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

void cronometro(int tempo)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando em...");
    lcd.setCursor(0, 4);

    for (int i = tempo; i > 0; i--)
    {
        lcd.setCursor(5, 4); // Coluna, Linha
        lcd.print(i);
        lcd.print(" segundos");
        Serial.println(i);
        delay(tempo * 1000);
    }
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Vai!");
}

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

void loop()
{
    // jogo.exibir_menu();

    if (reset_leds == 1) // Se o jogo foi resetado
    {
        Serial.println("Resetando players");
        // Resetando players

        writeData(ENDERECO_PCF8574_PROFESSOR, 0b11111111);

        for (uint8_t i = 0; i < MAX_JOGADORES; i++)
        {
            jogador[i].reiniciar_jogador();
        }

        reset_leds = 0;
        Serial.println("Playes Resetados.");
    }
    // Player 0, o que define qual eh a alternativa correta
    professor.verificar_botao_pressionado();
    jogo.definir_resposta_certa(professor.botao_pressionado);

    // Inicia a leiura periodica dos botoes dos jogadores
    if (iniciar_rodada == 1)
    {
        //
        for (int i = 0; i < MAX_JOGADORES; i++)
        {
            jogador[i].verificar_botao_pressionado();
        }
        //
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

        for (uint8_t i = 0; i < MAX_JOGADORES; i++)
        {
            jogador[i].pontuar_jogador(resposta_certa, 1);
        }
        uint8_t index = 0;
        for (uint8_t i = 7; i < 15; i += 2)
        {
            lcd.setCursor(i, 4); // Coluna, Linha
            lcd.print(jogador[index].pontuacao);
            resposta_player_A = 0;
            index++;
        }

        reset_leds = 1;
        finalizar_rodada = 0;
    }
}
