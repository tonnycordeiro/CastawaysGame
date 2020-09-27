/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "bote.h"
#include "representacao.h"
#include "funcao_grafica.h"
#include "utils.h"

/* Função responsável por cria os botes */
bote* inicializarBote()
{
	/* Aloca memória para os botes */
	bote *b = (bote*) malloc( sizeof(bote) );
	
	if( b == NULL )
	{
		printf("Memória insuficiente!");
		exit(1);
	}
	
	/* Inicialmente não houve colisão */
	b->colidido = 0;

	/* Nenhum passageiro foi resgatado ainda ou os mesmos se foram com o encalhamento */
	b->qtdePassageiros = 0;

	b->massa = MASSA_BOTE;

	b->posicao = (posicao*) malloc( sizeof(posicao) );

	if( b->posicao == NULL )
	{
	    printf("Memória insuficiente!");
	    exit(1);
	}

	b->posicao->tamanho_x = LARG_BOTE;
	b->posicao->tamanho_y = ALT_BOTE;	

	srand( clock() );

	/* Define o módulo da velocidade em um intervalo entre
	   MIN_VELOCIDADE, MAX_VELOCIDADE */
	b->posicao->modulo_velocidade = randIntervalo(MIN_VELOCIDADE, MAX_VELOCIDADE);

	/* Define, de forma aleatória, a posição inicial do bote */
	b->posicao->x = randIntervalo(0, obterLarguraRepresentacao()/4);
	b->posicao->y = randIntervalo(100, obterAlturaRepresentacao());

	/* Calcula a direção inicial do passageiro */
	calcularNovaDirecao(b->posicao);
	
    /* Define a diagonal que será usada no cálculo da colisão */
	calcularDiagonal(b->posicao);

	return b;
}

/* Função que destroi um bote */
void destruirBote(bote *b)
{
	free(b->posicao);
    free(b);
}

/*Verifica se passageiro colidiu com o bote, exclui o passageiro da tela e incrementa o numero de passageiros resgatados*/
void calcularPassageirosResgatados(passageiros *ps, bote *b)
{
    passageiro *p, *p_anterior = ps->head;
    passageiro *aux;

    for( p = ps->head->prox; p != NULL; p_anterior = p, p = p->prox )
    {
        if(verificarObjetosColididos( p->posicao->diagPrincipalRet, p->posicao, b->posicao->diagPrincipalRet, b->posicao ))
       	/*verificarUmaCoordenadaNoTrianguloIsosceles(ALT_BOTE,LARG_BOTE,b->posicao,p->posicao)*/
        {
            aux = p;
            p_anterior->prox = p->prox;
            p = p_anterior;

            b->qtdePassageiros++;

            destruirPassageiro(ps, aux);
        }
    }
}

void calcularDirecaoBote(bote *b, double taxa)
{
	/*taxa é um valor entre 0 e 2*PI*/
	calcularRotacaoVetor(b->posicao,taxa);
}

void calcularVelocidadeBote(bote *b, double aceleracao)
{
	b->posicao->modulo_velocidade += aceleracao; /* Velocidade = VelocidadeInicial + Aceleracao*(Tempo=1)*/
	if(b->posicao->modulo_velocidade > MAX_VELOCIDADE)
		b->posicao->modulo_velocidade = MAX_VELOCIDADE;
	else if(b->posicao->modulo_velocidade < MIN_VELOCIDADE)
		b->posicao->modulo_velocidade = MIN_VELOCIDADE;
}

void calcularColisaoBotes(bote *jg1, bote *jg2)
{
	if( verificarObjetosColididos( jg1->posicao->diagPrincipalRet, jg1->posicao, jg2->posicao->diagPrincipalRet, jg2->posicao  ) ){
            jg1->colidido = jg2->colidido = 1;
            calcularDirecaoFinal( jg1->posicao, jg2->posicao, jg1->massa, jg2->massa );
	}
}

