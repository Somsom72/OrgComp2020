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

#define MAX 15

/* INÍCIO: DECLARAÇÃO DAS FUNÇÕES QUE SERÃO EXECUTADAS COMO THREADS, E SUAS STRUCTS DE ENTRADA */

/** 
 * \brief Struct de entrada das threads. 
 */
typedef struct {
	char nome_jogador1[MAX];
	char nome_jogador2[MAX];
	int *ptr_j1;
	int *ptr_j2;
	float *ptr_placar;
	int *ptr_quemVenceu;
} Infos, *ptrInfos;

/** 
 * \brief Thread responsável por incrementar jogador1/2 dependendo das entradas dos usuários. 
 */
void *thread_entrada(void *void_ptr_Infos)
{
	ptrInfos ptr_Infos = (ptrInfos)void_ptr_Infos;

	system ("/bin/stty raw");

	/* Enquanto não há vencedor, capta entradas relevantes para atualizar os buffers do jogador1 e jogador2 */
	while(ptr_Infos -> ptr_quemVenceu == 0)
	{
		captaEntrada(ptr_Infos -> ptr_j1, ptr_Infos -> ptr_j2);
	}

	system ("/bin/stty cooked");
}

/** 
 * \brief Thread responsável por imprimir os gráficos de saída, dependendo do valor do placar. 
 */
void *thread_saida(void *void_ptr_Infos)
{
	Infos *ptr_Infos = (Infos *)void_ptr_Infos;

	/* Enquanto não há vencedor, imprime a animação de saída utilizando o valor atual do placar */
	while(*(ptr_Infos -> ptr_quemVenceu) == 0)
	{
		imprimeSaida(ptr_Infos -> ptr_placar, ptr_Infos->nome_jogador1, ptr_Infos->nome_jogador2);
	}
}

/** 
 * \brief Thread responsável por manter a variável "quemVenceu" atualizada. 
 */
void *thread_confereVencedor(void *void_ptr_Infos)
{
	Infos *ptr_Infos = (Infos *)void_ptr_Infos;

	/* Se há um vencedor, atualizar o "quemVenceu", assim notificando as demais threads que o jogo encerrou */
	while(*(ptr_Infos -> ptr_quemVenceu) == 0)
	{
		*(ptr_Infos -> ptr_quemVenceu) = determinaVencedor(*(ptr_Infos -> ptr_placar));
	}
}

/* FIM: DECLARAÇÃO DAS FUNÇÕES QUE SERÃO EXECUTADAS COMO THREADS, E SUAS STRUCTS DE ENTRADA */

/**
 * \brief Menu de abertura do jogo com as opções de jogar 's' e sair 'k'.
 */
void Menu(){
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
int jogo(char *nome1, char *nome2)
{
    int jogador1 = 0, jogador2 = 0; ///< Variáveis "buffers" dos jogadores.
	float placar = 0; ///< Valor do placar atual;
	int quemVenceu = determinaVencedor(placar); ///< Variável indica se alguém venceu (e quem). Usado como condição de parada das threads. 

	/* Declara identificadores das threads */
	pthread_t n_thread_entrada;
	pthread_t n_thread_saida;
	pthread_t n_thread_confereVencedor;
	pthread_t n_thread_jogador1, n_thread_jogador2;

	init_all_sem();

	/* Inicializa struct de entrada e as threads. */
	Infos in;
	in.ptr_j1 = &jogador1;
	in.ptr_j2 = &jogador2;
	in.ptr_placar = &placar;
	in.ptr_quemVenceu = &quemVenceu;
	strcpy(in.nome_jogador1, nome1);
	strcpy(in.nome_jogador2, nome2);
	if(pthread_create(&n_thread_entrada, NULL, thread_entrada, &in)) {exit(1);}
	if(pthread_create(&n_thread_saida, NULL, thread_saida, &in)) {exit(1);}
	if (pthread_create(&n_thread_jogador1, NULL, (void *) consumer, (void *)&in)) {exit(1);};
	if (pthread_create(&n_thread_jogador2, NULL, (void *) producer, (void *)&in)) {exit(1);};

	/* Libera threads */
	pthread_join(n_thread_confereVencedor, NULL);
	pthread_join(n_thread_entrada, NULL);
	pthread_join(n_thread_saida, NULL);
	pthread_join(n_thread_jogador1, NULL);
	pthread_join(n_thread_jogador2, NULL);

	destroy_all_sem();

    return quemVenceu;
}

/**
 * \brief Laço principal.
 */
int main(void)
{
    char opcao;
	char nome1[MAX];
	char nome2[MAX];
	memset(nome1, 'k', strlen(nome1));
	memset(nome2, 's', strlen(nome2));

    while(1)
    {
		clock_t inicio, fim; /*!< Variáveis auxiliares para o cálculo da duração do jogo. */
		int quemVenceu; /*!< Indica quem venceu (retorno de "jogo()"). Usada para imprimir resultado do jogo. */

		Menu();

        scanf("%c", &opcao);
		getchar();

        if(opcao == 's')
		{
			printf("Primeiramente, digite o nome dos dois jogadores, encerrando com um enter (máximo 15 letras).\n");
			printf("Jogador 1:");
			scanf("%[^\n]%*c", nome1);
			getchar();
			printf("Jogador 2:");
			scanf("%[^\n]%*c", nome2);
			getchar();

			inicio = clock();
			quemVenceu = jogo(nome1, nome2);
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