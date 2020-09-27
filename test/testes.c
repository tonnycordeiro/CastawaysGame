/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "minunit.h"

#include "../utils.h"
#include "../passageiro.h"
#include "../bote.h"
#include "../recife.h"
#include "../navio.h"
#include "../objeto.h"
#include "../representacao_textual.h2"
#include "../simulacao.h"

int tests_run = 0;

representacao oceano;
passageiros *ps;
bote *b1, *b2;
recifes *rs;
navio *nav;

/* Funções de teste de robustez */

char* testar_posicao_inicial_passageiro()
{
    passageiro *p;
    int x, y;

    for (p = ps->head->prox; p != NULL; p = p->prox)
    {
        /* Se o passageiro acabou de ser criado */
        if( p->tempo_tela == 1 )
        {
            x = p->posicao->x == 0 || p->posicao->x == NUMERO_COLUNA_REPRESENTACAO-1;
            y = p->posicao->y == 0 || p->posicao->y == NUMERO_LINHA_REPRESENTACAO-1;

            mu_assert("ERRO: Náufrago com primeira posição fora da borda.", x || y);
        }
    }

    return 0;
}

char* testar_posicao_passageiro_fora_oceano()
{
    passageiro *p;

    for (p = ps->head->prox; p != NULL; p = p->prox)
        mu_assert("ERRO: Náufrago(s) fora do campo de exibição.", !objetoForaArea(p->posicao) );

    return 0;
}

char* testar_estouro_qtde_passageiros()
{
    mu_assert("ERRO: Quantidade de náufragos acima do permitido.", ps->quantidade <= MAX_PASSAGEIROS_TELA);

    return 0;
}

char* testar_qtde_negativa_passageiros()
{
    mu_assert("ERRO: Quantidade de náufragos abaixo de ZERO.", ps->quantidade >= 0);

    return 0;
}

char* testar_passageiros_afogados()
{
    passageiro *p;

    for (p = ps->head->prox; p != NULL; p = p->prox)
        mu_assert("ERRO: Náufrago nadando com tempo de afogamento esgotado.", (p->tempo_afogamento >= 0));

    return 0;
}

/* Verifica se os passageiros colididos tomaram o rumo certo após a colisão */
char* testar_passageiros_colididos()
{
    return 0;
}

char* testar_direcao_apos_colisao()
{
    posicao *p1, *p2;
    double massa1, massa2;

    p1 = (posicao*) malloc( sizeof(posicao) );
    p2 = (posicao*) malloc( sizeof(posicao) );

    /* Define a mesma posição para os objetos */
    p1->x = p2->x = 1;
    p1->y = p2->y = 1;

    p1->direcao_x = sqrt(0.5);
    p1->direcao_y = sqrt(0.5);
    p1->modulo_velocidade = 1;

    p2->direcao_x = 1;
    p2->direcao_y = 0;
    p2->modulo_velocidade = 1;
    
    massa1 = massa2 = 10;

    calcularDirecaoFinal(p1, p2, massa1, massa2);

    mu_assert("ERRO: Massa do náufrago alterada após a colisão.", massa1 == 10 && massa2 == 10);

    free(p1);
    free(p2);

    return 0;
}

char* testar_calculo_nova_direcao()
{
    passageiro *p = (passageiro*) malloc( sizeof(passageiro) );
    double modulo_vetor;

    p->posicao = (posicao*) malloc( sizeof(posicao) );

    p->posicao->direcao_x = 1;
    p->posicao->direcao_y = 0;

    p->posicao->modulo_velocidade = 10;

    calcularNovaDirecao(p->posicao);

    /* Verifica se o módulo da velocidade não foi alterada */

    mu_assert("ERRO: Calculo da nova direção altera a velocidade do náufrago.",
        (p->posicao->modulo_velocidade == 10));

    /* Verifica se o vetor direção gerado é unitário */

    modulo_vetor = (double) pow(p->posicao->direcao_x, 2) + pow(p->posicao->direcao_y, 2);

    /* Como o módulo do vetor é do tipo double, é verificado se a
       diferença dele e 1 é menor que um número que tende a zero */
    mu_assert("ERRO: Calculo da nova direção define um vetor não unitário.", (modulo_vetor - 1 < 0.0000001) );

    free(p->posicao);
    free(p);

    return 0;
}

char* testar_deteccao_colisao()
{
    passageiro *p, *p2;

    /* Procura por passageiros colidos */
    for(p = ps->head->prox; p != NULL; p = p->prox)
    {
        for(p2 = p->prox; p2 != NULL; p2 = p2->prox)
        {
            if( verificarObjetosColididos( p->posicao->diagPrincipalRet, p->posicao, p2->posicao->diagPrincipalRet, p2->posicao ) )
                break;
        }

        if( p2 != NULL )
            mu_assert("ERRO: Colisão não registrada corretamente.", (p->colidido && p2->colidido));
    }

    return 0;
}

char* testar_representacao()
{
    passageiro *p;
    int c;

    for (p = ps->head->prox; p != NULL; p = p->prox)
    {
        c = ( oceano->representacao[(int)p->posicao->y][(int)p->posicao->x] == COLISAO );

        if( p->colidido )
            mu_assert("ERRO: Colisão não exibida no oceano.", c );
        else
            mu_assert("ERRO: Colisão não exibida no oceano.", !c );
    }

    return 0;
}

static char *rodar_bateria_testes(double freq, double velocidade)
{
    int i;

    unsigned int semente = 0;

    if( freq == -1 )
        freq = randIntervalo(1, 100);

    if( velocidade == -1 )
        velocidade = randIntervalo(MIN_VELOCIDADE_INICIAL, MAX_VELOCIDADE_INICIAL);
	
    /*inicializarSimulacao(&oceano, &ps, &b1, &b2, &rs, &nav);
    
    for(i = 0; i < TEMPO_SIMULACAO; i++)
    {
        interacaoSimulacao(oceano, ps, b1, b2, nav, freq, velocidade, semente);

        definirVisualRepresentacao(oceano, ps, rs, b1, b2, nav);*/

        /* Executa os testes */
       /* mu_run_test(testar_posicao_inicial_passageiro);
        mu_run_test(testar_posicao_passageiro_fora_oceano);
        mu_run_test(testar_estouro_qtde_passageiros);
        mu_run_test(testar_qtde_negativa_passageiros);
        mu_run_test(testar_passageiros_afogados);
        mu_run_test(testar_deteccao_colisao);
        mu_run_test(testar_representacao);
    }

    mu_run_test(testar_direcao_apos_colisao);
    mu_run_test(testar_calculo_nova_direcao);

    destruirSimulacao(oceano, ps, b1, b2, rs, nav);*/

    return 0;
}

char *all_tests()
{
    char *msg = malloc( sizeof(char) * 1000 );

    /* Executa a bateria de testes com frequencia e velocidade aleatórias */
    if(( msg = rodar_bateria_testes(-1, -1) ))
        return msg;

    /* Executa a bateria de testes com frequencia próxima a zero */
    if(( msg = rodar_bateria_testes(0.00000001, -1) ))
        return msg;

    /* Executa a bateria de testes com frequencia igual
       ao limite de passageiros na tela */
    if(( msg = rodar_bateria_testes(MAX_PASSAGEIROS_TELA, -1) ))
        return msg;

    return 0;
}

/*int main(int argc, char **argv)
{
	char *resultado = all_tests();

    if (resultado != 0)
    {
        printf("%s\n", resultado);
    }
    else
    {
        printf("TODOS OS TESTES PASSARAM\n");
    }

    printf("Testes executados: %d\n", tests_run);

    return resultado != 0;
}*/
