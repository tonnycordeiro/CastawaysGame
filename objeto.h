/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/

#ifndef __OBJETO_H__
#define __OBJETO_H__

# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */

# define MAXALT		100

typedef struct linha_s *ptrLinha;
typedef struct linha_s{
    int xEsq;
    int yEsq;

    int xDir;
    int yDir;
    
    ptrLinha prox;
    
} linha;

typedef struct
{
    int x;
    int y;
    
    double direcao_x;
    double direcao_y;
    
    /*Linha composta pelas coordenadas:
     * canto inferior esquerdo do menor "retângulo" que contém o BITMAP do passageiro
     * canto superior direito do menor "retângulo" que contém o BITMAP do passageiro
     */
    linha diagPrincipalRet;
    
    int tamanho_x;
    int tamanho_y;
    
    double modulo_velocidade;
} posicao;


void calcularDeslocamentoObjeto(posicao *pos);
void calcularDirecaoFinal(posicao *pos1, posicao *pos2, double massa1, double massa2);
void normalizarVelocidade(posicao *pos, double velocidade_x, double velocidade_y);
void calculaDeslocamentoDosEixos(posicao *pos, double *deslocamento_x, double *deslocamento_y);
void calcularNovaDirecao(posicao *pos);

int verificarObjetosColididos(linha diagRet_1, posicao *pos1, linha diagRet_2, posicao *pos2);
int verificarObjetosColididosEDeslocar(posicao *pos1, posicao *pos2, int largRepres, int altRepres);

/*Calcula a energia cinética de um objeto*/
double energiaCineticaObjeto(double velocidade, double massa);

/*Calcula a energia cinética de 2 objetos*/
double energiaCineticaTotal(double velocidade1, double velocidade2, double massa1, double massa2);

/*Calcula a quantidade de movimento*/
double qtdeMovimento(double velocidade1, double velocidade2, double massa1, double massa2);

/*Calcula a velocidade do centro de massa*/
double velocCentroMassa(double velocidade1, double velocidade2, double massa1, double massa2);

/*Calcula as velocidades do eixo X ou Y após o choque entre objetos*/
void calculoVelocUmEixo(double veloc_inicial_1, double veloc_inicial_2, double massa1, double massa2, double *veloc_final_1, double *veloc_final_2);

/* Calcula as componentes do vetor direção e módulo da velocidade finais de
   dois objetos após a colisÃ£o entre eles */
void calcularDirecaoFinalv2(posicao *pos1, posicao *pos2, double massa1, double massa2);

/*Rotaciona vetor da direção*/
void calcularRotacaoVetor(posicao *pos, double anguloR);	


#endif
