
#include "proj_h"

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

/*------------------------------------------------------------
| Nome: grafico
| Accao: determina se deve ser criada a janela gráfica ou exibido o menu de pausa;
| Recebe: apontador para inicio da lista de linhas, comboios e ligacoes;
|		  vetor com os valores de altura e largura da janela grafica;
+-----------------------------------------------------------*/

void grafico(int d[],LL *ilinha, LG *iligar, LC *icomb){
	int i=0, j=1, r=1;
	COR cores[10];
	
	cores[0].r = 230; cores[0].g = 230; cores[0].b = 230; strcpy(cores[0].nome , "BRANCO");
	cores[1].r = 255; cores[1].g = 255; cores[1].b = 0; strcpy(cores[1].nome , "AMARELO"); 
	cores[2].r = 185; cores[2].g = 0; cores[2].b = 255; strcpy(cores[2].nome , "ROXO");
	cores[3].r = 20; cores[3].g = 20; cores[3].b = 20; strcpy(cores[3].nome , "PRETO");
	cores[4].r = 125; cores[4].g = 90; cores[4].b = 55; strcpy(cores[4].nome , "CASTANHO");
	cores[5].r = 0; cores[5].g = 0; cores[5].b = 240; strcpy(cores[5].nome , "AZUL");
 	cores[6].r = 0; cores[6].g = 190; cores[6].b = 0; strcpy(cores[6].nome , "VERDE");
	cores[7].r = 255; cores[7].g = 0; cores[7].b = 0; strcpy(cores[7].nome , "VERMELHO");
	cores[8].r = 0; cores[8].g = 200; cores[8].b = 220; strcpy(cores[8].nome , "CIANO");
	cores[9].r = 145; cores[9].g = 145; cores[9].b = 145; strcpy(cores[9].nome , "CINZENTO");
	
	while(i==0){
		if(j==0)
			r=0;
			
		i = cria_janela(d, ilinha, iligar, icomb, r);
				
		if(i==1){	
			SDL_Quit();
			gfxPrimitivesSetFont(NULL, 0, 0);		
			j = menu_pausa(d, icomb, ilinha, iligar, cores);
		}
		if(i==2)
			j=1;
		
		SDL_Quit();
		gfxPrimitivesSetFont(NULL, 0, 0);
		i=j;
	}		
	SDL_Quit();
	gfxPrimitivesSetFont(NULL, 0, 0);		
}

/*------------------------------------------------------------
| Nome: cria_janela
| Accao: cria a janela gráfica, com a simulacao do movimento dos comboios;
| Recebe: apontador para inicio da lista de linhas, comboios e ligacoes;
|		  vetor com os valores de altura e largura da janela grafica;
|		  r - permite saber se os comboios devem proseguir (caso tenha sido
|			  feita uma pausa), ou fazer reset da sua posição (após stop);
| Devolve: inteiro (i) que permite saber se foi efectuada uma pausa ou se
|		   o utilizador acabou a simulação;
+-----------------------------------------------------------*/

