#include <stdio.h>
#include "Jogadores.h"
#include "EntradaSaida.h"

int atualizaPlacar(float *placar, int *j, float fator_inercia, int dir)
{
    if(placar == NULL || j == NULL) {return 1;}

    /* move placar para esquerda */
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