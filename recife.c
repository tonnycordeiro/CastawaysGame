/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#include <stdlib.h>
#include <stdio.h>

#include "recife.h"
#include "utils.h"

/* Função responsável por cria os recifes */
recifes* inicializarRecifes()
{
	recifes *rs = (recifes*) malloc( sizeof(recifes) );

    if( rs->head == NULL )
    {
        printf("Memória insuficiente!");
        exit(1);
    }
    
    rs->head->posicao = NULL;
    rs->head->prox = NULL;
		
	definirPosicao(rs);
		
	return rs;	
}

void definirPosicao(recifes* rs)
{
	int i;
	recife *r;
	
	for(i = 0; i < NUM_RECIFES; i++)
	{
		r = (recife*) malloc( sizeof(recife) );
		
		r->posicao = (posicao*) malloc( sizeof(posicao) );
		
		r->posicao->x = randIntervalo(0, 1014);
		r->posicao->y = randIntervalo(10, 758);
		
        /* Coloca o recife no começo da lista */
        r->prox = rs->head->prox;
        rs->head->prox = r;		
	}	
}

/* Função que chama a função de destruição de recifes de forma recursiva */
void destruirRecifeR(recife *r)
{
    if( r->prox != NULL )
        destruirRecifeR( r->prox );

    if( r->prox != NULL )
    	free( r->prox );
    	
    free( r );
}

/* Função que destroi cada recife da lista e no final a própria lista de recifes */
void destruirRecifes(recifes* rs)
{
    destruirRecifeR(rs->head);
    free(rs);
}
