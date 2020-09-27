/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

/*
Arquivo que reúne funções referentes aos calculos de posicionamento e velocidade dos objetos do jogo
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "objeto.h"
#include "utils.h"

/* Função que calcula as componentes do vetor velocidade.
   Esse vetor deverá ser unitário. */
void calcularNovaDirecao(posicao *pos)
{
    double sinal = randIntervalo(0, 1);

    /* Define um valor entre -1 e 1 para a componente x do vetor */
    pos->direcao_x = randIntervalo(-1, 1);

    /* Como o vetor deve ser unitário, a componente x e y devem
       satisfazer a seguinte função (x**2 + y**2 = 1) */
    pos->direcao_y = sqrt(1 - pow(pos->direcao_x, 2));

    /* Como a componente y tem como solução +/- a raíz quadrada de (1 - x**2)
       e a função SQRT sempre retorna um número positio, é feito um
       'sorteio' para trocar ou não o sinal do resultado */
    if( sinal >= 0.5 )
        pos->direcao_y *= -1;
}

/* Função que calcula o deslocamento de um objeto no eixo X */
void calculaDeslocamentoDosEixos(posicao *pos, double *deslocamento_x, double *deslocamento_y)
{
	double angulo;

    /* Calcula o angulo entre o vetor direção e o eixo x */
    angulo = atan( pos->direcao_y / pos->direcao_x );
    
    *deslocamento_x = pos->modulo_velocidade * cos(angulo);

    /* Atenção: É considerado -seno(angulo), pois para deslocar-se para cima
       é necessário decrementar a posição y do objeto e não incrementá-lo */
    *deslocamento_y = pos->modulo_velocidade * -sin(angulo);
}

/* Função que calcula o deslocamento de um objeto */
void calcularDeslocamentoObjeto(posicao *pos)
{
    double deslocamento_x, deslocamento_y;

    calculaDeslocamentoDosEixos(pos,&deslocamento_x,&deslocamento_y);

    pos->x += deslocamento_x;
    pos->y += deslocamento_y;
}


/* Calcula as componentes do vetor direção e módulo da velocidade finais de
   dois objetos após a colisÃ£o entre eles */