int cria_janela(int d[],LL *ilinha, LG *iligar, LC *icomb, int r){
	int i=0;
	COR cores[10];
	LL *auxlinha;
	LG *auxligar;
	LC *auxcomb;
	SDL_Rect r1, r2, r3;

	if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){               
		g_pWindow = SDL_CreateWindow("Simulação", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, d[0], d[1], SDL_WINDOW_SHOWN);
		if(g_pWindow != 0){
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);                     
		}
	}	
	SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(g_pRenderer);
	
	r1.x = d[0]-115; r1.y = 40; r1.h = 15; r1.w = 100;
	r2.x = d[0]-115; r2.y = 65; r2.h = 15; r2.w = 100;
	r3.x = d[0]-115; r3.y = 90; r3.h = 15; r3.w = 100;

	cores[0].r = 230; cores[0].g = 230; cores[0].b = 230; strcpy(cores[0].nome , "BRANCO");
	cores[1].r = 255; cores[1].g = 255; cores[1].b = 0; strcpy(cores[1].nome , "AMARELO"); 
	cores[2].r = 185; cores[2].g = 0; cores[2].b = 255; strcpy(cores[2].nome , "ROXO");
	cores[3].r = 20; cores[3].g = 20; cores[3].b = 20; strcpy(cores[3].nome , "PRETO");
	cores[4].r = 125; cores[4].g = 90; cores[4].b = 55; strcpy(cores[4].nome , "CASTANHO");
	cores[5].r = 0; cores[5].g = 0; cores[5].b = 240; strcpy(cores[5].nome , "AZUL");
 	cores[6].r = 0; cores[6].g = 190; cores[6].b = 0; strcpy(cores[6].nome , "VERDE");
	cores[7].r = 255; cores[7].g = 0; cores[7].b = 0; strcpy(cores[7].nome , "VERMELHO");
	cores[8].r = 0; cores[8].g = 200; cores[8].b = 220; strcpy(cores[8].nome , "CIANO");
	cores[9].r = 145; cores[9].g = 145; cores[9].b = 145; strcpy(cores[9].nome , "CINZENTO");
		
	for(i=0;i<2;){
		auxlinha=ilinha;
		auxligar=iligar;
		auxcomb=icomb;		
		SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
		i = menu_iterativo(d, r1, r2, r3);		
		if(i==1){
			return i;
		}					
		graf_insere_linhas(auxlinha, cores);	
		liga_linhas(auxlinha, auxligar);		
		graf_insere_comboio(auxlinha, auxcomb, cores, r);		
		r=0;		
		SDL_RenderPresent(g_pRenderer);		
		SDL_Delay(100);		
		SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);						
		SDL_RenderClear(g_pRenderer);
	}						
	SDL_Quit();
	gfxPrimitivesSetFont(NULL, 0, 0);	
	return i;
}

/*------------------------------------------------------------
| Nome: menu_iterativo
| Accao: desenha na simulacao um menu com 3 opcoes;
| Recebe: posicao de cada opcao do menu;
|		  vetor com os valores de altura e largura da janela grafica;
| Devolve: inteiro (i) que permite saber qual a opcao escolhida pelo
|		   utilizador;
+-----------------------------------------------------------*/

int menu_iterativo(int d[], SDL_Rect r1, SDL_Rect r2, SDL_Rect r3){
		
	char str1[9]= "Continue", str2[8]="Suspend", str3[5]="Stop";
	int x, y, i=0;		
		
	SDL_Event event;		
		
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState( &x, &y);
				if((x >= d[0]-115 && x<= d[0]-15) && (y>= 65 && y<= 80))
					i=1;
				if((x >= d[0]-115 && x<= d[0]-15) && (y>= 90 && y<= 105))
					i=2;
			break;
		break;
		}
	}
		
	SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
		
	SDL_SetRenderDrawColor( g_pRenderer, 200, 200, 200, 255);
	SDL_RenderFillRect( g_pRenderer, &r1 );
	stringRGBA(g_pRenderer, d[0]-100, 45, str1, 0, 0, 100, 255);
	SDL_SetRenderDrawColor( g_pRenderer, 200, 200, 200, 255 );
	SDL_RenderFillRect( g_pRenderer, &r2 );
	stringRGBA(g_pRenderer, d[0]-100, 70, str2, 0, 0, 0, 255);
	SDL_SetRenderDrawColor( g_pRenderer, 200, 200, 200, 255 );
	SDL_RenderFillRect( g_pRenderer, &r3 );
	stringRGBA(g_pRenderer, d[0]-100, 95, str3, 0, 0, 0, 255);
	SDL_RenderPresent(g_pRenderer);	
	
	return i;
}

