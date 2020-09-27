/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef _RECIFE_H_
#define _RECIFE_H_

#include "objeto.h"

#define NUM_RECIFES 3
#define NUM_TAMANHO_RECIFE 10

struct recife_t{
    posicao *posicao;
    int tamanho;
    struct recife_t *prox;
};

typedef struct recife_t recife;

typedef struct{
    recife *head;
} recifes;

recifes* inicializarRecifes();
void definirPosicao(recifes* rs);
void destruirRecifes(recifes* rs);

#endif
