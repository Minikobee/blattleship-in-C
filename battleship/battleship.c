#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include "battleship.h"
#define lim 4

//destrui coordenadas
void destruicoord(coordenadas *b)
{
    free(b);
}

//destrui bitmap
void destruibit(bit *b)
{
    for (int i = 0; i < 5; i++)
    {
        free(b->bitmap[i]);
    }
    free(b->bitmap);
    free(b);
}

//destrui boat
void destruiboat(boat *b)
{
    destruicoord(b->coord);
    destruibit(b->bitmap);
    free(b);
}

//destroi boat sem coordenadas
void destruiboattemp(boat *b)
{
    destruibit(b->bitmap);
    free(b);
}

// construir o tabuleiro de jogo
game *buildgame(int linhas)
{
    game *new = (game *)malloc(sizeof(game));

    new->linhas = linhas;
    new->matrix = (cell **)malloc(sizeof(cell *) * linhas);
    for (int x = 0; x < linhas; x++)
    {
        new->matrix[x] = (cell *)malloc(sizeof(cell) * linhas);
        for (int y = 0; y < linhas; y++)
        {
            new->matrix[x][y].estado = 0;
            new->matrix[x][y].shot = 0;
            new->matrix[x][y].barco = NULL;
        }
    }
    return new;
}

//construir coordenadas
coordenadas *buildcoord(int linhas, int colunas)
{
    coordenadas *new = (coordenadas *)malloc(sizeof(coordenadas));
    new->linhas = linhas;
    new->colunas = colunas;
    return new;
}

// construi o bitmap
bit *buildbit()
{
    bit *new = (bit *)malloc(sizeof(bit));
    new->bitmap = (char **)malloc(5 * sizeof(char *));
    for (int x = 0; x < 5; x++)
    {
        new->bitmap[x] = (char *)malloc(5 * sizeof(char));
    }
    return new;
}

//construi o barco
boat *buildboat(char id, coordenadas *co)
{
    boat *new = (boat *)malloc(sizeof(boat));
    new->id = id;
    new->nplaces = 0;
    new->coord = co;
    new->bitmap = buildbit();
    switch (id)
    {
    case 's':
        barsq(new->bitmap);
        new->nplaces = 9;
        break;
    case 'r':
        barcoret(new->bitmap);
        new->nplaces = 6;
        break;
    case 'l':
        barcoll(new->bitmap);
        new->nplaces = 4;
        break;
    case 'x':
        barcoxx(new->bitmap);
        new->nplaces = 5;
        break;
    case 't':
        barnor(new->bitmap);
        new->nplaces = 4;
        break;
    }
    return new;
}

//imprimir o bitmap
void tabela1(bit *p)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c", p->bitmap[i][j]);
        }
        printf("\n");
    }
}

// barco ultron
void barnor(bit *p)
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 2 && (i >= 0 && i <= 3))
                p->bitmap[i][j] = '1';
            else
                p->bitmap[i][j] = '0';
        }
    }
}

// barco loki
void barsq(bit *p)
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if ((i >= 1 && i < 4) && (j > 0 && j <= 3))
                p->bitmap[i][j] = '1';
            else
                p->bitmap[i][j] = '0';
        }
    }
}

//barco thanos
void barcoll(bit *p)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (((j > 2 && j <= 3) && i == 2) || ((i >= 0 && i < 3) && j == 2))
                p->bitmap[i][j] = '1';
            else
                p->bitmap[i][j] = '0';
        }
    }
}

// barco venom
void barcoxx(bit *p)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == 2 && j == 2)
                p->bitmap[i][j] = '1';
            else if (i == 1 && j == 1)
                p->bitmap[i][j] = '1';
            else if (i == 3 && j == 3)
                p->bitmap[i][j] = '1';
            else if (i == 1 && j == 3)
                p->bitmap[i][j] = '1';
            else if (i == 3 && j == 1)
                p->bitmap[i][j] = '1';
            else
                p->bitmap[i][j] = '0';
        }
    }
}

