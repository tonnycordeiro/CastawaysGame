/*
  Nome e n� USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef _PASSAGEIRO_H_
#define _PASSAGEIRO_H_

#include "barreiras.h"

#define MIN_VELOCIDADE_INICIAL 3
#define MAX_VELOCIDADE_INICIAL 6

#define MIN_MASSA 1	
#define MAX_MASSA 9

#define MIN_TEMPO_AFOGAMENTO 400
#define MAX_TEMPO_AFOGAMENTO 1000


struct passageiro_t{
    unsigned short int id;
    int tempo_afogamento;
    double massa;
    posicao *posicao;

    int colidido;
    int tempo_tela;

    struct passageiro_t *prox;
};

typedef struct passageiro_t passageiro;

typedef struct{
    passageiro *head;
    int quantidade_maxima;
    int quantidade;
} passageiros;

/* Inicializa uma lista ligada (com cabe�a) para guardar os passageiros */
passageiros* inicializarPassageiros(int max);

/* Fun��o que chama a fun��o de destrui��o de passageiros de forma recursiva */
void destruirPassageiros(passageiros *ps);

/*Fun��o que destroi um passageiro*/
void destruirPassageiro(passageiros *ps, passageiro *p);

/*Define o tamanho do passageiro com rela��o a sua massa*/
int definirTamanhoPassageiro(double massa);

/* Fun��o respons�vel por cria os passageiros na lista */
void criarPassageiros(passageiros *ps, double quantidade, int velocidade, int semente,ptr_marcaBarreiras ptrBarreiras);

/* Fun��o respons�vel por remover um passageiro da lista
   caso atenda a alguns requisitos descritos abaixo */
void eliminarPassageiros(passageiros *ps);

/* Fun��o que utiliza a cadeia de Markov estabelecida no jogo
   para calcular o pr�xima dire��o de cada passageiro contido
   na lista.
   Neste caso est� sendo considerado a generaliza��o da cadeia,
   ou seja, n�o est� sendo considerado os pontos cardeais e
   colaterais definidos no enunciado do EP. */
void calcularDirecaoPassageiros(passageiros *ps);

/* Marca os passageiros colididos e atualiza o vetor dire��o dos mesmos
 * o ap�s choque el�stico. 
 * Obs: o Movimento ter� continuidade no pr�ximo instante */
void calcularColisaoPassageiros(passageiros *ps);

/* Fun��o que decrementa o tempo at� o afogamento
   dos passageiros contidos na lista */
void atualizarTempoPassageiros(passageiros *ps);


#endif
