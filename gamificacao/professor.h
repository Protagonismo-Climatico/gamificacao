#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "header.h"

class Professor {
private:
    uint8_t endereco_;
    char nome_;

public:
    Professor(char nome, uint8_t endereco);
    Professor();

    Botao verificarBotaoPressionado();
    uint8_t obterEndereco();
    char obterNome();
};

#endif