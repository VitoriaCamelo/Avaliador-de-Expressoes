// o objetivo é criar um avaliador 
// de expressões matemáticas

#include "funcoes.h"

int main(void) {
  Pilha *pilha;
  cria_pilha(&pilha);
  interface(&pilha);
  return 0;
}