// barco mysterio
void barcoret(bit *p)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if ((i >= 1 && i < 3) && (j > 0 && j <= 3))
                p->bitmap[i][j] = '1';
            else
                p->bitmap[i][j] = '0';
        }
    }
}

// definicoes iniciais
void defin()
{
    system("clear");
    printf("** Estas são as instruções do jogo **\n\n");
    printf("- o tabuleiro de cada jogador tem o formato de um quadrado e, obrigatoramente, o tamanho entre 20 e 40\n");
    printf("- no inicio do jogo, os dois jogadores simultaneamente tem as opções de colocar as peças aleatoriamente ou manualmente\n");
    printf("- nas ações de posicionar e atacar, deve indicar as coordenadas no formato: x y , sendo o x a linha e o y a coluna\n");
    printf("- o número de barcos tem de estar de acordo como tamanho do tabuleiro\n");
    printf("- no inicio do jogo o tabuleiro está preenchido com _ pois ainda não foi colocado nenhum barco \n");
    printf("- cada carater x corresponde a uma peça de um barco\n");
    printf("- o carater 0 corresponde a um tiro falhado\n ");
    printf("- o carater B corresponde a um tiro certeiro na peça do barco adversário\n ");
    printf("- os 5 barcos existentes são os seguintes:\n\n");
    printf(". Barco Ultron\n");
    coordenadas *temp = buildcoord(0, 0);
    boat *b = buildboat('t', temp);
    tabela1(b->bitmap);
    printf("\n");
    b = buildboat('s', temp);
    printf(". Barco Loki\n");
    tabela1(b->bitmap);
    b = buildboat('l', temp);
    printf("\n");
    printf(". Barco Thanos\n");
    tabela1(b->bitmap);
    printf("\n");
    b = buildboat('x', temp);
    printf(". Barco Venom\n");
    tabela1(b->bitmap);
    printf("\n");
    b = buildboat('r', temp);
    printf(". Barco Mysterio\n");
    tabela1(b->bitmap);
    printf("\n");

    int verificar = 1;
    printf("\nSe quiser sair press 0\n");
    while (verificar != 0)
    {
        scanf("%d", &verificar);
    }
    system("clear");
}

//atacar o inimigo
//0 = no shot, 1= shot that didn't hit, 2=shot that hit an enemy piece
// converter int em char
char tradutorshot(char c)
{
    switch (c)
    {
    case 0:
        return '-';
    case 1:
        return '0';
    case 2:
        return 'B';
    default:
        return -1;
    }
}

//imprimir o tabuleiro dos ataques
void tabelashot(game *p)
{
    for (int i = 0; i < p->linhas; i++)
    {
        for (int j = 0; j < p->linhas; j++)
        {
            if (tradutorshot(p->matrix[i][j].shot) == '-')
            {
                printf("\033[0;31m");
                printf("%c", tradutorshot(p->matrix[i][j].shot));
                printf("\033[0m");
            }
            else if (tradutorshot(p->matrix[i][j].shot) == 'B')
            {
                printf("\033[0;34m");
                printf("%c", tradutorshot(p->matrix[i][j].shot));
                printf("\033[0m");
            }
            else
            {
                printf("\033[0;32m");
                printf("%c", tradutorshot(p->matrix[i][j].shot));
                printf("\033[0m");
            }
        }
        printf("\n");
    }
}

// imprimir que nao acertou em nenhum barco
void insertshot0(game *g, int x, int y)
{
    g->matrix[x - 1][y - 1].shot = 1;
}

//imprimir que acertou num barco
void insertshotB(game *g, int x, int y)
{
    g->matrix[x - 1][y - 1].shot = 2;
}

// tabuleiro do proprio jogadot
// 0 = empty, 1 = piece without being hitted, 2 = piece hitted, 3 = missed shot
// converter int em char
char tradutorlocal(char c)
{
    switch (c)
    {
    case 0:
        return '-';
    case 1:
        return 'x';
    case 2:
        return 'B';
    case 3:
        return '0';
    default:
        return -1;
    }
}