void calcularDirecaoFinal(posicao *pos1, posicao *pos2, double massa1, double massa2)
{
	double m1 = massa1;
	double m2 = massa2;
	
    double massa_total = m1 + m2;

    double velocidade_final_x, velocidade_final_y;

    /* Calcula o angulo entre o vetor direÃ§Ã£o e o eixo x do objeto 1 */
    double angulo1 = atan( pos1->direcao_y / pos1->direcao_x );

    /* Calcula as componentes do vetor velocidade do objeto 1 */
    double veloc_inicial_1_x = pos1->direcao_x * cos(angulo1);
    double veloc_inicial_1_y = pos1->direcao_y * sin(angulo1);

    /* Calcula o angulo entre o vetor direÃ§Ã£o e o eixo x do objeto 2 */
    double angulo2 = atan( pos2->direcao_y / pos2->direcao_x );

    /* Calcula as componentes do vetor velocidade do objeto 2 */
    double veloc_inicial_2_x = pos2->direcao_x * cos(angulo2);
    double veloc_inicial_2_y = pos2->direcao_y * sin(angulo2);
    
    /*todo: teste*/
    double velocidade_final_2_x,velocidade_final_2_y,velocidade_final_1_x,velocidade_final_1_y;
    
    velocidade_final_x = ( 2 * (m1 - m2) * veloc_inicial_1_x ) / massa_total + ( 2 * m2 * veloc_inicial_2_x ) / massa_total;
    velocidade_final_y = ( 2 * (m1 - m2) * veloc_inicial_1_y ) / massa_total + ( 2 * m2 * veloc_inicial_2_y ) / massa_total;
    velocidade_final_1_x = velocidade_final_x;
    velocidade_final_1_y = velocidade_final_y;
    /* Normaliza o vetor velocidade */
    normalizarVelocidade( pos1, velocidade_final_x, velocidade_final_y );

    velocidade_final_x = ( 2 * m1 * veloc_inicial_1_x ) / ( m2 - m1 ) + ( veloc_inicial_2_x * ( m2 - m1 ) / massa_total );
    velocidade_final_y = ( 2 * m1 * veloc_inicial_1_y ) / ( m2 - m1 ) + ( veloc_inicial_2_y * ( m2 - m1 ) / massa_total );
    velocidade_final_2_x = velocidade_final_x;
    velocidade_final_2_y = velocidade_final_y;
    /* Normaliza o vetor velocidade */
    normalizarVelocidade( pos2, velocidade_final_x, velocidade_final_y );
    
	/*printf("qtde movimento-> %5.2f = %5.2f \n",(m1*veloc_inicial_1 + m2*veloc_inicial_2),( m1*velocidade_final_1 + velocidade_final_2*m2));
	printf("cons energia ->  %5.2f = %5.2f \n",(m1*veloc_inicial_1*veloc_inicial_1 + m2*veloc_inicial_2*veloc_inicial_2),(m1*velocidade_final_1*velocidade_final_1 + m2*velocidade_final_2*velocidade_final_2));*/	
    
    
    /*if( velocidade_final_1_x == ((m1*veloc_inicial_1_x + m2*veloc_inicial_2_x - velocidade_final_2_x*m2)/m1) )
    	printf("conserv de movimento\n");
	printf("movimento-> %5.2f = %5.2f \n",velocidade_final_1_x,((m1*veloc_inicial_1_x + m2*veloc_inicial_2_x - velocidade_final_2_x*m2)/m1));
    if( velocidade_final_1_x == (sqrt((m1*veloc_inicial_1_x*veloc_inicial_1_x + m2*veloc_inicial_2_x*veloc_inicial_2_x - m2*velocidade_final_2_x*velocidade_final_2_x)/m1)) )
    	printf("conserv de energia cinética\n");
   	printf("energia -> %5.2f = %5.2f \n",velocidade_final_1_x,(sqrt((m1*veloc_inicial_1_x*veloc_inicial_1_x + m2*veloc_inicial_2_x*veloc_inicial_2_x - m2*velocidade_final_2_x*velocidade_final_2_x)/m1)));*/    	
    
    
}

void normalizarVelocidade(posicao *pos, double velocidade_x, double velocidade_y)
{
    /* Define o módulo da velocidade */
    pos->modulo_velocidade = sqrt( pow(velocidade_x, 2) + pow(velocidade_y, 2) );

    /* Normaliza as componentes do vetor direÃ§Ã£o */
    pos->direcao_x = velocidade_x / pos->modulo_velocidade;
    pos->direcao_y = velocidade_y / pos->modulo_velocidade;
}

/*Verifica se algum passageiro está colidindo com outro*/
/*int verificarObjetoContido(linha diagonal1, linha diagonal2)
{
	if( valorEntre(diagonal1.xEsq, diagonal2.xDir, diagonal2.xEsq)
	 	&& valorEntre(diagonal1.yDir, diagonal2.yEsq, diagonal2.yDir) )
	 	return 1;
	else if( valorEntre(diagonal1.yDir, diagonal2.yDir, diagonal2.yEsq)
	 	&& valorEntre(diagonal1.xDir, diagonal2.xEsq, diagonal2.xDir) )
	 	return 1;
	else if( valorEntre(diagonal1.yEsq, diagonal2.yDir, diagonal2.yEsq)
	 	&& valorEntre(diagonal1.xDir, diagonal2.xEsq, diagonal2.xDir) )
	 	return 1;
	else if( valorEntre(diagonal1.yEsq, diagonal2.yDir, diagonal2.yEsq)
	 	&& valorEntre(diagonal1.xEsq, diagonal2.xEsq, diagonal2.xDir) )
	 	return 1;
	 	
	 return 0;	
}*/

