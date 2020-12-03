#include <stdio.h>
#include <string.h>
#include "Jogadores.h"

Jogador inicializarJogador(char* nome, int* ptr_buffer)
{
    Jogador j;
    strcpy(j.nome, nome);
    j.ptr_buffer = ptr_buffer;
}

Infos inicializarInfos(Jogador j1, Jogador j2, float* ptr_placar, int* ptr_quemVenceu)
{
    Infos in;
    in.jogador1 = j1;
    in.jogador2 = j2;
    in.ptr_placar = ptr_placar;
    in.ptr_quemVenceu = ptr_quemVenceu;

    return in;
}

int atualizaPlacar(float *placar, int *j, float fator_inercia, int dir)
{
    if(placar == NULL || j == NULL) {return 1;}

    /* move placar e esvazia buffer do jogador */
    *placar += ((float)*j) * (dir); *j = 0;

    /* inércia */
    *placar += (*placar) * fator_inercia;

    return 0;
}

int determinaVencedor(float placar)
{
    if(placar <= -1 * DURACAO_DO_JOGO) {return 1;}
    else if(placar >= DURACAO_DO_JOGO) {return 2;}
    return 0;
}