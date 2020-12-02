#include <stdio.h>
#include "Jogadores.h"

int atualizaPlacar(float* placar, int* pontuacao, int direcao)
{
    if (placar == NULL || pontuacao== NULL) 
        return 1; // Erro

    /* Move to the direction (-1 - left or 1 - right) */
    *placar += (float) (*pontuacao) * direcao; 
    *pontuacao = 0;

    /* inertia factor */
    *placar += (*placar) * INERTIA_FACTOR;

    return 0;
}

int determinaVencedor(float placar)
{
    if(placar <= -1*DURACAO_DO_JOGO) {return 1;}
    else if(placar >= DURACAO_DO_JOGO) {return 2;}
    else return 0;
}