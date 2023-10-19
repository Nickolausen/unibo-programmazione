#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms * 1000)
#define CLEAR_CONSOLE system("cls")
#else
#include <unistd.h>
#define SLEEP(s) sleep(s)
#define CLEAR_CONSOLE system("clear")
#endif
#define LINE_SPLITTER puts("\n\n----------")

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

void matrix_print(char matrix[10][10])
{
    printf("\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrix_fill(char matrix[10][10])
{ 
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            matrix[i][j] = '.';
        }
    }
}

bool compute_legal_moves(int position[2], char matrix[10][10])
{
    bool legalMoves = false;
    int x = position[1];
    int y = position[0];
    int countLegalMoves = 4;

    //controllo mosse possibili sull'asse orizzontale
    if(x-1 < 0 )
        countLegalMoves--;
    else
        if(matrix[y][x-1] != '.')
            countLegalMoves--;
    if(x+1 > 9)
        countLegalMoves--;
    else
        if(matrix[y][x+1] != '.')
            countLegalMoves--;
        
    //controllo mosse possibili sull'asse verticale
    if(y-1 < 0 )
        countLegalMoves--;
    else
        if(matrix[y-1][x] != '.')
            countLegalMoves--;
    if(y+1 > 9)
        countLegalMoves--;
    else
        if(matrix[y+1][x] != '.')
            countLegalMoves--;

    if(countLegalMoves > 0)
        legalMoves = true;
    return legalMoves;
}

int main()
{
    srand(time(NULL));
    char matrix[10][10];
    bool game = true;
    char last_letter = 'A';
    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int alphabetPosition = 1;
    int position[2] = {0,0};
    matrix_fill(matrix);
    matrix[0][0] = last_letter;

    char message[100] = "Gioco finito!";

    do
    {
        bool legalMoves = compute_legal_moves(position, matrix);
        if(legalMoves)
        {
            int x, y;
            x = position[1];
            y = position[0];
            bool legalMove = false;
            do
            {
                legalMove = false;
                char dir;
                // u = su = 0, d = giù = 1, l = sinistra = 2, r = destra = 3
                int r = rand() % 4;
                if(r == 0)
                    dir = 'u';
                else if (r == 1)
                    dir = 'd';
                else if (r == 2)
                    dir = 'l';
                else
                    dir = 'r';   

                if(dir == 'u')
                {
                    if(y - 1 > 0 && matrix[y-1][x] == '.')
                    {
                        legalMove = true;
                        y = --position[0];
                    }
                }
                else if(dir == 'd')
                {
                    if(y + 1 < 9 && matrix[y+1][x] == '.')
                    {
                        legalMove = true;
                        y = ++position[0];
                        
                    }                      
                }
                else if(dir == 'l')
                {
                    if(x - 1 > 0 && matrix[y][x-1] == '.')
                    {
                        legalMove = true;
                        x = --position[1];
                    }                        
                }
                else
                {
                    if(x + 1 < 9 && matrix[y][x+1] == '.')
                    {
                        legalMove = true;
                        x = ++position[1];
                    }                     
                }
            } while (!legalMove);
            matrix[y][x] = alphabet[alphabetPosition];
            last_letter = alphabet[alphabetPosition++];
        }
        else
        {
            strcpy(message, "Nessuna mossa disponibile! Gioco terminato.");
            game = false;
        }4
    } while (game && last_letter != 'Z');

    printf("%s", message);
    matrix_print(matrix);

    return 0;
}