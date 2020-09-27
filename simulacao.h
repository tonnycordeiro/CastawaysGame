/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef _SIMULACAO_H_
#define _SIMULACAO_H_

#include "passageiro.h"
#include "bote.h"
#include "recife.h"
#include "navio.h"
#include "representacao.h"
#include "barreiras.h"

#define TEMPO_SIMULACAO 300
#define MAX_PASSAGEIROS_TELA 100

#define PRINT_INFO_TELA(ps) /*(printf("%d passageiro(s) na tela.\n\n", ps->quantidade))*/

void simular(double frequencia, int velocidade, unsigned int semente);
void inicializarSimulacao(representacao *oceano, passageiros **ps, bote **b1, bote **b2, recifes **rs, navio **n,ptr_marcaBarreiras *ptrBarreiras);
void destruirSimulacao(representacao oceano, passageiros *ps, bote *b1, bote *b2, recifes *rs, navio *nav);
void interacaoSimulacao(representacao oceano, passageiros *ps, bote *b1, bote *b2, navio *n, double frequencia, int velocidade, unsigned int semente, ptr_marcaBarreiras ptrBarreiras);


#endif
