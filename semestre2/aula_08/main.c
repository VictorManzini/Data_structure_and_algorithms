#include <stdio.h>
#include <stdlib.h>

struct Node{
    int dado; // A informacao
    struct Node * proximo; // O link
};

void inserirInicio(struct Node**head, int valor){
    struct Node* novo = malloc(sizeof(struct Node));
    novo->dado = valor; 
    novo->proximo = *head;
    *head = novo;
}

void imprimirLista(struct Node* head){
    struct Node* atual = head; //Auxiliar 

    while(atual !=NULL){
        printf("%d->", atual->dado);
        printf("\n");
        atual = atual->proximo;
    }
    printf("NULL\n");
}

int main(){
    // Criando um no dinamicamente 
    struct Node* novoNo;
    struct Node * novoNo2;

    // Aloca espaco para 1 no 
    novoNo = (struct Node*) malloc(sizeof(struct Node));
    novoNo2 = (struct Node*) malloc(sizeof(struct Node));

    if(novoNo == NULL){
        printf("Erro: Memoria insuficiente!\n");
        exit(1);
    }

    printf("O valor inicial --> %d\n", novoNo->dado);
    // Atribuindo valores
    novoNo->dado = 10;
    novoNo->proximo = NULL;
    printf("O valor atual --> %d\n", novoNo->dado);
    imprimirLista(novoNo);
    inserirInicio(&novoNo2, 20);
    imprimirLista(novoNo2);

    return 0;
}