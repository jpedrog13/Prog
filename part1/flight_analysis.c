//João Gonçalves 85211
//Carlos SIlva 86345

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL.h>

#define NL 200
#define pi 3.14159
#define altura 500
#define largura 500


SDL_Window* g_pWindow = NULL;
SDL_Renderer* g_pRenderer = NULL;

void leficheiro(float *x, float *y){
	int i=0;
	float n;
	char linha[NL];
	FILE * f1;
	f1=fopen("config_model.txt", "r");
	while(fgets(linha, NL, f1)!=NULL){
		if(sscanf(linha,"%f", &n)==1){
			if(i<10){
				x[i]=n;				
			}
			else{
				y[i-10]=n;
			}
			i=i+1;		
		}
	}
	fclose(f1);
}

void graph(FILE * f){
	
	if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){
		g_pWindow = SDL_CreateWindow("gráfico", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largura, altura, SDL_WINDOW_SHOWN);
		if(g_pWindow != 0){
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}
	}
	
	SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(g_pRenderer);
	
	
	SDL_Rect r1; 
				
	r1.x = 50;
	r1.y = 50;
	r1.w = 4;
	r1.h = 4;
						
	SDL_SetRenderDrawColor( g_pRenderer, 0, 0, 0, 255 );
	SDL_RenderFillRect(g_pRenderer, &r1);

				
	SDL_RenderPresent(g_pRenderer);
				
	SDL_Delay(5000);
			
	SDL_Quit();
}

int main(){
	
	int exit=0, o;
	char nome[100];
	FILE *f2;
	float parametros[10]={0}, vestado[4]={0}, t=0.0, tf, dt, s, b, m, g, den, cd0, e, alpha, AR, cons, cl, cd, v, gamma, x, h, l, d, v1, gamma1, x1, h1;
	
	while(exit!=1){
		
		printf("Lista de opções:\n0 - Terminar o Programa\n1 - Simular o movimento da aeronave\n2 - Visualizar resultados (gráficos)\nSelecione a opção:\n");
		scanf("%d", &o);
		if(o==1){
			char ch;
			printf("Que nome deseja dar ao ficheiro de dados?\n");
			scanf("%s", nome);
			f2=fopen(nome, "w");
			
			leficheiro(parametros,vestado);
			
			tf = parametros[0];
			dt = parametros[1];
			s = parametros[2];
			b = parametros[3];
			m = parametros[4];
			g = parametros[5];
			den = parametros[6];
			cd0 = parametros[7];
			e = parametros[8];
			alpha = parametros[9];
			AR = b*b/s;
			cons = 1/(pi*e*AR);
			
			cl = (alpha*pi*AR)/(1+sqrt(1+((AR/2)*(AR/2))));
			cd = cd0 + (cons*cl*cl);
			
			v = vestado[0];
			gamma = vestado[1];
			x = vestado [2];
			h = vestado[3];
			
			fprintf(f2, "(%f %f %f %f %f %f %f %f %f %f)\n\n", tf, dt, s, b, m, g, den, cd0, e, alpha);
			fprintf(f2, "%f %f %f %f %f\n", t, v, gamma, x, h);
			
			for(t = dt; t < tf; t=t+dt){			
				if(h>0){
					v1 = v;
					gamma1 = gamma;
					x1 = x;
					h1 = h;
					l = cl*den*v*v*s/2;
					d = cd*den*v*v*s/2;
					v = v1 + (dt/m)*(-d-m*g*sin(gamma1));
					gamma = gamma1 + (dt/(m*v1))*(l-m*g*cos(gamma1));
					x = x1 + dt*v1*cos(gamma1);
					h = h1 + dt*v1*sin(gamma1);
					fprintf(f2, "%f %f %f %f %f\n", t, v, gamma, x, h);
				}
				else{
					t =tf;
				}
			}
					
			fclose(f2);
			
			do{
				ch = getchar();
			}while(ch != '\n');
		}
		if(o==2){
			int c, g;
			char ch, nome[100], linha[NL];;
			FILE *f3;
			
			printf("Qual o nome do ficheiro?\n");
			scanf("%s", nome);
			
			f3=fopen(nome, "r");
	
			if(f3 == NULL){
				printf("Erro na abertura do ficheiro\n");
			}
			else{
				printf("Que gráfico prentende?\n1- velocidade/tempo\n2- trajetória\n3- posição/velocidade\n");
				scanf("%d", &g);
			
				while(fgets(linha, NL, f3)!=NULL){
					if(sscanf(linha,"%f %f %f %f %f", &t, &v, &gamma, &x, &h)==5){
					c=c+1;
					}
				}	
				
				graph(f3);
			}
			
			fclose(f3);
			
			do{
				ch = getchar();
			}while(ch != '\n');
		}
		if(o==0){
			exit=1;
		}	
	}
	return 0;
}
