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

/**
 * \brief Menu de abertura do jogo com as opções de jogar 's' e sair 'k'.
 */
void mostrarMenu(){
	printf("\n\n=========== Boas-vindas ao Cabo de Guerra ===========\n");
	printf("\nSelecione uma das opções abaixo:");
    printf("\n\nJogar: 's'\nSair: 'k'\n\n");
	
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
	float placar = 0; ///< Valor do placar atual;
	int quemVenceu = determinaVencedor(placar); ///< Variável indica se alguém venceu (e quem). Usado como condição de parada das threads. 

	/* Declara identificadores das threads */
	Threads t;

	Jogador j1 = inicializarJogador(nome1, &buffer_jogador1);
	Jogador j2 = inicializarJogador(nome2, &buffer_jogador2);
	Infos inf = inicializarInfos(j1, j2, &placar, &quemVenceu);

	criarThreads(t, inf);

	liberarThreads(t);

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
	memset(nome1, 'k', strlen(nome1));
	memset(nome2, 's', strlen(nome2));

    while(1)
    {
		clock_t inicio, fim; /*!< Variáveis auxiliares para o cálculo da duração do jogo. */
		int quemVenceu; /*!< Indica quem venceu (retorno de "jogo()"). Usada para imprimir resultado do jogo. */
	
		mostrarMenu();

        scanf("%c", &opcao);
		getchar();

        if(opcao == 's')
		{
			printf("Primeiramente, digite o nome dos dois jogadores, encerrando com um enter (máximo 15 letras).\n");
			printf("Jogador 1:");
			scanf("%[^\n]%*c", nome1);
			
			printf("Jogador 2:");
			scanf("%[^\n]%*c", nome2);

			inicio = clock();
			quemVenceu = iniciarJogo(nome1, nome2);
			fim = clock();

			printf("\n\nO jogo demorou %.1lf segundos e ", (double)fim-inicio);
			if(quemVenceu == 1) {printf("%s venceu!!\n\n", nome1);}
			else {printf("%s venceu!!\n\n", nome2);}
		}

        else if(opcao == 'k')
		{
			printf("\n\nVolte sempre!! Tenha um bom dia!!\n\n");
			break;
		}

        else {printf("\n\nOpção inválida, tente novamente.\n\n");}
    }

    return 0;
}