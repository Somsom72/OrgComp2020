/** 
 * \file CaboDeGuerra.c
 * \brief Arquivo que contém o laço principal do jogo.
 */

#include <stdio.h>
#include <pthread.h>
#include "Jogadores.h"
#include "EntradaSaida.h"
#include "Semaforo.h"

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
    /* Menu inicial */
    char opcao;
    while(1)
    {
        printf("\n\nJogar: 's'\nSair: 'k'\n\n");
        scanf("%c", &opcao);
        if(opcao == 's') {jogo();}
        else if(opcao == 'k') {break;}
        else {printf("Opção inválida, tente novamente.");}
    }

    return 0;
}