// mostrar a matriz
void tabelalocal(game *p)
{
    for (int i = 0; i < p->linhas; i++)
    {
        for (int j = 0; j < p->linhas; j++)
        {
            if (p->matrix[i][j].estado == 0)
            {
                printf("\033[0;31m");
                printf("%c", tradutorlocal(p->matrix[i][j].estado));
                printf("\033[0m");
            }
            else if (p->matrix[i][j].estado == 1)
            {
                printf("\033[0;34m");
                printf("%c", tradutorlocal(p->matrix[i][j].estado));
                printf("\033[0m");
            }
            else
            {
                printf("\033[0;32m");
                printf("%c", tradutorlocal(p->matrix[i][j].estado));
                printf("\033[0m");
            }
        }
        printf("\n");
    }
}

// inserir pontos dos barcos
void insertlocalx(game *g, int x, int y, boat *b)
{
    g->matrix[x - 1][y - 1].estado = 1;
    g->matrix[x - 1][y - 1].barco = b;
}

//a peça do jogador foi acertada
void insertlocalB(game *g, int x, int y)
{
    g->matrix[x - 1][y - 1].estado = 2;
    g->matrix[x - 1][y - 1].barco->nplaces--;

    if ((g->matrix[x - 1][y - 1].barco->nplaces) == 0)
    {
        switch (g->matrix[x - 1][y - 1].barco->id)
        {
        case 't':
            printf("Ultron foi totalmente destruido!!\n");
            break;
        case 's':
            printf("Loki foi totalmente destruido!!\n");
            break;
        case 'r':
            printf("Thanos foi totalmente destruido!!\n");
            break;
        case 'l':
            printf("Venom foi totalmente destruido!!\n");
            break;
        case 'x':
            printf("Mysterio foi totalmente destruido!!\n");
            break;
        default:
            break;
        }
    }
    else
        printf("Um barco foi atingido\n");
}

//nao acertou em nenhum barco
void insertlocal0(game *g, int x, int y)
{
    g->matrix[x - 1][y - 1].estado = 3;
    printf("Não acertou em nenhum barco\n");
}

//verificar se tem la um barco
int ver(game *g)
{
    for (int i = 0; i < g->linhas; i++)
    {
        for (int j = 0; j < g->linhas; j++)
        {
            if (g->matrix[i][j].estado == 1)
                return 0;
        }
    }
    return 1;
}

