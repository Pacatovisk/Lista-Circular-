#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char nome[20];
	char cantor[60];
	struct Musica *proxima;
}Musica;

void main(void){
	setlocale(LC_ALL,"Portuguese");
		
	int valor = 1;
	char nomeMusica[20];
	char cantor[20];
	
   	Musica *m1; 
			
	play(&m1);	
	
	adicionar(&m1,"Size","ColdPay");
	adicionar(&m1,"Pacato","Pacatovisk");
	adicionar(&m1,"Red","Pacatovisk");
	adicionar(&m1,"Black","Pacatovisk");
	adicionar(&m1,"Yellow","ColdPay");
	adicionar(&m1,"White","Pacatovisk");
		
		
	while (valor!= 0){
		printf("\n -----PLAYLIST DO PACATO------- \n");
		printf ("\n1 - ADICIONAR M�SICA \n");
		printf ("2 - EXCLUIR M�SICA \n");
		printf ("3 - BUSCAR M�SICA \n");
		printf ("4 - LISTAR M�SICAS \n");
		printf ("5 - QUANTIDADE DE M�SICAS \n");
		printf ("6 - SAIR \n\n\n");
	
		scanf("%d", &valor);
		
		switch (valor){
		   	case 1:
		   		printf("------ ADICIONAR M�SICA -------- \n");
		   		printf("Informe o nome da m�sica: ");
		   		scanf("%s", &nomeMusica);
		   		printf("Informe o nome do cantor: ");
		   		scanf("%s", &cantor);
		     	adicionar(&m1,cantor,nomeMusica);
		   	break;
		   	case 2:
		   		printf("------ REMOVENDO M�SICA --------- \n");
		   		printf("Informe o nome da m�sica: ");
		   		scanf("%s", &nomeMusica);
		    	removerMusica(&m1,nomeMusica);
		   	break;
		   	case 3:
		   		printf("------ BUSCA DE M�SICA --------- \n");
		   		printf("Informe o nome da m�sica: ");
		   		scanf("%s", &nomeMusica);
		    	buscarMusica(&m1,nomeMusica);
		   	break;
			case 4:
				printf("------  LISTA DE M�SICAS --------- \n");
				exibirMusicas(&m1);
		   	break;
		   	case 5:
				printf("------  TOTAL DE M�SICAS  --------- \n");
				printf("\nQuantidade de m�sicas = %d\n", totalMusica(&m1));
		   	break;
		   	case 6:
				printf("SAIU");
		   		valor = 0;
		   	break;
		 }
	}
}

void play(Musica **musica){
	*musica = NULL;
	printf("PLAYLIST INICIALIZADA!\n");	
}

void adicionar(Musica **musica,char auxNome[20],char auxCantor[60]){
	if(*musica == NULL){
		*musica = (Musica *) malloc(sizeof(Musica));

		strcpy((*musica)->nome,auxNome);
		strcpy((*musica)->cantor,auxCantor);

		(*musica)->proxima = NULL;
		printf("\n M�SICA %s ADICIONADA COM SUCESSO! \n", auxNome);
	}else{
		adicionar(&((*musica)->proxima)    ,auxNome,auxCantor); 
	}
}

void exibirMusicas(Musica **musica){
	if(*musica != NULL){
		printf("\nM�sica       \t\Cantor\n");
		printf("%s\t\t%s\n",(*musica)->nome,(*musica)->cantor);
		exibirMusicas(&((*musica)->proxima));			
	}else{
		printf("\n-------- FIM DA PLAYLIST ---------- \n");
	}
}

int totalMusica(Musica **musica){
	int contador = 0;
	return musicasNaPlaylist(musica,contador); 
	
}

int musicasNaPlaylist(Musica **musica,int contador){
	if(*musica != NULL){
		musicasNaPlaylist(&((*musica)->proxima),++contador);
	}else{
		return contador;
	}
}

void apagarPlaylist(Musica **musica){
	if((*musica) != NULL){
		apagarPlaylist(&((*musica)->proxima));		
		free (*musica);								
		(*musica) = NULL;
	}
}

void removerMusica(Musica **musica, char auxNome[20]){
	Musica *auxMusica;
	if((*musica) != NULL){						
		if(!(strcmp((*musica)->nome,auxNome))){	
			if((*musica)->proxima == NULL){	   	
				free (*musica);				
				(*musica) = NULL;			
	
			}else{
				auxMusica = *musica;
				*musica = (*musica)->proxima;
				free(auxMusica);
			}
			printf("M�sica %s removida com sucesso! \n", auxNome);
		}else{
			removerMusica(&((*musica)->proxima),auxNome);
		}
	}else{
		printf("A m�sica %s n�o foi encontrada!\n",auxNome);
	}			
}

void buscarMusica(Musica **musica, char auxNome[20]){
	Musica *auxMusica;
	if((*musica) != NULL){					
		if(!(strcmp((*musica)->nome,auxNome))){	
			printf("M�sica %s encontrada com sucesso! \n", auxNome);
		}else{
			buscarMusica(&((*musica)->proxima),auxNome);
		}
	}else{
		printf("A m�sica %s n�o foi encontrada!\n",auxNome);
	}
}


