/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#include <stdlib.h>
#include <stdio.h>

#include "simulacao.h"

int main(int argc, char *argv[])
{
    double freq, velocidade;
    int semente;

    if( argc < 4 )
    {
        printf("%s: uso incorreto!\n", argv[0]);
        printf("Tente: %s <frequencia> <velocidade> <semente>\n", argv[0]);
        return 1;
    }

    freq = atof( argv[1] );
    velocidade = atoi( argv[2] );
    semente = atoi( argv[3] );

    simular(freq, velocidade, semente);

    return 0;
}

