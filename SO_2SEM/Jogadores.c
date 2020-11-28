#include <stdio.h>
#include "Jogadores.h"

int atualizaPlacar1(float *placar, int *j, float fator_inercia)
{
    if(placar == NULL || j == NULL) {return 1;}

    /* move placar para esquerda*/
    *placar -= (float)*j; *j = 0;

    /* inércia */
    *placar += (*placar) * fator_inercia;

    return 0;
}

int atualizaPlacar2(float *placar, int *j, float fator_inercia)
{
    if(placar == NULL || j == NULL) {return 1;}

    /* move placar para direita */
    *placar += (float)*j; *j = 0;

    /* inércia */
    *placar += (*placar) * fator_inercia;

    return 0;
}

int determinaVencedor(float placar)
{
    if(placar <= -100) {return 1;}
    else if(placar >= 100) {return 2;}
    return 0;
}