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
#define FATOR_INERCIA 0.1

/* INÍCIO: DECLARAÇÃO DAS FUNÇÕES QUE SERÃO EXECUTADAS COMO THREADS, E SUAS STRUCTS DE ENTRADA */


/** 
 * \brief Struct de entrada da thread "entrada". 
 */
typedef struct {
	int *ptr_j1;
	int *ptr_j2;
	int *ptr_quemVenceu;
} EntradaEntrada;

/** 
 * \brief Thread responsável por incrementar jogador1/2 dependendo das entradas dos usuários. 
 */
void *thread_entrada(void *void_ptr_EntradaEntrada)
{
	EntradaEntrada *ptr_EntradaEntrada = (EntradaEntrada *)void_ptr_EntradaEntrada;

	system ("/bin/stty raw");

	/* Enquanto não há vencedor, capta entradas relevantes para atualizar os buffers do jogador1 e jogador2 */
	while(*(ptr_EntradaEntrada -> ptr_quemVenceu) == 0)
	{
		captaEntrada(ptr_EntradaEntrada -> ptr_j1, ptr_EntradaEntrada -> ptr_j2);
	}

	system ("/bin/stty cooked");
}


/** 
 * \brief Struct de entrada da thread "saida". 
 */
typedef struct {
	float *ptr_placar;
	int *ptr_quemVenceu;
} EntradaSaida;

/** 
 * \brief Thread responsável por imprimir os gráficos de saída, dependendo do valor do placar. 
 */
void *thread_saida(void *void_ptr_EntradaSaida)
{
	EntradaSaida *ptr_EntradaSaida = (EntradaSaida *)void_ptr_EntradaSaida;

	/* Enquanto não há vencedor, imprime a animação de saída utilizando o valor atual do placar */
	while(*(ptr_EntradaSaida -> ptr_quemVenceu) == 0)
	{
		imprimeSaida(ptr_EntradaSaida -> ptr_placar);
	}
}


/** 
 * \brief Struct de entrada da thread "confereVencedor". 
 */
typedef struct {
	float *ptr_placar;
	int *ptr_quemVenceu;
} EntradaConfereVencedor;

/** 
 * \brief Thread responsável por manter a variável "quemVenceu" atualizada. 
 */
void *thread_confereVencedor(void *void_ptr_EntradaConfereVencedor)
{
	EntradaConfereVencedor *ptr_EntradaConfereVencedor = (EntradaConfereVencedor *)void_ptr_EntradaConfereVencedor;

	/* Se há um vencedor, atualizar o "quemVenceu", assim notificando as demais threads que o jogo encerrou */
	while(*(ptr_EntradaConfereVencedor -> ptr_quemVenceu) == 0)
	{
		*(ptr_EntradaConfereVencedor -> ptr_quemVenceu) = determinaVencedor(*(ptr_EntradaConfereVencedor -> ptr_placar));
	}
}


/** 
 * \brief Struct de entrada da thread "jogador1". 
 */
typedef struct {
	int *ptr_j1;
	float *ptr_placar;
	int *ptr_quemVenceu;
} EntradaJogador1;

/** 
 * \brief Thread responsáveis por atualizar o placar (região crítica deste), dada uma apertada do jogador1.  
 */
void *thread_jogador1(void *void_ptr_EntradaJogador1)
{
	EntradaJogador1 *ptr_EntradaJogador1 = (EntradaJogador1 *)void_ptr_EntradaJogador1;

	/* Enquanto não há vencedor, atualiza o placar de acordo com o buffer do jogador1 */
	while(*(ptr_EntradaJogador1 -> ptr_quemVenceu) == 0)
	{
		atualizaPlacar1(ptr_EntradaJogador1 -> ptr_placar, ptr_EntradaJogador1 -> ptr_j1, FATOR_INERCIA);
	}
}


/** 
 * \brief Struct de entrada da thread "jogador2". 
 */
typedef struct {
	int *ptr_j2;
	float *ptr_placar;
	int *ptr_quemVenceu;
} EntradaJogador2;

/** 
 * \brief Thread responsáveis por atualizar o placar (região crítica deste), dada uma apertada do jogador2.  
 */
