/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef __NAVIO_H__
#define __NAVIO_H__

#include "objeto.h"
#include "passageiro.h"

struct navio_t{
    posicao *posicao;
};

typedef struct navio_t navio;

/*Atualiza o struct navio com suas coordenadas e sua diagonal principal*/
navio* inicializarNavio(ptr_marcaBarreiras posicaoBarreiras);

/*Verifica se houve colisao entre um objeto e o ASIMOV*/
void calcularColisaoNavio(passageiros *ps, navio *n);

/*Libera memoria utilizada para guardar os dados do asimov*/
void destruirNavio(navio *n);

#endif
