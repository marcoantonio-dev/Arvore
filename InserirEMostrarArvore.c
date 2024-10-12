#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore AVL
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

// Função para criar um novo nó
No* CriarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->altura = 1;
    return novoNo;
}

// Função para obter a altura de um nó
int Altura(No* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Função para obter o fator de balanceamento de um nó
int FatorDeBalanceamento(No* no) {
    if (no == NULL)
        return 0;
    return Altura(no->esquerda) - Altura(no->direita);
}

// Função para atualizar a altura de um nó
void AtualizarAltura(No* no) {
    if (no != NULL) {
        no->altura = 1 + (Altura(no->esquerda) > Altura(no->direita) ? Altura(no->esquerda) : Altura(no->direita));
    }
}

// Rotação simples à direita
No* RotacaoSimplesDireita(No* noY) {
    No* noX = noY->esquerda;
    No* temp = noX->direita;

    noX->direita = noY;
    noY->esquerda = temp;

    AtualizarAltura(noY);
    AtualizarAltura(noX);

    return noX;
}

// Rotação simples à esquerda
No* RotacaoSimplesEsquerda(No* noX) {
    No* noY = noX->direita;
    No* temp = noY->esquerda;

    noY->esquerda = noX;
    noX->direita = temp;

    AtualizarAltura(noX);
    AtualizarAltura(noY);

    return noY;
}

// Rotação dupla à direita
No* RotacaoDuplaDireita(No* no) {
    no->esquerda = RotacaoSimplesEsquerda(no->esquerda);
    return RotacaoSimplesDireita(no);
}

// Rotação dupla à esquerda
No* RotacaoDuplaEsquerda(No* no) {
    no->direita = RotacaoSimplesDireita(no->direita);
    return RotacaoSimplesEsquerda(no);
}

// Função para balancear um nó
No* Balancear(No* no) {
    int balanceamento = FatorDeBalanceamento(no);

    if (balanceamento > 1) {
        if (FatorDeBalanceamento(no->esquerda) >= 0) {
            return RotacaoSimplesDireita(no);
        } else {
            return RotacaoDuplaDireita(no);
        }
    }

    if (balanceamento < -1) {
        if (FatorDeBalanceamento(no->direita) <= 0) {
            return RotacaoSimplesEsquerda(no);
        } else {
            return RotacaoDuplaEsquerda(no);
        }
    }

    return no;
}

// Função para inserir um novo nó na árvore AVL
No* Inserir(No* no, int valor) {
    if (no == NULL)
        return CriarNo(valor);

    if (valor < no->valor)
        no->esquerda = Inserir(no->esquerda, valor);
    else if (valor > no->valor)
        no->direita = Inserir(no->direita, valor);
    else
        return no;

    AtualizarAltura(no);
    return Balancear(no);
}

// Função para encontrar o nó com valor mínimo
No* ValorMinimo(No* no) {
    No* atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Função para apagar um nó da árvore AVL
No* Apagar(No* no, int valor) {
    if (no == NULL)
        return no;

    if (valor < no->valor)
        no->esquerda = Apagar(no->esquerda, valor);
    else if (valor > no->valor)
        no->direita = Apagar(no->direita, valor);
    else {
        if ((no->esquerda == NULL) || (no->direita == NULL)) {
            No* temp = no->esquerda ? no->esquerda : no->direita;

            if (temp == NULL) {
                temp = no;
                no = NULL;
            } else {
                *no = *temp;
            }
            free(temp);
        } else {
            No* temp = ValorMinimo(no->direita);
            no->valor = temp->valor;
            no->direita = Apagar(no->direita, temp->valor);
        }
    }

    if (no == NULL)
        return no;

    AtualizarAltura(no);
    return Balancear(no);
}

// Função para buscar um nó na árvore AVL
No* Buscar(No* no, int valor) {
    if (no == NULL || no->valor == valor)
        return no;

    if (valor < no->valor)
        return Buscar(no->esquerda, valor);
    else
        return Buscar(no->direita, valor);
}

// Função para realizar percurso pré-ordem
void PercursoPreOrdem(No* no) {
    if (no != NULL) {
        printf("%d ", no->valor);
        PercursoPreOrdem(no->esquerda);
        PercursoPreOrdem(no->direita);
    }
}

// Função para realizar percurso em-ordem
void PercursoEmOrdem(No* no) {
    if (no != NULL) {
        PercursoEmOrdem(no->esquerda);
        printf("%d ", no->valor);
        PercursoEmOrdem(no->direita);
    }
}

// Função para realizar percurso pós-ordem
void PercursoPosOrdem(No* no) {
    if (no != NULL) {
        PercursoPosOrdem(no->esquerda);
        PercursoPosOrdem(no->direita);
        printf("%d ", no->valor);
    }
}

// Função para exibir a árvore
void MostrarArvore(No* no, int espaco) {
    if (no == NULL)
        return;
    espaco += 5;
    MostrarArvore(no->direita, espaco);
    printf("\n");
    for (int i = 5; i < espaco; i++)
        printf(" ");
    printf("%d\n", no->valor);
    MostrarArvore(no->esquerda, espaco);
}

// Função para o menu de opções
int menu() {
    int op;
    printf("\n-------- Menu --------\n");
    printf("[1] Inserir na arvore\n");
    printf("[2] Buscar na arvore\n");
    printf("[3] Exibir arvore (Pre-Ordem)\n");
    printf("[4] Exibir arvore (Em-Ordem)\n");
    printf("[5] Exibir arvore (Pos-Ordem)\n");
    printf("[6] Mostrar estrutura da arvore\n");
    printf("[7] Apagar no da arvore\n");
    printf("[0] Sair\n");
    printf("Digite uma opcao: ");
    scanf("%d", &op);
    return op;
}

// Função principal
int main() {
    No* raiz = NULL;
    int op, valor;

    do {
        op = menu();
        switch (op) {
        case 1:
            printf("Digite um valor para inserir na árvore: ");
            scanf("%d", &valor);
            raiz = Inserir(raiz, valor);
            printf("Valor %d inserido na árvore!\n", valor);
            break;
        case 2:
            printf("Digite um valor para buscar na árvore: ");
            scanf("%d", &valor);
            No* encontrado = Buscar(raiz, valor);
            if (encontrado != NULL) {
                printf("Valor %d encontrado na árvore!\n", valor);
            } else {
                printf("Valor %d não encontrado na árvore!\n", valor);
            }
            break;
        case 3:
            printf("Árvore em Pré-Ordem: ");
            PercursoPreOrdem(raiz);
            printf("\n");
            break;
        case 4:
            printf("Árvore em Em-Ordem: ");
            PercursoEmOrdem(raiz);
            printf("\n");
            break;
        case 5:
            printf("Árvore em Pós-Ordem: ");
            PercursoPosOrdem(raiz);
            printf("\n");
            break;
        case 6:
            printf("Estrutura da árvore:\n");
            MostrarArvore(raiz, 0);
            break;
        case 7:
            printf("Digite um valor para apagar da árvore: ");
            scanf("%d", &valor);
            raiz = Apagar(raiz, valor);
            printf("Valor %d apagado da árvore!\n", valor);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (op != 0);

    return 0;
}