/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef __ESTATISTICA_H__
#define __ESTATISTICA_H__

#include "../passageiro.h"

struct medidas_passageiro_t{
    int id_passageiro;
    double velocidade_maxima;
    double velocidade_minima;
    double soma_velocidade;
    unsigned short int quantidade_medidas;
    double desvio_padrao;
    struct medidas_passageiro_t *prox;
};

typedef struct medidas_passageiro_t medidas_passageiro;

struct medidas_t{
    struct medidas_passageiro_t *head;
};

typedef struct medidas_t medidas;

medidas* inicializarEstatistica();
void recolherDadosEstatistica(medidas *m, passageiros *ps);
void imprimirEstatistica(int tempo_simulacao, medidas *m);
void destruirEstatistica(medidas *m);

#endif
