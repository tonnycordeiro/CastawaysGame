/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

/*
Arquivo re reune funções responsáveis pelo gerenciamento dos passageiros
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "passageiro.h"
#include "representacao.h"
#include "utils.h"
#include "funcao_grafica.h"

/* Inicializa uma lista ligada (com cabeça) para guardar os passageiros */
passageiros* inicializarPassageiros(int max)
{
    passageiros *ps = (passageiros*) malloc( sizeof(passageiros) );

    /* Aloca memória para a cabeça da lista */
    ps->head = (passageiro*) malloc( sizeof(passageiro) );

    if( ps->head == NULL )
    {
        printf("Memória insuficiente!");
        exit(1);
    }
    
    ps->head->posicao = NULL;
    ps->head->prox = NULL;

    /* Define a quantidade máxima de passageiros (nós) */
    ps->quantidade_maxima = max;

    /* Guarda a quantidade de atual de passageiros na lista */
    ps->quantidade = 0;

    return ps;
}

/* Função que chama a função de destruição de passageiros de forma recursiva */
void destruirPassageiroR(passageiros *ps, passageiro *p)
{
    if( p->prox != NULL )
        destruirPassageiroR( ps, p->prox );

    destruirPassageiro( ps, p );
}

/* Função que destroi cada passageiro da lista e no final a própria lista de passageiros */
void destruirPassageiros(passageiros *ps)
{
    destruirPassageiroR(ps, ps->head);
    free(ps);
}

/*Função que destroi um passageiro*/
void destruirPassageiro(passageiros *ps, passageiro *p)
{
	ps->quantidade--;
	
	if( p->posicao != NULL )
    	free( p->posicao );

	free( p );
}

/*Define o tamanho do passageiro com relação a sua massa*/
int definirTamanhoPassageiro(double massa)
{
	int tamanho;
	
	switch((int) massa)
	{
		case 1: /* Caso seja o cachorro (35x35) */
			tamanho = 35;				
			break;
				
		case 2: /* Caso seja uma criança (40x40) */
		case 3: /* Caso seja uma criança (40x40) */
			tamanho = 40;
			break;	

		case 4: /*Caso seja uma mulher pequena(45x45)*/
		case 5: /*Caso seja uma mulher pequena(45x45)*/
		case 7: /*Caso seja um adulto pequeno(45x45)*/
		case 8: /*Caso seja um adulto pequeno(45x45)*/
			tamanho = 45;
			break;
			
		case 6: /*Caso seja uma mulher grande(50x50)*/
		case 9: /*Caso seja um adulto pequeno(50x50)*/
			tamanho = 50;
			break;
	}
	
	return tamanho;
}

