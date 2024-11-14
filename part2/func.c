
#include "proj_h" 

/*------------------------------------------------------------
| Nome: leficheiro
| Accao: abre o ficheiro de configuração, retira a informação e guarda-a em listas;
| Recebe: nome do ficheiro a ler e as variáveis que irá preencher após a sua leitura;
| Devolve: inteiro conforme a leitura (1) ou não (0) do ficheiro;
+-----------------------------------------------------------*/

int leficheiro(char nome[], int d[], LC **icomb, LL **ilinha, LG **iligar){
	
	FILE *fconfig;
	char s[DIMv], linhaf[NL], nomelinha[4];   
	PONTO p;
	COMBOIO c;
	LIGAR lig;
	LC *inicioc=NULL, *atualc=NULL;
	LINHA *iniciop=NULL, *atualp=NULL;
	LL *iniciol=NULL, *atuall=NULL;
	LG *iniciolig=NULL, *atuallig=NULL;
		
	fconfig = fopen(nome, "r");
	
    if (fconfig == NULL){
		printf("\nNão foi possível fazer a leitura do ficheiro!\n");
		return 0;
   	}
	while(fgets(linhaf, NL, fconfig)!=NULL){
		sscanf(linhaf,"%s", s);
			
        if(strncmp(s,"JANELA:", 7)==0){					
			sscanf(linhaf,"%s %d %d", s, &d[0],&d[1]);
        }                
        else if(strncmp(s,"LINHA:", 6)==0){					
			sscanf(linhaf,"%s %s", s, nomelinha);
                                        
            while(strncmp(s, "FIM_DE_LINHA:", 13)!=0){
				fgets(linhaf, NL, fconfig);
				sscanf(linhaf,"%s", s);
						
				if(s[0]!='%' && sscanf(linhaf,"%s %d %d %s %s", p.iponto, &p.x, &p.y, p.corponto, p.tipo)==5){														                           
					insere_pontos(p, &iniciop, &atualp);                       
                }                        
			}
			insere_linha(iniciop, nomelinha, &iniciol, &atuall);
			iniciop=NULL;
			*ilinha=iniciol;
		}				
		else if(strncmp(s,"LIGAR:", 6)==0 && sscanf(linhaf,"%s %s %s %s %s", s, lig.l1, lig.p1, lig.l2, lig.p2)== 5 && strcmp(s,"%")!=0){
									                                           
			insere_ligar(lig, &iniciolig, &atuallig);
				
			*iligar=iniciolig;	                            				
		}
		else if(strncmp(s,"COMBOIO:", 8)==0 && sscanf(linhaf,"%s %s %d %s %s %s %d", s, c.icomboio, &c.raiocomboio, c.corcarruagem, c.iferrovia, c.iponto, &c.numviagens)==7 && strcmp(s,"%")!=0){				                                        
            				                                            
            insere_comboio(c, &inicioc, &atualc);
		}				
	}
	iniciacomboio(iniciol, &inicioc);
	*icomb=inicioc;
	fclose(fconfig);
	return 1;	
}

/*------------------------------------------------------------
| Nome: insere_comboio
| Accao: aloca memória para cada comboio, e insere-os na lista de comboios;
| Recebe: dados do novo comboio e apontador para inicio da lista de comboios;
+-----------------------------------------------------------*/

void insere_comboio(COMBOIO novo, LC **inicio, LC **atual){
	LC *n;
	
	n = (LC *) calloc(1, sizeof(LC));
	
	if(n == NULL){
		printf("\nOcorreu um problema na alocação de memória para o armazenamento dos comboios!\n");
        exit(0);
	}
	novo.c1=rand()%9;
	novo.c2=rand()%9;
	novo.c3=rand()%9;
	n->c = novo;
	n->prox = NULL;
	
	if(*inicio==NULL){	
		*inicio=n;
		*atual=n;
	}
	else{					
		(*atual)->prox=n;
		*atual=n;
	}
}

/*------------------------------------------------------------
| Nome: mostra_comboio
| Accao: percorre a lista dos comboios e mostra a informação de um comboio pretendido;
|		 o utilizador introduz o nome do comboio que pretende visualizar;
| Recebe: apontador para inicio da lista de comboios;
+-----------------------------------------------------------*/

