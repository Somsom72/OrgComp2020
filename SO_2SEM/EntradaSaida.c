#include "EntradaSaida.h"
#include "defines.h"

void captaEntrada(int* pontuacao1, int* pontuacao2){

    char opcao;
	char lixo;

	system ("/bin/stty raw -echo");
    opcao = getchar();
	scanf("%c", &lixo);
	fflush(stdin);
	
	system ("/bin/stty cooked");

    if(opcao=='s') (*pontuacao1)++;
    else if (opcao == 'k') (*pontuacao2)++;

    return;
}

void imprimeSaida(int* placar, char *nome1, char *nome2){
    
    int i;

    system ("clear");

    printf("\n\t\t============ O cabo-de-guerra está valendo! ============\n\n");
	printf("\rPressione 's' para puxar o cabo para a esquerda ou 'k' para puxá-lo para a direita\n\n\n\n");

    printf("\r%s", nome1);

    if(*placar<0){
        for(i=(DURACAO_DO_JOGO) + (*placar);i>0;i--) printf(" ");
        printf("|"); for(i=0;i<TAMANHO_DA_CORDA;i++) printf("-"); printf("|");
        for(i=0;i<DURACAO_DO_JOGO;i++) printf(" ");
        for(i=0;i<abs(*placar);i++) printf(" ");
    } 

    else{
        for(i=0;i<DURACAO_DO_JOGO;i++) printf(" ");
        for(i=0;i<*placar;i++) printf(" ");
        printf("|"); for(i=0;i<TAMANHO_DA_CORDA;i++) printf("-"); printf("|");
        for(i=(int)*placar;i<DURACAO_DO_JOGO;i++) printf(" ");
    } 

	printf("%s", nome2);
	for(i = strlen(nome1)-strlen(nome2); i >= 0; i--) printf("\b");
	
    printf("\r\n");

    if(*placar==0) printf("PlacarAtual: 0. Está tudo empatado!\n\n");
    else if(*placar<0) printf("PlacarAtual: %d de vantagem para %s\n\n",-(*placar), nome1);
    else printf("PlacarAtual: %d de vantagem para %s\n\n",(*placar), nome2);

    return;
}
