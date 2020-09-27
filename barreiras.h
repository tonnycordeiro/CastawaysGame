#ifndef _BARREIRA_H_
#define _BARREIRA_H_

#include "objeto.h"
#include "utils.h" 

#define BAR_BORDA -1
#define BAR_PASSAGEIRO -2
#define BAR_RECIFE -3
#define BAR_ASIMOV -4
#define BAR_DESCARGA 1


#define MARGEM 0
#define MARGEM_DIREITA 0
#define MARGEM_INFERIOR 0

#define LARG_PLOT 1
#define LARGURA_REPRESENTACAO 1024
#define ALTURA_REPRESENTACAO 768

struct marcacaoDeBarreiras /*barreiras*/
{
	int** posicoes;
};

typedef struct marcacaoDeBarreiras *ptr_marcaBarreiras;

void retornaPtoDeColisaoComBarreira(posicao *pos, int *x, int *y, ptr_marcaBarreiras posicaoBarreiras);
ptr_marcaBarreiras inicializarMarcacaoDasBarreiras();
void definirCoordenadasBarreiras(ptr_marcaBarreiras posicaoBarreiras);
void direcaoPosChoque(posicao *pos, ptr_marcaBarreiras barreiras);
void imprimeRepresentacaoBarreiras(ptr_marcaBarreiras ptrBarreiras);
void renovarBordasMarcacaoDasBarreiras(int tamanho_margem, ptr_marcaBarreiras ptrBarreiras);
void marcarBarreiras(ptr_marcaBarreiras posicaoBarreiras, int largura, int altura, int x, int y, int barreira);

#endif