// escolher o número de barcos para os dois jogadores
void barcos(int vec[], int limite, int start, int soma, int tamanho)
{
    char *valor = (char *)malloc(sizeof(char));
    while (soma > (tamanho / 25))
    {
        soma = 0;

        // manualmente
        if (start == 1)
        {
            printf("As peças têm de caber no tabuleiro \n\n");
            printf("Quantos barcos Ultron? (mínimo de 1 barco)\n");
            scanf("%s", valor);
            vec[0] = atoi(valor);
            while (vec[0] <= 0)
            {
                printf("Erro! O valor não satifaz a condição.\n");
                scanf("%s", valor);
                vec[0] = atoi(valor);
            }
            soma = soma + (vec[0]);

            printf("\nQuantos barcos Loki? (mínimo de 1 barco)\n");
            scanf("%s", valor);
            vec[1] = atoi(valor);
            while (vec[1] <= 0)
            {
                printf("Erro! O valor não satifaz a condição.\n");
                scanf("%s", valor);
                vec[1] = atoi(valor);
            }
            soma = soma + (vec[1]);
            printf("\nQuantos barcos Thanos? (mínimo de 1 barco)\n");
            scanf("%s", valor);
            vec[2] = atoi(valor);
            while (vec[2] <= 0)
            {
                printf("Erro! O valor não satifaz a condição.\n");
                scanf("%s", valor);
                vec[2] = atoi(valor);
            }
            soma = soma + (vec[2]);
            printf("\nQuantos barcos Venom? (mínimo de 1 barco)\n");
            scanf("%s", valor);
            vec[3] = atoi(valor);
            while (vec[3] <= 0)
            {
                printf("Erro! O valor não satifaz a condição.\n");
                scanf("%s", valor);
                vec[3] = atoi(valor);
            }
            soma = soma + (vec[3]);
            printf("\nQuantos barcos Mysterio? (mínimo de 1 barco)\n");
            scanf("%s", valor);
            vec[4] = atoi(valor);
            while (vec[4] <= 0)
            {
                printf("Erro! O valor não satifaz a condição.\n");
                scanf("%s", valor);
                vec[4] = atoi(valor);
            }
            soma = soma + (vec[4]);
        }

        // a partir da funçao random
        if (start == 2)
        {
            vec[0] = rand() % limite;
            while (vec[0] <= 0)
            {
                vec[0] = rand() % limite;
            }
            soma = soma + (vec[0]);

            vec[1] = rand() % limite;
            while (vec[1] <= 0)
            {
                vec[1] = rand() % limite;
            }
            soma = soma + (vec[1]);

            vec[2] = rand() % limite;
            while (vec[2] <= 0)
            {
                vec[2] = rand() % limite;
            }
            soma = soma + (vec[2]);

            vec[3] = rand() % limite;
            while (vec[3] <= 0)
            {
                vec[3] = rand() % limite;
            }
            soma = soma + (vec[3]);

            vec[4] = rand() % limite;
            while (vec[4] <= 0)
            {
                vec[4] = rand() % limite;
            }
            soma = soma + (vec[4]);
        }
    }
    system("clear");
}

// rodar o bitmap 90 graus
void rotateMatrix90(bit *p)
{
    for (int x = 0; x < 5 / 2; x++)
    {

        for (int y = x; y < 5 - x - 1; y++)
        {
            int temp = p->bitmap[x][y];

            p->bitmap[x][y] = p->bitmap[y][5 - 1 - x];

            p->bitmap[y][5 - 1 - x] = p->bitmap[5 - 1 - x][5 - 1 - y];

            p->bitmap[5 - 1 - x][5 - 1 - y] = p->bitmap[5 - 1 - y][x];

            p->bitmap[5 - 1 - y][x] = temp;
        }
    }
}

// rodar o bitmap 180 graus
void rotateMatrix180(bit *p)
{
    for (int i = 0; i < 5 / 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int temp = p->bitmap[i][j];
            p->bitmap[i][j] = p->bitmap[5 - i - 1][5 - j - 1];
            p->bitmap[5 - i - 1][5 - j - 1] = temp;
        }
    }
    for (int j = 0; j < 5 / 2; j++)
    {
        int temp = p->bitmap[5 / 2][j];
        p->bitmap[5 / 2][j] = p->bitmap[5 / 2][5 - j - 1];
        p->bitmap[5 / 2][5 - j - 1] = temp;
    }
}

// rodar o bitmap 270 graus
void rotateMatrix270(bit *p)
{
    for (int i = 0; i < 5 / 2; i++)
    {
        for (int j = i; j < 5 - i - 1; j++)
        {

            int temp = p->bitmap[i][j];
            p->bitmap[i][j] = p->bitmap[5 - 1 - j][i];
            p->bitmap[5 - 1 - j][i] = p->bitmap[5 - 1 - i][5 - 1 - j];
            p->bitmap[5 - 1 - i][5 - 1 - j] = p->bitmap[j][5 - 1 - i];
            p->bitmap[j][5 - 1 - i] = temp;
        }
    }
}

