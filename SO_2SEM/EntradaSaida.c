#include "EntradaSaida.h"

int main(void){

    char opcao=0;

    int i,j, placarAtual;

    placarAtual=20;

    system ("/bin/stty raw");

    while(opcao!='q'){

        opcao=getchar();

        if(opcao == 'a') placarAtual++;
        else if(opcao == 'b') placarAtual--;

        system ("clear");

        printf("\ri");

        for(i=0;i<placarAtual;i++) printf(" ");

        printf("|");

        for(j=0;j<10;j++) printf("-");
        
        printf("|");

        for(;i<40;i++) printf(" ");

        printf("f\r\n");
        
        printf("\rplacarAtual: %d\r\n",placarAtual);

        if(placarAtual==0){
            printf("\rAzul venceu!!\n");
            opcao='q';
        }
        else if(placarAtual==40){
            printf("\rVermelho venceu!!\n");
            opcao='q';
        }

    }

    system ("/bin/stty cooked");

    return 0;
}