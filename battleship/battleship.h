#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int linhas;
    int colunas;
} coordenadas;

// struct do bitmap onde tem lá os barcos construidos
typedef struct
{
    char **bitmap;
} bit;

//constituiçao dos barcos e o tipo de barco que correspondem
typedef struct
{
    char id;
    coordenadas *coord;
    bit *bitmap;
    int nplaces;

} boat;

//struct que tem as duas matrizes de jogo lá dentro, em que cada cell tem dois valores diferentes
// uma para o valor da propria cell e outro para a cell do adversario
typedef struct
{
    // info local
    // 0 = empty, 1 = piece without being hitted, 2 = piece hitted, 3 = missed shot
    char estado;
    boat *barco;
    // info adversaria
    //0 = no shot, 1= shot that didn't hit, 2=shot that hit an enemy piece
    char shot;

} cell;

//
typedef struct
{

    cell **matrix;
    int linhas;
} game;

void destruicoord(coordenadas *b);
void destruibit(bit *b);
void destruiboat(boat *b);
void destruiboattemp(boat *b);
game *buildgame(int linhas);
coordenadas *buildcoord(int linhas, int colunas);
bit *buildbit();
boat *buildboat(char id, coordenadas *co);
void barnor(bit *p);
void tabela1(bit *p);
void barsq(bit *p);
void barcoll(bit *p);
void barcoxx(bit *p);
void barcoret(bit *p);
void defin();
char tradutorlocal(char c);
char tradutorshot(char c);
void tabelalocal(game *p);
void tabelashot(game *p);
void insertshot0(game *g, int x, int y);
void insertshotB(game *g, int x, int y);
void insertlocalx(game *g, int x, int y, boat *b);
void insertlocalB(game *g, int x, int y);
void insertlocal0(game *g, int x, int y);
int ver(game *g);
void barcos(int vec[], int limite, int start, int soma, int tamanho);
void rotateMatrix90(bit *p);
void rotateMatrix180(bit *p);
void rotateMatrix270(bit *p);
int inserirbarco(game *g, bit *p, int tamanho, int start, boat *b, int i);
void chooseboats(game *p, int vec[], int tamanho, int start, char nome[]);
void ataque(game *m1, game *m2, char nome1[], char nome2[], int vec[], int tamanho);