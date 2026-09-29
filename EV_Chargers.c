#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAX_SESSOES 100
#define LIMITE_POTENCIA_TOTAL 1500.0 
// Definidas as cores para os prints
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define ORANGE "\033[38;5;208m"
#define RESET "\033[0m"

typedef struct{
    char placa[8];
    char modelo[50];
    float potencia_bateria;
    float porcentagem_bateria;
    float porcentagem_bateria_atual;
    float percentual_alvo;
}Veiculo;

typedef struct{
    int id;
    char nome[70];
    Veiculo carro; 
    float energia; 
    time_t hora_inicio;
    time_t hora_fim;
    float custo;
    float tarifa_kWh;
    float potencia_atual;
    float potencia_necessaria; // potencia minima para a sessao especifica nao estourar o cap do tipo 
    int tipo_carga; // 1 = recarga rapida | 2 = recarga lenta
    int status; // 0 = sessao vazia | 1 = ativa/em andamento | 2 = sessao concluida
}Sessao; 

struct tm formatarDataHora(time_t momento){
    struct tm resultado;
    resultado = *localtime(&momento);
    return resultado;
}

float determinarTarifa(struct tm dataInicio, int tipo_carga){
    int dia_sem = dataInicio.tm_wday;
    int tempo_atual = dataInicio.tm_hour * 60 + dataInicio.tm_min;

    float tarifa; 
    if((dia_sem > 0 && dia_sem < 6) && (tempo_atual >= 1050 && tempo_atual <=1230)){
        tarifa = 1.12;
    }
    else if((dia_sem > 0 && dia_sem < 6) && (tempo_atual >= 990 && tempo_atual <= 1290)){
        tarifa = 0.72;
    }
    else{
        tarifa = 0.51;
    }

    if(tipo_carga == 1) tarifa *= 1.3;
    return tarifa;
}

float calcularEnergiaAtual(Sessao sessao){
    if(sessao.status == 2){
        return sessao.energia;
    }
    float horas = difftime(time(NULL), sessao.hora_inicio) / 3600.0;
    float energia = horas * sessao.potencia_atual;
    float energia_maxima = (100.0 - sessao.carro.porcentagem_bateria) / 100.0 * sessao.carro.potencia_bateria;
    if(energia > energia_maxima){
        energia = energia_maxima;
    }
    return energia;
}

float calcularDuracaoAtual(Sessao sessao){
    if(sessao.status == 2){
        return difftime(sessao.hora_fim, sessao.hora_inicio);
    }
    return difftime(time(NULL), sessao.hora_inicio);
}

float calcularPercentualAtual(Sessao sessao){
    float energia = calcularEnergiaAtual(sessao);
    sessao.carro.porcentagem_bateria_atual = sessao.carro.porcentagem_bateria + (energia / sessao.carro.potencia_bateria) * 100.0;
    return sessao.carro.porcentagem_bateria_atual;
}

float tetoPorTipo(int tipo_carga){
    if(tipo_carga == 1){
        return 235.0;
    }
    else{
        return 118.0;
    }
}

void verificarSessoesConcluidas(Sessao sessoes[], int total);   // prototipo, para nao dar erro na hora de compilar e rodar, ja que ele esta abaixo de iniciarSessao e abaixo de finalizarSessao;