int verificarObjetoContido(linha diagRet_1, linha diagRet_2) /*posicao *pos1, posicao *pos2 */
{
	int ehIterseccao = 0;
	
	/* diagRet_2.yEsq <= diagRet_1.yEsq <= diagRet_2.yDir*/
	if(diagRet_1.yEsq >= diagRet_2.yEsq && diagRet_1.yEsq <= diagRet_2.yDir)
	{
		ehIterseccao = 1;
	}
	/* diagRet_2.yEsq <= diagRet_1.yDir <= diagRet_2.yDir*/
	else if(diagRet_1.yDir >= diagRet_2.yEsq && diagRet_1.yDir <= diagRet_2.yDir)
	{
		ehIterseccao = 1;
	}
	/*Retângulo da fig 1 CONTÉM o da fig 2*/
	else if(diagRet_1.yEsq <= diagRet_2.yEsq && diagRet_1.yDir >= diagRet_2.yDir) 
	{
		ehIterseccao = 1;
	}
	/*o eixo y pertence a zona de intersecção. Vejamos o eixo x.*/
	if(ehIterseccao){
		ehIterseccao = 0;
		/* diagRet_2.xEsq <= diagRet_1.xEsq <= diagRet_2.xDir*/
		if(diagRet_1.xEsq >= diagRet_2.xEsq && diagRet_1.xEsq <= diagRet_2.xDir)
		{
			ehIterseccao = 1;
		}
		/* diagRet_2.xEsq <= diagRet_1.xDir <= diagRet_2.xDir*/
		else if(diagRet_1.xDir >= diagRet_2.xEsq && diagRet_1.xDir <= diagRet_2.xDir)
		{
			ehIterseccao = 1;
		}
		/*Retângulo da fig 1 CONTÉM o da fig 2*/
		else if(diagRet_1.xEsq <= diagRet_2.xEsq && diagRet_1.xDir >= diagRet_2.xDir) 
		{
			ehIterseccao = 1;
		}
	}
	return ehIterseccao; 
	
}

int deslocaObjetoContido(posicao *pos1, posicao *pos2, int largRepres, int altRepres) /*posicao *pos1, posicao *pos2 */
{
	linha diagRet_1, diagRet_2;
	int ehIterseccao = 0;
	/*deslocamentos calculados em função da posição 1*/
	int deslocY;
	int deslocX;

	diagRet_1 = pos1->diagPrincipalRet;
	diagRet_2 = pos2->diagPrincipalRet;
	
	/* diagRet_2.yEsq <= diagRet_1.yEsq <= diagRet_2.yDir*/
	if(diagRet_1.yEsq >= diagRet_2.yEsq && diagRet_1.yEsq <= diagRet_2.yDir)
	{
		deslocY = (diagRet_2.yDir - diagRet_1.yEsq);
		ehIterseccao = 1;
	}
	/* diagRet_2.yEsq <= diagRet_1.yDir <= diagRet_2.yDir*/
	else if(diagRet_1.yDir >= diagRet_2.yEsq && diagRet_1.yDir <= diagRet_2.yDir)
	{
		deslocY = (diagRet_1.yDir - diagRet_2.yEsq)*(-1);
		ehIterseccao = 1;
	}
	/*Retângulo da fig 1 CONTÉM o da fig 2*/
	else if(diagRet_1.yEsq <= diagRet_2.yEsq && diagRet_1.yDir >= diagRet_2.yDir) 
	{
		deslocY = (diagRet_2.yDir-diagRet_2.yEsq);
		if((diagRet_2.yEsq-diagRet_1.yEsq)<(diagRet_1.yDir-diagRet_2.yDir)){
			deslocY += (diagRet_2.yEsq-diagRet_1.yEsq);
		}
		else{
			deslocY += (diagRet_1.yDir-diagRet_2.yDir);
			deslocY *= -1;
		}
		ehIterseccao = 1;
	}
	/*o eixo y pertence a zona de intersecção. Vejamos o eixo x.*/
	if(ehIterseccao){
		ehIterseccao = 0;
		/* diagRet_2.xEsq <= diagRet_1.xEsq <= diagRet_2.xDir*/
		if(diagRet_1.xEsq >= diagRet_2.xEsq && diagRet_1.xEsq <= diagRet_2.xDir)
		{
			deslocX = (diagRet_2.xDir - diagRet_1.xEsq);
			ehIterseccao = 1;
		}
		/* diagRet_2.xEsq <= diagRet_1.xDir <= diagRet_2.xDir*/
		else if(diagRet_1.xDir >= diagRet_2.xEsq && diagRet_1.xDir <= diagRet_2.xDir)
		{
			deslocX = (diagRet_1.xDir - diagRet_2.xEsq)*(-1);
			ehIterseccao = 1;
		}
		/*Retângulo da fig 1 CONTÉM o da fig 2*/
		else if(diagRet_1.xEsq <= diagRet_2.xEsq && diagRet_1.xDir >= diagRet_2.xDir) 
		{
			deslocX = (diagRet_2.xDir-diagRet_2.xEsq);
			if((diagRet_2.xEsq-diagRet_1.xEsq)<(diagRet_1.xDir-diagRet_2.xDir)){
				deslocX += (diagRet_2.xEsq-diagRet_1.xEsq);
			}
			else{
				deslocX += (diagRet_1.xDir-diagRet_2.xDir);
				deslocX *= -1;
			}			
			ehIterseccao = 1;
		}
	}
	if(ehIterseccao){
		if((pos1->y + deslocY < 0) || (pos1->y + deslocY > altRepres-1)){
			if((pos2->y - deslocY >= 0) || (pos1->y - deslocY < altRepres))
				pos1->y-=deslocY;	
		}
		else
			pos1->y+=deslocY;
	
		if((pos1->x + deslocX < 0) || (pos1->x + deslocX > largRepres-1)){
			if((pos2->x - deslocX >= 0) && (pos1->x - deslocX < largRepres))
				pos2->x-=deslocX;
		}
		else
			pos1->x+=deslocX;
	}
	return ehIterseccao; 
}

