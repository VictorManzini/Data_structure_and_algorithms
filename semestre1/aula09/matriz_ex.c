#include <stdio.h>


int main(){
    int linha, coluna, i, j;
    
    printf("Digite a quantidade de linhas: ");
    scanf("%d", &linha);
    printf("\n");
    printf("Digite a quantidade de colunas: ");
    scanf("%d", &coluna);
    int matriz[linha][coluna];  
    printf("\n");
    for(i = 0; i < linha; i++){
        for(j = 0; j < coluna; j++){
            printf("Digite o elemento da linha %d coluna %d: ", i+1, j+1);
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("\n");
    printf("===Matriz concluida===\n");
    for(i = 0; i < linha; i++){
        for(j = 0; j < coluna; j++){
            printf("|%d|", matriz[i][j]);
        }
    }
    printf("\n");
    return 0;
}