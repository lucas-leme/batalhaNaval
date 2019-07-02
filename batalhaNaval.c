#include <stdio.h>
#include <stdlib.h>

#define MAXLINHAS 20
#define MAXCOLUNAS 20
#define MAXNOME 64
#define TRUE 1
#define FALSE 0

#define SUBMARINO 'S'
#define DESTROYER 'D'
#define CRUZADOR 'C'
#define PORTA_AVIAO 'P'
#define HIDRO_AVIAO 'H'
#define BARCO 'B'
#define EXPLOSAO '*'
#define AGUA 'a'
#define RASTRO '.'
#define ESQUERDA 'e'
#define BAIXO 'b'
#define DIREITA 'd'
#define CIMA 'c'

void inicializa_gerador(int semente)
{
    srand(semente);
}

int no_aleatorio(int n)
{
    return 1 + (rand() / (RAND_MAX + 1.0)) * n;
}

void sorteie_posicao(int no_linhas, int no_colunas, int *linha, int *coluna)
{
    *linha = no_aleatorio(no_linhas);
    *coluna = no_aleatorio(no_colunas);
}

void leia_ate_barra_n(FILE *arq)
{
    char ch;

    fscanf(arq, "%c", &ch);
    while (ch != '\n')
    {
        fscanf(arq, "%c", &ch);
    }
}

int coluna_inicial_barco(char mapa[MAXLINHAS][MAXCOLUNAS])
{
    int i = 0;
    char b = mapa[1][0];
    while (b != BARCO)
    {
        i++;
        b = mapa[1][i];
    }
    return i;
}

void leia_mapa(int *no_linhas, int *no_colunas,
               char mapa[MAXLINHAS][MAXCOLUNAS], int *c_barco)
{
    FILE *arq;                  /* arquivo que contem o mapa */
    char nome_arquivo[MAXNOME]; /* nome do arquivo que contem o mapa */
    int no_l;                   /* numero de linha do mapa */
    int no_c;                   /* numero de colunas do mapa */
    int c_bar;                  /* coluna inicial do barco */
    int i;                      /* indice de linhas */
    int j;                      /* indice de colunas */
    int codigo;                 /* semente do gerador de numeros aleatorios */
    printf("MSG do QG: "
           "preparando para leitura do mapa.\n");

    printf("MSG do QG: "
           "forneca nome do arquivo que contem o mapa: ");
    scanf("%s", nome_arquivo);

    arq = fopen(nome_arquivo, "r");
    if (arq == NULL)
    {
        printf("MSG do QG: "
               "erro na abertura do arquivo %s.\n",
               nome_arquivo);
        printf("MSG do QG: "
               "MISSAO ABORTADA!\n\n");
        system("pause"); /* para WINDOWS */
        exit(-1);
    }
    printf("MSG do QG: "
           "arquivo %s foi encontrado.\n",
           nome_arquivo);

    printf("MSG do QG: "
           "mapa esta sendo lido do arquivo %s.\n",
           nome_arquivo);
    fscanf(arq, "%d %d %d", &no_l, &no_c, &codigo);
    leia_ate_barra_n(arq);
    printf("MSG do QG: "
           "mapa tem %d linhas e %d colunas.\n",
           no_l, no_c);
    printf("MSG do QG: "
           "codigo de ataque: %d\n",
           codigo);

    inicializa_gerador(codigo);

    for (i = 1; i <= no_l; i++)
    {
        for (j = 1; j <= no_c; j++)
        {
            fscanf(arq, "%c", &mapa[i][j]);
        }
        leia_ate_barra_n(arq); /* le os caracteres ate' o fim-de-linha*/
    }

    c_bar = coluna_inicial_barco(mapa);

    printf("MSG do QG: "
           "posicao inicial do barco e' (1,%d).\n",
           c_bar);

    fclose(arq);
    printf("MSG do QG: "
           "mapa lido com sucesso.\n");

    *no_linhas = no_l;
    *no_colunas = no_c;
    *c_barco = c_bar;
}

