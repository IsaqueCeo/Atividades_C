#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int nivel;
    float num;
    struct node *left;
    struct node *right;
} node_t;

typedef struct tree {
    node_t *root;
} tree_t;

void criarArvore(tree_t **tree);
void inserir(node_t **root, int num, int nivel);
int buscar(node_t *root, int num);
void imprimirPreOrdem(node_t *root);
void imprimirInOrdem(node_t *root);
void imprimirPosOrdem(node_t *root);
void esvaziar(node_t **root, int num);
int altura(node_t *root);

void criarArvore(tree_t **tree) {
    if (*tree == NULL) {
        *tree = (tree_t *)malloc(sizeof(tree_t));
        (*tree)->root = NULL;
        printf("Árvore criada com sucesso!\n");
    } else {
        printf("A árvore já foi criada.\n");
    }
}

void inserir(node_t **root, int num, int nivel) {
    if (*root == NULL) {
        *root = (node_t *)malloc(sizeof(node_t));
        (*root)->num = num;
        (*root)->nivel = nivel;
        (*root)->left = NULL;
        (*root)->right = NULL;
        printf("Nó inserido com valor: %d e nível: %d\n", num, nivel);
    } else if (num < (*root)->num) {
        inserir(&(*root)->left, num, nivel + 1);
    } else {
        inserir(&(*root)->right, num, nivel + 1);
    }
}

int buscar(node_t *root, int num) {
    if (root == NULL) return -1;
    if (root->num == num) return root->nivel;
    
    if (num < root->num) {
        return buscar(root->left, num);
    }
    return buscar(root->right, num);
}

void imprimirPreOrdem(node_t *root) {
    if (root != NULL) {
        printf("Valor: %.2f, Nível: %d\n", root->num, root->nivel);
        imprimirPreOrdem(root->left);
        imprimirPreOrdem(root->right);
    }
}

void imprimirInOrdem(node_t *root) {
    if (root != NULL) {
        imprimirInOrdem(root->left);
        printf("Valor: %.2f, Nível: %d\n", root->num, root->nivel);
        imprimirInOrdem(root->right);
    }
}

void imprimirPosOrdem(node_t *root) {
    if (root != NULL) {
        imprimirPosOrdem(root->left);
        imprimirPosOrdem(root->right);
        printf("Valor: %.2f, Nível: %d\n", root->num, root->nivel);
    }
}

void esvaziar(node_t **root, int num) {
    if (*root == NULL) return;

    if ((*root)->num == num) {
        node_t *temp = *root;
        if ((*root)->left == NULL && (*root)->right == NULL) {
            free(temp);
            *root = NULL;
        } else if ((*root)->left == NULL) {
            *root = (*root)->right;
            free(temp);
        } else if ((*root)->right == NULL) {
            *root = (*root)->left;
            free(temp);
        }
        return;
    }

    esvaziar(&(*root)->left, num);
    esvaziar(&(*root)->right, num);
}

int altura(node_t *root) {
    if (root == NULL) {
        return -1;
    }
    int alturaEsquerda = altura(root->left);
    int alturaDireita = altura(root->right);
    return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;
}

int main() {
    int op = 0, num = 0, nivel, op2;
    tree_t *tree = NULL;

    while (op != 8) {
        printf("====== MENU ======\n");
        printf("1. Criar uma árvore;\n");
        printf("2. Verificar se a árvore está vazia;\n");
        printf("3. Inserir um elemento na árvore;\n");
        printf("4. Buscar um elemento na árvore;\n");
        printf("5. Mostrar todos os elementos da árvore;\n");
        printf("6. Esvaziar a árvore ou alguma subárvore;\n");
        printf("7. Verificar a altura da árvore;\n");
        printf("8. Encerrar o programa;\n");
        printf("Opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                criarArvore(&tree);
                break;

            case 2:
                if (tree == NULL || tree->root == NULL) {
                    printf("A árvore está vazia ou ainda não foi criada.\n");
                } else {
                    printf("A árvore não está vazia.\n");
                }
                break;

            case 3:
                if (tree == NULL) {
                    printf("Árvore ainda não criada!\n");
                } else {
                    printf("Digite o valor do nó a ser inserido: ");
                    scanf("%d", &num);
                    inserir(&tree->root, num, 0);
                }
                break;

            case 4:
                if (tree == NULL || tree->root == NULL) {
                    printf("Árvore ainda não criada ou vazia!\n");
                } else {
                    printf("Digite o valor do nó a buscar: ");
                    scanf("%d", &num);
                    int nivelBusca = buscar(tree->root, num);
                    if (nivelBusca == -1) {
                        printf("Nó não encontrado.\n");
                    } else {
                        printf("Nível do nó %d: %d\n", num, nivelBusca);
                    }
                }
                break;

            case 5:
                if (tree == NULL || tree->root == NULL) {
                    printf("Árvore ainda não criada ou vazia!\n");
                } else {
                    printf("Escolha a forma de impressão:\n");
                    printf("1. Pré-ordem\n2. In-ordem\n3. Pós-ordem\n");
                    printf("Opção: ");
                    scanf("%d", &op2);
                    switch (op2) {
                        case 1:
                            imprimirPreOrdem(tree->root);
                            break;
                        case 2:
                            imprimirInOrdem(tree->root);
                            break;
                        case 3:
                            imprimirPosOrdem(tree->root);
                            break;
                        default:
                            printf("Opção inválida!\n");
                            break;
                    }
                }
                break;

            case 6:
                if (tree == NULL || tree->root == NULL) {
                    printf("Árvore ainda não criada ou vazia!\n");
                } else {
                    printf("Digite o valor do nó a ser apagado: ");
                    scanf("%d", &num);
                    esvaziar(&tree->root, num);
                    printf("Nó %d apagado (se existia).\n", num);
                }
                break;

            case 7:
                if (tree == NULL || tree->root == NULL) {
                    printf("Árvore ainda não criada ou vazia!\n");
                } else {
                    int alturaAtual = altura(tree->root);
                    printf("Altura da árvore: %d\n", alturaAtual);
                }
                break;

            case 8:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
