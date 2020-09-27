/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef _BOTE_H_
#define _BOTE_H_

#include "objeto.h"
#include "passageiro.h"

#define MIN_VELOCIDADE 0
#define MAX_VELOCIDADE 15

#define MIN_ACELERACAO 0
#define MAX_ACELERACAO 2

#define PROB_ENCALHAR 0.25

#define MASSA_BOTE 30

#define LARG_BOTE 90
#define ALT_BOTE 60

struct bote_t{
    double massa;
    posicao *posicao;
    int colidido;
    int qtdePassageiros;
};

typedef struct bote_t bote;


/* Função responsável por cria os botes */
bote* inicializarBote();

/* Função que destroi um bote */
void destruirBote(bote *b);

/*Verifica se passageiro colidiu com o bote, exclui o passageiro da tela e incrementa o numero de passageiros resgatados*/
void calcularPassageirosResgatados(passageiros *ps, bote *b);

void calcularDirecaoBote(bote *b, double taxa);

void calcularVelocidadeBote(bote *b, double aceleracao);

void calcularColisaoBotes(bote *jg1, bote *jg2);

#endif
