#include <stdio.h>
#include <stdlib.h>

// Aluno: André Werlang Menegazzo

typedef struct No {
    int dado;
    struct No* prox;
} No;

typedef struct {
    No* cabeca;
    int tamanho;
} Lista;

//  Criacao 

void criaLista(Lista* L) {
    L->cabeca = NULL;
    L->tamanho = 0;
}

//  Consultas 

int vazia(Lista* L) {
    return (L->tamanho == 0);
}

int tamanho(Lista* L) {
    return L->tamanho;
}

// Obtem valor do elemento da posicao pos (1..n) 
int elemento(Lista* L, int pos) {
    if (pos < 1 || pos > L->tamanho) return -1;

    No* aux = L->cabeca;
    int cont = 1;
    while (cont < pos) {
        aux = aux->prox;
        cont++;
    }
    return aux->dado;
}

// Modifica o valor do elemento da posicao pos 
int modifica(Lista* L, int pos, int novo) {
    if (pos < 1 || pos > L->tamanho) return 0;

    No* aux = L->cabeca;
    int cont = 1;
    while (cont < pos) {
        aux = aux->prox;
        cont++;
    }
    aux->dado = novo;
    return 1;
}

//  Insercoes 

int insereInicio(Lista* L, int dado) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) return 0;

    novo->dado = dado;
    novo->prox = L->cabeca;

    L->cabeca = novo;
    L->tamanho++;
    return 1;
}

int insereFim(Lista* L, int dado) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) return 0;

    novo->dado = dado;
    novo->prox = NULL;

    if (vazia(L)) {
        L->cabeca = novo;
    } else {
        No* aux = L->cabeca;
        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
    L->tamanho++;
    return 1;
}

int insereMeio(Lista* L, int pos, int dado) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) return 0;

    novo->dado = dado;

    No* aux = L->cabeca;
    int cont = 1;

    while (cont < pos - 1) {
        aux = aux->prox;
        cont++;
    }

    novo->prox = aux->prox;
    aux->prox = novo;
    L->tamanho++;
    return 1;
}

// Interface principal 
int insere(Lista* L, int pos, int dado) {
    if (pos < 1 || pos > L->tamanho + 1)
        return 0;

    if (pos == 1) return insereInicio(L, dado);
    if (pos == L->tamanho + 1) return insereFim(L, dado);
    return insereMeio(L, pos, dado);
}

//  Remocoes  

int removeInicio(Lista* L) {
    if (vazia(L)) return -1;

    No* p = L->cabeca;
    int dado = p->dado;

    L->cabeca = p->prox;
    free(p);

    L->tamanho--;
    return dado;
}

int removeFim(Lista* L) {
    if (vazia(L)) return -1;

    No* atual = L->cabeca;
    No* ant = NULL;

    while (atual->prox != NULL) {
        ant = atual;
        atual = atual->prox;
    }

    int dado = atual->dado;

    if (ant == NULL) {
        L->cabeca = NULL;
    } else {
        ant->prox = NULL;
    }

    free(atual);
    L->tamanho--;
    return dado;
}

int removeMeio(Lista* L, int pos) {
    No* atual = L->cabeca;
    No* ant = NULL;

    int cont = 1;
    while (cont < pos) {
        ant = atual;
        atual = atual->prox;
        cont++;
    }

    int dado = atual->dado;
    ant->prox = atual->prox;
    free(atual);

    L->tamanho--;
    return dado;
}

int removePos(Lista* L, int pos) {
    if (vazia(L) || pos < 1 || pos > L->tamanho)
        return -1;

    if (pos == 1) return removeInicio(L);
    if (pos == L->tamanho) return removeFim(L);
    return removeMeio(L, pos);
}

//  Impressao 

void imprime(Lista* L) {
    No* aux = L->cabeca;
    while (aux != NULL) {
        printf("%d ", aux->dado);
        aux = aux->prox;
    }
    printf("\n");
}

//  Main para testes 

int main(void) {
    Lista L;
    criaLista(&L);

    insere(&L, 1, 10);
    insere(&L, 2, 20);
    insere(&L, 3, 30);
    insere(&L, 2, 99);

    imprime(&L);

    printf("Remove pos 3 -> %d\n", removePos(&L, 3));
    imprime(&L);

    modifica(&L, 2, 555);
    imprime(&L);

    return 0;
}
