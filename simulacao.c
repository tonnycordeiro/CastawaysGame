/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

/*
Arquivo da funcao que gerencia toda a simulacao do oceano
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "simulacao.h"

void simular(double frequencia, int velocidade, unsigned int semente)
{
    int i;
    ptr_marcaBarreiras ptrBarreiras; 
	representacao oceano;
    passageiros *ps;    
    bote *b1, *b2;
    recifes *rs;
    navio *navio;
    
	struct timespec t;
    
    struct timeval t_inicial, t_final;

    inicializarSimulacao(&oceano, &ps, &b1, &b2, &rs, &navio, &ptrBarreiras);    
    
    /*todo: teste:*/
    /*imprimeRepresentacaoBarreiras(ptrBarreiras);*/
    
    for(i = 0; i < TEMPO_SIMULACAO; i++)
    {
    	t.tv_sec = 0.0;
    	t.tv_nsec = 100000000.0;
    
    	/* Guarda o tempo de início da geração do quadro */
    	gettimeofday(&t_inicial, NULL);
    	
        interacaoSimulacao(oceano, ps, b1, b2, navio, frequencia, velocidade, semente,ptrBarreiras);/*, */

        definirVisualRepresentacao(oceano, ps, rs, b1, b2, navio);

        imprimirRepresentacao(oceano);

        PRINT_INFO_TELA(ps);
        
        /* Guarda o tempo de término da geração do quadro */ 
        gettimeofday(&t_final, NULL);
        
        /* Desconta o tempo gasto no processamento do quadro
           no tempo que a execução deverá ficar 'dormindo',
           tornando a simulação mais real. */ 
    	t.tv_nsec -= (t_final.tv_usec - t_inicial.tv_usec) * 1000;

        nanosleep(&t, NULL);
    }

    destruirSimulacao(oceano, ps, b1, b2, rs, navio);
}

void inicializarSimulacao(representacao *oceano, passageiros **ps, bote **b1, bote **b2, recifes **rs, navio **n, ptr_marcaBarreiras *ptrBarreiras)
{
	*ptrBarreiras = inicializarMarcacaoDasBarreiras();
	
    *oceano = inicializarRepresentacao();
    *ps = inicializarPassageiros( MAX_PASSAGEIROS_TELA );
    
    *b1 = inicializarBote();
    *b2 = inicializarBote();
    
    *rs = inicializarRecifes();
    
    *n = inicializarNavio(*ptrBarreiras);
}

void destruirSimulacao(representacao oceano, passageiros *ps, bote *b1, bote *b2, recifes *rs, navio *nav)
{

	/* Destrói os botes */
	destruirBote(b1);
	destruirBote(b2);

	/* Destrói os recifes */
	destruirRecifes(rs);
	
	/* Destrói o navio */
	destruirNavio(nav);
	
    destruirPassageiros(ps);
    
    destruirRepresentacao(oceano);
}

void interacaoSimulacao(representacao oceano, passageiros *ps, bote *b1, bote *b2, navio *n, double frequencia, int velocidade, unsigned int semente, ptr_marcaBarreiras ptrBarreiras)
{
    calcularDirecaoPassageiros(ps);

    eliminarPassageiros(ps);
    
    calcularPassageirosResgatados(ps, b1);
    calcularPassageirosResgatados(ps, b2);
    criarPassageiros(ps, frequencia, velocidade, semente,ptrBarreiras);

    calcularColisaoPassageiros(ps);
    calcularColisaoNavio(ps, n);
    /*calcularColisaoComBarreira(ps,ptrBarreiras);*/
    
    eliminarPassageiros(ps);

    atualizarTempoPassageiros(ps);
}
