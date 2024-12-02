#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PESSOAS 3
#define MAX_DISCIPLINAS 3

typedef struct {
    char nome[100];
    int cargaHoraria;
    char turno[20];
} Disciplina;

typedef struct {
    char nome[100];
    int qtdPeriodos;
    int qtdDisciplinas;
    char faculdade[100];
    float valorMensal;
    Disciplina disciplinas[MAX_DISCIPLINAS];
} Curso;

typedef struct {
    int numeroConta;
    int codigoBanco;
    float saldo;
} Conta;

typedef struct {
    char nome[100];
    int idade;
    float peso;
    float altura;
    char cpf[20];
    char *matricula;
    Conta conta;
    Curso *curso;
} Pessoa;

void inicializarPessoa(Pessoa *p) {
    strcpy(p->nome, "NULL");
    p->idade = 0;
    p->peso = 0.0;
    p->altura = 0.0;
    strcpy(p->cpf, "NULL");
    p->matricula = NULL;
    p->curso = NULL;
}

void criarPessoa(Pessoa *p) {
    printf("\n--- Criar Pessoa ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", p->nome);
    printf("Idade: ");
    scanf("%d", &p->idade);
    printf("Peso: ");
    scanf("%f", &p->peso);
    printf("Altura: ");
    scanf("%f", &p->altura);
    printf("CPF: ");
    scanf(" %[^\n]", p->cpf);
}

void criarCurso(Pessoa *p) {
    p->curso = (Curso *)malloc(sizeof(Curso));
    if (!p->curso) {
        printf("Erro ao alocar memória para o curso!\n");
        return;
    }

    printf("\n--- Criar Curso ---\n");
    printf("Nome do Curso: ");
    scanf(" %[^\n]", p->curso->nome);
    printf("Quantidade de Períodos: ");
    scanf("%d", &p->curso->qtdPeriodos);
    printf("Quantidade de Disciplinas: ");
    scanf("%d", &p->curso->qtdDisciplinas);
    printf("Nome da Faculdade: ");
    scanf(" %[^\n]", p->curso->faculdade);
    printf("Valor Mensal: ");
    scanf("%f", &p->curso->valorMensal);

    for (int i = 0; i < p->curso->qtdDisciplinas && i < MAX_DISCIPLINAS; i++) {
        printf("\n--- Disciplina %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", p->curso->disciplinas[i].nome);
        printf("Carga Horária: ");
        scanf("%d", &p->curso->disciplinas[i].cargaHoraria);
        printf("Turno: ");
        scanf(" %[^\n]", p->curso->disciplinas[i].turno);
    }

    if (p->curso->qtdDisciplinas > 0) {
        p->matricula = (char *)malloc(20 * sizeof(char));
        if (p->matricula) {
            sprintf(p->matricula, "MAT-%s", p->cpf);
        }
    }
}

void criarConta(Pessoa *p) {
    printf("\n--- Criar Conta Bancária ---\n");
    printf("Número da Conta: ");
    scanf("%d", &p->conta.numeroConta);
    printf("Código do Banco: ");
    scanf("%d", &p->conta.codigoBanco);
    printf("Saldo: ");
    scanf("%f", &p->conta.saldo);
}

void editarPessoa(Pessoa *p) {
    int opcao;
    printf("\n--- Editar Pessoa ---\n");
    printf("1. Editar Dados Pessoais\n");
    printf("2. Editar Curso\n");
    printf("3. Editar Conta\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            criarPessoa(p);
            break;
        case 2:
            if (p->curso) {
                criarCurso(p);
            } else {
                printf("Curso ainda não cadastrado.\n");
            }
            break;
        case 3:
            criarConta(p);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }
}

void imprimirPessoa(Pessoa *p) {
    printf("\n--- Dados da Pessoa ---\n");
    printf("Nome: %s\n", p->nome);
    printf("Idade: %d\n", p->idade);
    printf("Peso: %.2f\n", p->peso);
    printf("Altura: %.2f\n", p->altura);
    printf("CPF: %s\n", p->cpf);

    if (p->matricula) {
        printf("Matrícula: %s\n", p->matricula);
    } else {
        printf("Matrícula: Não disponível\n");
    }

    if (p->curso) {
        printf("\n--- Dados do Curso ---\n");
        printf("Nome do Curso: %s\n", p->curso->nome);
        printf("Quantidade de Períodos: %d\n", p->curso->qtdPeriodos);
        printf("Quantidade de Disciplinas: %d\n", p->curso->qtdDisciplinas);
        printf("Nome da Faculdade: %s\n", p->curso->faculdade);
        printf("Valor Mensal: %.2f\n", p->curso->valorMensal);

        for (int i = 0; i < p->curso->qtdDisciplinas; i++) {
            printf("\nDisciplina %d:\n", i + 1);
            printf("Nome: %s\n", p->curso->disciplinas[i].nome);
            printf("Carga Horária: %d\n", p->curso->disciplinas[i].cargaHoraria);
            printf("Turno: %s\n", p->curso->disciplinas[i].turno);
        }
    } else {
        printf("Curso: Não disponível\n");
    }

    printf("\n--- Dados da Conta ---\n");
    printf("Número da Conta: %d\n", p->conta.numeroConta);
    printf("Código do Banco: %d\n", p->conta.codigoBanco);
    printf("Saldo: %.2f\n", p->conta.saldo);
}

void liberarPessoa(Pessoa *p) {
    if (p->matricula) {
        free(p->matricula);
    }
    if (p->curso) {
        free(p->curso);
    }
}

int main() {
    Pessoa pessoas[MAX_PESSOAS];
    for (int i = 0; i < MAX_PESSOAS; i++) {
        inicializarPessoa(&pessoas[i]);
    }

    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Criar Pessoa\n");
        printf("2. Criar Curso\n");
        printf("3. Criar Conta\n");
        printf("4. Imprimir Dados\n");
        printf("5. Editar Dados\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 5) {
            printf("Escolha uma pessoa (1 a %d): ", MAX_PESSOAS);
            int pessoaEscolhida;
            scanf("%d", &pessoaEscolhida);
            pessoaEscolhida--;

            if (pessoaEscolhida < 0 || pessoaEscolhida >= MAX_PESSOAS) {
                printf("Pessoa inválida!\n");
                continue;
            }

            switch (opcao) {
                case 1:
                    criarPessoa(&pessoas[pessoaEscolhida]);
                    break;
                case 2:
                    criarCurso(&pessoas[pessoaEscolhida]);
                    break;
                case 3:
                    criarConta(&pessoas[pessoaEscolhida]);
                    break;
                case 4:
                    imprimirPessoa(&pessoas[pessoaEscolhida]);
                    break;
                case 5:
                    editarPessoa(&pessoas[pessoaEscolhida]);
                    break;
            }
        }
    } while (opcao != 6);

    for (int i = 0; i < MAX_PESSOAS; i++) {
        liberarPessoa(&pessoas[i]);
    }

    return 0;
}
