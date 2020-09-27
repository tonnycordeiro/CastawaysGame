/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/


#include "navio.h"
#include "funcao_grafica.h"
#include "barreiras.h"

#include <stdlib.h>
#include <stdio.h>

/*Atualiza o struct navio com suas coordenadas e sua diagonal principal*/
navio* inicializarNavio(ptr_marcaBarreiras posicaoBarreiras)
{
	navio *n = (navio*) malloc( sizeof(navio) );
	
	n->posicao = (posicao*) malloc( sizeof(posicao) );
	
	n->posicao->x = 180; /*512*/
	n->posicao->y = 200; /*300*/
	
	n->posicao->tamanho_x = 269; 
	n->posicao->tamanho_y = 232;
	
    /* Define a diagonal que será usada no cálculo da colisão */
	calcularDiagonal(n->posicao);
	/*Marcar o navio como uma barreira*/
	marcarBarreiras(posicaoBarreiras, n->posicao->tamanho_x, n->posicao->tamanho_y, n->posicao->diagPrincipalRet.xEsq, n->posicao->diagPrincipalRet.yEsq, BAR_ASIMOV);

	/*Definir posição de descarga de passageiros*/
	marcarBarreiras(posicaoBarreiras, 163, 74, n->posicao->diagPrincipalRet.xEsq, n->posicao->diagPrincipalRet.yEsq, BAR_DESCARGA);	
	
	return n;	
}

/*Verifica se houve colisao entre um objeto e o ASIMOV*/
void calcularColisaoNavio(passageiros *ps, navio *n)
{
    passageiro *p, *p_anterior = ps->head;

    for( p = ps->head->prox; p != NULL; p_anterior = p, p = p->prox )
    {
        if( verificarObjetosColididos( p->posicao->diagPrincipalRet, p->posicao, n->posicao->diagPrincipalRet, n->posicao ) )
        {
			calcularDirecaoFinal( p->posicao, n->posicao, p->massa, 10 );
        }
    }
}

/*Libera memoria utilizada para guardar os dados do ASIMOV*/
void destruirNavio(navio *n)
{
	free(n->posicao);
	free(n);	
}


