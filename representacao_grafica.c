/*
  Nome e nº USP

  Cirillo Ribeiro Ferreira - 6431200
  Matheus de Lima Barbosa - 5968663
  Tonny Costa Cordeiro - 6539839
*/
#include <stdlib.h>
#include <stdio.h>

#include "representacao_grafica.h"

/* Inicializa a biblioteca Allegro */
representacao inicializarRepresentacao()
{
	representacao oceano = (representacao) malloc( sizeof(struct representacao_t) );
			
	/* Inicializa de fato a biblioteca Allegro */
	if( allegro_init() )
	{
		printf("Não foi possivel inicializar a biblioteca gráfica\n");
		exit(1);
	}
	
	/* Define o numero de cores que será usado */
	set_color_depth( 24 );
	
	/* Inicializa o modo gráfico */
	if( set_gfx_mode( GFX_AUTODETECT_WINDOWED, LARGURA_REPRESENTACAO, ALTURA_REPRESENTACAO, 0, 0 ) )
	{
		allegro_exit();
	}

	oceano->representacao = (BITMAP*) create_bitmap(LARGURA_REPRESENTACAO, ALTURA_REPRESENTACAO);

	return oceano;
}

/* Finaliza a biblioteca grafica */
void destruirRepresentacao(representacao oceano)
{
	if( oceano->representacao != NULL )
	{
		limparRepresentacao(oceano);
		destroy_bitmap(oceano->representacao);
	}
		
	free( oceano );
	
	allegro_exit();
}

/*todo início testes*/
/*BITMAP *colidido;
BITMAP *retangulo;
*//*todo fim testes*/

/* Define a posição dos passageiros na matriz */
void definirVisualRepresentacao(representacao oceano, passageiros *ps, recifes *rs, bote *b1, bote *b2, navio *n)
{
    passageiro *p;
    recife *r;
    
    char arquivo[20];
    int i;
    
    limparRepresentacao(oceano);
    
	/* Imprime o fundo */
	oceano->fundo = (BITMAP*) load_bitmap("images/bg_oceano.bmp", NULL);
	blit(oceano->fundo, oceano->representacao, 0, 0, 0, 0, 
		LARGURA_REPRESENTACAO, ALTURA_REPRESENTACAO);
		
	/* Imprime o navio ASIMOV */
	oceano->navio = load_bitmap("images/navio.bmp", NULL);
	blit(oceano->navio, oceano->representacao, 0, 0, 
		LARGURA_REPRESENTACAO/2 - n->posicao->tamanho_x/2, 
		ALTURA_REPRESENTACAO/2 - n->posicao->tamanho_y/2, 
		oceano->navio->w, 
		oceano->navio->h);
		
	/* Imprime os botes */
	oceano->imagens[1] = load_bitmap("images/barco.bmp", NULL);
	blit(oceano->imagens[1], oceano->representacao, 0, 0, 
		b1->posicao->x - b1->posicao->tamanho_x/2, 
		b1->posicao->y - b1->posicao->tamanho_y/2, 
		oceano->imagens[1]->w, 
		oceano->imagens[1]->h);
	
	oceano->imagens[2] = load_bitmap("images/barco.bmp", NULL);
	blit(oceano->imagens[2], oceano->representacao, 0, 0, 
		b2->posicao->x - b2->posicao->tamanho_x/2, 
		b2->posicao->y - b2->posicao->tamanho_y/2,  
		oceano->imagens[2]->w, 
		oceano->imagens[2]->h);
	
	/*testes*/
	
	
	/* Imprime os recifes */
	for(r = rs->head->prox, i = 0; r != NULL && i < NUM_RECIFES; r = r->prox, i++)
	{
		/*oceano->recifes[i] = load_bitmap("images/recife.bmp", NULL);
		blit(oceano->recifes[i], oceano->representacao, 0, 0, 
			r->posicao->x - r->posicao->tamanho_x/2, 
			r->posicao->y - r->posicao->tamanho_y/2,   
			oceano->recifes[i]->w, 
			oceano->recifes[i]->h);*/		
	}
	
    /* Percorre a lista de passageiros e imprime sua identificação
       na posição corresponente na representação.
       Nesta representação, são tomadas os valores inteiros das
       posições x e y. */
    for(p = ps->head->prox, i = 3; p != NULL; p = p->prox, i++)
    {
 		sprintf(arquivo, "images/%d.bmp", ((int)p->massa) -1); 
 		
        oceano->imagens[i] = load_bitmap(arquivo, NULL);
        
        blit(oceano->imagens[i], oceano->representacao, 0, 0, 
        	p->posicao->x - p->posicao->tamanho_x/2, 
        	p->posicao->y - p->posicao->tamanho_y/2, 
        	oceano->imagens[i]->w, 
        	oceano->imagens[i]->h);
        /*todo início testes*/
/*        if (p->colidido){
        	colidido = load_bitmap("images/colisao.bmp", NULL);;
        	blit(colidido, oceano->representacao, 0, 0, 
        	        	p->posicao->x - p->posicao->tamanho_x/2, 
        	        	p->posicao->y - p->posicao->tamanho_y/2, 
        	        	oceano->imagens[i]->w, 
        	        	oceano->imagens[i]->h);	
        }
    	line(oceano->representacao, 
    	        	p->posicao->diagPrincipalRet.xEsq, 
    	        	p->posicao->diagPrincipalRet.yEsq, 
    	        	p->posicao->diagPrincipalRet.xDir, 
    	        	p->posicao->diagPrincipalRet.yDir,20);*/
    	
    	/*printf("%d %d\n",p->posicao->diagPrincipalRet.yEsq,p->posicao->diagPrincipalRet.yDir);*/
        /*todo fim testes*/
    }    
}

void imprimirRepresentacao(representacao oceano)
{
	stretch_blit(oceano->representacao,screen, 0, 0, LARGURA_REPRESENTACAO, ALTURA_REPRESENTACAO, 0, 0, LARGURA_REPRESENTACAO, ALTURA_REPRESENTACAO);
}

void limparRepresentacao(representacao oceano)
{
	int i;
	
	destroy_bitmap(oceano->fundo);
	destroy_bitmap(oceano->navio);
	
	/*todo início testes*/
/*	destroy_bitmap(colidido);
	destroy_bitmap(retangulo);
*/	/*todo fim testes*/
	
	for(i = 0; i < MAX_OBJETO_TELA; i++)
	{
		if( oceano->imagens[i] != NULL )
			destroy_bitmap(oceano->imagens[i]);
			
		oceano->imagens[i] = NULL;
	}
		
	/*clear(oceano->representacao);*/
}

int objetoForaArea(posicao *pos)
{
	int x = pos->x;
    int y = pos->y;
	
    if( x < 0 || x >= LARGURA_REPRESENTACAO )
        return 1;

    if( y < 0 || y >= ALTURA_REPRESENTACAO )
        return 1;

    return 0;
}

int obterLarguraRepresentacao()
{
	return LARGURA_REPRESENTACAO;
}

int obterAlturaRepresentacao()
{
	return ALTURA_REPRESENTACAO;
}
