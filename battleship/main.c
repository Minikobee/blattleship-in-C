#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "battleship.h"
char nome1[40];
char nome2[40];
int vec[4];


int main()
{
    srand(time(NULL)); //randomize seed
    int soma = 2000000, tamanho, tamanho2;
    char* valor =(char*) malloc(sizeof(char));
    int menu;
    int start;

    system("clear");
    printf("+-----------------------------------------------------------------------------------+\n");
    printf("+                                                                                   +\n");
    printf("+                               WELCOME TO BATTLESHIP                               +\n");
    printf("+                                                                                   +\n");
    printf("+-----------------------------------------------------------------------------------+\n");
    printf("\n");

    menu = 10;
    while (menu != 1)
    {
        printf("+-----------------------------------------------------------------------------------+\n");
        printf("+                                                                                   +\n");
        printf("+                            Press 1 para começar o jogo                            +\n");
        printf("+                      Press 2 para ver as instruções do jogo                       +\n");
        printf("+                             Press 3 para sair do jogo                             +\n");
        printf("+                                                                                   +\n");
        printf("+-----------------------------------------------------------------------------------+\n");
        printf("\n");

        scanf("%s", valor);
        menu = atoi(valor);
        printf("%d",menu);
        if (menu == 3)
        {
            printf("Saiu do jogo!\n");
            return 0;
        }
        else if (menu == 2)
        {
            //definiçoes do jogo
            defin();
        }
        else if (menu < 1 || menu > 3)
            printf("Valor não reconhecido, tente novamente.\n\n");
        

        system("clear");
    }

    printf("+-----------------------------------------------------------------------------------+\n");
    printf("+                                                                                   +\n");
    printf("+                  Press 1 para as peças serem posicionadas por si                  +\n");
    printf("+              Press 2 para as peças serem posicionadas aleatoriamente              +\n");
    printf("+                                                                                   +\n");
    printf("+-----------------------------------------------------------------------------------+\n");
    printf("\n");

    scanf("%s", valor);
    start=atoi(valor);

    while ((start != 1) && (start != 2))
    {
        printf("Erro! O valor não satifaz a condição. Tenta de novo: ");
        scanf("%s", valor);
        start=atoi(valor);
    }

    system("clear");

    printf("Insira o tamanho do tabuleiro n por n entre 20 e 40: ");
    scanf("%s", valor);
    tamanho = atoi(valor);
    while (tamanho < 20 || tamanho > 40)
    {
        printf("Tamanho do tabuleiro deve ser entre 20 a 40 \n");
        scanf("%s", valor);
        tamanho = atoi(valor);
    }

    // área do tabuleiro
    tamanho2 = tamanho * tamanho;

    game *m1, *m2;

    //matrix do player 1
    m1 = buildgame(tamanho);

    //matrix do player 2
    m2 = buildgame(tamanho);

    // nome do primeiro jogador e imprimir a matriz toda com valor 0
    printf("\n");
    printf("Nome do primeiro jogador: ");
    scanf("%s", nome1);
    printf("\n");
    tabelalocal(m1);

    // nome do segundo jogador e imprimir a matriz toda com valor 0
    printf("\n");
    printf("Nome do segundo jogador: ");
    scanf("%s", nome2);
    printf("\n");
    tabelalocal(m2);
    printf("\n");

    // escolher o número de barcos para os dois jogadores
    barcos(vec, 8, start, soma, tamanho2);

    printf("+-----------------------------------------------------------------------------------+\n");
    printf("+                                                                                   +\n");
    printf("+                                 COLOCAR OS BARCOS                                 +\n");
    printf("+                                                                                   +\n");
    printf("+-----------------------------------------------------------------------------------+\n");

    // player 1 para colocar os barcos na forma manual ou na forma random
    chooseboats(m1, vec, tamanho, start, nome1);
    system("clear");

    // player 2 para colocar os barcos na forma manual ou na forma random
    chooseboats(m2, vec, tamanho, start, nome2);
    system("clear");

    //player 1 vs player 2 (jogo)
    ataque(m1, m2, nome1, nome2, vec,tamanho);

    free(m1);
    free(m2);
    return 0;
}