void *thread_jogador2(void *void_ptr_EntradaJogador2)
{
	EntradaJogador2 *ptr_EntradaJogador2 = (EntradaJogador2 *)void_ptr_EntradaJogador2;

	/* Enquanto não há vencedor, atualiza o placar de acordo com o buffer do jogador2 */
	while(*(ptr_EntradaJogador2 -> ptr_quemVenceu) == 0)
	{
		atualizaPlacar2(ptr_EntradaJogador2 -> ptr_placar, ptr_EntradaJogador2 -> ptr_j2, FATOR_INERCIA);
	}
}


/* FIM: DECLARAÇÃO DAS FUNÇÕES QUE SERÃO EXECUTADAS COMO THREADS, E SUAS STRUCTS DE ENTRADA */

/**
 * \brief Menu de abertura do jogo com as opções de jogar 's' e sair 'k'.
 */
void Menu(){
	printf("\n\n=========== Bem-vinde ao Cabo de Guerra ===========\n");
	printf("\nSelecione uma das opções abaixo:");
    printf("\n\nJogar: 's'\nSair: 'k'\n\n");
	
	return;
}

/**
 * \brief Contém a lógica do jogo.
 * 
 * \return 1 caso jogador1 venceu, 2 caso perdeu.
 */
int jogo(void)
{
    int jogador1 = 0, jogador2 = 0; ///< Variáveis "buffers" dos jogadores.
	float placar = 0; ///< Valor do placar atual;
	int quemVenceu = determinaVencedor(placar); ///< Variável indica se alguém venceu (e quem). Usado como condição de parada das threads. 

	/* Declara identificadores das threads */
	pthread_t n_thread_entrada;
	pthread_t n_thread_saida;
	pthread_t n_thread_confereVencedor;
	pthread_t n_thread_jogador1, n_thread_jogador2;

	/* Inicializa threads (e suas structs de entrada) */

	EntradaEntrada ee;
	ee.ptr_j1 = &jogador1;
	ee.ptr_j2 = &jogador2;
	ee.ptr_quemVenceu = &quemVenceu;
	if(pthread_create(&n_thread_entrada, NULL, thread_entrada, &ee)) {exit(1);}

	EntradaSaida es;
	es.ptr_placar = &placar;
	es.ptr_quemVenceu = &quemVenceu;
	if(pthread_create(&n_thread_saida, NULL, thread_saida, &es)) {exit(1);}

	EntradaJogador1 ej1;
	ej1.ptr_j1 = &jogador1;
	ej1.ptr_placar = &placar;
	ej1.ptr_quemVenceu = &quemVenceu;
	if(pthread_create(&n_thread_jogador1, NULL, thread_jogador1, &ej1)) {exit(1);}

	EntradaJogador2 ej2;
	ej2.ptr_j2 = &jogador2;
	ej2.ptr_placar = &placar;
	ej2.ptr_quemVenceu = &quemVenceu;
	if(pthread_create(&n_thread_jogador2, NULL, thread_jogador2, &ej2)) {exit(1);}

	/* Libera threads */
	pthread_join(n_thread_confereVencedor, NULL);
	pthread_join(n_thread_entrada, NULL);
	pthread_join(n_thread_saida, NULL);
	pthread_join(n_thread_jogador1, NULL);
	pthread_join(n_thread_jogador2, NULL);

    return quemVenceu;
}

/**
 * \brief Laço principal.
 */
int main(void)
{
    char opcao;

    while(1)
    {
		clock_t inicio, fim; /*!< Variáveis auxiliares para o cálculo da duração do jogo. */
		int quemVenceu; /*!< Indica quem venceu (retorno de "jogo()"). Usada para imprimir resultado do jogo. */

		Menu();

        scanf("%c", &opcao);
		getchar();

        if(opcao == 's')
		{
			inicio = clock();
			quemVenceu = jogo();
			fim = clock();

			printf("\n\nO jogo demorou %.1lf segundos e ", (double)fim-inicio);
			if(quemVenceu == 1) {printf("o jogador 1 venceu!!\n\n");}
			else {printf("o jogador 2 venceu!!\n\n");}
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