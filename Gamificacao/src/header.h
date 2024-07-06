#ifndef header_h
#define header_h
#include <stdint.h>
#define ENDERECO_PCF8574_PLAYER_A 0x20 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_B 0x21 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_C 0x22 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_D 0x23 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_E 0x24 // Endereco I2C para o PCF8574
#define ENDERECO_PCF8574_PLAYER_0 0x25 // Endereco I2C para o PCF8574

extern uint8_t byte_player_0;
extern uint8_t byte_player_A;
extern uint8_t byte_player_B;
extern uint8_t byte_player_C;
extern uint8_t byte_player_D;
extern uint8_t byte_player_E;

extern uint8_t botoes_player_0;
extern uint8_t botoes_player_A;
extern uint8_t botoes_player_B;
extern uint8_t botoes_player_C;
extern uint8_t botoes_player_D;
extern uint8_t botoes_player_E;

extern uint8_t resposta_player_A;
extern uint8_t resposta_player_B;
extern uint8_t resposta_player_C;
extern uint8_t resposta_player_D;
extern uint8_t resposta_player_E;

extern uint8_t pontuacao_player_A;
extern uint8_t pontuacao_player_B;
extern uint8_t pontuacao_player_C;
extern uint8_t pontuacao_player_D;
extern uint8_t pontuacao_player_E;

extern uint8_t reset_leds;
extern uint8_t iniciar_rodada;
extern uint8_t finalizar_rodada;
extern uint8_t resposta_certa;

#define botao_INICIAR 0b011111
#define botao_FINALIZAR 0b101111
#define botao_A 0b00000111
#define botao_B 0b00001011
#define botao_C 0b00001101
#define botao_D 0b00001110
#define botoes_jogador 0b00001111
#define botoes_mestre 0b00111111


void writeData(uint8_t, uint8_t);
uint8_t readData(uint8_t, uint8_t, uint8_t);
uint8_t verify_buttons_players(uint8_t);
uint8_t verify_answer_players(uint8_t, uint8_t);
#endif