int iniciarSessao(Sessao sessoes[], int total){
    int confirma_placa;
    int confirma_modelo;
    int opcao_bateria;
    int confirma_potencia_bateria;
    int confirma_bateria; //Porcentagem da bateria
    int opcao_alvo; //Opcao do alvo da carga da bateria
    int confirma_alvo; //Confirmacao do alvo da carga da bateria

    verificarSessoesConcluidas(sessoes, total);

    if (total >= MAX_SESSOES){
        printf(RED"TODAS AS VAGAS FORAM PREENCHIDAS\n"RESET);
        printf("Por favor, volte mais tarde quando houver vagas disponiveis\n");
        return total;
    }
    // Criando o ID da sessao
    sessoes[total].id = total + 1;
    printf(RED"ID da sessao: "RESET "%d\n", sessoes[total].id);
    printf("\n");
    printf("Por favor, guarde o ID da sua sessao, ele sera necessario para finalizar a sessao e realizar o pagamento\n");
    printf("\n");
    usleep(500000);
    // Registrando o nome do cliente

    printf(BLUE"Digite o seu nome e sobrenome: "RESET);
    fgets(sessoes[total].nome, sizeof(sessoes[total].nome), stdin);
    sessoes[total].nome[strcspn(sessoes[total].nome, "\n")] = '\0'; //Usa o strcspn para tirar o "\n" que sobra do fgets, assim nao da erro no print
    printf(ORANGE"Nome digitado:"RESET" %s\n", sessoes[total].nome);
    printf("\n");

    // Registrando as infos do veiculo
    // Placa do veiculo
    do{
        printf(BLUE"Digite a placa do carro: "RESET);
        fgets(sessoes[total].carro.placa, sizeof(sessoes[total].carro.placa), stdin);
        sessoes[total].carro.placa[strcspn(sessoes[total].carro.placa, "\n")] = '\0';
        printf(ORANGE"Placa digitada:"RESET" %s\n", sessoes[total].carro.placa);
        printf(YELLOW"A placa do carro esta certa?"RESET" (Digite 1 para sim | 2 para nao)\n");
        printf("Resposta: ");
        scanf("%d", &confirma_placa);
        while(getchar() !='\n');
        printf("\n");
        if(confirma_placa < 1 || confirma_placa > 2){
            printf(YELLOW"Opcao invalida... tente novamente\n"RESET);
            printf("\n");
        }
        else if(confirma_placa == 2){
            printf(ORANGE"Sem problemas, vamos voltar essa etapa\n"RESET);
            printf("\n");
        }
    }while(confirma_placa != 1);

    // Modelo do veiculo
    do{
        printf(BLUE"Digite o modelo do veiculo: "RESET);
        fgets(sessoes[total].carro.modelo, sizeof(sessoes[total].carro.modelo), stdin);
        sessoes[total].carro.modelo[strcspn(sessoes[total].carro.modelo, "\n")] = '\0';
        printf(ORANGE"Modelo do carro:"RESET" %s\n", sessoes[total].carro.modelo);
        printf(YELLOW"O modelo do caro esta certo?"RESET" (Digite 1 para sim | 2 para nao)\n");
        printf("Resposta: ");  
        scanf("%d", &confirma_modelo);
        while(getchar() !='\n');
        printf("\n");
        if(confirma_modelo < 1 || confirma_modelo > 2){
            printf(YELLOW"Opcao invalida... tente novamente\n"RESET);
            printf("\n");
        }
        else if(confirma_modelo == 2){
            printf(ORANGE"Sem problemas, vamos voltar essa etapa\n"RESET);
            printf("\n");
        }
    }while(confirma_modelo != 1);

    // Porcentagem de carga atual da bateria
    do{
        printf(BLUE"Digite a porcentagem de carga da bateria: "RESET);
        scanf("%f", &sessoes[total].carro.porcentagem_bateria);
        while(getchar() != '\n');
        printf("\n");

        if(sessoes[total].carro.porcentagem_bateria < 1 || sessoes[total].carro.porcentagem_bateria > 100){
            printf(YELLOW"Porcentagem da bateria digitada invalida...\n"RESET);
            printf("A porcentagem da carga da bateria nao pode ser menor que 1 ou maior que 100\n");
            printf("\n");
            confirma_bateria = 2;
        }
        else{
            printf(ORANGE"Carga atual da bateria: "RESET"%.1f%%\n", sessoes[total].carro.porcentagem_bateria);
            printf(YELLOW"A porcentagem da bateria esta correta?"RESET" (Digite 1 para sim | 2 para nao)\n");
            printf("Resposta: ");
            scanf("%d", &confirma_bateria);
            while(getchar() != '\n');
            printf("\n");

            if(sessoes[total].carro.porcentagem_bateria >= 90 && confirma_bateria == 1){
                printf(YELLOW"O seu carro nao precisa de recarga no momento...\n"RESET);
                printf("Carga atual da bateria: %.1f%%\n", sessoes[total].carro.porcentagem_bateria);
                printf("\n");
                sleep(2);
                return total;
            }

            if(confirma_bateria < 1 || confirma_bateria > 2){
                printf(YELLOW"Opcao invalida... tente novamente\n"RESET);
                printf("\n");
            }
            else if(confirma_bateria == 2){
                printf(ORANGE"Sem problemas, vamos voltar essa etapa\n"RESET);
                printf("\n");
            }
        }
    }while(confirma_bateria != 1);

    // Percentual alvo da bateria
    do{
        printf(BLUE"Digite 1"RESET" para carregar totalmente a bateria (100%%)\n");
        printf(RED"Digite 2"RESET" para selecionar um percentual alvo da carga da bateria\n");
        printf("Resposta: ");
        scanf("%d", &opcao_alvo);
        printf("\n");
        switch(opcao_alvo){
            case 1: 
                printf(GREEN"Carga total da bateria selecionada\n"RESET);
                printf("\n");
                sessoes[total].carro.percentual_alvo = 100;
                confirma_alvo = 1;
                break;
            
            case 2:
                printf(BLUE"Digite o percentual alvo desejado: "RESET);
                scanf("%f", &sessoes[total].carro.percentual_alvo);
                printf("\n");
                if(sessoes[total].carro.percentual_alvo <= sessoes[total].carro.porcentagem_bateria){
                    printf(RED"O percentual alvo nao pode ser menor ou igual a porcentagem atual da bateria\n"RESET);
                    printf("\n");
                    confirma_alvo = 0;
                    break;
                }
                else if(sessoes[total].carro.percentual_alvo > 100 || sessoes[total].carro.percentual_alvo < 1){
                    printf(RED"O percentual alvo precisa ser um valor maior que 1 e menor que 100\n"RESET);
                    printf("\n");
                    confirma_alvo = 0;
                    break;
                }
                else{
                    printf(ORANGE"Percentual alvo desejado:"RESET" %.1f%%\n", sessoes[total].carro.percentual_alvo);
                    printf(YELLOW"O percentual alvo desejado esta correto?"RESET" (Digite 1 para sim | 2 para nao)\n");
                    printf("Resposta: ");
                    scanf("%d", &confirma_alvo);
                    printf("\n");
                    while(getchar() != '\n');
                    if(confirma_alvo < 1 || confirma_alvo > 2){
                        printf(YELLOW"Opcao invalida... tente novamente\n"RESET);
                        printf("\n");
                        break;
                    }
                    else if(confirma_alvo == 2){
                        printf(ORANGE"Sem problemas, vamos voltar essa etapa\n"RESET);
                        printf("\n");
                        break;
                    }
                break;
                }
            default:
                printf(YELLOW"Opcao invalida... tente novamente\n"RESET);
                printf("\n");
                confirma_alvo = 0;

        printf("\n");
        }
    }while(confirma_alvo != 1);

    // Potencia da bateria
    do{
        printf(BLUE"Deseja inserir a potencia da bateria ou deixar o sistema escolher automaticamente?"RESET" (padrao 38.8kWh)\n");
        printf("(Digite 1 para manual | 2 para automatico)\n");
        printf("Resposta: ");
        scanf("%d", &opcao_bateria);
        printf("\n");
        if(opcao_bateria != 1 && opcao_bateria != 2){
            printf(YELLOW"Opcao invalida... tente novamente\n"RESET);
            
        }
        else if(opcao_bateria == 2){
            sessoes[total].carro.potencia_bateria = 38.8; // 38.8 kWh
            printf(ORANGE"Potencia da bateria selecionada automaticamente em 38.8kWh\n"RESET);
            printf("\n");

        }
        else{
            do{
                printf(BLUE"Digite a potencia da bateria em kW: "RESET);
                scanf("%f", &sessoes[total].carro.potencia_bateria);
                printf("\n");
                printf(ORANGE"Potencia da bateria:"RESET" %.1fkWh\n", sessoes[total].carro.potencia_bateria);
                printf(YELLOW"A potencia da bateria esta correta?"RESET" (Digite 1 para sim | 2 para nao)\n");
                printf("Resposta: ");
                scanf("%d", &confirma_potencia_bateria);
                printf("\n");

                if(sessoes[total].carro.potencia_bateria > 246.8 && confirma_potencia_bateria == 1){
                    printf(RED"\nATENCAO!\n"RESET);
                    printf("\nO EV com a maior capacidade de bateria eh o GMC Hummer EV Pickup com 246.8kWh\n");
                    printf("Nenhum carro a venda nos dias atuais conta com uma bateria mais potente\n");
                    printf("Por favor, insira um valor real ou um valor aproximado da potencia da bateria do seu veiculo\n");
                    printf("\n");
                    confirma_potencia_bateria = 0;
                }
                else if(sessoes[total].carro.potencia_bateria < 15.9 && confirma_potencia_bateria == 1){
                    printf(RED"\nATENCAO!\n"RESET);
                    printf("\nO EV com a menor capacidade de bateria eh o JMEV Emova Easy com 15.9kWh\n");
                    printf("Nenhum carro a venda nos dias atuais conta com uma bateria mais fraca\n");
                    printf("Por favor, insira um valor real ou um valor aproximado da potencia da bateria do seu veiculo\n");
                    printf("\n");
                    confirma_potencia_bateria = 0;
                }
                else if(confirma_potencia_bateria < 1 || confirma_potencia_bateria > 2){
                    printf(YELLOW"Opcao invalida... tente novamente\n"RESET);
                    printf("\n");
                }
                else if(confirma_potencia_bateria == 2){
                    printf(ORANGE"Sem problemas, vamos voltar essa etapa\n"RESET);
                    printf("\n");
                }
            }while(confirma_potencia_bateria != 1);
            confirma_potencia_bateria = 1;

        }
    }while(opcao_bateria !=1 && opcao_bateria !=2);
 
    // Pega qual o tipo de recarga que o usuário deseja
    do{
        printf(BLUE"Qual o tipo de carga que deseja:\n"); 
        printf(BLUE"1 Carga Rapida\n"RESET); 
        printf(RED"2 Carga Lenta\n"RESET);
        printf("Resposta: ");
        scanf("%d", &sessoes[total].tipo_carga);
        printf("\n");
        if(sessoes[total].tipo_carga != 1 && sessoes[total].tipo_carga != 2){
            printf(YELLOW"Tipo de carga selecionada incorreta... tente novamente\n"RESET);
        }
        else if(sessoes[total].tipo_carga == 2){
            printf(GREEN"Carga Lenta selecionada\n"RESET);
        }
        else{
            printf(GREEN"Carga Rapida selecionada\n"RESET);
        }
        printf("\n");
    }while(sessoes[total].tipo_carga != 1 && sessoes[total].tipo_carga != 2);

    // Pega o horario de inicio da sessao
    sessoes[total].hora_inicio = time(NULL);
    struct tm dataInicio = formatarDataHora(sessoes[total].hora_inicio);

    sessoes[total].tarifa_kWh = determinarTarifa(dataInicio, sessoes[total].tipo_carga);
    sessoes[total].hora_fim = 0;
    sessoes[total].energia = 0;
    sessoes[total].custo = 0;
    sessoes[total].status = 1;
    printf(ORANGE"Nome do(a) usuario(a) da sessao ID: "RESET"%d: %s\n", sessoes[total].id, sessoes[total].nome);
    char buffer_inicio[20];
    strftime(buffer_inicio, sizeof(buffer_inicio), "%d/%m/%Y %H:%M:%S", &dataInicio);
    printf(ORANGE"Horario inicio: "RESET"%s\n", buffer_inicio);
    printf(ORANGE"Modelo do veiculo: "RESET"%s\n", sessoes[total].carro.modelo);
    printf(ORANGE"Placa do veiculo: "RESET"%s\n", sessoes[total].carro.placa);
    printf(ORANGE"Potencia selecionada: "RESET"%.1f"ORANGE"kWh\n"RESET, sessoes[total].carro.potencia_bateria);
    printf(ORANGE"Carga atual da bateria: "RESET"%.1f%%\n", sessoes[total].carro.porcentagem_bateria);
    printf(ORANGE"Percentual alvo de carga: "RESET"%.1f%%\n", sessoes[total].carro.percentual_alvo);
    if(sessoes[total].tipo_carga == 1){printf(ORANGE"Tipo da carga: "RESET"Rapida\n");}
    else{printf(ORANGE"Tipo da carga: "RESET"Lenta\n");}
    float energia_necessaria = (sessoes[total].carro.percentual_alvo - sessoes[total].carro.porcentagem_bateria) / 100.0 * sessoes[total].carro.potencia_bateria;
    float tempo_max_horas; 
    if(sessoes[total].tipo_carga == 1){
        tempo_max_horas = 10.0/60.0;
    }
    else{
        tempo_max_horas = 20.0 / 60.0;
    }
    float teto_base = tetoPorTipo(sessoes[total].tipo_carga);
    float potencia_minima = energia_necessaria / tempo_max_horas;
    if(potencia_minima > teto_base){
        sessoes[total].potencia_necessaria = potencia_minima;
    }
    else{
        sessoes[total].potencia_necessaria = teto_base;
    }
    float horas_previstas = energia_necessaria / sessoes[total].potencia_necessaria;
    int horas_previsao = (int)horas_previstas;
    int minutos_previsao = (int)((horas_previstas - horas_previsao) * 60);
    printf(ORANGE"Previsao de tempo de carregamento: (garantido, respeitando o limite do tipo de carga): "RESET"%dh %dm\n", horas_previsao, minutos_previsao);
    printf("\n");
    return total + 1;
}

