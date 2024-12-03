#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
    int valor;
    struct elemento *prox;
    struct elemento *ant;
} elemento_t;

typedef struct {
    elemento_t *inicio;
    elemento_t *fim;
} lista_t;

elemento_t* criarElemento(int valor);
lista_t* criarLista(int valor);
void inserirFim(lista_t *lista, int valor);
void inserirInicio(lista_t *lista, int valor);
void excluirFim(lista_t *lista);
void excluirInicio(lista_t *lista);
void imprimirListaInicioFim(lista_t *lista);
void imprimirListaFimInicio(lista_t *lista);

int main() {
    lista_t *lista = criarLista(10);

    inserirFim(lista, 20);
    inserirFim(lista, 30);

    imprimirListaInicioFim(lista);
    imprimirListaFimInicio(lista);

    inserirInicio(lista, 5);
    imprimirListaInicioFim(lista);

    excluirFim(lista);
    imprimirListaInicioFim(lista);

    excluirInicio(lista);
    imprimirListaInicioFim(lista);

    return 0;
}

elemento_t* criarElemento(int valor) {
    elemento_t *novo = (elemento_t *)malloc(sizeof(elemento_t));
    if (novo == NULL) {
        return NULL;
    }
    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

lista_t* criarLista(int valor) {
    lista_t *novaLista = (lista_t *)malloc(sizeof(lista_t));
    if (novaLista == NULL) {
        return NULL;
    }
    elemento_t *primeiro = criarElemento(valor);
    novaLista->inicio = primeiro;
    novaLista->fim = primeiro;
    return novaLista;
}

void inserirFim(lista_t *lista, int valor) {
    elemento_t *novo = criarElemento(valor);
    if (lista->fim == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->prox = novo;
        novo->ant = lista->fim;
        lista->fim = novo;
    }
}

void inserirInicio(lista_t *lista, int valor) {
    elemento_t *novo = criarElemento(valor);
    if (lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        novo->prox = lista->inicio;
        lista->inicio->ant = novo;
        lista->inicio = novo;
    }
}

void excluirFim(lista_t *lista) {
    if (lista->fim == NULL) {
        return;
    }
    elemento_t *paraExcluir = lista->fim;
    if (lista->inicio == lista->fim) { 
        lista->inicio = NULL;
        lista->fim = NULL;
    } else {
        lista->fim = paraExcluir->ant;
        lista->fim->prox = NULL;
    }
    free(paraExcluir);
}

void excluirInicio(lista_t *lista) {
    if (lista->inicio == NULL) {
        return;
    }
    elemento_t *paraExcluir = lista->inicio;
    if (lista->inicio == lista->fim) { 
        lista->inicio = NULL;
        lista->fim = NULL;
    } else {
        lista->inicio = paraExcluir->prox;
        lista->inicio->ant = NULL;
    }
    free(paraExcluir);
}

void imprimirListaInicioFim(lista_t *lista) {
    elemento_t *aux = lista->inicio;
    printf("Lista do início ao fim: ");
    while (aux != NULL) {
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}

void imprimirListaFimInicio(lista_t *lista) {
    elemento_t *aux = lista->fim;
    printf("Lista do fim ao início: ");
    while (aux != NULL) {
        printf("%d ", aux->valor);
        aux = aux->ant;
    }
    printf("\n");
}