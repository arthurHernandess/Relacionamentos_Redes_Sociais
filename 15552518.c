/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2025                          **/
/**   Prof. Luciano Digiampietri                                    **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   ARTHUR DE LIMA HERNANDES                15552518              **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define NUM_CARACT 10
#define MAX_VALOR 99

#define true 1
#define false 0

typedef int bool;

typedef struct {
  /* grafo com representação de matriz de adjacência, não-direcionado e não-ponderado */
    int numVertices;
    int numArestas;
    bool** matriz; // matriz de adjacência, representando todos os relacionamentos (booleano)
    int** caracteristicas;  // matriz de características de cada usuário -> são v vertices por 10 caracteristicas (fixo)  
} Grafo;

typedef struct aux{
  int valor;
  struct aux* prox;
} No;
typedef struct{
  No* inicio;
  No* fim;
} Fila;


void printf123(){
    // Funcao usada pelo sistema de correcao automatica (nao mexer)
}

bool inicializaGrafo(Grafo* g, int vertices){
  if (g==NULL || vertices<1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool**) malloc(sizeof(bool*)*vertices);
  g->caracteristicas = (int**) malloc(sizeof(int*)*vertices);
  for (x=0; x<vertices; x++){
    g->matriz[x] = (bool*) malloc(sizeof(bool)*vertices);
    for (y=0; y<vertices; y++){
      g->matriz[x][y] = false;
    }
    g->caracteristicas[x] = (int*) malloc(sizeof(int)*NUM_CARACT);
    for (y=0; y<NUM_CARACT; y++){
      g->caracteristicas[x][y] = -1;
    }
  }
  return true;
}

bool liberaGrafo(Grafo* g){
  if (g==NULL) return false;
  int x;
  for (x=0; x<g->numVertices; x++){
    free(g->matriz[x]);
    free(g->caracteristicas[x]);
  }
  free(g->matriz);
  free(g->caracteristicas);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  g->caracteristicas = NULL;
  return true;
}

int numeroDeVertices(Grafo* g){
  if (g != NULL) return g->numVertices;
  else return -1;
}

int numeroDeArestas(Grafo* g){
  if (g != NULL) return g->numArestas;
  else return -1;
}

bool possuiVizinhos(Grafo* g, int v){
  if (!g || v < 0 || v >= g->numVertices) return false;
  int x;
  for (x=0;x<g->numVertices;x++)
    if (g->matriz[v][x]) return true;
  return false;
}

bool insereAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || v1 == v2) return false;
  if (g->matriz[v1][v2] == false){
      g->matriz[v1][v2] = true;
      g->matriz[v2][v1] = true;
      g->numArestas++;
  }
  return true;
}

bool removeAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  g->matriz[v1][v2] = false;
  g->matriz[v2][v1] = false;
  g->numArestas--;
  return true;
}

bool atualizaCaracteristica(Grafo* g, int v, int c, int valor){
  if (!g || v < 0 || c < 0 || v >= g->numVertices || c >= NUM_CARACT || valor<-1) return false;
  g->caracteristicas[v][c] = valor;
  return true;
}

bool arestaExiste(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  return true;
}