int finalizarSessao(Sessao sessoes[], int total, int id){
    for(int i = 0; i < total; i++){
        if(sessoes[i].id == id){
            sessoes[i].hora_fim = time(NULL);
            sessoes[i].status = 2;

            float horas_totais = difftime(sessoes[i].hora_fim, sessoes[i].hora_inicio) / 3600.0;
            sessoes[i].energia = horas_totais * sessoes[i].potencia_atual;
            float energia_maxima = (100.0 - sessoes[i].carro.porcentagem_bateria) / 100.0 * sessoes[i].carro.potencia_bateria;
            if(sessoes[i].energia > energia_maxima){
                sessoes[i].energia = energia_maxima;
            }
            sessoes[i].custo = sessoes[i].energia * sessoes[i].tarifa_kWh;

            float percentual_final = calcularPercentualAtual(sessoes[i]);

            struct tm tm_inicio = formatarDataHora(sessoes[i].hora_inicio);
            struct tm tm_fim = formatarDataHora(sessoes[i].hora_fim);
            char buffer_inicio[20];
            char buffer_fim[20];
            strftime(buffer_inicio, sizeof(buffer_inicio), "%d/%m/%Y %H:%M:%S", &tm_inicio);
            strftime(buffer_fim, sizeof(buffer_fim), "%d/%m/%Y %H:%M:%S", &tm_fim);

            printf("\n");
            printf(GREEN"Sessao ID %d finalizada\n"RESET, sessoes[i].id);
            printf("Inicio: %s\n", buffer_inicio);
            printf("Porcentagem inicial da bateria: %.1f\n", sessoes[i].carro.porcentagem_bateria);
            printf("Fim: %s\n", buffer_fim);
            printf("Porcentagem final da bateria: %.1f\n", percentual_final);
            printf("Energia consumida: %.1fkWh\n", sessoes[i].energia);
            printf("Custo total: R$%.1f\n", sessoes[i].custo);
            printf("\n");
            return total;
        }
    }
    printf(RED"ID da sessao nao encontrado\n"RESET);
    printf("\n");
    return total;
}

