// aqui vão ficar minhas queridas funções
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pilha Pilha;
struct pilha {
  char caractere;
  struct pilha *prox;
};
char abrem[4] = "{[(";
char fecham[4] = "}])";

// essencial
void cria_pilha(Pilha **pp) { *pp = 0; }
void push(Pilha **pp, char letra) {
  Pilha *novo;
  novo = (Pilha *)malloc(sizeof(Pilha));
  if (!novo)
    return;
  novo->caractere = letra;
  novo->prox = *pp;
  *pp = novo;
}
void pop(Pilha **pp) {
  Pilha *some;
  if (!*pp) {
    printf("Já não tem nada aqui\n");
    return;
  } else {
    some = *pp;
    *pp = (*pp)->prox;
    free(some);
  }
}
char mostrar_topo(Pilha *pp) {
  if (pp)
    return pp->caractere;
}
void limpar(Pilha **pp) {
  Pilha *novotopo;
  if (!*pp)
    return;
  else {
    novotopo = (*pp)->prox;
    free(*pp);
    *pp = 0;
    limpar(&novotopo);
  }
}

int avalia_qtde(int qtde) {
  if (qtde % 2 != 0) {
    printf("Hummm, essa expressão não tem tamanho adequado\n");
    return 1;
  } else {
    return 0;
  }
}
int segunda_analise(int qtde, char original[]) {
  for (int i = 0; i < 4; i++) {
    if (original[0] == fecham[i]) {
      printf("Sua expressão começou de forma errada\n");
      return 1;
    }
    if (original[qtde - 1] == abrem[i]) {
      printf("Sua expressão terminou de forma errada\n");
      return 1;
    }
  }
  return 0;
}
void avaliador(int qtde, char original[], Pilha **pp) {
  push(pp, original[0]);
  for (int i = 1; i < qtde; i++) {
    for (int j = 0; j < 4; j++) {
      if (original[i] == abrem[j]) {
        push(pp, original[i]);
      } else if (original[i] == fecham[j]) {
        if (mostrar_topo(*pp) == abrem[j]) {
          pop(pp);
        } else {
          printf("Expressão inválida\n");
          return;
        }
      }
    }
  }
  printf("Expressão aceita\n");
  return;
}
void primeira_analise(Pilha **pp) {
  int qtde;
  printf("Quantos elementos?\n");
  scanf("%d", &qtde);
  int check_qtde = avalia_qtde(qtde);
  if (check_qtde == 1)
    return;
  else {
    char original[qtde];
    printf("Insira a expressão:\n");
    scanf("%s", original);
    int check_IF = segunda_analise(qtde, original);
    if (check_IF == 1)
      return;
    else
      avaliador(qtde, original, pp);
  }
}

void interface(Pilha **pp) {
  int continuar = 1;
  printf("> Avaliador de expressões da Vi <\n");
  while (continuar != 2) {
    int opcao;
    printf("\n");
    printf("[1] Nova expressão\n");
    printf("[2] Sair\n");
    scanf("%d", &opcao);
    if (opcao == 2)
      return;
    else {
      primeira_analise(pp);
    }
  }
}