Grafo* criaGrafoAleatorio(int numVertices, int numArestas){
  printf("### Criando grafo: v=%i e a=%i ###\n",numVertices, numArestas);
  int x, y, a = 0;
  if (numVertices < 1 || numArestas >= numVertices*(numVertices-1)/2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;  
  }
  Grafo* g = (Grafo*)malloc(sizeof(Grafo));
  inicializaGrafo(g,numVertices);
  while(a<numArestas){
    x = rand()%numVertices;
    y = rand()%numVertices;
    if (x!=y && g->matriz[x][y] == false){
      g->matriz[x][y] = true;
      g->matriz[y][x] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  for (x=0; x<numVertices; x++){
    for (y=0; y<NUM_CARACT; y++){
      if (rand() % 3 < 2){
        g->caracteristicas[x][y] = rand() % 5;
      }
    }
  }
  return g;
}

void exibeGrafo(Grafo* g){   /* exibe em matriz */
  if(!g) return;
  int x, y;
  printf("\nImprimindo grafo (v=%i; a=%i)\n   ", g->numVertices, g->numArestas);
  for (x=0;x<g->numVertices;x++) printf(" %3i",x);
  printf("\n");
  for (x=0;x<g->numVertices;x++){
    printf("%3i",x);
    for (y=0;y<g->numVertices;y++)
      printf(" %3i",g->matriz[x][y]);  
    printf("\n");
  }
  printf("\nCaracteristicas:\n");

  for (x=0;x<g->numVertices;x++){
    printf("[%2i]",x);
    for (y=0;y<NUM_CARACT;y++)
      printf(" %3i",g->caracteristicas[x][y]);  
    printf("\n");
  }
}

void exibeArranjoReais(double* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf("  v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%3.2f\t",arranjo[x]);
  }
  printf("\n\n");
}

void exibeArranjoInteiros(int* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf(" v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%3i\t",arranjo[x]);
  }
  printf("\n\n");
}

void zerarArray(int* array, int n){
  if(array == NULL || n <= 0) return;
  for(int g = 0; g < n; g++){
    array[g] = 0;
  }
}

void zerarArrayDouble(double* array, int n){
	if(array == NULL || n <= 0) return;
	for(int h = 0; h < n; h++){
		array[h] = 0.00;
	}
}

void homofiliaPonderada(Grafo* g, int v, double* valores, int* pesos){
	for(int i = 0; i < g->numVertices; i++){
    for(int j = 0; j < NUM_CARACT; j++){
      if(g->caracteristicas[i][j] == g->caracteristicas[v][j] && g->caracteristicas[i][j] != -1){
        valores[i] = (double)1/pesos[j] + valores[i];
      }
    }
  }
}

void inicializarFila(Fila* f){
  f->fim = NULL;
  f->inicio = NULL;
}

bool filaTaVazia(Fila* f){
  if(f->inicio == NULL)
    return true;
  else
    return false;
}

void inserirFila(Fila* f, int valor){
  if(!f) return;
  No* novo = (No*)malloc(sizeof(No));
  novo->valor = valor;
  novo->prox = NULL;
  if(f->inicio == NULL){
    f->inicio = novo;
    f->fim = novo;
  }
  else{
    f->fim->prox = novo;
    f->fim = novo;
  }
}

int excluirFila(Fila* f){
  if(f == NULL) return -1;
  if(filaTaVazia(f)) return -1;
  int valor = f->inicio->valor;
  f->inicio = f->inicio->prox;
  if(f->inicio == NULL)
    f->fim == NULL;
  return valor;
}

/* --------------------------------------------------------------------------------------------------------------- */

void homofilia(Grafo* g, int v, int* valores) {
  // 'valores' eh um array de todos os vertices, que eu devo preencher cada indice (inclusive o do próprio v) com a quantidade de características em comum com o vertice v. Só toamr cuidado pois -1 é não preenchido e nao pode ser considerado caracteristica em comum
  if(g == NULL || v >= g->numVertices || valores == NULL) return;
  zerarArray(valores, g->numVertices);
  
  for(int i = 0; i < g->numVertices; i++){
    for(int j = 0; j < NUM_CARACT; j++){
      if(g->caracteristicas[i][j] == g->caracteristicas[v][j] && g->caracteristicas[i][j] != -1){
        valores[i]++;
      }
    }
  }
  return;
}

void raridade(Grafo* g, int v, double* valores) {
  if(g == NULL || v >= g->numVertices || valores == NULL) return;
	zerarArrayDouble(valores, g->numVertices);

	int* repeticoes = (int*)calloc(NUM_CARACT, sizeof(int)); // conta a quantidade de repetições que o valor da característica y tem entre o vertice v e os outros
	for(int j = 0; j < NUM_CARACT; j++){	//	roda a matriz verticalmente
		for(int i = 0; i < g->numVertices; i++){
			if(g->caracteristicas[v][j] == g->caracteristicas[i][j] && g->caracteristicas[i][j] > -1){
				repeticoes[j]++;
			}	
		}
	}

	homofiliaPonderada(g, v , valores, repeticoes);
}  

