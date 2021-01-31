#ifndef MATRIZESPARSA_H_INCLUDED
#define MATRIZESPARSA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int linha;
	int coluna;
	int valor;
	struct node* direita;
	struct node* baixo;	
}Node;


typedef struct{
	Node** linhas;	//ponteiro para o vetor cujas células são ponteiros de nós
	Node** colunas;	//ponteiro para o vetor cujas células são ponteiros de nós
	int numLinhas;	//Quantidade de linhas da matriz
	int numColunas;	//Quantidade de colunas da matriz
}MatrizEsparsa;

//Funções auxiliares

Node* criarNode(int linha,int coluna, int valor){ //função para criar um no
    Node* no=(Node*)malloc(sizeof(Node));//alocar espaço na memoria
    no->linha=linha; // atribuindo os valores passado por parametro
    no->coluna=coluna;
    no->valor=valor;
    no->direita=NULL; //ponteiros vazios
    no->baixo=NULL;
}

Node* PegaEnderecoNode(MatrizEsparsa* m, int linha, int coluna){//buscar o endereco do elemento buscado
	
    if(m == NULL) return NULL; //se a matriz esta vazia
    if(linha > m->numLinhas-1) return NULL;//se o número de linhas é maior que tem na linhas de matriz
	if(coluna > m->numColunas-1) return NULL;//se o número de colunas é maior que tem na colunas de matriz
    if(linha < 0) return NULL;// verificar se são numeros negativos
	if(coluna < 0) return NULL;
    
    int i = 0;//contador
    Node* aux = m->linhas[linha];// auxiliar para não peder os dados da matriz e acessa-la
    while(aux->direita != NULL && i < coluna){//enquanto o ponteiro nao estiver vazio e for menor coluna 
        if(aux->direita->coluna <= coluna ){// quando chegar na posiçao desejada
			aux = aux->direita;	//auxiliar receber a proxima posicao
		}
		i++;
    }
	
    return aux;//retornar o endereço
}


// Protóticos 

MatrizEsparsa* criarMatriz(int qtdeLinhas, int qtdeColunas);
void inserir(MatrizEsparsa* m, int linha, int coluna, int valor);
void remover(MatrizEsparsa* m, int linha, int coluna);
int acessar(MatrizEsparsa* m, int linha, int coluna);
void imprimir(MatrizEsparsa* m);
void desalocar_matriz(MatrizEsparsa* m);

// Implementação

void inserir(MatrizEsparsa* m, int linha, int coluna, int valor){
    Node* novo;
    novo = criarNode(linha,coluna,valor);//criar um nó para o auxiliar
	if(m->linhas[linha] == NULL){//se estiver vazio ele verifica
		m->linhas[linha] = novo;
	}else{
		Node* aux = PegaEnderecoNode(m, linha, coluna);//auxiliares
		Node* aux1 = PegaEnderecoNode(m, linha, aux->coluna-1);
		if(aux->coluna == coluna){//Se já existir um elemento onde deseja inserir na coluna
			aux->valor = novo->valor;
		}else{
			if(aux->coluna > coluna){//caso a coluna ainda for maior
				novo->direita = aux;//auxiliar recebe a proxima posiçao
				m->linhas[linha] = novo;
			}else{
				novo->direita = aux->direita;//auxiliar recebe posiçao anterior
				aux->direita = novo;
			}
		}
	}
	if(m->colunas[coluna] == NULL){//caso esteja vazio
		m->colunas[coluna] = novo;
	}
	else{
		Node* aux = PegaEnderecoNode(m, linha, coluna);//auxiliares
		Node* aux2 = PegaEnderecoNode(m, aux->linha-1, coluna);
		if(aux->linha == linha){//Se já existir um elemento onde deseja inserir na linha
			aux->valor = novo->valor;
		}
		else{
			if(aux->linha > linha){//caso a linha ainda for maior
				novo->baixo = m->colunas[coluna];//aux recebe a proxima posiçao
				m->colunas[coluna] = novo;
			}
			else{
				novo->baixo = aux->baixo;//aux recebe posiçao anterior
				aux->baixo = novo;
			}
		}	
	}		
}




