/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#include <stdlib.h>
#include <stdio.h>

#include "../utils.h"
#include "estatistica.h"

#include "../passageiro.h"
#include "../bote.h"
#include "../simulacao.h"
#include "../representacao.h"

int gerarRelatorio(int tempo_simulacao)
{
    int i;

    double freq, velocidade;
    unsigned int semente = 0;

    medidas *m;

    representacao oceano;
    passageiros *ps;
    bote *b1, *b2;
    recifes *rs;
    navio *nav;
    return 0;
    freq = randIntervalo(1, 100);
    velocidade = randIntervalo(MIN_VELOCIDADE_INICIAL, MAX_VELOCIDADE_INICIAL);

    m = inicializarEstatistica();

    /*inicializarSimulacao(&oceano, &ps, &b1, &b2, &rs, &nav);

    for(i = 0; i < tempo_simulacao; i++)
    {
        interacaoSimulacao(oceano, ps, b1, b2, nav, freq, velocidade, semente);

        definirVisualRepresentacao(oceano, ps, rs, b1, b2, nav);
*/
        /* Recolhe os dados dos passageiros para realizar as estatisticas */
  /*      recolherDadosEstatistica(m, ps);
    }*/

    /* Imprime o relatório no final da bateria de testes */
    imprimirEstatistica(tempo_simulacao, m);

    destruirEstatistica(m);

    destruirSimulacao(oceano, ps, b1, b2, rs, nav);

    //return 0;
}

/*int main(int argc, char **argv)
{
    gerarRelatorio(TEMPO_SIMULACAO);

    return 0;
}*/