/*Verifica a colisao simetricamente*/
int verificarObjetosColididos(linha diagonal1, posicao *pos1, linha diagonal2, posicao *pos2)
{
	return verificarObjetoContido(diagonal1, diagonal2);
}

/*Verifica os objetos colididos e tira a intersecção entre eles*/
int verificarObjetosColididosEDeslocar(posicao *pos1, posicao *pos2, int largRepres, int altRepres)
{
	return deslocaObjetoContido(pos1, pos2,largRepres,altRepres);
}

/*Calcula a energia cinética de um objeto*/
double energiaCineticaObjeto(double velocidade, double massa){
	return massa*velocidade*velocidade/2;
}

/*Calcula a energia cinética de 2 objetos*/
double energiaCineticaTotal(double velocidade1, double velocidade2, double massa1, double massa2){
	return energiaCineticaObjeto(velocidade1,massa1) + energiaCineticaObjeto(velocidade2,massa2); 
}

/*Calcula a quantidade de movimento*/
double qtdeMovimento(double velocidade1, double velocidade2, double massa1, double massa2){
	return (massa1*velocidade1 + massa2*velocidade2);
}

/*Calcula a velocidade do centro de massa*/
double velocCentroMassa(double velocidade1, double velocidade2, double massa1, double massa2){
	return qtdeMovimento(velocidade1,velocidade2,massa1,massa2)/(massa1 + massa2);
}

