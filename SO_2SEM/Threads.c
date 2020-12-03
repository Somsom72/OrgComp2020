#include "Threads.h"

void *thread_entrada(void *void_ptr_Infos)
{
	Infos* ptr_Infos = (Infos*) void_ptr_Infos;

	system ("/bin/stty raw -echo");

	/* Enquanto não há vencedor, capta entradas relevantes para atualizar os buffers do jogador1 e do jogador2 */
	while(*(ptr_Infos -> ptr_quemVenceu) == 0)
	{
		captaEntrada(ptr_Infos -> jogador1.ptr_buffer, ptr_Infos -> jogador2.ptr_buffer);
	}

	system ("/bin/stty cooked");
}

void *thread_saida(void *void_ptr_Infos)
{
	Infos *ptr_Infos = (Infos *)void_ptr_Infos;

	/* Enquanto não há vencedor, imprime a animação de saída utilizando o valor atual do placar */
	while(*(ptr_Infos -> ptr_quemVenceu) == 0)
	{
		imprimeSaida(ptr_Infos -> ptr_placar, ptr_Infos-> jogador1.nome, ptr_Infos-> jogador2.nome);
	}
}

void *thread_confereVencedor(void *void_ptr_Infos)
{
	Infos *ptr_Infos = (Infos *)void_ptr_Infos;

	/* Se há um vencedor, atualizar o "quemVenceu", assim notificando as demais threads que o jogo encerrou */
	while(*(ptr_Infos -> ptr_quemVenceu) == 0)
	{
		*(ptr_Infos -> ptr_quemVenceu) = determinaVencedor(*(ptr_Infos -> ptr_placar));
	}
}

void criarThreads(Threads t, Infos info)
{
	init_all_sem();

    if (pthread_create(&(t.entrada), NULL, thread_entrada, &info)) {exit(1);}
	if (pthread_create(&(t.saida), NULL, thread_saida, &info)) {exit(1);}
    if (pthread_create(&(t.verificadorVitoria), NULL, thread_confereVencedor, &info)) {exit(1);}
	if (pthread_create(&(t.jogador1), NULL, (void *) consumer, &info)) {exit(1);};
	if (pthread_create(&(t.jogador2), NULL, (void *) producer, &info)) {exit(1);};
}

void liberarThreads(Threads t)
{
    pthread_join(t.entrada, NULL);
	pthread_join(t.saida, NULL);
	pthread_join(t.verificadorVitoria, NULL);
	pthread_join(t.jogador1, NULL);
	pthread_join(t.jogador2, NULL);

	destroy_all_sem();
}


