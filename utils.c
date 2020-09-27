/*
  Nome e n� USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

/*
Arquivo que re�ne fun��es utilizadas, ou que poder�o ser utilizadas em todo o jogo
*/

#include <stdlib.h>
#include <time.h>

#include "utils.h"

/* Calcula um n�mero aleat�rio entre min e max */
double randIntervalo( double min, double max )
{
    /* Vari�vel est�tica para garantir que em cada gera��o
       de n�mero aleat�rio seja usada uma semente diferente.
       Dessa forma o conjuto de n�meros gerados fica mais
       disperso, pois em muitos momentos essa fun��o
       ser� chamada em intervalos de tempo t�o pequenos
       que o valor de clock() ser� o mesmo. */
    static int geracoes = 0;
    double r;

    srand( clock() + (++geracoes));

    /* Gera um n�mero real no intevalo [0 e 1[ */
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
