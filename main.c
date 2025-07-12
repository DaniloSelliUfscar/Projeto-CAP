/******************************************************************************
Descrição: 
Requer:  
Assegura: 

Danilo Djovano Selli Junior Nº UFSCar 842868
Enzo Furquim Bonetto Nº UFSCar 842869
Ryan Sohaky Duda Kondo Nº UFSCar 834056
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // (chat disse que usaria, preciso ver oq faz)

#define MAX_CARTAS 52
#define MAX_JOGADORES 2


struct carta {
    char naipe;
    int valor;
};

struct jogador {
    char nome[50];
    int pontos;
    int mao[20];
};

// Procedimento para criar o baralho, embaralhar e salvar no arquivo baralho.dat
void criar_baralho() {
    // Abre o arquivo escrita zerando ele 
    FILE *arquivo = fopen("baralho.dat", "w");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo do baralho.\n");
     //   return 1;
    }
    
    // Criação do baralho formado por 52 cartas
    struct carta baralho[MAX_CARTAS];
    
    char naipes[] = {'C', 'D', 'H', 'S'};  // Naipes: Copas, Ouros, Copas, Espadas
    int indice_carta = 0; // indice para as cartas (1ª, 2ª, ... 52ª)
    
    // Preechendo o baralho com cartas de naipes e valores
    for (int n = 0; n < 4; n++) {
        for (int v = 1; v <= 13; v++) {
            baralho[indice_carta].naipe = naipes[n];
            baralho[indice_carta].valor = (v > 10) ? 10 : v; // dama, rei, valete = 10
            indice_carta++;
        }
    }
    
    //Embaralhar as cartas (rand) e escrever no arquivo
    srand(time(NULL));
    for (int i = 0; i < MAX_CARTAS; i++) {
        int r = rand() % MAX_CARTAS;
        struct carta temp = baralho[i]; // struct Carta auxiliar
        baralho[i] = baralho[r];
        baralho[r] = temp;
        
        //escreve carta uma por uma
        fwrite(baralho, sizeof(struct carta), MAX_CARTAS, arquivo); 
    }

    fclose(arquivo);
}


// Função para comprar carta, retorna a carta que está no topo do baralho (struct carta atual do arquivo) quando chamada
struct carta comprar_carta(){
    // Abre o arquivo para leitura
    FILE *arquivo = fopen("baralho.dat", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo do baralho para leitura.\n");
     //   return 1;
    }
    
    struct carta carta_comprada;
    fread(&carta_comprada, sizeof(carta_comprada), 1, arquivo); //lê a carta do arquivo
    return carta_comprada;
    
    fclose(arquivo);
}


int main()
{
    
    return 0;
}