int mostra_comboio(LC *icomb){
	char nome[3];
	int k=0;
	
	if(icomb==NULL){
		printf("\nA lista dos comboios está vazia!\n");
		return 0;
	}
	printf("\nQue comboio pretende visualizar? ");
	scanf("%s", nome);
	while(icomb!=NULL){
		if(strcmp(icomb->c.icomboio, nome)==0){
			printf("\nComboio: %s\n%d %s %s %s %d\n", icomb->c.icomboio, icomb->c.raiocomboio, icomb->c.corcarruagem, icomb->nomef, icomb->nomep, icomb->auxv);
			k=1;		
		}
		icomb=icomb->prox;
	}
	if(k==0)
		printf("\nO comboio introduzido não existe!\n");
		
	return 0;
}

/*------------------------------------------------------------
| Nome: elimina_comboio
| Accao: elimina um comboio da lista de comboios;
| Recebe: apontador para inicio da lista de comboios;
|		  x - detecta se o comboio a eliminar é o primeiro;
| Devolve: apontador para inicio da lista de comboios;
+-----------------------------------------------------------*/

LC *elimina_comboio(LC *icomb, int *x, int i){
	char nome[3];
	int k=0;
	
	LC *ant=NULL, *elimina;
	
	printf("\nEscolha o comboio a eliminar: ");
	scanf("%s", nome);
	
	while(icomb!=NULL){
		if(strcmp(icomb->c.icomboio,nome)==0){
			if(ant==NULL){
				if(i==2){
					printf("\nA operação não pode ser realizada\n");
				}
				else{
					*x=1;
					elimina = icomb;
					icomb = icomb->prox;
					free(elimina);
				}					
			}			
			else{
				*x=0;
				elimina = icomb;
				ant->prox=elimina->prox;
				free(elimina);				
			}
			k=1;						
		}					
		ant=icomb;	
		icomb=icomb->prox;			
	}
	if(k==0)
		printf("\nO comboio introduzido não existe!\n");
	return icomb;	
}

/*------------------------------------------------------------
| Nome: insere_pontos
| Accao: aloca memória para cada ponto de uma linha, e insere-os na lista de pontos (linha);
| Recebe: dados do novo ponto e apontador para inicio da lista de pontos;
+-----------------------------------------------------------*/

void insere_pontos(PONTO novo, LINHA **inicio, LINHA **atual){
	LINHA *n;
	
	n = (LINHA *) calloc(1, sizeof(LINHA));
	
	if(n == NULL){
		printf("\nOcorreu um problema na alocação de memória para o armazenamento dos pontos!\n");
        exit(0);
	}
	n->p = novo;
	n->prox = NULL;
	
	if(*inicio==NULL){	
		*inicio=n;
		*atual=n;
	}
	else{					
		(*atual)->prox=n;
		*atual=n;
	}
}

/*------------------------------------------------------------
| Nome: insere_linha
| Accao: aloca memória para cada linha, e insere-os na lista de linhas;
| Recebe: dados da nova linha, apontador para inicio da lista de linhas
|		  e nome da linha;
+-----------------------------------------------------------*/

void insere_linha(LINHA *novo, char nome[], LL **inicio, LL **atual){
	LL *n;
	
	n = (LL *) calloc(1, sizeof(LL));
	
	if(n == NULL){
		printf("\nOcorreu um problema na alocação de memória para o armazenamento das linhas!\n");
        exit(0);
	}
	n->l.inicio = novo;
	
	strcpy(n->nome,nome); 
	n->prox = NULL;
	
	if(*inicio==NULL){	
		*inicio=n;
		*atual=n;
	}
	else{					
		(*atual)->prox=n;
		*atual=n;
	}
}

/*------------------------------------------------------------
| Nome: mostra_linha
| Accao: percorre a lista de linhas e mostra a informação da linha pretendida;
|		 o utilizador introduz o nome da linha que pretende visualizar;
|		 percorre tambem a lista de pontos da linha inserida, escrevendo a
|		 indormação de cada ponto;
| Recebe: apontador para inicio da lista de linhas;
+-----------------------------------------------------------*/

int mostra_linha(LL *ilinha){
	char nome[4];
	int k=0;
        LINHA *aux;
	
	if(ilinha==NULL){
		printf("\nA lista das linhas está vazia!\n");
		return 0;
	}
	printf("\nQue linha pretende visualizar? ");
	scanf("%s", nome);
	while(ilinha!=NULL){
		if(strcmp(nome, ilinha->nome)==0){
			printf("\nLinha: %s\n", ilinha->nome);
			aux = ilinha->l.inicio;
			while(aux!=NULL){			
				printf("%s %d %d %s %s\n",aux->p.iponto, aux->p.x, aux->p.y, aux->p.corponto, aux->p.tipo);
				aux=aux->prox;
                fflush(stdout);
			}
			k=1;
		}
		ilinha=ilinha->prox;
	}
	if(k==0)
		printf("\nA linha introduzida não existe!\n");
		
	return 0;
}

