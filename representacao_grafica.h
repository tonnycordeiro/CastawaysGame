/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef _REPRESENTACAO_GRAFICA_H_
#define _REPRESENTACAO_GRAFICA_H_

#include <allegro.h>
#include "representacao.h"
#include "recife.h"

#define LARGURA_REPRESENTACAO 1024
#define ALTURA_REPRESENTACAO 768

#define MAX_OBJETO_TELA 113

#define MAX_LARG_PASSAGEIRO 50

struct representacao_t
{
	BITMAP *representacao;
	BITMAP *fundo;
	BITMAP *navio;
	BITMAP *recifes[NUM_RECIFES];
	BITMAP *imagens[MAX_OBJETO_TELA];
};

#endif