/*------------------------------------------------------------
| Nome: menu_pausa
| Accao: cria a janela gráfica, com o menu de pausa;
|		 neste o botão de suspend passa a possibilitar ao utilizador efectuar
|		 uma accao no menu;
| Recebe: apontador para inicio da lista de linhas, comboios e ligacoes;
|		  vetor com os valores de altura e largura da janela grafica;
|		  vetor com a informacao das varias cores disponiveis;
| Devolve: inteiro (i) que permite saber se o utilizador pretende retomar
|		   ou acabar a simulação;
+-----------------------------------------------------------*/

int menu_pausa(int d[], LC *icomb, LL *ilinha, LG *iligar, COR cores[]){
		
	char str1[9]= "Continue", str2[8]="Menu", str3[5]="Stop";
	int x, y, i=0;
	SDL_Rect r1, r2, r3;
		
	if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){               
		g_pWindow = SDL_CreateWindow("Simulação", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, d[0], d[1], SDL_WINDOW_SHOWN);
		if(g_pWindow != 0){
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);                     
		}
	}	
	SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(g_pRenderer);
	
	graf_insere_linhas(ilinha, cores);
	liga_linhas(ilinha, iligar);
	graf_insere_comboio(ilinha, icomb, cores, 0);
	
	for(i=0;i<2;){	
		SDL_Event event;
						
		r1.x = d[0]-115; r1.y = 40; r1.h = 15; r1.w = 100;
		r2.x = d[0]-115; r2.y = 65; r2.h = 15; r2.w = 100;
		r3.x = d[0]-115; r3.y = 90; r3.h = 15; r3.w = 100;				
				
		while(SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState( &x, &y);
					if((x >= d[0]-115 && x<= d[0]-15) && (y>= 40 && y<= 55)){
						i=0;
						return i;
					}
					if((x >= d[0]-115 && x<= d[0]-15) && (y>= 65 && y<= 80))
						menu(d, icomb, ilinha, iligar, 2);
					
					if((x >= d[0]-115 && x<= d[0]-15) && (y>= 90 && y<= 105))
						i=2;
					
				break;
			break;
			}		
		}
		SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);		
		SDL_SetRenderDrawColor( g_pRenderer, 200, 200, 200, 255);
		SDL_RenderFillRect( g_pRenderer, &r1 );
		stringRGBA(g_pRenderer, d[0]-100, 45, str1, 0, 0, 100, 255);
		SDL_SetRenderDrawColor( g_pRenderer, 200, 200, 200, 255 );
		SDL_RenderFillRect( g_pRenderer, &r2 );
		stringRGBA(g_pRenderer, d[0]-100, 70, str2, 0, 0, 0, 255);
		SDL_SetRenderDrawColor( g_pRenderer, 200, 200, 200, 255 );
		SDL_RenderFillRect( g_pRenderer, &r3 );
		stringRGBA(g_pRenderer, d[0]-100, 95, str3, 0, 0, 0, 255);
		SDL_RenderPresent(g_pRenderer);
	}
	return 2;
}

/*------------------------------------------------------------
| Nome: graf_insere_linhas
| Accao: desenha na janela gráfica as varias linhas;
| Recebe: apontador para inicio da lista de linhas;
|		  vetor com a informacao das varias cores disponiveis;
+-----------------------------------------------------------*/

void graf_insere_linhas(LL *ilinha, COR cores[]){
	
    int i = 0, j,  ax, ay;
    COR  auxcor;
    LINHA *aux;
    LL *aux2;
    
    aux2=ilinha;
      	            
	while(aux2!=NULL){
        aux = aux2->l.inicio; 
		i = 0;              
		while(aux!=NULL){                       
            for(j = 0; j<9; j = j +1){
				if(strcmp(aux->p.corponto, cores[j].nome)==0)
				auxcor = cores[j]; 
			}
			if (strcmp(aux->p.tipo, "VIA")==0)
				filledCircleRGBA(g_pRenderer, aux->p.x, aux->p.y, 2,auxcor.r, auxcor.g, auxcor.b, 255);

			else 
				filledCircleRGBA(g_pRenderer, aux->p.x, aux->p.y, 5, auxcor.r, auxcor.g, auxcor.b, 255);
            
            if (i !=0) {
                SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
				SDL_RenderDrawLine(g_pRenderer, ax, ay, aux->p.x, aux->p.y);
            }				
			ax = aux->p.x, ay = aux->p.y;  
			aux = aux->prox;
            i = i +1;
            fflush(stdout);
		}	
		aux2=aux2->prox;
	}	
}

