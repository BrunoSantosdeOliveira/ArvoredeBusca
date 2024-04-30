#include <stdio.h>
#include <stdlib.h>


typedef struct tItem {
    int chave;
    struct tItem *pai, *esq, *dir;
} Item;


typedef struct tArvore {
    Item *raiz;
    int quantidade;
} Arvore;


Item *criaItem(int x) {
    Item *novo = (Item *)malloc(sizeof(Item));
    if (novo != NULL) {
        novo->chave = x;
        novo->pai = NULL;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}


Arvore *criaArvoreVazia() {
    Arvore *novaArvore = (Arvore *)malloc(sizeof(Arvore));
    if (novaArvore != NULL) {
        novaArvore->raiz = NULL;
        novaArvore->quantidade = 0;
    }
    return novaArvore;
}


void liberaArvoreRecursivo(Item *raiz) {
    if (raiz != NULL) {
        liberaArvoreRecursivo(raiz->esq);
        liberaArvoreRecursivo(raiz->dir);
        printf("libera: %d\n", raiz->chave);
        free(raiz);
    }
}

void liberaArvore(Arvore *arvore) {
    if (arvore != NULL) {
        liberaArvoreRecursivo(arvore->raiz);
        free(arvore);
    }
}


int vazia(Arvore *arv) {
    return arv->raiz == NULL;
}


void inserir(Arvore *arv, int x) {
    if (arv == NULL)
        return;

    Item *novo = criaItem(x);
    if (novo == NULL)
        return;

    Item *atual = arv->raiz;
    Item *anterior = NULL;

  
    while (atual != NULL) {
        anterior = atual;
        if (x < atual->chave)
            atual = atual->esq;
        else if (x > atual->chave)
            atual = atual->dir;
        else {
            free(novo); 
            return;
        }
    }

  
    novo->pai = anterior;
    if (anterior == NULL)
        arv->raiz = novo; // Árvore vazia
    else if (x < anterior->chave)
        anterior->esq = novo;
    else
        anterior->dir = novo;

    arv->quantidade++;
}


void imprimirRecursivo(Item *raiz) {
    if (raiz != NULL) {
        imprimirRecursivo(raiz->esq);
        printf("%d ", raiz->chave);
        imprimirRecursivo(raiz->dir);
    }
}

void imprimir(Arvore *arv) {
    if (arv != NULL && !vazia(arv)) {
        imprimirRecursivo(arv->raiz);
        printf("\n");
    }
}

int main() {
    int n, i, x;
    scanf("%d", &n);
    Arvore *arv = criaArvoreVazia();
    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        inserir(arv, x);
    }
    imprimir(arv);
    liberaArvore(arv);
    return 0;
}
