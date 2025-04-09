#ifndef PROFESSOR_H
#define PROFESSOR_H
#include <stdint.h>
#include "header.h"
#include "Arduino.h"
#include "util.h"
class Professor
{
public:
    char nome;
    uint8_t endereco;
    uint8_t botao_pressionado;

    Professor(char nome, uint8_t endereco) : nome(nome), endereco(endereco), botao_pressionado(0) {}

    void verificar_botao_pressionado();
};

#endif