/*------------------------------------------------------------
| Nome: liga_linhas
| Accao: desenha na janela gráfica as ligacoes entre pontos;
| Recebe: apontador para inicio da lista de linhas e de ligacoes;
+-----------------------------------------------------------*/

void liga_linhas(LL *ilinha, LG *iligar){
	int  auxx1=0, auxx2=0, auxy1=0, auxy2=0, k1, k2;
	LINHA *aux;
	LL *aux2;
	LG *aux3;
	
	aux3=iligar;
	
	while(aux3!=NULL){
		k1=0;
		k2=0;
		aux2 = ilinha;  
		while(aux2!=NULL){
			aux = aux2->l.inicio;
 			if(strncmp(aux2->nome, aux3->lig.l1, 4)==0){
				k1=1;
				while(aux!=NULL){  
					if(strncmp(aux->p.iponto, aux3->lig.p1, 5)==0 ){
						auxx1 = aux->p.x; auxy1 = aux->p.y;						
					}
					aux = aux->prox;							
				}				
			}
			if(strncmp(aux2->nome, aux3->lig.l2, 4)==0){
				k2=1;
				while(aux!=NULL){  							
					if(strncmp(aux->p.iponto, aux3->lig.p2, 5)==0 ){
						auxx2 = aux->p.x; auxy2 = aux->p.y;						
					}
					aux = aux->prox;
				}				
			}					
			aux2=aux2->prox;
		}
		if(k1==1 && k2==1){
		SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(g_pRenderer, auxx1, auxy1, auxx2, auxy2);
		}
		aux3 = aux3->prox;
	}		
}

/*------------------------------------------------------------
| Nome: graf_insere_comboio
| Accao: calcula a posicao dos comboios (movimento);
| Recebe: apontador para inicio da lista de linhas e de comboios;
|		  vetor com a informacao das varias cores disponiveis;
|		  r - permite saber se os comboios devem proseguir (caso tenha sido
|			  feita uma pausa), ou fazer reset da sua posição (após stop); 
+-----------------------------------------------------------*/

void graf_insere_comboio(LL *ilinha, LC *icomb, COR cores[], int r){
	float angulo=0.0, dis=3;
	LINHA *aux;
	LC *aux1;
	LL *aux2;

	aux1=icomb;
			
	while(aux1!=NULL){
		if(r==1){
			reinicia(aux1);
			aux1->c.numviagens= aux1->auxv;
		}
		aux2=ilinha;		
		while(aux2!=NULL){			
			if(strcmp(aux2->nome, aux1->c.iferrovia)==0){
				aux = aux2->l.inicio;              
				while(aux!=NULL){														
					if (strcmp(aux->p.iponto, aux1->c.iponto)==0 && aux->prox!=NULL){
																						
						angulo = desenha(aux, aux1, cores);
						
						if(abs(aux1->x - aux->prox->p.x) < 3.1 && abs(aux1->y - aux->prox->p.y) < 3.1){
							strcpy(aux1->c.iponto , aux->prox->p.iponto);
							if(strcmp(cores[aux1->c.c1].nome, aux->prox->p.corponto)==0 && strcmp(aux->prox->p.tipo,"EST")==0){
								aux1->c.c1=9;
							}
							if(strcmp(cores[aux1->c.c2].nome, aux->prox->p.corponto)==0 && strcmp(aux->prox->p.tipo,"EST")==0){
								aux1->c.c2=9;
							}
							if(strcmp(cores[aux1->c.c3].nome, aux->prox->p.corponto)==0 && strcmp(aux->prox->p.tipo,"EST")==0){
								aux1->c.c3=9;								
							}
							aux1->x=aux->prox->p.x;
							aux1->y=aux->prox->p.y;				
						}						
						else{	
							aux1->x = aux1->x + dis * cos(angulo);
							aux1->y = aux1->y + dis * sin(angulo);
						}														
					}
					if(strcmp(aux->p.iponto, aux1->c.iponto)==0 && aux->prox==NULL){
						if(aux1->c.numviagens!=1){
							reinicia(aux1);
							aux1->c.numviagens= aux1->c.numviagens - 1;
						}
					}					
					aux = aux->prox;												
				}
			}
			aux2=aux2->prox;			
		}
		aux1=aux1->prox;  		             
	}	
}

