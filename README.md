# Projeto-CAP: Jogo Blackjack em C - Terminal

## Descrição

Este projeto implementa um jogo inspirado no Blackjack, desenvolvido em linguagem C para ser executado no terminal.  
O baralho é representado por um arquivo binário (`baralho.dat`), que armazena as 52 cartas embaralhadas.  
Cada jogador compra cartas lendo diretamente deste arquivo, garantindo uma mecânica realista de compra de cartas.

## Funcionalidades

- Criação e embaralhamento do baralho, com salvamento em arquivo binário.  
- Jogadores recebem 2 cartas cada no início do jogo.  
- Soma automática dos valores das cartas na mão de cada jogador.  
- Interação via terminal, apresentando o total da mão do jogador perguntando se deseja comprar cartas com escolha de sim ou não.  
- Impressão da mão atual dos jogadores a cada rodada.  
- Determinação do vencedor baseado nas regras básicas do Blackjack (não ultrapassar ou igualar 21).

## Estrutura do código

- `struct carta`: representa uma carta com naipe e valor.  
- `struct jogador`: armazena nome, soma da mão, cartas da mão (naipe e valor) e quantidade de cartas.  
- Procedimento `criar_baralho()`: cria, embaralha e salva o baralho em arquivo binário.  
- Procedimento `comprar_carta()`: lê uma carta do arquivo com base no índice como ponteiros e adiciona na mão do jogador, por fim soma o índice para que se compre a próxima carta do baralho na outra rodada.  
- Procedimento `imprimir_mao()`: mostra as cartas que o jogador possui com formatação legível.  
- `main()`: controla o fluxo do jogo, inicializa jogadores, distribui cartas iniciais e gerencia as rodadas com as interações, compras de cartas e finalização do jogo.

## Autores

- Danilo Djovano Selli Junior — Nº UFSCar 842868  
- Enzo Furquim Bonetto — Nº UFSCar 842869  
- Ryan Sohaky Duda Kondo — Nº UFSCar 834056
