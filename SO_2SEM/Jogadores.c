#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Jogadores.h"

Jogador inicializarJogador(char* nome, int* ptr_buffer)
{
    Jogador j;
    strncpy(j.nome, nome, strlen(nome));
    j.ptr_buffer = ptr_buffer;

    return j;
}

Infos inicializarInfos(Jogador j1, Jogador j2, int* ptr_placar, int* ptr_quemVenceu)
{
    Infos in;
    in.jogador1 = j1;
    in.jogador2 = j2;
    in.ptr_placar = ptr_placar;
    in.ptr_quemVenceu = ptr_quemVenceu;

    return in;
}

int atualizaPlacar(int *placar, int *j, float fator_inercia, int dir)
{
    if(placar == NULL || j == NULL) {return 1;}

    /* inércia (em que o fator de inércia decide a frequência em que a vantagem da inércia é concedida) */
<<<<<<< HEAD
    int i;/*
    for(i = 1; i < FATOR_INERCIA; i++)
    {
        if((dir == -1) && (*placar == -i * floor((double)(DURACAO_DO_JOGO / FATOR_INERCIA)))) {(*placar)--;}
        else if((dir == 1) && (*placar == i * floor((double)(DURACAO_DO_JOGO / FATOR_INERCIA)))) {(*placar)++;}
    }*/
=======
    int i;
    for(i = 1; i < fator_inercia; i++)
    {
        if((dir == -1) && (*placar == -i * floor((double)(DURACAO_DO_JOGO / fator_inercia))) && (*j > 0)) {(*placar)--;}
        else if((dir == 1) && (*placar == i * floor((double)(DURACAO_DO_JOGO / fator_inercia))) && (*j > 0)) {(*placar)++;}
    }
>>>>>>> d248a84ae740774a0e1c13df2f73e2eeb3445924

    /* move placar e esvazia buffer do jogador */
    (*placar) += (*j) * (dir);
	(*j) = 0;

    return 0;
}

int determinaVencedor(int placar)
{
    if(placar <= -1 * DURACAO_DO_JOGO) {return 1;}
    else if(placar >= DURACAO_DO_JOGO) {return 2;}
    return 0;
}