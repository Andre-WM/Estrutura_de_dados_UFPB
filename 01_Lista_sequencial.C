#include <stdio.h>

#define MAX 100


// Estrutura da Lista Sequencial

typedef struct {
    int dados[MAX];
    int tamAtual;
    int tamMax;
} ListaSeq;


// Funções da Lista Sequencial

void criarLista(ListaSeq *l) {
    l->tamMax = MAX;
    l->tamAtual = 0;
}

int vazia(ListaSeq *l) {
    return (l->tamAtual == 0);
}

int cheia(ListaSeq *l) {
    return (l->tamAtual == l->tamMax);
}

int tamanho(ListaSeq *l) {
    return l->tamAtual;
}

int elemento(ListaSeq *l, int pos) {
    if (pos <= 0 || pos > l->tamAtual)
        return -1;  
    return l->dados[pos - 1];   
}

int posicao(ListaSeq *l, int dado) {
    for (int i = 0; i < l->tamAtual; i++) {
        if (l->dados[i] == dado)
            return i + 1;   
    }
    return -1;
}

int insere(ListaSeq *l, int pos, int dado) {

    if (cheia(l) || pos <= 0 || pos > l->tamAtual + 1)
        return 0;

    for (int i = l->tamAtual; i >= pos; i--)
        l->dados[i] = l->dados[i - 1];

    l->dados[pos - 1] = dado;
    l->tamAtual++;

    return 1;
}

int removePos(ListaSeq *l, int pos) {

    if (pos <= 0 || pos > l->tamAtual)
        return -1;

    int dado = l->dados[pos - 1];

    for (int i = pos - 1; i < l->tamAtual - 1; i++)
        l->dados[i] = l->dados[i + 1];

    l->tamAtual--;

    return dado;
}


// Exemplo de uso

int main(void) {
    ListaSeq lista;
    criarLista(&lista);

    insere(&lista, 1, 10);
    insere(&lista, 2, 20);
    insere(&lista, 2, 15);

    printf("Tamanho da lista: %d\n", tamanho(&lista));

    for (int i = 1; i <= tamanho(&lista); i++)
        printf("%d ", elemento(&lista, i));

    printf("\nRemove o elemento da posicao 2:\n");

    int removido = removePos(&lista, 2);
    printf("Removido: %d\n", removido);

    for (int i = 1; i <= tamanho(&lista); i++)
        printf("%d ", elemento(&lista, i));

    return 0;
}