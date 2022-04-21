#include <stdio.h>
#include <locale.h>
#define TAMANHO 6
int mostrarTodos(int matriz[TAMANHO][TAMANHO]){
	int i, j;
	for(i=0;i<TAMANHO;i++){
		for(j=0;j<TAMANHO;j++){
			if(matriz[i][j] == 1) printf ("\nO vértice %d é incidênte do vértice %d", i+1, j+1);
		}
	}
	return 0;
}
int encontrarCaminho(int ini, int dest, int matriz[6][6]){
	int verticeIsolado = 0;
	int i, j, k;
	int inicio = ini; //cria copia do inicio e do destino caso precise fazer uma recursividade
	int destino = dest;
	//inicio e destino iguais
	if(inicio == destino){
		printf("Vértice de inicio igual à de destino");
		return 0;
	}
	
	//verica se eles tem conexão direta
	if(matriz[inicio][destino] == 1){
		printf("%d => %d", inicio+1, destino+1);
		return 0;
	}
	
	//verifica se o vértice é isolado
	for(i=0;i<6;i++){
		if((matriz[destino][i] == 1)||(matriz[inicio][i] == 1)) verticeIsolado = 1;
		}
	if(verticeIsolado == 0){
		printf("\nCaminho não encontrado\n");
		return 0;
	}
		
	printf("\n%d", inicio+1);
	//outros caminhos
	for(j=0;j<6;j++){
		for(i=0;i<6;i++){
			if(matriz[inicio][i] == 1){
				for(k=0;k<6;k++){
					//limpa a coluna
					matriz[k][inicio] = 0;
				}
				inicio = i;
				printf("=>%d", inicio+1);
				if(inicio == destino){
					printf("\nCaminho encontrado!\n");
					resetar(matriz);
					return 0;
				}
			}
		}
	}
	encontrarCaminho(ini, dest, matriz);
	return 0;
}

int mostrarVertice(int vertice,int matriz[TAMANHO][TAMANHO]){
	int i;
	for(i=0;i<TAMANHO;i++){
			if(matriz[i][vertice] == 1) printf ("\nO vértice %d é incidênte do vértice %d", vertice+1, i+1);
		}
	return 0;
}
int mostrarMatriz(int matriz[TAMANHO][TAMANHO]){
	int i, j;
	printf("\n\t1\t2\t3\t4\t5\t6\n");
	for(i=0;i<TAMANHO;i++){
		for(j=0;j<TAMANHO;j++){
			if(j%TAMANHO == 0)printf("\n%d\t", i+1);
			printf("%d \t",	matriz[i][j]);
			
		}
	}
}
int procuraPontes(int matriz[TAMANHO][TAMANHO]){
	int i, j , k;
	for(i=0;i<TAMANHO;i++){
		for(j=0;j<TAMANHO;j++){
			if(matriz[i][j] == 1){
				for(k=0;k<TAMANHO;k++){
					resetar(matriz);
					matriz[i][j] = 0;
					matriz[j][i] = 0;
					if(encontrarCaminhoP(i, k,matriz) == 10) printf("\nA aresta de %d para %d é uma ponte\n", i+1, j+1);
				}
			}
		}
	}
	resetar(matriz);
	return 0;
}
int encontrarCaminhoP(int ini, int dest, int matriz[TAMANHO][TAMANHO]){
	int iIsolado = 0, dIsolado = 0;
	int i, j, k;
	int inicio = ini; //cria copia do inicio e do destino caso precise fazer uma recursividade
	int destino = dest;
	//inicio e destino iguais
	if(inicio == destino){
		return 0;
	}
	
	//verica se eles tem conexão direta
	if(matriz[inicio][destino] == 1){
		return 0;
	}
	
	//verifica se o vértice é isolado
	for(i=0;i<TAMANHO;i++){
		if(matriz[inicio][i] == 1) iIsolado = 1;
		if(matriz[destino][i] == 1) dIsolado = 1;
	}
	if(iIsolado == 0||dIsolado == 0){
		return 10;
	}
	//outros caminhos
	for(j=0;j<TAMANHO;j++){
		for(i=0;i<TAMANHO;i++){
			if(matriz[inicio][i] == 1){
				matriz[inicio][i] = 0;
				matriz[i][inicio] = 0;
				inicio = i;
				if(inicio == destino){
					resetar(matriz);
					return 0;
				}
			}
		}
	}
	encontrarCaminhoP(ini, dest, matriz);
	return 0;
}
int resetar(int matriz[TAMANHO][TAMANHO]){
	int i, j;
	for(i=0;i<TAMANHO;i++){
		for(j=0;j<TAMANHO;j++){
			matriz[i][j] = 0;
		}
	}
	//caminhos
	matriz[0][1] = 1;
	matriz[0][3] = 1;
	matriz[0][2] = 1;
	matriz[1][2] = 1;
	matriz[1][0] = 1;
	matriz[2][1] = 1;
	matriz[2][0] = 1;
	matriz[2][4] = 1;
	matriz[2][5] = 1;
	matriz[3][0] = 1;
	matriz[4][2] = 1;
	matriz[4][5] = 1;
	matriz[5][2] = 1;
	matriz[5][4] = 1;
	
	return 0;
}
	
int main(){
	setlocale(LC_ALL, "Portuguese");
	int matriz[TAMANHO][TAMANHO];
	//zera a matriz
	resetar(matriz);
	
	
	int opcoes;
	int parar = 0;
	int vertice = 1;
	int vertice2 = 1;
	do{
		printf("\nEscolha uma opção:\n1:mostrar matriz\n2:mostrar todos os incidêntes\n");
		printf("3:mostrar incidênte especifico\n4:encontrar caminho\n5:encontrar ponte\n6:sair\n");
		scanf("%d", &opcoes);
		switch(opcoes){
			case 1: mostrarMatriz(matriz); break;
			case 2: mostrarTodos(matriz); break;
			case 3: printf("Digite o vértice desejado\n");
			scanf("%d", &vertice);
			mostrarVertice(vertice-1, matriz);
			break;
			case 4: printf("Digite o vértice inicial\n");
			scanf("%d", &vertice);
			printf("Digite o vértice final\n");
			scanf("%d", &vertice2);
			encontrarCaminho(vertice-1, vertice2-1, matriz);
			break;
			case 5: procuraPontes(matriz);
			break;
			case 6: parar = 1; break;
			default: printf("\nOpção inválida");
		}
	}while(parar!=1);
	
}

