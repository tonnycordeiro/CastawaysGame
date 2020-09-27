#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "barreiras.h"
#include "math.h"
 
ptr_marcaBarreiras inicializarMarcacaoDasBarreiras(){
    int i,j;
    ptr_marcaBarreiras ptrBarreiras = malloc(sizeof(*ptrBarreiras)); 
    /* Aloca memoria para as colunas da matrix posicaoBarreiras */
    int **posicaoBarreiras = (int**) malloc( (ALTURA_REPRESENTACAO+MARGEM_INFERIOR) * sizeof(int*) );

    if( posicaoBarreiras == NULL )
    {
        printf("Memoria insuficiente!");
        exit(1);
    }

    for(i = 0; i < (ALTURA_REPRESENTACAO+MARGEM_INFERIOR); i++)
    {
        /* Aloca memoria para a linha 'i' da matrix oceano */
    	posicaoBarreiras[i] = (int*) malloc( (LARGURA_REPRESENTACAO+MARGEM_DIREITA) * sizeof(int) );

        if( posicaoBarreiras[i] == NULL )
        {
            printf("Memoria insuficiente!");
            exit(1);
        }
    }

    for(i = 0; i < ALTURA_REPRESENTACAO; i++)
    	for(j = 0; j < LARGURA_REPRESENTACAO; j++)
    		posicaoBarreiras[i][j] = 0;

    ptrBarreiras->posicoes = posicaoBarreiras;    
    return ptrBarreiras;
}

void renovarBordasMarcacaoDasBarreiras(int tamanho_margem, ptr_marcaBarreiras ptrBarreiras){
    int i,j;
    for(i=0;i<tamanho_margem;i++){
    	for(j=0;j<ALTURA_REPRESENTACAO;j++){
    		ptrBarreiras->posicoes[j][i]=0;
    		ptrBarreiras->posicoes[j][LARGURA_REPRESENTACAO-1-i]=0;
    	}
    	for(j=0;j<LARGURA_REPRESENTACAO;j++){
    		ptrBarreiras->posicoes[i][j]=0;
    		ptrBarreiras->posicoes[ALTURA_REPRESENTACAO-1-i][j]=0;
    	}
    }
}
 	
void marcarBarreiras(ptr_marcaBarreiras posicaoBarreiras, int largura, int altura, int x, int y, int barreira){
    int i, j;
    altura = y + altura;
    largura = x + largura;
    for(i=y;i<altura;i++){
    	for(j=x;j<largura;j++){
    		posicaoBarreiras->posicoes[i][j] = barreira;
    	}
    }
}

void imprimeRepresentacaoBarreiras(ptr_marcaBarreiras ptrBarreiras){
    int i,j;
    
    for(i=0;i<ALTURA_REPRESENTACAO+MARGEM_INFERIOR;i++){
    	for(j=0;j<LARGURA_REPRESENTACAO+MARGEM_DIREITA;j++)
    		printf("%d",ptrBarreiras->posicoes[i][j]);
    	printf("\n");
    }
}

void retornaPtoDeColisaoComBarreira(posicao *pos, int *x, int *y, ptr_marcaBarreiras posicaoBarreiras){
	int i, j;
	int sentY, sentX, indInX, indInY;
	linha diagRet = pos->diagPrincipalRet;
	
	sentY = pos->direcao_y/abs(pos->direcao_y);
	sentX = pos->direcao_x/abs(pos->direcao_x);
	
	*x=-1; *y=-1;
	
	indInX = diagRet.xEsq;
	indInY = diagRet.yDir;
	if(sentX){
		indInX = diagRet.xDir;
	}
	if(!sentY){/*sentido para cima: verificar a partir da primeira linha*/
		indInY = diagRet.yEsq;
	}
	
	for(i=indInY;i>=diagRet.yEsq && i<=diagRet.yDir;i+=sentY)
		for(j=indInX;j>=diagRet.xEsq && j<=diagRet.xDir;j+=sentX){
			if(posicaoBarreiras->posicoes[i][j]<0){
				*x = i;
				*y = j;
				return;				
			}
		}
}

void definirCoordenadasBarreiras(ptr_marcaBarreiras posicaoBarreiras){
	int ln, marcarLinha,i,j;

    for(i = 0; i < ALTURA_REPRESENTACAO; i++){
    	ln = 0;
    	marcarLinha=1;
    	for(j = 0; j < LARGURA_REPRESENTACAO; j++){
    		if(posicaoBarreiras->posicoes[i][j]>0){
    			if(marcarLinha){
    				posicaoBarreiras->posicoes[ln][j]=j;
    				marcarLinha = 0;
    			}
    			posicaoBarreiras->posicoes[i][0]=j;/*marca na linha*/
    			break;
    		}
    		else if (!marcarLinha){
    			marcarLinha = 1;
    			ln=i;/*próxima posição*/
    		}
    	}
    }

    for(i = 0; i < ALTURA_REPRESENTACAO; i++){
    	ln = LARGURA_REPRESENTACAO-1;
    	marcarLinha=1;
    	for(j = LARGURA_REPRESENTACAO-1; j >=0; j--){
    		if(posicaoBarreiras->posicoes[i][j]>0){
    			if(marcarLinha){
    				posicaoBarreiras->posicoes[ln][j]=j;
    				marcarLinha = 0;
    			}
    			posicaoBarreiras->posicoes[i][0]=j;/*marca na linha*/
    			break;
    		}
    		else if (!marcarLinha){
    			marcarLinha = 1;
    			ln=i;/*próxima posição*/
    		}
    	}
    }    
    
}


