
#include "proj_h"

int main(int argc, char *argv[]){
	
	int verifica, d[2];
	char nome[DIMn];
	LC *icomb=NULL;
	LL *ilinha;
	LG *iligar;
	
	if(argc==2){
		strcpy(nome, argv[1]);
	}
	else{
		printf("Número de argumentos errado!");
		return 0;
	}
	
	verifica = leficheiro(nome, d, &icomb, &ilinha, &iligar);
	
	if(verifica!=1){
		printf("A leitura do ficheiro não foi bem sucedida!");
		return 0;
	}
	
	menu(d, icomb, ilinha, iligar, 1);
	
	return 0;
}

