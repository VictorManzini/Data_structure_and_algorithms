#include <stdio.h>

int main(){
    char alunos[3][50];
    int i;
    printf("Registro de alunos: \n");

    for(i = 0; i < 3; i++){
        printf("Digite o nome do aluno %d: ", i+1);
        fgets(alunos[i], 50, stdin);

    }
    printf("\n");
    printf("%c", alunos[0][0]);

    return 0;
}