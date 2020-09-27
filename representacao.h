/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef _REPRESENTACAO_H_
#define _REPRESENTACAO_H_

#include "objeto.h"
#include "passageiro.h"
#include "bote.h"
#include "recife.h"
#include "navio.h"

typedef struct representacao_t* representacao;

representacao inicializarRepresentacao();
void destruirRepresentacao(representacao oceano);
void limparRepresentacao(representacao oceano);
void definirVisualRepresentacao(representacao oceano, passageiros *ps, recifes *rs, bote *b1, bote *b2, navio *n);
void imprimirRepresentacao(representacao oceano);
int objetoForaArea(posicao *pos);

int obterLarguraRepresentacao();
int obterAlturaRepresentacao();

#endif