/*Calcula as velocidades do eixo X ou Y após o choque entre objetos*/
void calculoVelocUmEixo(double veloc_inicial_1, double veloc_inicial_2, double massa1, double massa2, double *veloc_final_1, double *veloc_final_2){
	double a, b, c, x1, x2;
	double sentido;
	double vcm; /*velocidade do centro de massa*/
	double qtdeMov;
	double m1 = massa1;
	double m2 = massa2;

    vcm = velocCentroMassa(veloc_inicial_1,veloc_inicial_2,m1,m2);
    veloc_inicial_1 = veloc_inicial_1 - vcm; /*velocidade em relação ao centro de massa*/
    veloc_inicial_2 = veloc_inicial_2 - vcm;
    
    /*sentido = veloc_inicial_1_x / abs(veloc_inicial_1_x);*/
    
    qtdeMov = qtdeMovimento(veloc_inicial_1,veloc_inicial_2,m1,m2);
    
    a = m2*m2+m1*m2;
    b = -2*qtdeMov*m2;
    c = qtdeMov*qtdeMov - 2*m1*(energiaCineticaTotal(veloc_inicial_1,veloc_inicial_2,m1,m2));
    
    x1 = (-b + sqrt(b*b-4*a*c))/(2*a);
    x2 = (-b - sqrt(b*b-4*a*c))/(2*a);
    
    sentido = veloc_inicial_2; /*sentido após colisão: contrário ao centro de massa*/
    if(sentido!=0){
    	sentido/=(fabs(sentido)*(-1));
    }
    if (sentido>=0){
    	if(x1>=0)
    		*veloc_final_2 = x1;
    	else
    		*veloc_final_2 = x2;
    } else{
    	if(x1<0)
    		*veloc_final_2 = x1;
    	else
    		*veloc_final_2 = x2;
    }	
    *veloc_final_1 = (qtdeMov - m2 * (*veloc_final_2))/m1; 
    
    *veloc_final_1 = *veloc_final_1 + vcm;
    *veloc_final_2 = *veloc_final_2 + vcm;
}

/* Calcula as componentes do vetor direção e módulo da velocidade finais de
   dois objetos após a colisÃ£o entre eles */
void calcularDirecaoFinalv2(posicao *pos1, posicao *pos2, double massa1, double massa2)
{
	double m1 = massa1;
	double m2 = massa2;
	
    double velocidade_final_1_x, velocidade_final_1_y;
    double velocidade_final_2_x, velocidade_final_2_y;

    /* Calcula o angulo entre o vetor direÃ§Ã£o e o eixo x do objeto 1 */
    double angulo1 = atan( pos1->direcao_y / pos1->direcao_x );

    /* Calcula as componentes do vetor velocidade do objeto 1 */
    double veloc_inicial_1_x = pos1->direcao_x * cos(angulo1);
    double veloc_inicial_1_y = pos1->direcao_y * sin(angulo1);

    /* Calcula o angulo entre o vetor direÃ§Ã£o e o eixo x do objeto 2 */
    double angulo2 = atan( pos2->direcao_y / pos2->direcao_x );

    /* Calcula as componentes do vetor velocidade do objeto 2 */
    double veloc_inicial_2_x = pos2->direcao_x * cos(angulo2);
    double veloc_inicial_2_y = pos2->direcao_y * sin(angulo2);


    calculoVelocUmEixo(veloc_inicial_1_x,veloc_inicial_2_x,m1,m2,&velocidade_final_1_x,&velocidade_final_2_x);
    calculoVelocUmEixo(veloc_inicial_1_y,veloc_inicial_2_y,m1,m2,&velocidade_final_1_y,&velocidade_final_2_y);
    
    /* Normaliza o vetor velocidade */
    normalizarVelocidade(pos1, velocidade_final_1_x, velocidade_final_1_y );

    /* Normaliza o vetor velocidade */
    normalizarVelocidade( pos2, velocidade_final_2_x, velocidade_final_2_y );
    
}

/*Rotaciona vetor da direção*/
void calcularRotacaoVetor(posicao *pos, double anguloR)
{
    /* Calcula o angulo entre o vetor direção e o eixo x do objeto*/
    double angulo = atan( pos->direcao_y / pos->direcao_x );

    /* Calcula as componentes do vetor velocidade do objeto*/
    double veloc_x = pos->direcao_x * cos(angulo);
    double veloc_y = pos->direcao_y * sin(angulo);

    angulo += anguloR; /*após rotação*/
    
    if (cos(angulo) == 0) /*k*90º  (float)angulo == (float)M_PI_2*/
    	pos->direcao_x = 0;
    else
    	pos->direcao_x = veloc_x/cos(angulo);
    
    if (sin(angulo) == 0) /*0º*/
    	pos->direcao_y = 0;
    else
    	pos->direcao_y = veloc_y/sin(angulo); 
    
    /* Normaliza o vetor velocidade */
    normalizarVelocidade( pos, veloc_x, veloc_y );

}












