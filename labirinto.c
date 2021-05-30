#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define NMAX 105
#define INF 1000000000

typedef struct EVENTO
{
	int dist;
	int lin;
	int col;
}Ev;

int num_lin, num_col;
int labirinto[NMAX][NMAX];
int direcao_lin[] = {-1, 0, 1, 0};
int direcao_col[] = { 0, 1, 0,-1};
int distancia[NMAX][NMAX];
bool marc[NMAX][NMAX];
int caminho_lin[NMAX];
int caminho_col[NMAX];
int caminho_tam = 0;

void one_second(){
	int i;
	for(i = 0;i < 200000000;i++)
	{
	}
	return;
}



void BT(int lin, int col){
	int i, j, k, new_lin, new_col;
	one_second();
	printf("\n\n");
	for(i = 0;i < num_col + 2;i++){
		printf("-");
	}
	printf("\n");
	for(i = 0;i < num_lin;i++){
		printf("|");
		for(j = 0;j < num_col;j++){
			if(i == lin && j == col){
				printf("*");
			}else if(labirinto[i][j] == 0){
				printf("X");
			}else if(labirinto[i][j] == 1){
				printf(" ");
			}else if(labirinto[i][j] == 2){
				printf(".");
			}else{
				printf("o");
			}
		}
		printf("|\n");
	}
	for(i = 0;i < num_col + 2;i++){
		printf("-");
	}
	printf("\n\n");
	marc[lin][col] = true;
	for(k = 0;k < 4;k++){
		new_lin = lin + direcao_lin[k];
		new_col = col + direcao_col[k];
		if(new_lin < 0 || num_lin < new_lin || new_col < 0 || num_col < new_col || labirinto[new_lin][new_col] == 0 || marc[new_lin][new_col] == true){
			continue;
}
		labirinto[lin][col] = 2;
		BT(new_lin, new_col);
		labirinto[lin][col] = 1;
		one_second();
		printf("\n\n");
		for(i = 0;i < num_col + 2;i++){
			printf("-");
		}
		printf("\n");
		for(i = 0;i < num_lin;i++){
			printf("|");
			for(j = 0;j < num_col;j++){
				if(i == lin && j == col){
					printf("*");
				}else if(labirinto[i][j] == 0){
					printf("X");
				}else if(labirinto[i][j] == 1){
					printf(" ");
				}else if(labirinto[i][j] == 2){
					printf(".");
				}else{
					printf("o");
				}
			}
			printf("|\n");
		}
		for(i = 0;i < num_col + 2;i++){
			printf("-");
		}
		printf("\n\n");
	}	
	labirinto[lin][col] = 3;
	return;
}

void DFS(int lin, int col){
	int new_lin, new_col, i, j;
	marc[lin][col] = true;
	for(i = 0;i < 4;i++){
		new_lin = lin + direcao_lin[i];
		new_col = col + direcao_col[i];
		if(new_lin < 0 || num_lin < new_lin || new_col < 0 || labirinto[new_lin][new_col] == 0){
			continue;
		}
		if(distancia[new_lin][new_col] == distancia[lin][col] - 1){
			DFS(new_lin, new_col);
			break;
		}
	}
	caminho_lin[caminho_tam] = lin;
	caminho_col[caminho_tam] = col;
	caminho_tam++;
	return;
}

int main(){
	int lin_ini, col_ini, lin_fim, col_fim, d, lin, col, new_d, new_lin, new_col, i, j, k;
	Ev aux;
	printf("Digite o numero de linhas (MAX 100): ");
	scanf("%d", &num_lin);
	printf("Digite o numero de colunas (MAX 100): ");
	scanf("%d", &num_col);
	printf("Digite o labirinto (0 ocupado e 1 livre):\n");
	for(i = 0;i < num_lin;i++){
		for(j = 0;j < num_col;j++){
			scanf("%d", &labirinto[i][j]);
			distancia[i][j] = INF;
			marc[i][j] = false;
		}		
	}
	printf("Digite a linha e a coluna do inicio: ");
	scanf("%d %d", &lin_ini, &col_ini);
	printf("Digite a linha e a coluna do fim: ");
	scanf("%d %d", &lin_fim, &col_fim);
	Ev fila[10010];
	int tam_fila = 0;
	aux.dist = 0;
	aux.lin = lin_ini;
	aux.col = col_ini;
	fila[tam_fila] = aux;
	tam_fila++;
	distancia[lin_ini][col_ini] = 0;
	k = 0;
	while(k != tam_fila){
		d = fila[k].dist;
		lin = fila[k].lin;
		col = fila[k].col;
		k++;
		if(d != distancia[lin][col])	{
			continue;
		}
		for(i = 0;i < 4;i++){
			new_lin = lin + direcao_lin[i];
			new_col = col + direcao_col[i];
			new_d = d + 1;
			if(new_lin < 0 || num_lin < new_lin || new_col < 0 || num_col < new_col || labirinto[new_lin][new_col] == 0){
				continue;
			}
			if(distancia[new_lin][new_col] > new_d){
				distancia[new_lin][new_col] = new_d;
				aux.dist = new_d;
				aux.lin = new_lin;
				aux.col = new_col;
				fila[tam_fila] = aux;
				tam_fila++;
			}
		}	
	}
	if(distancia[lin_fim][col_fim] == INF){
		BT(lin_ini, col_ini);
		printf("Este labirinto não tem saída, traga-me um helicóptero\n");
	}else{
		DFS(lin_fim, col_fim);
		for(k = 0;k < caminho_tam;k++){
			lin = caminho_lin[k];
			col = caminho_col[k];
			one_second();
			printf("\n\n");
			for(i = 0;i < num_col + 2;i++){
				printf("-");
			}
			printf("\n");
			for(i = 0;i < num_lin;i++){
				printf("|");
				for(j = 0;j < num_col;j++){
					if(i == lin && j == col){
						printf("*");
					}else if(labirinto[i][j] == 0){
						printf("X");
					}else if(labirinto[i][j] == 1){
						printf(" ");
					}else if(labirinto[i][j] == 2){
						printf(".");
					}else{
						printf("o");
					}
				}
				printf("|\n");
			}
			for(i = 0;i < num_col + 2;i++){
				printf("-");
			}
			printf("\n\n");
			labirinto[lin][col] = 2;
		}
		printf("Ufa… Encontrei a saída\n");
	}
	return 0;
}