void influenciaSocial(Grafo* g, int v, int* valores) {
  if(g == NULL || v >= g->numVertices || valores == NULL) return;
	zerarArray(valores, g->numVertices);

  for(int i = 0; i < g->numVertices; i++){  // a posição "fixa" q eu vou preencher o array 'valores'
    for(int j = 0; j < 10; j++){  
      for(int k = 0; k < g->numVertices; k++){
        if(g->matriz[v][k]){
          if(g->caracteristicas[i][j] == g->caracteristicas[k][j] && g->caracteristicas[i][j] != -1){
            valores[i]++;
          }
        }    
      }
    }
  }
}

void amizadesEmComum(Grafo* g, int v, int* valores) {
  if(g == NULL || v >= g->numVertices || valores == NULL) return;
	zerarArray(valores, g->numVertices);

  for(int i = 0; i < g->numVertices; i++){
    for(int j = 0; j < g->numVertices; j++){
      if(g->matriz[i][j]){
        if(g->matriz[v][j]){
          valores[i]++;
        }
      }
    }
  }
}

void proximidadeSocial(Grafo* g, int v, int* valores) {
  if(g == NULL || v >= g->numVertices || valores == NULL) return;
  for(int j = 0; j < g->numVertices; j++) // inicia o array de valores com -1 (vamos usar isso direto ao invés de um array "visitados")
    valores[j] = -1;

  int distancia = 1;
  int qtNosCamadaAtual = 1;
  int qtNosProximaCamada = 0;
  int atual;
  Fila filaDeExecucao;

  inicializarFila(&filaDeExecucao);
  inserirFila(&filaDeExecucao, v);
  valores[v] = 0;

  while(!filaTaVazia(&filaDeExecucao)){
    atual = excluirFila(&filaDeExecucao);
    qtNosCamadaAtual--;

    for(int i = 0; i < g->numVertices; i++){
      if(valores[i] == -1 && g->matriz[atual][i]){    // verifica se foi visitado (distancia atribuida) e se existe relação
        inserirFila(&filaDeExecucao, i);              // coloca na fila pra ser o "atual" e atualiza a distancia
        valores[i] = distancia;
        qtNosProximaCamada++;
      }
    }

    if(qtNosCamadaAtual == 0){    // verifica se acabou os vertices dessa camada, se acabou, vai pra proxima e aumenta a distancia
      if(qtNosProximaCamada > 0){
        distancia++;
        qtNosCamadaAtual = qtNosProximaCamada;
        qtNosProximaCamada = 0;
      }
    }
  }

  for(int k = 0; k < g->numVertices; k++){  // para os vertices nao alcançados (que ficaram com dist -1) - membros desconexos
    if(valores[k] == -1){
      valores[k] = g->numVertices;          // atualiza a dist deles para numero de vertices do grafo
    }
  }
}

void conexaoPreferencial(Grafo* g, int v, int* valores) {
  // o vertice v em específico não importa aqui
  if(g == NULL || v >= g->numVertices || valores == NULL) return;
	zerarArray(valores, g->numVertices);

  for(int i = 0; i < g->numVertices; i++){
    for(int j = 0; j < g->numVertices; j++){
      if(g->matriz[i][j]){
        valores[i]++;
      }
    }
  }
}

/* -------------------------------------------------------------------------------------------------------------- */