void redistribuirPotencia(Sessao sessoes[], int total){
    int processando[MAX_SESSOES] = {0};
    float potencia_alocada = 0;
    int sessoes_ativas = 0;

    for(int i = 0; i < total; i++){
        if(sessoes[i].status == 1) sessoes_ativas++;
    }

    if(sessoes_ativas == 0){
        printf(YELLOW"Nenhuma sessao ativa no momento...\n"RESET);
        return;
    }

    for(int contador = 0; contador < sessoes_ativas; contador ++){
        int menor_id = -1;
        int indice_menor = -1;

        for(int i = 0; i < total; i++){
            if(sessoes[i].status == 1 && !processando[i]){
                if(menor_id == -1 || sessoes[i].id < menor_id){
                    menor_id = sessoes[i].id;
                    indice_menor = i;
                }
            }
        }

        float teto = sessoes[indice_menor].potencia_necessaria;

        if(potencia_alocada + teto <= LIMITE_POTENCIA_TOTAL){
            sessoes[indice_menor].potencia_atual = teto;
            potencia_alocada += teto;
            processando[indice_menor] = 1;
        }
        else{
            float restante = LIMITE_POTENCIA_TOTAL - potencia_alocada;
            if(restante > 0){
                sessoes[indice_menor].potencia_atual = restante;
                potencia_alocada += restante;
            }
            else{
                sessoes[indice_menor].potencia_atual = 0;
            }
            
            processando[indice_menor] = 1;
        }
    }
}