/*------------------------------------------------------------
| Nome: desenha
| Accao: desenha na janela gráfica os comboios e as suas carruagens;
|		 calcula a posicao das carruagens em relacao ao comboio;
| Recebe: apontador para o ponto em que se encontra o comboio;
|		  apontador para o comboio a desenhar;
|		  vetor com a informacao das varias cores disponiveis;
| Devolve: angulo da direcao do comboio;
+-----------------------------------------------------------*/

float desenha(LINHA *aux, LC *aux1, COR cores[]){
	int xc1, xc2, xc3, yc1, yc2, yc3, j=0;
	float x1=0.0, y1=0.0, angulo=0.0;
	COR auxcor;
		
	for(j = 0; j<9; j = j +1){
		if(strcmp(aux1->c.corcarruagem, cores[j].nome)==0)
			auxcor = cores[j];
	}	
	y1 = aux->prox->p.y-aux->p.y;
	x1 = aux->prox->p.x-aux->p.x;
	
	angulo = atan(y1/x1);
							
	xc1 = aux1->x + (2*aux1->c.raiocomboio)*cos(angulo+pi); yc1 = aux1->y + (2*aux1->c.raiocomboio)*sin(angulo+pi);
	xc2 = aux1->x + (4*aux1->c.raiocomboio)*cos(angulo+pi); yc2 = aux1->y + (4*aux1->c.raiocomboio)*sin(angulo+pi);
	xc3 = aux1->x + (6*aux1->c.raiocomboio)*cos(angulo+pi); yc3 = aux1->y + (6*aux1->c.raiocomboio)*sin(angulo+pi);	
						
	filledCircleRGBA(g_pRenderer, aux1->x, aux1->y, aux1->c.raiocomboio , auxcor.r, auxcor.g, auxcor.b, 255);
	filledCircleRGBA(g_pRenderer, xc1, yc1, aux1->c.raiocomboio , cores[aux1->c.c1].r, cores[aux1->c.c1].g, cores[aux1->c.c1].b, 255);
	filledCircleRGBA(g_pRenderer, xc2, yc2, aux1->c.raiocomboio , cores[aux1->c.c2].r, cores[aux1->c.c2].g, cores[aux1->c.c2].b, 255);
	filledCircleRGBA(g_pRenderer, xc3, yc3, aux1->c.raiocomboio , cores[aux1->c.c3].r, cores[aux1->c.c3].g, cores[aux1->c.c3].b, 255);
	
	return angulo;	
}

/*------------------------------------------------------------
| Nome: reinicia
| Accao: devolve ao comboio os seus valores iniciais;
| Recebe: apontador para o comboio a que se pretende reiniciar a informacao;
+-----------------------------------------------------------*/

void reinicia(LC *aux1){
	aux1->x=aux1->auxx;
	aux1->y=aux1->auxy;
	strcpy(aux1->c.iponto, aux1->nomep);
	aux1->c.c1=aux1->c1;
	aux1->c.c2=aux1->c2;
	aux1->c.c3=aux1->c3;
}

