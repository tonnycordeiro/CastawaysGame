/*
  Nome e n� USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#include <stdlib.h>
#include <stdio.h>

#include "recife.h"
#include "utils.h"

/* Fun��o respons�vel por cria os recifes */
recifes* inicializarRecifes()
{
	recifes *rs = (recifes*) malloc( sizeof(recifes) );

    if( rs->head == NULL )
    {
        printf("Mem�ria insuficiente!");
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
		
        /* Coloca o recife no come�o da lista */
        r->prox = rs->head->prox;
        rs->head->prox = r;		
	}	
}

/* Fun��o que chama a fun��o de destrui��o de recifes de forma recursiva */
void destruirRecifeR(recife *r)
{
    if( r->prox != NULL )
        destruirRecifeR( r->prox );

    if( r->prox != NULL )
    	free( r->prox );
    	
    free( r );
}

/* Fun��o que destroi cada recife da lista e no final a pr�pria lista de recifes */
void destruirRecifes(recifes* rs)
{
    destruirRecifeR(rs->head);
    free(rs);
}