void verificarSessoesConcluidas(Sessao sessoes[], int total){
    for(int i = 0; i < total; i++){
        if(sessoes[i].status == 1){
            float percentual_atual = calcularPercentualAtual(sessoes[i]);
            if(percentual_atual >= sessoes[i].carro.percentual_alvo){
                finalizarSessao(sessoes, total, sessoes[i].id);
                redistribuirPotencia(sessoes, total);
            }  
        }
    }
}

void listarSessoes(Sessao sessoes[], int total){
    verificarSessoesConcluidas(sessoes, total);
    if(total == 0){
        printf(YELLOW"Nenhuma sessao ativa no momento\n"RESET);
        return;
    }
    printf(BLUE"Quantidade de sessoes ativas: %d\n"RESET, total);
    
    for(int i = 0; i < total; i++){
        if(sessoes[i].status == 1){
            printf("ID: %d | Status: Ativa\n", sessoes[i].id);
        }
        else if(sessoes[i].status == 2){
            printf("ID: %d | Status: Finalizada\n", sessoes[i].id);
        }
        printf("Nome do usuario da sessao ID %d: %s\n", sessoes[i].id, sessoes[i].nome);
        printf("Placa do carro da sessao ID %d: %s\n", sessoes[i].id, sessoes[i].carro.placa);

        float energia_atual = calcularEnergiaAtual(sessoes[i]);
        float custo_atual = energia_atual * sessoes[i].tarifa_kWh;
        printf(ORANGE"Energia consumida ate o momento: %.2fkW | Custo ate o momento: R$%.2f\n"RESET, energia_atual, custo_atual);
        
    }
    printf("\n");
    sleep(1);
}

