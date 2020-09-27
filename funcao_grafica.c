/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "funcao_grafica.h"

/*Calcula a diagonal dos objetos da tela para serem 
 * utilizados no algoritmo de tratamento de colisão*/
void calcularDiagonal(posicao *pos)
{
	double x = pos->x;
	double y = pos->y;
	
	pos->diagPrincipalRet.xEsq = x - pos->tamanho_x/2;
	pos->diagPrincipalRet.yEsq = y - pos->tamanho_y/2;
	
	pos->diagPrincipalRet.xDir = x + pos->tamanho_x/2;
	pos->diagPrincipalRet.yDir = y + pos->tamanho_y/2;	
}