/* Função responsável por cria os passageiros na lista */
void criarPassageiros(passageiros *ps, double quantidade, int velocidade, int semente,ptr_marcaBarreiras ptrBarreiras)
{
    /* Variáveis auxiliares */
    int i, ind;

    /*controla a máxima inserção de passageiros nas laterais da tela conforme a capacidade*/
    int maxInsercaolaterais[QTDE_LADOS_TELA];
    
    /* Variável que define uma identificação para o passageiro */
    static unsigned short int id = 0;

    passageiro *p;
    int quantidade_inteira = quantidade;

    static double resto_quantidade = 0;

    maxInsercaolaterais[0]=LARGURA_REPRESENTACAO/(2*MAX_LARG_PASSAGEIRO-1);
    maxInsercaolaterais[1]=LARGURA_REPRESENTACAO/(2*MAX_LARG_PASSAGEIRO-1);
    maxInsercaolaterais[2]=ALTURA_REPRESENTACAO/(2*MAX_LARG_PASSAGEIRO-1);
    maxInsercaolaterais[3]=ALTURA_REPRESENTACAO/(2*MAX_LARG_PASSAGEIRO-1);    
    
    /* Guarda o valor inteiro da quantidade de passageiros
      que deverá ser criado */
    quantidade_inteira = (int) quantidade;

    /* Soma o resto da quantidade e a guarda da varíável
       'resto_quantidade' */
    resto_quantidade += quantidade - quantidade_inteira;

    /* Caso o resto seja maior ou igual a 1 (um) soma a
       parte inteira do resto com a quantidade de passageiros
       que deverá ser criado e guarda novamente o resto
       na variável correspondente */
    if ( resto_quantidade >= 1 )
    {
       quantidade_inteira += (int) resto_quantidade;
       resto_quantidade -= (int) resto_quantidade;
    }

    /* Caso a semente seja igual a 0 usa-se a hora
       atual como semente */
    srand( semente == 0 ? clock() : semente );

    /* Não permite que a nova quantidade de passageiros
       ultrapasse a quantidade máxima indicada na lista */
    if( ps->quantidade + quantidade_inteira > ps->quantidade_maxima )
        quantidade_inteira = ps->quantidade_maxima - ps->quantidade;

    renovarBordasMarcacaoDasBarreiras(MAX_LARG_PASSAGEIRO/2+1,ptrBarreiras);
    
    for(i = 0; i < quantidade_inteira; i++)
    {
        /* Aloca memória para o novo passageiro */
        p = (passageiro*) malloc( sizeof(passageiro) );

        if( p == NULL )
        {
            printf("Memória insuficiente!");
            exit(1);
        }

        /* Define um id para o passageiro para poder identificá-lo
           melhor nas próximas fases do jogo. Dessa forma será possível
           identificá-lo visualmente no jogo */
        p->id = id++;

        /* Define o tempo até o afogamento em uum intervalo entre
           MIN_TEMPO_AFOGAMENTO e MAX_TEMPO_AFOGAMENTO */
        p->tempo_afogamento = randIntervalo(MIN_TEMPO_AFOGAMENTO, MAX_TEMPO_AFOGAMENTO);

        /* Define a massa do passageiro em um intervalo entre
           MIN_MASSA e MAX_MASSA */
        p->massa = randIntervalo(MIN_MASSA, MAX_MASSA);
        
        /* Inicialmente não houve colisão */
        p->colidido = 0;

        /* Inicialmente o tempo em que o passageiro está em tela é zero */
        p->tempo_tela = 0;

        /* Aloca memória para os dados de posição */
        p->posicao = (posicao*) malloc( sizeof(posicao) );

        if( p->posicao == NULL )
        {
        	free( p );

            printf("Memória insuficiente!");
            exit(1);
        }
        
        /* Define o tamanho da representação do passageiro */
        p->posicao->tamanho_x  = p->posicao->tamanho_y = definirTamanhoPassageiro(p->massa);

        /* Define o módulo da velocidade em um intervalo entre
           MIN_VELOCIDADE, MAX_VELOCIDADE */
        p->posicao->modulo_velocidade = randIntervalo(MIN_VELOCIDADE_INICIAL, MAX_VELOCIDADE_INICIAL);

        /* Define, de forma aleatória, a posição inicial do passageiro */
        for(i=0;i<4;i++){
        	if(maxInsercaolaterais[ind=(rand()%4)]>0){
        		switch(ind){
	        		case 0:
	        			p->posicao->x = 0;
	        			p->posicao->y = randIntervalo(0, obterAlturaRepresentacao()-1);
	        			break;
	        		case 1:
	            		p->posicao->x = obterLarguraRepresentacao()-1;
	            		p->posicao->y = randIntervalo(0, obterAlturaRepresentacao()-1);
	        			break;
	        		case 2:
	        			p->posicao->y = 0;
	        			p->posicao->x = randIntervalo(0, obterLarguraRepresentacao()-1);
	        			break;
	        		case 3:
	        			p->posicao->y = obterAlturaRepresentacao()-1;
	        			p->posicao->x = randIntervalo(0, obterLarguraRepresentacao()-1);
	        			break;
            	}
        		maxInsercaolaterais[ind]--;
        	}
        }

        /* Define a diagonal que será usada no cálculo da colisão */
		calcularDiagonal(p->posicao);

        /* Calcula a direção inicial do passageiro */
        calcularNovaDirecao(p->posicao);

        /* Incrementa a variável de quantidade de passageiros */
        ps->quantidade++;

        /* Coloca o passageiro no começo da lista */
        p->prox = ps->head->prox;
        ps->head->prox = p;
    }
}

