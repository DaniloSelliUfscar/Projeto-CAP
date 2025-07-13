/******************************************************************************
Descrição: 
Jogo de Blackjack simplificado para terminal, onde dois jogadores se alternam comprando cartas de um baralho salvo em arquivo binário. 
Cada carta comprada atualiza o estado do jogador, incluindo valor e naipe das cartas em sua mão.

Requer: 
- Dois jogadores.
- Entradas a partir do teclado.
 
Assegura:
- Baralho embaralhado salvo no arquivo "baralho.dat".
- O jogo encerra quando um dos jogadores ultrapassa 21 pontos.
- Apresentação da situação do jogo e do resultado final.


Danilo Djovano Selli Junior Nº UFSCar 842868
Enzo Furquim Bonetto Nº UFSCar 842869
Ryan Sohaky Duda Kondo Nº UFSCar 834056
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  

#define MAX_CARTAS 52
#define MAX_JOGADORES 2

// Estrutura que representa uma carta
struct carta {
    char naipe;
    int valor;
};

// Estrutura que representa um jogador
struct jogador {
    char nome[50];
    int soma_mao;
    int valor_mao[20];
    char naipe_mao[20];
    int qtd_carta;
    int recusou;
};

// Procedimento para criar um baralho embaralhado e salva no arquivo binário "baralho.dat"
void criar_baralho() {
    // Abre o arquivo escrita zerando ele 
    FILE *arquivo = fopen("baralho.dat", "wb");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo do baralho.\n");
    }
    
    // Criação do baralho formado por 52 cartas
    struct carta baralho[MAX_CARTAS];
    
    char naipes[] = {'C', 'O', 'P', 'E'};  // Naipes: Copas, Ouros, Paus, Espadas
    int indice_carta = 0; // indice para as cartas (1ª, 2ª, ... 52ª)
    
    // Preechendo o baralho com cartas de naipes e valores
    for (int n = 0; n < 4; n++) {
        for (int v = 1; v <= 13; v++) {
            baralho[indice_carta].naipe = naipes[n];
            baralho[indice_carta].valor = (v > 10) ? 10 : v; // dama, rei, valete = 10
            indice_carta++;
        }
    }
    
    //Embaralhar as cartas (rand)
    srand(time(NULL));
    for (int i = 0; i < MAX_CARTAS; i++) {
        int r = rand() % MAX_CARTAS;
        struct carta temp = baralho[i]; // struct Carta auxiliar
        baralho[i] = baralho[r];
        baralho[r] = temp;
        
    }
    //Escreve o baralho no arquivo
    fwrite(baralho, sizeof(struct carta), MAX_CARTAS, arquivo); 
    fclose(arquivo);
}


// Procedimento para comprar carta, lê uma carta específica do arquivo binário e adiciona na mão do jogador
void comprar_carta(struct jogador *jogador, int *indice){
    // Abre o arquivo para leitura
    FILE *arquivo = fopen("baralho.dat", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo do baralho para leitura.\n");
    }
    
    // Setando a posição do baralho e lê a carta atual do arquivo
    fseek(arquivo, sizeof(struct carta) * (*indice), SEEK_SET);
    struct carta carta_comprada;
    fread(&carta_comprada, sizeof(carta_comprada), 1, arquivo);

    
    // Jogador recebe a carta (soma o total da mão e a quantidade de cartas, preenche o vetor da mao com a carta, valor e naipe)
    jogador->valor_mao[jogador->qtd_carta] = carta_comprada.valor;
    jogador->naipe_mao[jogador->qtd_carta] = carta_comprada.naipe;
    jogador->qtd_carta++;
    jogador->soma_mao += carta_comprada.valor;
    jogador->recusou = 0;
    
    // Incrementa o indice para a próxima leitura ("retira a carta do baralho")
    (*indice)++;
    
    fclose(arquivo);
}

//Procedimento para imprimir a mão do jogador, com os valores e naipes de suas cartas
void imprimir_mao(struct jogador jogador){
    printf("\nMão de %s", jogador.nome);
    for(int i = 0; i < jogador.qtd_carta; i++)
        printf("    %d de %c\n", jogador.valor_mao[i], jogador.naipe_mao[i]);
}


int main(void) {
    // Inicia o jogo e cria o baralho já embaralhado
    criar_baralho();
    
    // Variável para auxiliar a posição de leitura do arquivo (Qual carta deve ser tirada do baralho)
    int indice_carta = 0;
    
    
    
    //Inicializa os jogadores
    struct jogador jogador1;
    jogador1.qtd_carta = 0;
    jogador1.soma_mao = 0;
    
    struct jogador jogador2;
    jogador2.qtd_carta = 0;
    jogador2.soma_mao = 0;
    
    //perguntar o nome dos jogadores
    printf("Digite o nome do jogador 1: ");
    fgets(jogador1.nome, sizeof jogador1.nome, stdin);
    printf("Digite o nome do jogador 2: ");
    fgets(jogador2.nome, sizeof jogador2.nome, stdin);
    
    // Jogadores recebem as duas primeiras cartas
    for (int i = 0; i < 2; i++) {
        comprar_carta(&jogador1, &indice_carta);
    }
    
    for (int i = 0; i < 2; i++) {
        comprar_carta(&jogador2, &indice_carta);
    }
    
    int rodadas = 1;
    int desistencia_dupla = 0; //Contar se jogadores nao quiserem mais comprar cartas
    
    // Inicia as rodadas e continua enquanto nenhum dos jogadores tem soma igual a 21 ou mais
    while((jogador1.soma_mao < 21 && jogador2.soma_mao < 21) && desistencia_dupla < 2){
        // imprime a mão dos jogadores
        imprimir_mao(jogador1);    
        imprimir_mao(jogador2);
        
        // Variáveis para leitura da opção
        char entrada[10];
        char opcao;
        int alguem_comprou = 0;
        
        //Verifica a paridade das rodadas para decidir de quem é a vez
        if(rodadas % 2 != 0){
            printf("\nTotal da mão de %s %d\n", jogador1.nome, jogador1.soma_mao);
            printf("Deseja comprar uma carta? (s/n): ");
            fgets(entrada, sizeof entrada, stdin);
            sscanf(entrada, "%c", &opcao);
            
            if(opcao == 's'){
                comprar_carta(&jogador1, &indice_carta);
                printf("A carta comprada foi %d de %c\n", jogador1.valor_mao[jogador1.qtd_carta - 1], jogador1.naipe_mao[jogador1.qtd_carta - 1]);
                alguem_comprou = 1;
                
            }else{
                jogador1.recusou++;
            }
        }
        else{
            printf("\nTotal da mão de %s %d\n", jogador2.nome, jogador2.soma_mao);
            printf("Deseja comprar uma carta? (s/n): "); 
            fgets(entrada, sizeof entrada, stdin);
            sscanf(entrada, "%c", &opcao);
            
            if(opcao == 's'){
                comprar_carta(&jogador2, &indice_carta);
                printf("A carta comprada foi %d de %c\n", jogador2.valor_mao[jogador2.qtd_carta - 1], jogador2.naipe_mao[jogador2.qtd_carta - 1]);
                alguem_comprou = 1;
            }else{
                jogador2.recusou++;
            }
        }
        // Atualiza contador de desistência
        if(!alguem_comprou) {
            desistencia_dupla++;
        }else {
            desistencia_dupla = 0;
        }
        rodadas++;
    }
    
    // Determina o vencedor
    char *vencedor;
    if(jogador1.soma_mao > 21){
        vencedor = jogador2.nome;
    }
    else if(jogador2.soma_mao > 21){
        vencedor = jogador1.nome;
    }
    else if(desistencia_dupla >= 2){
        if(jogador1.soma_mao == jogador2.soma_mao) {
            vencedor = "Empate";
        } else {
            vencedor = (jogador1.soma_mao > jogador2.soma_mao) ? jogador1.nome : jogador2.nome;
        }
    }
    else {
        vencedor = (jogador1.soma_mao > jogador2.soma_mao) ? jogador1.nome : jogador2.nome;
    }
    
    printf("\n----- FIM DE JOGO -----\n");
    printf("Resultado final:\n");
    imprimir_mao(jogador1);
    imprimir_mao(jogador2);
    printf("\nVencedor: %s\n", vencedor);
    printf("\n----- FIM DE JOGO -----\n");
    return 0;
}
