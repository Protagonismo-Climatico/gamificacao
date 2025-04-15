#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "header.h"
#include "util.h"

class Professor {

private:
  uint8_t endereco_;
  char nome_;

public:

  Professor(char nome, uint8_t endereco)
    : nome_(nome), endereco_(endereco) {}
  Professor()
    : nome_('P'), endereco_(0) {}


  Botao verificarBotaoPressionado();
  uint8_t obterEndereco();
  char obterNome();
};

#endif