//inserir o barco no tabuleiro do jogador
int inserirbarco(game *g, bit *p, int tamanho, int start, boat *b, int i)
{

    int l = 0, m = 0, verificar = 1;

    for (int j = b->coord->linhas - 2; j <= b->coord->linhas + 2; j++)
    {
        m = 0;
        for (int i = b->coord->colunas - 2; i <= b->coord->colunas + 2; i++)
        {

            if (p->bitmap[l][m] == '1')
            {

                if (j <= 0 || i <= 0 || j > tamanho || i > tamanho)
                {
                    printf("Barco impossível de criar. (sai fora do tabuleiro)\n\n");
                    return 0;
                }
                else if (g->matrix[j - 1][i - 1].estado == 1)
                {
                    printf("Barco impossível de criar. (coincide com outro)\n\n");
                    return 0;
                }
            }
            m++;
        }
        l++;
    }

    l = 0;
    for (int j = b->coord->linhas - 2; j <= b->coord->linhas + 2; j++)
    {
        m = 0;
        for (int i = b->coord->colunas - 2; i <= b->coord->colunas + 2; i++)
        {
            if (p->bitmap[l][m] == '1')
            {
                insertlocalx(g, j, i, b);
            }

            m++;
        }
        l++;
    }

    if (start == 1 && i < 4)
    {
        tabelalocal(g);
        printf("\nPara passar ao próxima peça press 0: ");
        while (verificar != 0)
        {
            scanf("%d", &verificar);
        }
    }

    else if (start == 1 && i == 4)
    {
        tabelalocal(g);
        printf("\nPara passar para a próxima fase press 0: ");
        while (verificar != 0)
        {
            scanf("%d", &verificar);
        }
    }
    system("clear");

    return 1;
}