/*------------------------------------------------------------
| Nome: elimina_linha
| Accao: elimina uma linha da lista de linhas;
| Recebe: apontador para inicio da lista de linhas;
|		  x - detecta se a linha a eliminar é a primeira;
| Devolve: apontador para inicio da lista de linhas;
+-----------------------------------------------------------*/

LL *elimina_linha(LL *ilinha, int *x, int i){
	char nome[4];
	int k=0;
	
	LL *ant=NULL, *elimina;
	
	printf("\nEscolha a linha a eliminar: ");
	scanf("%s", nome);
	
	while(ilinha!=NULL){
		if(strcmp(ilinha->nome,nome)==0){
			if(ant==NULL){
				if(i==2){
					printf("\nA operação não pode ser realizada\n");
				}
				else{
					*x=1;
					elimina = ilinha;
					ilinha = ilinha->prox;
					free(elimina);
				}			
			}			
			else{
				*x=0;
				elimina = ilinha;
				ant->prox=elimina->prox;
				free(elimina);
				
			}			
			k=1;						
		}					
		ant=ilinha;	
		ilinha=ilinha->prox;			
	}
	if(k==0)
		printf("\nA linha introduzida não existe!\n");
	return ilinha;	
}

/*------------------------------------------------------------
| Nome: cria_comboio
| Accao: cria um comboio novo e adiciona-o à lista de comboios;
|		 o utilizador escreve as informações do novo comboio;
|		 a função deteta se os dados são corretos (podem ser utilizados)
|		 e devolve uma mensagem de erro caso não sejam;
| Recebe: apontador para inicio da lista de comboios;
|		  apontador para inicio da lista de linhas;
| Devolve: apontador para inicio da lista de comboios;
+-----------------------------------------------------------*/

LC *cria_comboio(LC *inicio, LL *ilinha){
	int k=0;
	LC *n, *aux;
	LL *aux3;
	LINHA *aux2;
	COMBOIO comb;
	
	printf("\nQuais as informações do novo comboio?\n");
	scanf("%s %d %s %s %s %d", comb.icomboio, &comb.raiocomboio, comb.corcarruagem, comb.iferrovia, comb.iponto, &comb.numviagens);	
	
	aux3 = ilinha;
	
	while(aux3!=NULL){
		aux2 = aux3->l.inicio;
		if(strcmp(comb.iferrovia,aux3->nome)==0){
			while(aux2!=NULL){
				if(strcmp(aux2->p.iponto,comb.iponto)==0)
					k=1;
				
				aux2=aux2->prox;	
			}
		}
		aux3=aux3->prox;
	}
	
	if(strlen(comb.icomboio)!=2 || (strcmp(comb.corcarruagem,"BRANCO")!=0 && 
	strcmp(comb.corcarruagem,"PRETO")!=0 && strcmp(comb.corcarruagem,"CASTANHO")!=0 &&
	strcmp(comb.corcarruagem,"VERMELHO")!=0 && strcmp(comb.corcarruagem,"ROXO")!=0 && 
	strcmp(comb.corcarruagem,"AZUL")!=0 && strcmp(comb.corcarruagem,"CYAN")!=0 && 
	strcmp(comb.corcarruagem,"VERDE")!=0 && strcmp(comb.corcarruagem,"AMARELO")!=0) || k==0){
		printf("\nAs informações introduzidas estão erradas!\n");
		fflush(stdout);
		return inicio;
	}
	
	n = (LC *) calloc(1, sizeof(LC));
	
	if(n == NULL){
		printf("\nOcorreu um problema na alocação de memória para o armazenamento dos comboios!\n");
        exit(0);
	}
	comb.c1=rand()%9;
	comb.c2=rand()%9;
	comb.c3=rand()%9;
	n->c = comb;
	n->prox = NULL;
	
	aux = inicio;
	
	if(inicio==NULL){
		inicio=n;
	}
	else{		
		while(aux->prox!=NULL){
			aux = aux->prox;
		}
		aux->prox=n;
	}
	iniciacomboio(ilinha, &inicio);	
	return inicio;
}

/*------------------------------------------------------------
| Nome: insere_ligar
| Accao: aloca memória para cada ligação de pontos, e insere-os na lista de ligações;
| Recebe: dados da nova ligação, apontador para inicio da lista de ligações;
+-----------------------------------------------------------*/

