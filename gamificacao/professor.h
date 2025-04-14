#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "header.h"
#include "util.h"

class Professor {
public:
  char nome;
  uint8_t endereco;
  uint8_t botao_pressionado;

  Professor(char nome, uint8_t endereco)
    : nome(nome), endereco(endereco), botao_pressionado(0) {}
  Professor()
    : nome(' '), endereco(0), botao_pressionado(0) {}


  void verificar_botao_pressionado();
};

#endif