//escolher a rotaçao do barco o tipo do barco que vou colocar no tabuleiro
void chooseboats(game *p, int vec[], int tamanho, int start, char nome[])
{
    char *valor = (char *)malloc(sizeof(char));
    coordenadas *temp;
    boat *b;
    int n, x1, y1, rotation = 0, i = 0;
    ;

    if (start == 1)
    {
        printf("\n*** %s é a sua vez de escolher as coordenadas ***\n\n", nome);

        while (i < 5)
        {
            for (int j = 0; j < vec[i]; j++)
            {

                if (i == 0)
                {
                    printf("Colocar as peças do barco Ultron!\n\n");

                    printf("Que rotação quer no barco? (0º, 90º, 180º, 270º) : ");
                    scanf("%d", &rotation);
                    while (rotation != 0 && rotation != 90 && rotation != 180 && rotation != 270)
                    {
                        printf("Erro! O valor não satifaz a condição. Tente novamente.\n");
                        scanf("%d", &rotation);
                    }

                    printf("\nInsira um valor para a linha e um valor para a coluna: \n");
                    scanf("%s", valor);
                    x1 = atoi(valor);
                    scanf("%s", valor);
                    y1 = atoi(valor);
                    while (x1 > tamanho || y1 > tamanho || x1 <= 0 || y1 <= 0)
                    {

                        printf("Os valores têm de estar entre 0 e %d para caber no tabuleiro.\n", tamanho);
                        scanf("%s", valor);
                        x1 = atoi(valor);
                        scanf("%s", valor);
                        y1 = atoi(valor);
                        printf("\n");
                    }
                    printf("\n");
                    temp = buildcoord(x1, y1);
                    b = buildboat('t', temp);
                }

                else if (i == 1)
                {

                    printf("Colocar as peças do barco Loki!\n\n");

                    printf("Que rotação quer no barco? (0º, 90º, 180º, 270º): ");
                    scanf("%d", &rotation);
                    while (rotation != 0 && rotation != 90 && rotation != 180 && rotation != 270)
                    {
                        printf("Erro! O valor não satifaz a condição. Tente novamente.\n");
                        scanf("%d", &rotation);
                    }

                    printf("\nInsira um valor para a linha e um valor para a coluna: \n");
                    scanf("%s", valor);
                    x1 = atoi(valor);
                    scanf("%s", valor);
                    y1 = atoi(valor);
                    while (x1 > tamanho || y1 > tamanho || x1 <= 0 || y1 <= 0)
                    {

                        printf("Os valores têm de estar entre 0 e %d para caber no tabuleiro.\n", tamanho);
                        scanf("%s", valor);
                        x1 = atoi(valor);
                        scanf("%s", valor);
                        y1 = atoi(valor);
                    }
                    printf("\n");
                    temp = buildcoord(x1, y1);
                    b = buildboat('s', temp);
                }

                else if (i == 2)
                {
                    printf("Colocar as peças do barco Thanos!\n\n");
                    printf("Que rotação quer no barco? (0º, 90º, 180º, 270º): ");
                    scanf("%d", &rotation);
                    while (rotation != 0 && rotation != 90 && rotation != 180 && rotation != 270)
                    {
                        printf("Erro! O valor não satifaz a condição. Tente novamente.\n");
                        scanf("%d", &rotation);
                    }

                    printf("\nInsira um valor para a linha e um valor para a coluna: \n");
                    scanf("%s", valor);
                    x1 = atoi(valor);
                    scanf("%s", valor);
                    y1 = atoi(valor);
                    while (x1 > tamanho || y1 > tamanho || x1 <= 0 || y1 <= 0)
                    {

                        printf("Os valores têm de estar entre 0 e %d para caber no tabuleiro.\n", tamanho);
                        scanf("%s", valor);
                        x1 = atoi(valor);
                        scanf("%s", valor);
                        y1 = atoi(valor);
                    }
                    printf("\n");
                    temp = buildcoord(x1, y1);
                    b = buildboat('l', temp);
                }

                else if (i == 3)
                {
                    printf("Colocar as peças do barco Ultron!\n\n");
                    printf("Que rotação quer no barco? (0º, 90º, 180º, 270º): ");
                    scanf("%d", &rotation);
                    while (rotation != 0 && rotation != 90 && rotation != 180 && rotation != 270)
                    {
                        printf("Erro! O valor não satifaz a condição. Tente novamente.\n");
                        scanf("%d", &rotation);
                    }

                    printf("\nInsira um valor para a linha e um valor para a coluna: \n");
                    scanf("%s", valor);
                    x1 = atoi(valor);
                    scanf("%s", valor);
                    y1 = atoi(valor);
                    while (x1 > tamanho || y1 > tamanho || x1 <= 0 || y1 <= 0)
                    {

                        printf("Os valores têm de estar entre 0 e %d para caber no tabuleiro.\n", tamanho);
                        scanf("%s", valor);
                        x1 = atoi(valor);
                        scanf("%s", valor);
                        y1 = atoi(valor);
                    }
                    printf("\n");
                    temp = buildcoord(x1, y1);
                    b = buildboat('r', temp);
                }

                else
                {

                    printf("Colocar as peças do barco Mysterio!\n\n");
                    printf("Que rotação quer no barco? (0º, 90º, 180º, 270º): ");
                    scanf("%d", &rotation);
                    while (rotation != 0 && rotation != 90 && rotation != 180 && rotation != 270)
                    {
                        printf("Erro! O valor não satifaz a condição. Tente novamente.\n");
                        scanf("%d", &rotation);
                    }

                    printf("\nInsira um valor para a linha e um valor para a coluna: \n");
                    scanf("%s", valor);
                    x1 = atoi(valor);
                    scanf("%s", valor);
                    y1 = atoi(valor);
                    while (x1 > tamanho || y1 > tamanho || x1 <= 0 || y1 <= 0)
                    {

                        printf("Os valores têm de estar entre 0 e %d para caber no tabuleiro.\n", tamanho);
                        scanf("%s", valor);
                        x1 = atoi(valor);
                        scanf("%s", valor);
                        y1 = atoi(valor);
                    }
                    printf("\n");
                    temp = buildcoord(x1, y1);
                    b = buildboat('x', temp);
                }
                switch (rotation)
                {
                case 0:
                    break;
                case 90:
                    rotateMatrix90(b->bitmap);
                    break;
                case 180:
                    rotateMatrix180(b->bitmap);
                    break;
                case 270:
                    rotateMatrix270(b->bitmap);
                    break;
                default:
                    break;
                }
                n = inserirbarco(p, b->bitmap, tamanho, start, b, i);

                if (n == 0)
                {
                    j--;
                    destruiboattemp(b);
                    destruicoord(temp);
                }
            }
            i++;
        }
    }

    if (start == 2)
    {
        while (i < 5)
        {
            for (int j = 0; j < vec[i]; j++)
            {
                if (i == 0)
                {
                    x1 = 2 + rand() % (tamanho - 3);
                    y1 = 2 + rand() % (tamanho - 3);
                    while (x1 > (tamanho - 1) || y1 > (tamanho - 1) || x1 <= 0 || y1 <= 0)
                    {
                        x1 = 2 + rand() % (tamanho - 3);
                        y1 = 2 + rand() % (tamanho - 3);
                    }
                    temp = buildcoord(x1, y1);
                    b = buildboat('t', temp);
                }
                else if (i == 1)
                {
                    x1 = 2 + rand() % (tamanho - 3);
                    y1 = 2 + rand() % (tamanho - 3);
                    while (x1 > (tamanho - 1) || y1 > (tamanho - 1) || x1 <= 0 || y1 <= 0)
                    {
                        x1 = 2 + rand() % (tamanho - 3);
                        y1 = 2 + rand() % (tamanho - 3);
                    }
                    temp = buildcoord(x1, y1);
                    b = buildboat('s', temp);
                }
                else if (i == 2)
                {
                    x1 = 2 + rand() % (tamanho - 3);
                    y1 = 2 + rand() % (tamanho - 3);
                    while (x1 > (tamanho - 1) || y1 > (tamanho - 1) || x1 <= 0 || y1 <= 0)
                    {
                        x1 = 2 + rand() % (tamanho - 3);
                        y1 = 2 + rand() % (tamanho - 3);
                    }
                    temp = buildcoord(x1, y1);
                    b = buildboat('l', temp);
                }
                else if (i == 3)
                {
                    x1 = 2 + rand() % (tamanho - 3);
                    y1 = 2 + rand() % (tamanho - 3);
                    while (x1 > (tamanho - 1) || y1 > (tamanho - 1) || x1 <= 0 || y1 <= 0)
                    {
                        x1 = 2 + rand() % (tamanho - 3);
                        y1 = 2 + rand() % (tamanho - 3);
                    }
                    temp = buildcoord(x1, y1);
                    b = buildboat('r', temp);
                }
                else
                {
                    x1 = 2 + rand() % (tamanho - 3);
                    y1 = 2 + rand() % (tamanho - 3);
                    while (x1 > (tamanho - 1) || y1 > (tamanho - 1) || x1 <= 0 || y1 <= 0)
                    {
                        x1 = 2 + rand() % (tamanho - 3);
                        y1 = 2 + rand() % (tamanho - 3);
                    }
                    temp = buildcoord(x1, y1);
                    b = buildboat('x', temp);
                }

                rotation = rand() % lim;
                while (rotation < 0 || rotation > 4)
                    rotation = rand() % lim;

                if (rotation == 2)
                    rotateMatrix90(b->bitmap);
                else if (rotation == 3)
                    rotateMatrix180(b->bitmap);
                else if (rotation == 4)
                    rotateMatrix270(b->bitmap);

                n = inserirbarco(p, b->bitmap, tamanho, start, b, i);

                if (n == 0)
                {
                    j--;
                    destruiboattemp(b);
                    destruicoord(temp);
                }
            }

            i++;
        }
    }
}

