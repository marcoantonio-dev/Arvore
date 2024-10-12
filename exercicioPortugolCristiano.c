#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;

No* CriarArvore(int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;
    return novo;
}

int Altura (No* No)
{
    if (No == NULL)
    {    return 0;
    }else 
        return (No -> altura);
}

No* AtualizarAltura(No* no) {
    if (no == NULL)
        return no;

    int alturaEsquerda = Altura(no->esquerda);
    int alturaDireita = Altura(no->direita);

    if (alturaEsquerda > alturaDireita) {
         no->altura = 1 + alturaEsquerda;
    } else {
         no->altura = 1 + alturaDireita;
    }
    return no;
}

No* RotacaoSimplesDireita(No* noY) {
    No* noX = noY->esquerda;
    No* temp = noX->direita;
    noX->direita = noY;
    noY->esquerda = temp->direita;
    temp->direita = noY;
    AtualizarAltura(noX);
    AtualizarAltura(noY);
    return noX;
}

No* Inserir(No* No, int valor)
{
    if(No == NULL)
    {
    return CriarArvore(valor);
    }else if( valor < No -> valor)
    {
        No->esquerda = Inserir(No->esquerda, valor);
    }else if(valor > No -> valor)
    {
        No->direita = Inserir(No->direita, valor);
    }else
        return No;
    AtualizarAltura(No);
    return Balancear(No);
}

No *Buscar(No* No, int valor)
{
    if (No == NULL || No->valor == valor)

        return No;

    if (valor < No->valor)
        return Buscar(No->esquerda, valor);
    else
        return Buscar(No->direita, valor);
}
int menu(void)
{
    int op;
    printf("--------Menu-----\n [1]Cria arvore \n [2] Inserir \n [3] buscar, [4]mostrar \n [5]remover \n [0]Sair \n Digite uma opcao");
    scanf("%d", &op);
    return op;
}
int main()
{   
    int op, valor;
    No *raiz = NULL;
    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            printf("Digite um valor para a raiz: ");
            scanf("%d", &valor);
            raiz = CriarArvore(valor);
            break;
        case 3:
            printf("Digite um valor para buscar: ");
            scanf("%d", &valor);
            Buscar(raiz, valor);
            No *receberRaiz = Buscar(raiz, valor);
            if(receberRaiz->valor == valor)
            {
                 printf("Valor %d encontrado na arvore!\n", *receberRaiz);
               
            }else{
                printf("Valor %d não encontrado na árvore!\n", *receberRaiz);
            }

        default:
            break;
        }
    } while (op != 0);
}