void testaFuncoes(Grafo* g, int n, int v){
  int* valoresInteiros = (int*)malloc(sizeof(int)*n);
  double* valoresReais = (double*)malloc(sizeof(double)*n);

  printf("\nRealizando analise em relacao ao vertice %i.\n",v);

  printf("Homofilia:\n");
  homofilia(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  printf("Raridade:\n");
  raridade(g, v, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Influencia Social:\n");
  influenciaSocial(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  printf("Amizades em Comum:\n");
  amizadesEmComum(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  printf("Proximidade Social:\n");
  proximidadeSocial(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  printf("Conexao Preferencial:\n");
  conexaoPreferencial(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  free(valoresInteiros);
  free(valoresReais);
}

int main() {
  int n = 5;
  int* valoresInteiros = (int*)malloc(sizeof(int)*n);
  double* valoresReais = (double*)malloc(sizeof(double)*n);

  Grafo g1;
  inicializaGrafo(&g1, n);
  insereAresta(&g1,0,1);
  insereAresta(&g1,0,2);
  insereAresta(&g1,1,4);
  insereAresta(&g1,1,3);
  insereAresta(&g1,2,3);
  atualizaCaracteristica(&g1, 0, 2, 2);
  atualizaCaracteristica(&g1, 0, 1, 1);
  atualizaCaracteristica(&g1, 1, 1, 1);
  atualizaCaracteristica(&g1, 1, 2, 2);
  atualizaCaracteristica(&g1, 1, 3, 3);
  atualizaCaracteristica(&g1, 2, 2, 2);
  atualizaCaracteristica(&g1, 3, 2, 2);
  atualizaCaracteristica(&g1, 4, 3, 3);
  atualizaCaracteristica(&g1, 4, 2, 5);
  atualizaCaracteristica(&g1, 4, 4, 4);

  /*atualizaCaracteristica(&g1, 0, 2, 2);
  atualizaCaracteristica(&g1, 0, 1, 1);
  atualizaCaracteristica(&g1, 0, 5, 10);
  atualizaCaracteristica(&g1, 0, 7, 2);
  atualizaCaracteristica(&g1, 1, 1, 1);
  atualizaCaracteristica(&g1, 1, 2, 2);
  atualizaCaracteristica(&g1, 1, 3, 3);
  atualizaCaracteristica(&g1, 1, 5, 11);
  atualizaCaracteristica(&g1, 1, 7, 2);
  atualizaCaracteristica(&g1, 2, 0, 7);
  atualizaCaracteristica(&g1, 2, 2, 2);
  atualizaCaracteristica(&g1, 2, 6, 6);
  atualizaCaracteristica(&g1, 2, 8, 4);
  atualizaCaracteristica(&g1, 2, 5, 10);
  atualizaCaracteristica(&g1, 3, 0, 7);
  atualizaCaracteristica(&g1, 3, 2, 9);
  atualizaCaracteristica(&g1, 3, 8, 4);
  atualizaCaracteristica(&g1, 3, 5, 11);
  atualizaCaracteristica(&g1, 3, 6, 6);
  atualizaCaracteristica(&g1, 3, 9, 0);
  atualizaCaracteristica(&g1, 4, 3, 3);
  atualizaCaracteristica(&g1, 4, 2, 5);
  atualizaCaracteristica(&g1, 4, 4, 4);
  atualizaCaracteristica(&g1, 4, 6, 4);
  atualizaCaracteristica(&g1, 4, 7, 2);
  atualizaCaracteristica(&g1, 4, 5, 11);
  atualizaCaracteristica(&g1, 4, 9, 0);*/

  printf("PRIMEIRO EXEMPLO\n");
  exibeGrafo(&g1);
  testaFuncoes(&g1, n, 0);

  printf("\n\nSEGUNDO EXEMPLO\n");
  removeAresta(&g1,0,2);
  removeAresta(&g1,2,3);
  exibeGrafo(&g1);
  testaFuncoes(&g1, n, 0);

  printf("\n\nTERCEIRO EXEMPLO\n");
  exibeGrafo(&g1);
  testaFuncoes(&g1, n, 3);

  printf("\n\nQUARTO EXEMPLO\n\n");
  n = 6;
  int arestas = 8;
  Grafo* g2 = criaGrafoAleatorio(n,arestas);
  exibeGrafo(g2);
  testaFuncoes(g2, n, 4);

	liberaGrafo(&g1);
  liberaGrafo(g2);
  free(valoresInteiros);
  free(valoresReais);
  return 0;  
}