//player 1 vs player 2 (jogo)
void ataque(game *m1, game *m2, char nome1[], char nome2[], int vec[], int tamanho)
{
    char *valor = (char *)malloc(sizeof(char));
    int x, y;
    int soma = vec[0] + vec[1] + vec[2] + vec[3] + vec[4];
    while ((ver(m1) == 0) && (ver(m2) == 0))
    {
        printf("O jogo no total tem %d peças, Ultron - %d , Loki - %d, Thanos - %d, Venom - %d e Mysterio - %d\n\n", soma, vec[0], vec[1], vec[2], vec[3], vec[4]);
        printf("O próprio tabuleiro do jogador %s:\n\n", nome1);
        tabelalocal(m1);
        printf("\n");
        printf("O tabuleiro dos ataques do jogador %s:\n\n", nome1);
        tabelashot(m1);
        printf("\n\n\n");
        printf("%s ataque o oponente: (x,y)\n", nome1);
        scanf("%s", valor);
        x = atoi(valor);
        scanf("%s", valor);
        y = atoi(valor);
        while (x > tamanho || y > tamanho || x <= 0 || y <= 0)
        {

            printf("Os valores têm de estar entre 0 e %d para caber no tabuleiro.\n", tamanho);
            scanf("%s", valor);
            x = atoi(valor);
            scanf("%s", valor);
            y = atoi(valor);
        }
        printf("\n");
        system("clear");

        if (m2->matrix[x - 1][y - 1].estado == 2)
        {
            printf("Essa posição do barco já foi atingida!\n");
        }

        else if (m2->matrix[x - 1][y - 1].estado == 3)
        {
            printf("Essa posição já foi jogada!\n");
        }

        else if (m2->matrix[x - 1][y - 1].estado == 1)
        {
            printf("\n");
            insertshotB(m1, x, y);
            insertlocalB(m2, x, y);
        }

        else
        {
            printf("\n");
            insertshot0(m1, x, y);
            insertlocal0(m2, x, y);
        }

        if ((ver(m2) == 1))
            break;

        int verificar = 1;
        printf("\nPara passar ao prox jogador press 0\n");
        while (verificar != 0)
        {
            scanf("%d", &verificar);
        }
        system("clear");

        //-------------------------------------------------------------------------------------------------------------------------

        printf("O jogo no total tem %d peças, Ultron - %d , Loki - %d, Thanos - %d, Venom - %d e Mysterio - %d\n\n", soma, vec[0], vec[1], vec[2], vec[3], vec[4]);
        ;
        printf("O próprio tabuleiro do jogador %s:\n\n", nome2);
        tabelalocal(m2);
        printf("\n");
        printf("O tabuleiro dos ataques do jogador %s:\n\n", nome2);
        tabelashot(m2);
        printf("\n \n \n");
        printf("%s ataque o oponente: (x,y)\n", nome2);
        scanf("%s", valor);
        x = atoi(valor);
        scanf("%s", valor);
        y = atoi(valor);
        while (x > tamanho || y > tamanho || x <= 0 || y <= 0)
        {

            printf("Os valores têm de estar entre 0 e %d para caber no tabuleiro.\n", tamanho);
            scanf("%s", valor);
            x = atoi(valor);
            scanf("%s", valor);
            y = atoi(valor);
        }
        printf("\n");
        system("clear");

        if (m1->matrix[x - 1][y - 1].estado == 2)
        {
            printf("Essa posição do barco já foi atingida!\n");
        }
        else if (m1->matrix[x - 1][y - 1].estado == 3)
        {
            printf("Essa posição já foi jogada!\n");
        }

        else if (m1->matrix[x - 1][y - 1].estado == 1)
        {
            printf("\n");
            insertshotB(m2, x, y);
            insertlocalB(m1, x, y);
        }

        else
        {
            printf("\n");
            insertshot0(m2, x, y);
            insertlocal0(m1, x, y);
        }

        if ((ver(m2) == 1))
            break;

        verificar = 1;
        printf("\nPara passar ao prox jogador press 0\n");
        while (verificar != 0)
        {
            scanf("%d", &verificar);
        }
        system("clear");
    }

    if (ver(m2) == 1)
        printf("O VECEDOR É %s!!\n", nome2);
    else
        printf("O VECEDOR É %s!!\n", nome1);
}