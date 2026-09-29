/*
* FIAP | DSA | Atividade de Fixação
* Recursividade e Lista Simplesmente Encadeada
*/
 
#include <stdio.h>
#include <stdlib.h>
 
/* ===================== PARTES 1 E 2: RECURSIVIDADE ===================== */
 
/* Parte 1: S(n) = 1 + 2 + ... + n */
int somatorio(int n) {
    /* CASO BASE: quando n <= 0 (ou n == 1) a recursão para */
    if (n <= 0) {
        return 0;
    }

    /* CHAMADA RECURSIVA: o problema diminui de n para n-1 */
    return n + somatorio(n - 1);
}
 
/* Parte 2: soma dos n primeiros elementos do vetor */
int somaVetor(int vetor[], int n) {
    /* CASO BASE: vetor sem elementos restantes */
    if (n == 0) {
        return 0;
    }

    /* CHAMADA RECURSIVA: último elemento + soma dos n-1 anteriores */
    return vetor[n - 1] + somaVetor(vetor, n - 1);
}
 
/* Parte 2: maior elemento entre os n primeiros do vetor */
int maiorVetor(int vetor[], int n) {
    /* CASO BASE: um único elemento é o maior */
    if (n == 1) {
        return vetor[0];
    }

    /* CHAMADA RECURSIVA: maior dos n-1 anteriores comparado ao último */
    int maiorResto = maiorVetor(vetor, n - 1);
    return (vetor[n - 1] > maiorResto) ? vetor[n - 1] : maiorResto;
}
 
/* ===================== PARTES 3 A 6: LISTA ENCADEADA ===================== */
 
typedef struct No No;
struct No {
    int valor;
    No *proximo;
};
 
/* Insere no início da lista e devolve o novo início. Complexidade: O(1) */
No *inserirInicio(No *inicio, int valor) {
    /* ALOCAÇÃO DO NÓ */
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return inicio; /* mantém a lista como estava */
    }

    novo->valor = valor;
    /* LIGAÇÃO COM O PRÓXIMO NÓ: o novo nó aponta para o antigo início */
    novo->proximo = inicio;
    /* o novo nó passa a ser o início */
    return novo;
}
 
/* Percorre e imprime a lista. Complexidade: O(n) */
void imprimirLista(No *inicio) {
    No *atual = inicio; /* ponteiro auxiliar: "inicio" não é alterado */
    
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->proximo; /* avança para o próximo nó */
    }
    printf("NULL\n");
}
 
/* BUSCA sequencial: retorna 1 se encontrar, 0 caso contrário.
* Melhor caso O(1) (primeiro nó); pior caso O(n) (último nó ou ausente) */
int buscar(No *inicio, int valor) {
    No *atual = inicio;
    while (atual != NULL) {
        if (atual->valor == valor) {
            return 1; /* encontrado */
        }
        atual = atual->proximo;
    }
    return 0;
}
 
/* Libera todos os nós (boa prática ao encerrar; não é remoção pedida) */
void liberarLista(No *inicio) {
    No *atual = inicio;
    while (atual != NULL) {
        No *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}
 
/* ===================== PROGRAMA PRINCIPAL ===================== */
 
int main(void) {
    No *inicio = NULL; /* lista vazia */
    int opcao, valor;
 
    do {
        printf("\n===== LISTA ENCADEADA =====\n");
        printf("1 - Inserir no inicio\n");
        printf("2 - Mostrar lista\n");
        printf("3 - Buscar valor\n");
        printf("4 - Mostrar primeiro elemento\n");
        printf("5 - Demonstrar recursividade (Partes 1 e 2)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) {
            break;
        }
 
        switch (opcao) {
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                inicio = inserirInicio(inicio, valor);
                break;
            case 2:
                imprimirLista(inicio);
                break;
            case 3:
                printf("Valor para buscar: ");
                scanf("%d", &valor);
                if (buscar(inicio, valor)) {
                    printf("Valor %d encontrado na lista.\n", valor);
                } else {
                    printf("Valor %d NAO encontrado.\n", valor);
                }
                break;
            case 4:
                if (inicio == NULL) {
                    printf("A lista esta vazia.\n");
                } else {
                    printf("Primeiro elemento: %d\n", inicio->valor);
                }
                break;
            case 5: {
                int n;
                int vetor[] = {10, 20, 30, 40, 50};
                int tam = sizeof(vetor) / sizeof(vetor[0]);
                printf("Digite n: ");
                scanf("%d", &n);
                printf("Somatorio(%d) = %d\n", n, somatorio(n));
                printf("Soma do vetor = %d\n", somaVetor(vetor, tam));
                printf("Maior do vetor = %d\n", maiorVetor(vetor, tam));
                break;
            }
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
 
    liberarLista(inicio);
    return 0;
}