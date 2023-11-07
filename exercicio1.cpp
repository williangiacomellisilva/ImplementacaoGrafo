#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
}ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cab;
}VERTICE;

typedef struct grafo{
 int vertices;
 int arestas;
 VERTICE *adj;
}GRAFO;

GRAFO *criaGrafo (int v){
 int i;

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g -> vertices = v;
    g -> arestas = 0;
    g -> adj = (VERTICE *)malloc(v*sizeof(VERTICE));

    for (i=0; i<v;i++){
        g -> adj[i].cab=NULL;
    }
    return (g);
}

ADJACENCIA *criadAdj(int v, int peso){
ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
temp -> vertice =v;
temp -> peso = peso;
temp -> prox = NULL;
return(temp);
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){
if(!gr) return(false);
if((vf<0)||(vf>=gr->vertices))return(false);
if((vi<0)||(vf>=gr->vertices))return(false);

ADJACENCIA *novo = criadAdj(vf,p);

novo->prox = gr->adj[vi].cab;
gr->adj[vi].cab=novo;
gr->arestas++;
return (true);
}


void imprime(GRAFO *gr){

printf("Vertices: %d. Arestas: %d \n",gr->vertices,gr->arestas);
int i;

for(i = 0; i<gr->vertices; i++){
    printf("v%d:",i+1);
    ADJACENCIA *ad = gr->adj[i].cab;
    while (ad){
        printf("v%d(%d) ",ad->vertice+1,ad->peso);
        ad=ad->prox;
    }
    printf("\n");

}
}

void Matriz(GRAFO *gr){ 
printf("\n\nMatriz de Adjacência:\n");
    for (int i = 0; i < gr->vertices; i++) {
        for (int j = 0; j < gr->vertices; j++) {
            int adjacencia = 0;
            ADJACENCIA *ad = gr->adj[i].cab;
            while (ad) {
                if (ad->vertice == j) {
                    adjacencia = ad->peso;
                }
                ad = ad->prox;
            }
            printf("%d\t", adjacencia);
        }
        printf("\n");
    }
}

int calculaValorTotalCaminho(GRAFO* gr, int* caminho, int numVertices) {
    int valorTotalCaminho = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int vi = caminho[i] - 1; // Convertemos o vertices do caminho para um índice (subtraindo 1)
        int vf = caminho[i + 1] - 1; // O mesmo para o vértice seguinte
        ADJACENCIA* ad = gr->adj[vi].cab;
        bool found = false;

        while (ad) {
            if (ad->vertice == vf) {
                valorTotalCaminho += ad->peso;
                found = true;
                break;
            }
            ad = ad->prox;
        }

        if (!found) {
            // Se a aresta entre os vertices for encontrada, o caminho invalid.
            return -1;
        }
    }

    return valorTotalCaminho;
}

int somaCaminhosDFS(GRAFO *gr, int inicio, int destino, int *visitados) {
    if (inicio == destino) {
        return 0;
    }

    visitados[inicio] = 1;
    ADJACENCIA *ad = gr->adj[inicio].cab;
    int somaCaminhos = 0;

    while (ad != NULL) {
        int proximoVertice = ad->vertice;
        int pesoAresta = ad->peso;

        if (!visitados[proximoVertice]) {
            somaCaminhos += pesoAresta + somaCaminhosDFS(gr, proximoVertice, destino, visitados);
        }

        ad = ad->prox;
    }

    visitados[inicio] = 0;
    return somaCaminhos;
}

int somaCaminhos(GRAFO *gr, int inicio, int destino) {
    int *visitados = (int *)malloc(gr->vertices * sizeof(int));
    for (int i = 0; i < gr->vertices; i++) {
        visitados[i] = 0;
    }
    int soma = somaCaminhosDFS(gr, inicio, destino, visitados);
    free(visitados);
    return soma;
}


int main (){

GRAFO * grafito = criaGrafo(5);

// Arestas
criaAresta(grafito, 0,0,0);
criaAresta(grafito, 0,2,0);
criaAresta(grafito, 1,2,0);
criaAresta(grafito, 1,3,0);
criaAresta(grafito, 1,4,0);
criaAresta(grafito, 2,3,0);
criaAresta(grafito, 3,4,0);

// Lista de adjacencia
printf("\nGrafo em lista de adjacência:\n");
imprime(grafito);

//Matriz de adjacencia
Matriz(grafito);

//------------------- Segundo Grafo
printf("\n");
for(int l=0; l<25;l++) if(l<24) printf("-"); else printf("\n");

GRAFO *grafoOrientado = criaGrafo(5);

    criaAresta(grafoOrientado, 0, 0, 2); 
    criaAresta(grafoOrientado, 0, 2, 7);
    criaAresta(grafoOrientado, 2, 1, 5);
    criaAresta(grafoOrientado, 2, 3, 10);
    criaAresta(grafoOrientado, 3, 1, 9);
    criaAresta(grafoOrientado, 3, 4, 1);
    criaAresta(grafoOrientado, 4, 1, 12);

    printf("Lista de Adjacência (Grafo Orientado e Ponderado):\n");
    imprime(grafoOrientado);
    Matriz(grafoOrientado);

//Soma dos caminhos {1,5}
    imprime(grafoOrientado);
    printf("\nValor total do caminho: %d ",somaCaminhos(grafoOrientado,0,4));

    return 0;
}