MatrizEsparsa* criarMatriz(int qtdeLinhas, int qtdeColunas){
    MatrizEsparsa* m=(MatrizEsparsa*)malloc(sizeof(MatrizEsparsa)); //Alocação o espaco para as matriz
    m->linhas=(Node**)calloc(qtdeLinhas,sizeof(Node*));// alocação da memória para as linas
    m->colunas=(Node**)calloc(qtdeColunas,sizeof(Node*));//alocação da memória para as colunas
    for(int i=0;i<qtdeLinhas;i++){//cria a  matriz vazia
        m->linhas[i]=NULL;
    }
    for(int j=0;j<qtdeColunas;j++){
        m->colunas[j]=NULL;
    }
    m->numLinhas=qtdeLinhas;
    m->numColunas=qtdeColunas;
    return m;
}



void remover(MatrizEsparsa* m, int linha, int coluna){

	Node* aux = PegaEnderecoNode(m, linha, coluna);//auxiliares
	Node* aux1;
	int x = 0;
	printf("test\n");

	if (m->linhas[linha] == NULL)
	{
		printf("Posição Inválida.\n");
	}else if (m->linhas[linha]->coluna < coluna)
	{
		aux1 = m->linhas[linha];
		while(x == 0){
			if (aux1->direita->direita->coluna == coluna)
			{
				aux1->direita = aux1->direita->direita;
				x = 1;
			}
		}

	}else if (m->linhas[linha]->coluna == coluna)
	{
		m->linhas[linha] = m->linhas[linha]->direita;	
	}














	// if (m->linhas[linha]->coluna == coluna)
	// {
	// 	m->linhas[linha] = aux->direita;	
	// }else
	// 	if (m->linhas[linha] != NULL)
	// 	{
	// 		aux1 = m->linhas[linha];
	// 		while(aux1->direita->coluna <= coluna){
	// 			if (aux1->direita->coluna == coluna)
	// 			{
	// 				if (aux1->direita->direita != NULL)
	// 					aux1->direita = aux1->direita->direita;
	// 				else{
	// 			printf("test: \n");
	// 					aux1->direita = NULL;
	// 				}
	// 			}else
	// 			{
	// 				aux1 = aux1->direita;
	// 			}
	// 		}
	// 	}
	// if (m->colunas[coluna]->linha == linha)
	// {
	// 	m->colunas[coluna] = aux->baixo;	
	// }else
	// 	if (m->colunas[coluna] != NULL)
	// 	{
	// 		aux1 = m->colunas[coluna];
	// 		while(aux1->baixo->linha <= linha){
	// 			if (aux1->baixo->linha == linha)
	// 			{
	// 				aux1->baixo = aux1->baixo->baixo;
	// 			}
	// 			else
	// 			{
	// 				aux1 = aux1->baixo;

	// 			}
	// 		}
	// 	}


}

int acessar(MatrizEsparsa* m, int linha, int coluna){
    Node* aux = PegaEnderecoNode(m, linha, coluna);//auxiliar
	if(aux->coluna == coluna){//buscar a posicao desejada
		return aux->valor;
	}
	else{
		return 0;
	}
}

void imprimir(MatrizEsparsa* m){
    Node* aux;
	for(int i=0; i < m->numLinhas; i++){//acessar as linhas
		aux = m->linhas[i];//armazenar os dados
		for(int j = 0; j < m->numColunas; j++){//acessar as colunas;
			if(aux != NULL && j == aux->coluna){//se caso tiver elemento estiver na coluna
				printf("%d ", aux->valor);	// imprime			
				aux = aux->direita;// auxiliar vai para proxima posicao
            }
			else{
			    printf("%d ",0);//imprime o zero
				}
				

		}
		printf("\n");
    } 
}

void desalocar_matriz(MatrizEsparsa* m){
	for(int i=0;i< m->numLinhas; i++){
		for(int j = 0;j < m->numColunas;j++){
			Node* aux = m->linhas[i];//auxiliar para armazenar os dados da matriz
			Node* aux1;//auxilia para armazenar a posicao anterior
			while(aux->direita != NULL){//se a proxima posicao nao for nula
				aux1= aux;//auxiliar 1 recebe os dados da variavel
				aux = aux->direita;//auxiliar vai para proxima posiçao
			}
			aux1->direita = NULL;//auxiliar 1 tambem vai para proxima posicao
			free (aux);// limpara a auxiliar
		}		
	}
    free(m);
}



#endif // MATRIZESPARSA_H_INCLUDED