int buscarSessaoPorId(Sessao sessoes[], int total, int id){
    verificarSessoesConcluidas(sessoes, total);
    printf("Por favor digite o ID da sessao que deseja buscar: ");
    scanf("%d", &id);
    printf("\n");
    for(int i = 0; i < total; i++){
        if(sessoes[i].id == id){
            float energia_atual = calcularEnergiaAtual(sessoes[i]);
            float custo_atual = energia_atual * sessoes[i].tarifa_kWh;
            float percentual = calcularPercentualAtual(sessoes[i]);

            printf(GREEN"ID encontrado!\n"RESET);
            usleep(200000); 
            printf("ID: %d\n", sessoes[i].id);
            usleep(200000);
            printf("Nome do usuario: %s\n", sessoes[i].nome);
            usleep(200000);
            printf("Marca e modelo do veiculo: %s\n", sessoes[i].carro.modelo);
            usleep(200000);
            printf("Percentual atual da bateria: %.1f%%\n", percentual);
            usleep(200000);
            printf("Placa do veiculo: %s\n", sessoes[i].carro.placa);
            usleep(200000);
            printf("Potencia da bateria: %.2f\n", sessoes[i].carro.potencia_bateria);
            usleep(200000);
            printf("Energia consumida ate o momento: %.2fkW\n", energia_atual);
            usleep(200000);
            printf("Custo atual: %.2f\n", custo_atual);
            usleep(200000);
            printf("\n");
            usleep(500000);
            return i;
        }
    }
    printf(RED"ID de sessao nao encontrado\n"RESET);
    printf("\n");
    return -1;
}