void insere_ligar(LIGAR novo, LG **inicio, LG **atual){
	LG *n;
	
	n = (LG *) calloc(1, sizeof(LG));
	
	if(n == NULL){
		printf("\nOcorreu um problema na alocação de memória para o armazenamento das informações para ligar linhas!\n");
        exit(0);
	}
	n->lig = novo;
	n->prox = NULL;
	
	if(*inicio==NULL){	
		*inicio=n;
		*atual=n;
	}
	else{					
		(*atual)->prox=n;
		*atual=n;
	}
}

/*------------------------------------------------------------
| Nome: iniciacomboio
| Accao: apos leitura dos comboios ou criação de um comboio, preenche na estrutura
|		 da lista de comboios variaveis auxiliares que guardam valores de
|		 inicializacao do comboio;
| Recebe: apontador para inicio da lista de comboios;
|		  apontador para inicio da lista de linhas;
+-----------------------------------------------------------*/

void iniciacomboio(LL *ilinha, LC **icomb){
	LL *aux2;
	LC *aux1, *inicio;
	LINHA *aux;
	
	aux1=*icomb;
	inicio=aux1;
		
	while(aux1!=NULL){
		aux2=ilinha;
		while(aux2!=NULL){
				
			if(strcmp(aux2->nome, aux1->c.iferrovia)==0){
				aux = aux2->l.inicio;              
				while(aux!=NULL){
					
					if (strcmp(aux->p.iponto, aux1->c.iponto)==0){
						aux1->x= aux->p.x;
						aux1->y= aux->p.y;
						aux1->auxx= aux->p.x;
						aux1->auxy= aux->p.y;
						strcpy(aux1->nomef, aux2->nome);
						strcpy(aux1->nomep, aux->p.iponto);
						aux1->c1=aux1->c.c1;
						aux1->c2=aux1->c.c2;
						aux1->c3=aux1->c.c3;
						aux1->auxv=aux1->c.numviagens;
					}
					aux = aux->prox;
					fflush(stdout);							
				}
			}
			aux2=aux2->prox;
			fflush(stdout);			
		}
		aux1=aux1->prox; 
		fflush(stdout);		             
	}
	*icomb=inicio;	
}

/*------------------------------------------------------------
| Nome: menu
| Accao: permite aceder ao menu, dentro ou fora de simulação;
| Recebe: apontador para inicio da lista de linhas, comboios e ligacoes;
|		  vetor com os valores de altura e largura da janela grafica;
|		  i - permite saber se está na pausa da janela gráfica,
|			  e se for esse o caso o menu só é exibido uma vez e não em loop;
+-----------------------------------------------------------*/

void menu(int d[], LC *icomb, LL *ilinha, LG *iligar, int i){
	int veliminac=0, veliminal=0, j;
	char e[2]="1";
	LL *eliminal;
	LC *eliminac;
	
	while(strcmp(e,"0")!=0){
		printf("-----------------------------------------\n");
		printf("Lista de opções:\n\n0 - Terminar programa\n\n1 - Mostrar a informação de uma ferrovia\n\n");
		printf("2 - Permite eliminar uma ferrovia\n\n3 - Mostra a informação de um comboio\n\n");
		printf("4 - Permite eliminar um comboio\n\n5 - Permite criar um comboio\n\n6 - Simulação\n");
		printf("-----------------------------------------\n");
		printf("Seleciona a opção: ");				
		scanf("%s", e);
		printf("-----------------------------------------\n");
		for(j=0; j<1; j=j+1){
			if(strcmp(e,"1")==0){
				mostra_linha(ilinha);
			}
			else if(strcmp(e,"2")==0){				
				eliminal = elimina_linha(ilinha, &veliminal, i);
				if(veliminal==1)
					ilinha=eliminal;
			}							    
			else if(strcmp(e,"3")==0){
				mostra_comboio(icomb);
			}
			else if(strcmp(e,"4")==0){								
				eliminac = elimina_comboio(icomb, &veliminac, i);
				if(veliminac==1)
					icomb=eliminac;								
			}
			else if(strcmp(e,"5")==0){
				icomb = cria_comboio(icomb, ilinha);
			}
			else if(strcmp(e,"6")==0){
				if(i==2){
					printf("A simulação encontra-se em suspensão\n");
				}
				else		
					grafico(d, ilinha, iligar, icomb);
			}
			else if(strcmp(e,"0")==0){
				exit(0);
			}
			else
				printf("\nA opção não é válida!\n");		
		}
		if(i==2){
			strcpy(e,"0");
		}
		else
			getchar();		
	}	
}

