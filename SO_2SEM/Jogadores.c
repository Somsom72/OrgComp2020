#include <stdio.h>
#include "Jogadores.h"

#define INERTIA_FACTOR 0.1;

int updateScoreboard(float* scoreboard, int* item, int direction)
{
    if (scoreboard == NULL || item == NULL)
        return 1;

    /* Move to the direction (-1 - left or 1 - right) */
    *scoreboard += (float) (*item) * direction; 
    *item = 0;

    /* inertia factor */
    *scoreboard += (*scoreboard) * INERTIA_FACTOR;

    return 0;
}

int determinaVencedor(float placar)
{
    if(placar <= -100) {return 1;}
    else if(placar >= 100) {return 2;}
    return 0;
}