void ordenarSessoes(Sessao sessoes[], int total){
    verificarSessoesConcluidas(sessoes, total);
    int opcao_ordenar = 0;
    printf("Selecione como deseja ordenar as sessoes: \n");
    printf("1 - ID\n");
    printf("2 - Energia Consumida\n");
    printf("3 - Custo\n");
    printf("4 - Duracao\n");
    printf("Digite a sua escolha: ");
    scanf("%d", &opcao_ordenar);
    printf("\n");

    switch(opcao_ordenar){

        case 1: 
        printf(GREEN"Ordenacao por ID selecionada\n"RESET);
        for(int i = 0; i < total -1; i++){
            for(int j = 0; j < total -1; j++){
                if(sessoes[j].id > sessoes[j+1].id){
                    Sessao temp = sessoes[j];
                    sessoes[j] = sessoes[j+1];
                    sessoes[j+1] = temp;
                }
            }
        }
        printf(GREEN"SESSOES ORDENADAS POR ID: \n"RESET);
        for(int i = 0; i < total; i++){
            if(sessoes[i].status == 1){
                float percentual = calcularPercentualAtual(sessoes[i]);
                printf("ID: %d\n", sessoes[i].id);
                printf("Porcentagem da bateria: %.1f%%\n", percentual);
                usleep(100000);
            }
        }
        break;

        case 2: 
        printf(GREEN"Ordenacao por energia consumida selecionada\n"RESET);
        for(int i = 0; i < total -1; i++){
            for(int j = 0; j < total -1; j++){
                float energia_j = calcularEnergiaAtual(sessoes[j]); 
                float energia_j1 = calcularEnergiaAtual(sessoes[j+1]);
                if(energia_j > energia_j1){
                    Sessao temp = sessoes[j]; 
                    sessoes[j] = sessoes[j+1]; 
                    sessoes[j+1] = temp; 
                }
            }
        }
        for(int i = 0; i < total; i++){
            float energia = calcularEnergiaAtual(sessoes[i]);
            float percentual = calcularPercentualAtual(sessoes[i]);
            printf(GREEN"ID da sessao: %d\n"RESET, sessoes[i].id);
            printf(GREEN"Energia consumida: %.2fkW\n"RESET, energia);
            printf(GREEN"Porcentagem da bateria: "RESET"%.1f%%\n", percentual);
            printf("\n");
            usleep(100000);
        }
        break;

        case 3: 
        printf(GREEN"Ordenacao por custo selecionada\n"RESET);
        for(int i = 0; i < total -1; i++){
            for(int j = 0; j < total -1; j++){
                float custo_j = calcularEnergiaAtual(sessoes[j]) * sessoes[j].tarifa_kWh;
                float custo_j1 = calcularEnergiaAtual(sessoes[j+1]) * sessoes[j+1].tarifa_kWh;
                if(custo_j > custo_j1){
                    Sessao temp = sessoes[j]; 
                    sessoes[j] = sessoes[j+1]; 
                    sessoes[j+1] = temp; 
                }

            }
        }
        for(int i = 0; i < total; i++){
            float custo = calcularEnergiaAtual(sessoes[i]) * sessoes[i].tarifa_kWh;
            float percentual = calcularPercentualAtual(sessoes[i]);
            printf(GREEN"ID da sessao: %d\n"RESET, sessoes[i].id);
            printf(GREEN"Custo da sessao: R$%.2f\n"RESET, custo);
            printf(GREEN"Percentual da bateria: "RESET"%.1f%%\n", percentual);
            printf("\n");
            usleep(100000);
        }
        break;

        case 4:
        printf(GREEN"Ordenacao por duracao selecionada\n"RESET);

        for(int i = 0; i < total -1; i++){
            for(int j = 0; j < total -1; j++){
                float duracao_j = calcularDuracaoAtual(sessoes[j]);
                float duracao_j1 = calcularDuracaoAtual(sessoes[j+1]);

                if(duracao_j > duracao_j1){
                    Sessao temp = sessoes[j];
                    sessoes[j] = sessoes[j+1];
                    sessoes[j+1] = temp;
                }
            }
        }
        for(int i = 0; i < total; i++){
            float duracao = calcularDuracaoAtual(sessoes[i]);
            int horas = duracao / 3600;
            int minutos = (int)duracao % 3600 / 60;
            printf(GREEN"ID da sessao: %d\n"RESET, sessoes[i].id);
            printf(GREEN"Duracao da sessao: %dh %dm\n"RESET, horas, minutos);
            usleep(100000);
        }
        break;
    }
    sleep(1);
}

