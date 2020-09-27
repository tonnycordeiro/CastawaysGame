/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "estatistica.h"
#include "../simulacao.h"

medidas* inicializarEstatistica()
{
    medidas *m = (medidas*) malloc( sizeof(medidas) );

    /* Aloca memória para a cabeça da lista */
    m->head = (medidas_passageiro*) malloc( sizeof(medidas_passageiro) );

    if( m->head == NULL )
    {
        printf("Memória insuficiente!");
        exit(1);
    }

    m->head->prox = NULL;

    return m;
}

void definirValores(medidas_passageiro *mp, passageiro *p)
{
    if( mp->velocidade_maxima < 0 || mp->velocidade_maxima < p->posicao->modulo_velocidade )
        mp->velocidade_maxima = p->posicao->modulo_velocidade;

    if( mp->velocidade_minima < 0 || mp->velocidade_minima > p->posicao->modulo_velocidade )
        mp->velocidade_minima = p->posicao->modulo_velocidade;

    mp->soma_velocidade += p->posicao->modulo_velocidade;

    mp->quantidade_medidas++;
}

void recolherDadosEstatistica(medidas *m, passageiros *ps)
{
    passageiro *p;
    medidas_passageiro *mp;
    int nova_medida_passageiro = 1;

    for(p = ps->head->prox; p != NULL; p = p->prox)
    {
        for(mp = m->head->prox; mp != NULL; mp = mp->prox)
            if( mp->id_passageiro == p->id )
            {
                nova_medida_passageiro = 0;
                definirValores(mp, p);

                break;
            }

        if( nova_medida_passageiro )
        {
            mp = (medidas_passageiro*) malloc( sizeof(medidas_passageiro) );

            mp->id_passageiro = p->id;

            mp->velocidade_maxima = -1;
            mp->velocidade_minima = -1;
            mp->soma_velocidade = 0;
            mp->quantidade_medidas = 0;

            definirValores(mp, p);

            /* Coloca a medida do passageiro no começo da lista */
            mp->prox = m->head->prox;
            m->head->prox = mp;
        }
    }

}

void imprimirEstatistica(int tempo_simulacao, medidas *m)
{
    medidas_passageiro *mp;

    printf("\nRELATORIO DE VARIACOES\n");

    printf("Tempo de simulacao (frames): %d\n", tempo_simulacao);

    printf("\n");
    printf("Contantes utilizadas:\n");

    printf("Maximo de passageiros na tela (MAX_PASSAGEIROS_TELA): %d\n",
        MAX_PASSAGEIROS_TELA);

    printf("Faixa de velocidade inicial dos passageiros (MIN_VELOCIDADE_INICIAL e MAX_VELOCIDADE_INICIAL): %d - %d\n",
        MIN_VELOCIDADE_INICIAL, MAX_VELOCIDADE_INICIAL);

    printf("Faixa de massa dos passageiros (MIN_MASSA e MAX_MASSA): %d - %d\n",
        MIN_MASSA, MAX_MASSA);

    printf("Faixa de tempo ate o afogamento (MIN_TEMPO_AFOGAMENTO e MAX_TEMPO_AFOGAMENTO): %d - %d\n",
        MIN_TEMPO_AFOGAMENTO, MAX_TEMPO_AFOGAMENTO);

    printf("\n");
    printf("Velocidade dos passageiros:\n");

    printf("Passageiro:     Maxima          Minima          Media\n");

    for(mp = m->head->prox; mp != NULL; mp = mp->prox)
        printf("%-15d %-15lf %-15lf %-15lf\n",
            mp->id_passageiro, mp->velocidade_maxima, mp->velocidade_minima, mp->soma_velocidade / mp->quantidade_medidas);
}

void destruirEstatisticaR(medidas_passageiro *mp)
{
    if( mp != NULL )
    {
        destruirEstatisticaR(mp->prox);
        free( mp );
    }
}

void destruirEstatistica(medidas *m)
{
    destruirEstatisticaR(m->head);
}
