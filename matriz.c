/**********************************
Algoritmos e Estrutura de Dados 1
Prof. Rafael Liberato
-----------------------------------
Exercício: APS.
Aluno: Juan Felipe S. Rangel 
       Vinicius Henrique Soares
Data: 11/07/2019
***********************************/
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"



int main(){
int op,dash,dash2;
MatrizEsparsa* m;
int linhas,colunas;
int linha,coluna,valor;


do{
	    printf("+------------------------------------+\n");
	    printf("| 1-Criar matriz                     |\n");
	    printf("| 2-Inserir elemento                 |\n");
	    printf("| 3-Acessar Elemento                 |\n");
	    printf("| 4-Imprimir matriz                  |\n");
	    printf("| 5-Desalocar                        |\n");
	    printf("| 6-Remover                          |\n");
	    printf("| 8-Sair                             |\n");
	    printf("+------------------------------------+\n");
	    scanf("%i", &op);
	    system ("cls");

	    	if(op == 1)
	    	{
                printf("Informe a quantidade de linhas da matriz\n");
                scanf("%d",&linhas);
                printf("Informe a quantidade de colunas da matriz\n");
                scanf("%d",&colunas);
                m = criarMatriz(linhas,colunas);


            }
            if(op == 2){
                printf("Informe a linha de 1 - %d\n",linhas);
                scanf("%d", &linha);
                linha = linha-1;
                printf("Informe a coluna de 1 - %d\n",colunas);
                scanf("%d", &coluna);
                coluna = coluna-1;
                printf("Informe o valor\n");
                scanf("%d", &valor);
                system ("cls");
                inserir(m,linha ,coluna ,valor);
                
            }
            if(op == 3)
             {
                printf("Informe a linha para acessar\n");
                scanf("%d", &linha);
                printf("Informe a coluna para acessar\n");
                scanf("%d", &coluna);
                dash = acessar(m,linha-1,coluna-1);
                printf("O valor contido e : %d\n",dash);

            }
            if(op == 4)
            {
                imprimir(m);
            }
            if(op == 5)
            {
                desalocar_matriz(m);
            }
            if(op == 6)
            {
                printf("Informe a linha que você deseja remover\n");
                scanf("%d",&linhas);
                printf("Informe a coluna que você deseja remover\n");
                scanf("%d",&colunas);
                remover(m,linhas-1,colunas-1);


            }
	}while(op != 8);
return 0;
}