void mostrarEstatisticas(Sessao sessoes[], int total){
    verificarSessoesConcluidas(sessoes, total);
    if(total == 0){
        printf(YELLOW"Nenhuma sessao cadastrada ainda\n"RESET);
        return;
    }
    float energia_utilizada = 0; 
    float custo_total = 0;
    int total_sessoes = 0; 
    float maior_consumo = calcularEnergiaAtual(sessoes[0]); 
    float menor_consumo = calcularEnergiaAtual(sessoes[0]);
    for(int i = 0; i < total; i++){
        total_sessoes +=1;
        float energia_i = calcularEnergiaAtual(sessoes[i]);
        float custo_i = energia_i * sessoes[i].tarifa_kWh;
        energia_utilizada += energia_i;
        custo_total += custo_i;

        if(energia_i > maior_consumo){
            maior_consumo = energia_i;
        }
        if(energia_i < menor_consumo){
            menor_consumo = energia_i;
        }
    }
    float media_custo = custo_total / total_sessoes;
    printf("Total de sessoes: %d\n", total_sessoes); 
    printf("Energia total utilizada: %.2fkWh\n", energia_utilizada); 
    printf("Custo total: R$%.2f\n", custo_total);
    printf("Custo medio das recargas: R$%.2f\n", media_custo); 
    printf("Maior consumo de energia: %.2fkW\n", maior_consumo); 
    printf("Menor consumo de energia: %.2fkW\n", menor_consumo);
    printf("\n");
    usleep(500000);
}

int main(){ 
    Sessao sessoes[MAX_SESSOES];
    int opcao;
    int total_sessoes = 0;
    int id = 0;
    system("clear");
    printf(ORANGE"Bem-vindo ao ChargeGrid Inteligence\n"RESET);
    do{
        verificarSessoesConcluidas(sessoes, total_sessoes);
        printf("====MENU====\n");
        printf("Por favor selecione uma das opcoes abaixo: \n");
        printf("1 - Iniciar nova sessao\n");
        printf("2 - Listar sessoes\n"); 
        printf("3 - Buscar por sessao por ID\n");
        printf("4 - Ordenar sessoes\n");
        printf("5 - Mostrar estatisticas\n");
        printf("6 - Finalizar sessao\n");
        printf("7 - Encerrar o programa\n");
        printf("Resposta: ");
        scanf("%d", &opcao);
        while(getchar() !='\n'); 
        printf("\n"); 
        switch(opcao){
            case 1: 
            system("clear");
            printf(BLUE"Opcao 1, iniciar sessao, selecionada\n"RESET);
            total_sessoes = iniciarSessao(sessoes, total_sessoes);
            redistribuirPotencia(sessoes, total_sessoes);
            break;

            case 2: 
            system("clear");
            printf("Opcao 2, listar sessoes, selecionada\n");
            listarSessoes(sessoes, total_sessoes);
            break;

            case 3: 
            system("clear");
            printf("Opcao 3, buscar sessao por ID, selecionada\n");
            buscarSessaoPorId(sessoes, total_sessoes, 0);
            break;

            case 4: 
            system("clear");
            printf("Opcao 4, ordenar sessoes, selecionada\n");
            ordenarSessoes(sessoes, total_sessoes);
            break;

            case 5: 
            system("clear");
            printf("Opcao 5, mostrar estatisticas, selecionada\n");
            mostrarEstatisticas(sessoes, total_sessoes);
            break;

            case 6:{
                system("clear");
                printf("Opcao 6, finalizar sessao, selecionada\n");
                printf("Por favor digite o ID da sessao que deseja finalizar: ");
                scanf("%d", &id);
                while(getchar() != '\n');
                finalizarSessao(sessoes, total_sessoes, id);
                redistribuirPotencia(sessoes, total_sessoes);
                break;
            }

            case 7:
            system("clear");
            printf("Opcao 7, encerrar programa, selecionada\n");
            printf(GREEN"Obrigado por usar EV_Chargers\n");
            printf("Ate a proxima\n"RESET);
            printf("\n");
            return 0;

            default: 
            printf(RED"Opcao selecionada invalida... tente novamente\n"RESET);
            printf("\n");
            sleep(2);
            break;
        }

    }while (opcao != 7);
    return 0;
}