
#include "header.h"
#include "Arduino.h"
#include <Wire.h>

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

uint8_t verify_buttons_players(uint8_t device)
{
    uint8_t botoes_player = readData(device, 1, botoes_jogador);
    uint8_t resposta_player = botoes_player;

    switch (botoes_player)
    {
    case botao_A:
        Serial.println("Jogador apertou a opcao 'A'"); // Imprime no terminal
        //writeData(device, 0b11101111);
        break;

    case botao_B:
        Serial.println("Jogador apertou a opcao 'B'"); // Imprime no terminal
        //writeData(device, 0b11011111);
        break;
    case botao_C:
        Serial.println("Jogador apertou a opcao 'C'"); // Imprime no terminal
        //writeData(device, 0b10111111);
        break;
    case botao_D:
        Serial.println("Jogador apertou a opcao 'D'"); // Imprime no terminal
        //writeData(device, 0b01111111);
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
