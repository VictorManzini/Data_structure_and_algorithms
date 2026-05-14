#include <stdio.h>

void mostrar_matriz(){
    int i,j;
    printf("===Matriz Exemplo===\n");
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            printf("|%d||%d|", i, j);
        }
        printf("\n");
    }
}

int main(){
    int matriz_num[3][3];
    int i,j;
    mostrar_matriz();
    for(i = 0; i <3 ; i++){
        for(j = 0; j < 3; j++){
            printf("Digite o elemento da posicao linha %d e coluna %d: ", i, j);
            scanf("%d", &matriz_num[i][j]);
        }
    }
    printf("\n");
    printf("===Matriz concluida===\n");
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            printf("|%d|", matriz_num[i][j]);
        }
        printf("\n");
    }

    return 0;
}