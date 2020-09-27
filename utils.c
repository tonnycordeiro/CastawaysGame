/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

/*
Arquivo que reúne funções utilizadas, ou que poderão ser utilizadas em todo o jogo
*/

#include <stdlib.h>
#include <time.h>

#include "utils.h"

/* Calcula um número aleatório entre min e max */
double randIntervalo( double min, double max )
{
    /* Variável estática para garantir que em cada geração
       de número aleatório seja usada uma semente diferente.
       Dessa forma o conjuto de números gerados fica mais
       disperso, pois em muitos momentos essa função
       será chamada em intervalos de tempo tão pequenos
       que o valor de clock() será o mesmo. */
    static int geracoes = 0;
    double r;

    srand( clock() + (++geracoes));

    /* Gera um número real no intevalo [0 e 1[ */
    r = (double)rand() / ( (double)RAND_MAX + 1 );

    return min + (r * (max - min));
}

/*verifica se borda1<= valor <=borda2*/
int valorEntre(int valor, int borda1, int borda2)
{
	return valor >= borda1 && valor <= borda2;
}

int minimo(int x, int y){
	return (x <= y)? x : y;
}
