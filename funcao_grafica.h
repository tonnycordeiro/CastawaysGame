/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef __FUNCAO_GRAFICA_H__
#define __FUNCAO_GRAFICA_H__

#include "objeto.h"

# define PI		3.14159265358979323846
#define MAX_LARG_PASSAGEIRO 50
#define QTDE_LADOS_TELA 4

struct coordenada{
	int x;
	int y;
};
typedef struct coordenada coord;

/*Calcula a diagonal dos objetos da tela para serem 
 * utilizados no algoritmo de tratamento de colisão*/
void calcularDiagonal(posicao *pos);


#endif
