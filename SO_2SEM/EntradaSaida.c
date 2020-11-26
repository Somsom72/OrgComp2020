#include "EntradaSaida.h"

int main(void){

    char opcao=0;

    int i,j, placaratual;

    placaratual=20;

    system ("/bin/stty raw");

    while(opcao!='q'){

        opcao=getchar();

        if(opcao == 'a') placaratual++;
        else if(opcao == 'b') placaratual--;

        system ("clear");

        printf("\ri");

        for(i=0;i<placaratual;i++) printf(" ");

        printf("|");

        for(j=0;j<10;j++) printf("-");
        
        printf("|");

        for(;i<40;i++) printf(" ");

        printf("f\r\n");
        
        printf("\rPlacaratual: %d\r\n",placaratual);

        if(placaratual==0){
            printf("\rAzul venceu!!\n");
            opcao='q';
        }
        else if(placaratual==40){
            printf("\rVermelho venceu!!\n");
            opcao='q';
        }

    }

    system ("/bin/stty cooked");

    return 0;
}