void escreva_mapa_arquivo(int no_linhas, int no_colunas,
                          char mapa[MAXLINHAS][MAXCOLUNAS])
{
    FILE *arq;
    int i; /* indice de linhas */
    int j; /* indice de colunas */
    int num_c;

    arq = fopen("secreto.dat", "w");
    if (arq == NULL)
    {
        printf("MSG do QG: "
               "erro na criacao do arquivo secreto.dat.\n");
        printf("MSG do QG: "
               "MISSAO ABORTADA!\n\n");
        exit(-1);
    }
    fprintf(arq, "    MAPA SECRETO DA BATALHA\n\n");
    fprintf(arq, "    no. linhas = %d     no. colunas = %d\n\n",
            no_linhas, no_colunas);
    printf("   ");
    for (num_c = 1; num_c <= no_colunas; num_c++)
    {
        fprintf(arq, "%4d", num_c);
    }
    fprintf(arq, "\n");

    for (num_c = 0; num_c < no_colunas; num_c++)
    {
        if (num_c == 0)
        {
            fprintf(arq, "    +");
        }
        fprintf(arq, "---+");
    }
    fprintf(arq, "\n");

    for (i = 1; i <= no_linhas; i++)
    {
        j = 1;
        while (j <= no_colunas)
        {
            if (j == 1)
            {
                fprintf(arq, "%3d ", i);
            }
            fprintf(arq, "| %c ", mapa[i][j]);

            j++;
        }
        fprintf(arq, "|\n");
        for (num_c = 0; num_c < no_colunas; num_c++)
        {
            if (num_c == 0)
            {
                fprintf(arq, "    +");
            }
            fprintf(arq, "---+");
        }
        fprintf(arq, "\n");
    }
    fprintf(arq, "\n\nFIM DO ARQUIVO.");
    fclose(arq);
}

void escreva_mapa_tela(int no_linhas, int no_colunas, char mapa[MAXLINHAS][MAXCOLUNAS])
{
    int i = 1, j = 1, num_c;
    printf("\n    MAPA DA BATALHA\n\n");
    printf("   ");
    for (num_c = 1; num_c <= no_colunas; num_c++)
    {
        printf("%4d", num_c);
    }
    printf("\n");

    for (num_c = 0; num_c < no_colunas; num_c++)
    {
        if (num_c == 0)
        {
            printf("    +");
        }
        printf("---+");
    }
    printf("\n");

    for (i = 1; i <= no_linhas; i++)
    {
        j = 1;
        while (j <= no_colunas)
        {
            if (j == 1)
            {
                printf("%3d ", i);
            }
            if (mapa[i][j] != SUBMARINO && mapa[i][j] != DESTROYER && mapa[i][j] != HIDRO_AVIAO && mapa[i][j] != PORTA_AVIAO && mapa[i][j] != CRUZADOR)
            {
                printf("| %c ", mapa[i][j]);
            }
            else
            {
                printf("|   ");
            }
            j++;
        }
        printf("|\n");
        for (num_c = 0; num_c < no_colunas; num_c++)
        {
            if (num_c == 0)
            {
                printf("    +");
            }
            printf("---+");
        }
        printf("\n");
    }
}

int main()
{
    int no_linhas, no_colunas, c_barco, l_barco, saida = FALSE;
    int mov_l, mov_c, imp_loop;
    char mapa[MAXLINHAS][MAXCOLUNAS];
    char comando;
    printf("MSG do QG: prepare-se para a missao.\n");

    leia_mapa(&no_linhas, &no_colunas, mapa, &c_barco);
    l_barco = 1;

    printf("MSG do QG: segue mapa da batalha.\n\n");

    escreva_mapa_tela(no_linhas, no_colunas, mapa);
    printf("MSG do QG: permissao para passear por cima das embarcacoes concedida.\n");
    printf("MSG do QG: a sua posicao e' (%d,%d).\n", l_barco, c_barco);
    printf("MSG do QG: selecione ('e'=esquerda,'b'=baixo,'d'=direita,'c'=cima,'f'=fim): ");
    scanf(" %c", &comando);

    imp_loop = 0;
    do
    {
        if (imp_loop != 0)
        {
            escreva_mapa_tela(no_linhas, no_colunas, mapa);
            printf("MSG do QG: selecione ('e'=esquerda,'b'=baixo,'d'=direita,'c'=cima,'f'=fim): ");
            scanf(" %c", &comando);
        }
        imp_loop = 1;

        mapa[l_barco][c_barco] = RASTRO;
        mov_l = l_barco;
        mov_c = c_barco;
        if (comando == CIMA && l_barco != 1)
        {
            l_barco--;
        }
        else if (comando == BAIXO && l_barco != no_linhas)
        {
            l_barco++;
        }
        else if (comando == ESQUERDA && c_barco != 1)
        {
            c_barco--;
        }
        else if (comando == DIREITA && c_barco != no_colunas)
        {
            c_barco++;
        }
        else if (comando == 'f')
        {
            escreva_mapa_tela (no_linhas,no_colunas,mapa);
            break;
        }
        mapa[l_barco][c_barco] = BARCO;
        escreva_mapa_arquivo(no_linhas, no_colunas, mapa);

        printf("MSG do QG: direcao escolhida: %c\n", comando);
        printf("MSG do QG: ");
        if (mov_l == l_barco && mov_c == c_barco)
        {
            printf("ficou parado em ");
        }
        else
        {
            printf("moveu-se para ");
        }
        printf("(%d,%d).\n", l_barco, c_barco);
        printf("MSG do QG: segue o mapa da batalha.\n");
    } while (1);

    printf("MSG do QG: PARABENS!!! Voce chegou a (%d,%d).\n", l_barco, c_barco);

    return 0;
}
