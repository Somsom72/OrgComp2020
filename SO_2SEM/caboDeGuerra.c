/** 
 * \file CaboDeGuerra.c
 * \brief Arquivo que contém o laço principal do jogo.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Threads.h"
#include "Jogadores.h"
#include "defines.h"
#include <unistd.h>

#define _sleep(x) sleep(x)

/**
 * \brief Menu de abertura do jogo com as opções de jogar 's' e sair 'k'.
 */
void mostrarMenu(){
	printf("\n\n=========== Boas-vindas ao Cabo de Guerra ===========\n");
	printf("\nSelecione 'p' para jogar!\n\n");
	
	return;
}

/**
 * \brief Contém a lógica do jogo.
 * 
 * \return 1 caso jogador1 venceu, 2 caso perdeu.
 */
int iniciarJogo(char *nome1, char *nome2)
{
    int buffer_jogador1 = 0, buffer_jogador2 = 0; ///< Variáveis "buffers" dos jogadores.
	int placar = 0; ///< Valor do placar atual;
	int quemVenceu = determinaVencedor(placar); ///< Variável indica se alguém venceu (e quem). Usado como condição de parada das threads. 

	/* Declara identificadores das threads */
	Threads t;

	Jogador j1 = inicializarJogador(nome1, &buffer_jogador1);
	Jogador j2 = inicializarJogador(nome2, &buffer_jogador2);
	Infos inf = inicializarInfos(j1, j2, &placar, &quemVenceu);

	criarThreads(&t, &inf);

	liberarThreads(&t);

    return quemVenceu;
}

/**
 * \brief Laço principal.
 */
int main(void)
{
    char opcao;
	char nome1[MAX_CARACTERES];
	char nome2[MAX_CARACTERES];

    while(1)
    {
		clock_t inicio, fim; /*!< Variáveis auxiliares para o cálculo da duração do jogo. */
		int quemVenceu; /*!< Indica quem venceu (retorno de "jogo()"). Usada para imprimir resultado do jogo. */
	
		mostrarMenu();

        scanf("%c", &opcao);
		getchar();

        if(opcao == 'p')
		{
			memset(nome1, '\0', MAX_CARACTERES);
			memset(nome2, '\0', MAX_CARACTERES);
			
			printf("Primeiramente, digite o nome dos dois jogadores, encerrando com um enter (máximo 15 letras).\n");
			printf("Jogador 1: ");
			scanf("%[^\n]%*c", nome1);
			
			printf("Jogador 2: ");
			scanf("%[^\n]%*c", nome2);
			for(int i = 5; i >= 0; i--){
				printf("Começando em %d \r", i);
				fflush(stdout);
				_sleep(1);
			}

			inicio = clock();
			quemVenceu = iniciarJogo(nome1, nome2);
			fim = clock();

			printf("\n\nO jogo demorou %.1lf segundos e ", (double)(fim-inicio)/CLOCKS_PER_SEC);
			if(quemVenceu == 1) {printf("%s venceu!!\n\n", nome1);}
			else {printf("%s venceu!!\n\n", nome2);}

			printf("\n\nVolte sempre!! Tenha um bom dia!!\n\n");
			break;
		}

        else {printf("\n\nOpção inválida, tente novamente.\n\n");}
    }

    return 0;
}