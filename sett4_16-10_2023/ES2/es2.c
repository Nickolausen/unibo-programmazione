#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <stdbool.h> 
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

// u = su = 0, d = giù = 1, l = sinistra = 2, d = destra = 3
char direction()
{
    srand(time(NULL));
    int r = rand() % 4;
    if(r == 0)
        return 'u';
    else if (r == 1)
        return 'd';
    else if (r == 2)
        return 'l';
    else
        return 'r';
}

bool compute_legal_moves(int position[2], char matrix[10][10])
{
    bool legalMoves = false;
    int x = position[0];
    int y = position[1];
    int countLegalMoves = 4;

    //controllo mosse possibili sull'asse orizzontale
    if(x-1 < 0 )
        countLegalMoves--;
    else
        if(matrix[x-1][y] != '.')
            countLegalMoves--;
    if(x+1 > 9)
        countLegalMoves--;
    else
        if(matrix[x+1][y] != '.')
            countLegalMoves--;
        
    //controllo mosse possibili sull'asse verticale
    if(y-1 < 0 )
        countLegalMoves--;
    else
        if(matrix[x][y-1] != '.')
            countLegalMoves--;
    if(y+1 > 9)
        countLegalMoves--;
    else
        if(matrix[x][y+1] != '.')
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
    do
    {
        bool legalMoves = compute_legal_moves(position, matrix);
        if(legalMoves)
        {
            bool legalMove = false;
            do
            {
                legalMove = false;
                char dir= direction();
                if(dir == 'u')
                {
                    if(position[1] - 1 > 0 && matrix[position[0]][position[1] - 1] == '.')
                    {
                        legalMove = true;
                        position[1]--;
                        matrix[position[1]][position[0]] = alphabet[alphabetPosition];
                        last_letter = alphabet[alphabetPosition++];
                    }
                }
                else if(dir == 'd')
                {
                    if(position[1] + 1 > 0 && matrix[position[0]][position[1] + 1] == '.')
                    {
                        legalMove = true;
                        position[1]++;
                        matrix[position[1]][position[0]] = alphabet[alphabetPosition];
                        last_letter = alphabet[alphabetPosition++];
                    }                      
                }
                else if(dir == 'l')
                {
                    if(position[0] - 1 > 0 && matrix[position[0] - 1][position[1]] == '.')
                    {
                        legalMove = true;
                        position[0]--;
                        matrix[position[1]][position[0]] = alphabet[alphabetPosition];
                        last_letter = alphabet[alphabetPosition++];
                    }                        
                }
                else
                {
                    if(position[0] + 1 > 0 && matrix[position[0] + 1][position[1]] == '.')
                    {
                        legalMove = true;
                        position[0]++;
                        matrix[position[1]][position[0]] = alphabet[alphabetPosition];
                        last_letter = alphabet[alphabetPosition++];
                    }                     
                }
            } while (!legalMove);
        }
        else
        {
            printf("\nNessuna mossa disponibile, gioco finito.");
            matrix_print(matrix);
            game = false;
        }
    } while (game && last_letter != 'Z');

    printf("\nGioco Finito!");
    matrix_print(matrix);
    
    return 0;
}