/* Função responsável por remover um passageiro da lista
   caso atenda a alguns requisitos descritos abaixo */
void eliminarPassageiros(passageiros *ps)
{
    passageiro *p, *p_anterior = ps->head;
    passageiro *aux;

    for( p = ps->head->prox; p != NULL; p_anterior = p, p = p->prox )
    {
        /* Caso o tempo para o afogamento seja 0 (zero) ou o passageiro esteja
           fora da area visual elimina o passageiro da lista */
        if( p->tempo_afogamento == 0 || objetoForaArea( p->posicao ) )
        {
            aux = p;
            p_anterior->prox = p->prox;
            p = p_anterior;

			destruirPassageiro( ps, aux );
        }
    }
}

/* Função que utiliza a cadeia de Markov estabelecida no jogo
   para calcular o próxima direção de cada passageiro contido
   na lista.
   Neste caso está sendo considerado a generalização da cadeia,
   ou seja, não está sendo considerado os pontos cardeais e
   colaterais definidos no enunciado do EP. */
void calcularDirecaoPassageiros(passageiros *ps)
{
    passageiro *p;
    double r;

    for(p = ps->head->prox; p != NULL; p = p->prox)
    {
        /* Somente será definido a nova direção para os passageiros não colididos */
        if( !p->colidido )
        {
            r = randIntervalo(0, 1);

            /* Pela definição da cadeia de Markov, a probabilidade
               da próxima direção ser igual à atual é de 65%.
               Portanto, caso o número aleatório entre 0 e 1 seja
               maior ou igual e 0.65, é calculado uma nova direção
               para o passageiro */
            if ( r >= 0.65 )
                calcularNovaDirecao( p->posicao );
        }

        p->colidido = 0;

        /* Calcula o deslocamento do passageiro de acordo com sua velocidade */
        calcularDeslocamentoObjeto(p->posicao);
        
        /* Calcula a diagonal usada no calculo da colisão */
        calcularDiagonal(p->posicao);
    }
}

/* Marca os passageiros colididos e atualiza o vetor direção dos mesmos
 * o após choque elástico. 
 * Obs: o Movimento terá continuidade no próximo instante */
void calcularColisaoPassageiros(passageiros *ps)
{
    passageiro *p, *p2;

    for(p = ps->head->prox; p != NULL; p = p->prox)
    {
        for(p2 = p->prox; p2 != NULL; p2 = p2->prox)
        {
            if( verificarObjetosColididosEDeslocar(p->posicao,p2->posicao,obterLarguraRepresentacao(),obterAlturaRepresentacao()))
           		/*verificarObjetosColididos( p->posicao->diagPrincipalRet, p->posicao, p2->posicao->diagPrincipalRet, p2->posicao )*/
                break;
        }

        if( p2 != NULL )
        {
            p->colidido = p2->colidido = 1;

            /*todo: verificando nova versão*/
            /*calcularDirecaoFinal( p->posicao, p2->posicao, p->massa, p2->massa );*/
            calcularDirecaoFinalv2( p->posicao, p2->posicao, p->massa, p2->massa );

        }
    }
}

/* Função que decrementa o tempo até o afogamento
   dos passageiros contidos na lista */
void atualizarTempoPassageiros(passageiros *ps)
{
    passageiro *p;

    for(p = ps->head->prox; p != NULL; p = p->prox)
    {
        p->tempo_tela++;
        p->tempo_afogamento--;
    }
}
