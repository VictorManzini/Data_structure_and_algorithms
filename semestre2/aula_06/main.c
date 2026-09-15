// Aula 06 Recursividade
#include <stdio.h>
#include <string.h>

void contagem(int n){
    if(n == 0){
        return;
    }

    printf("%d\n", n);

    contagem(n - 1); // Chamada recursiva, toda vez que uma funcao chama ela mesma, isso eh chamado recursividade
}

int main(){

    return 0;
}