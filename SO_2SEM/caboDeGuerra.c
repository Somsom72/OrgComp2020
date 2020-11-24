/** 
 * \file CaboDeGuerra.c
 * \brief Arquivo que contém o laço principal do jogo.
 */

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "Jogadores.h"
#include "EntradaSaida.h"
#include "Semaforo.h"

/**
 * \brief Menu de abertura do jogo com as opções de jogar 's' e sair 'k'
 */
void Menu(){
	printf("\n\n=========== Bem-vinde ao Cabo de Guerra ===========\n");
	printf("\nSelecione uma das opções abaixo:");
    printf("\n\nJogar: 's'\nSair: 'k'\n\n");
	
	return;
}

/**
 * \brief Contém a lógica do jogo.
 */
int jogo(void)
{
    int jogador1 = 0, jogador2 = 0, placar = 0;

    // (threads aqui em breve..)

    return 0;
}

/**
 * \brief Laço principal.
 */
int main(void)
{

    char opcao;
    while(1)
    {
		Menu();
        scanf("%c", &opcao);
		getchar();
        if(opcao == 's')
		{
			clock_t inicio, fim; /*!< Variáveis auxiliares para o cálculo da duração do jogo */
			inicio = clock();
			jogo();
			fim = clock();

			printf("O jogo demorou %.1lf segundos!!\n", (double)fim-inicio);
		}
        else if(opcao == 'k')
		{
			printf("\n\nVolte sempre!! Tenha um bom dia!!\n\n");
			break;
		}
        else {printf("Opção inválida, tente novamente.");}
    }

    return 0;
}