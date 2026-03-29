//
// Author: William Li
//

#include "reversi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 26

void setBoard(char board[][N], int n, char player, int row, int col);
void boardInit(char board[][N], int n);
void printBoard(char board[][N], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][N], int n, int row, int col, char colour, int deltaRow, int deltaCol);
char *availableMove(char board[][N], int n, char player);
bool isValid(char board[][N], int n, int row, int col, char player);
void placeDot(char board[][N], int n, int row, int col, char player);
void killTheGame(char board[][N], int n, char botPlay);
int checkScore(char board[][N], int n, int nr, int nc, char botPlayer);

int main(void)
{
    int n = 0;
    do
    {
        printf("Enter the board dimension: ");
        scanf(" %3d", &n);
    } while (n > 26 || n < 2);

    char board[N][N]; // 注意！！！macro在这一行之后才能看到
    boardInit(board, n);

    char botPlay = '\0', userPlay = '\0';
    printf("Computer plays (B/W): ");
    do
    {
        scanf(" %c", &botPlay);
    } while (botPlay != 'B' && botPlay != 'W');

    printBoard(board, n);

    if (botPlay == 'B')
    {
        killTheGame(board, n, botPlay);
        printBoard(board, n);
    }

    userPlay = (botPlay == 'B') ? 'W' : 'B';
    char userRow, userCol;
    while (1)
    {
        // Chekc win
        char *botMoves = availableMove(board, n, botPlay);
        char *userMoves = availableMove(board, n, userPlay);

        if (botMoves[0] == '\0' && userMoves[0] == '\0')
        {
            free(botMoves);
            free(userMoves); ////MEMORY LEAK!
            break;
        }

        if (userMoves[0] != '\0')
        {
            printf("Enter move for colour %c (RowCol): ", userPlay);
            scanf(" %c%c", &userRow, &userCol);
            if (isValid(board, n, userRow - 'a', userCol - 'a', userPlay))
            {
                placeDot(board, n, userRow - 'a', userCol - 'a', userPlay);
                printBoard(board, n);
            }
            else
            {
                printf("Invalid move.\n%c player wins.\n", botPlay);
                free(botMoves);
                free(userMoves);
                return 0;
            }
        }
        else
        {
            printf("%c player has no valid move.\n", userPlay);
        }

        free(botMoves);
        botMoves = availableMove(board, n, botPlay); // recalculate

        free(userMoves);
        userMoves = availableMove(board, n, userPlay);

        if (botMoves[0] == '\0' && userMoves[0] == '\0') // change due to new place
        {
            free(botMoves);
            free(userMoves);
            break;
        }
        if (botMoves[0] != '\0')
        {
            killTheGame(board, n, botPlay);
            printBoard(board, n);
        }
        else
        {
            printf("%c player has no valid move.\n", botPlay);
        }

        free(botMoves);
        free(userMoves);
    }
    int bCount = 0, wCount = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 'B')
                bCount++;
            else if (board[i][j] == 'W')
                wCount++;
        }
    if (bCount > wCount)
    {
        printf("B player wins.\n");
    }
    else if (wCount > bCount)
    {
        printf("W player wins.\n");
    }
    else
    {
        printf("Draw!\n");
    }
    return 0;
}

/*functions




*/
bool positionInBounds(int n, int row, int col)
{
    return (row >= 0 && row < n && col >= 0 && col < n);
}

bool checkLegalInDirection(char board[][N], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    char other = (colour == 'W') ? 'B' : 'W';
    bool foundOther = false;
    for (int num = 1; num < n; num++)
    {
        int nr = row + num * deltaRow;
        int nc = col + num * deltaCol;

        // don't go out of bound
        if (!positionInBounds(n, nr, nc))
        {
            break;
        }
        if (board[nr][nc] == other)
        {
            foundOther = true;
        }
        else if (board[nr][nc] == colour) ////CORE!!! next depend on prevoius
        {
            if (foundOther)
            {
                return true;
            }
            break;
        }
        else
        {
            break; // empty
        }
    }
    return false;
}

void boardInit(char board[][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 'U';
        }
    }
    int mid = n / 2;
    board[mid - 1][mid - 1] = 'W';
    board[mid - 1][mid] = 'B';
    board[mid][mid - 1] = 'B';
    board[mid][mid] = 'W';
}

void printBoard(char board[][N], int n)
{
    // print board legend
    printf("  ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", 'a' + i); // use char 'a' + i (ASCII code), not arrays
    }
    printf("\n");

    // print inner board
    for (int i = 0; i < n; i++)
    {
        printf("%c ", 'a' + i);
        for (int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

char *availableMove(char board[][N], int n, char player)
{
    char *p = calloc(2 * n * n, sizeof(char));
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isValid(board, n, i, j, player))
            {
                p[num] = 'a' + i;
                p[num + 1] = 'a' + j;
                num += 2;
            }
        }
    }
    p[num] = '\0';
    return p;
}

bool isValid(char board[][N], int n, int row, int col, char player)
{
    int deltaRows[] = {0, 1, 1, 1, 0, -1, -1, -1}; // star from 0 rad, counterclockwise
    int deltaCols[] = {1, 1, 0, -1, -1, -1, 0, 1};
    if ((board[row][col] != 'U') || (!positionInBounds(n, row, col)))
    {
        return false;
    }

    for (int i = 0; i < 8; i++)
    {
        if (checkLegalInDirection(board, n, row, col, player, deltaRows[i], deltaCols[i]))
        {
            return true;
        }
    }
    return false;
}

void placeDot(char board[][N], int n, int row, int col, char player)
{
    int deltaRows[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int deltaCols[] = {1, 1, 0, -1, -1, -1, 0, 1};
    char other = (player == 'W') ? 'B' : 'W';
    board[row][col] = player; // forgot to place piece

    for (int i = 0; i < 8; i++) // direction first!
    {
        if (checkLegalInDirection(board, n, row, col, player, deltaRows[i], deltaCols[i]))
        {
            // 遇到对手棋子, flip them
            for (int num = 1; num < n; num++)
            {
                int nr = row + num * deltaRows[i];
                int nc = col + num * deltaCols[i];
                if (!positionInBounds(n, nr, nc))
                    break;
                if (board[nr][nc] == other)
                {
                    board[nr][nc] = player; // 要确认有效才能反转
                }
                else
                {
                    break; // hit own piece or empty, stop
                }
            }
        }
    }
}

void killTheGame(char board[][N], int n, char botPlayer)
{
    int deltaRows[] = {0, 1, 1, 1, 0, -1, -1, -1}; // star from 0 rad, counterclockwise
    int deltaCols[] = {1, 1, 0, -1, -1, -1, 0, 1};
    char otherPlayer = (botPlayer == 'B') ? 'W' : 'B';
    int score = 0, best[2] = {-1, -1};

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            int tempScore = 0;
            if (board[row][col] != 'U')
            {
                continue;
            }
            for (int i = 0; i < 8; i++) // gos all 8 directions
            {
                int tempScoreDirection = 0;
                for (int num = 1; num <= n; num++) // extend in one direction
                {
                    int nr = row + num * deltaRows[i];
                    int nc = col + num * deltaCols[i];

                    if (!positionInBounds(n, nr, nc))
                    {
                        break;
                    }

                    if (board[nr][nc] == otherPlayer)
                    {
                        tempScoreDirection += positionWeight(n, row, col);
                    }
                    else if (board[nr][nc] == botPlayer)
                    {
                        tempScore += tempScoreDirection;
                        break; // end of this direction
                    }
                    else
                    {
                        break; // empty
                    }
                }
            }
            if (score < tempScore)
            {
                score = tempScore;
                best[0] = row;
                best[1] = col;
            }
        }
    }
    if (best[0] != -1)
    {
        placeDot(board, n, best[0], best[1], botPlayer);
        printf("Computer places %c at %c%c.\n", botPlayer, best[0] + 'a', best[1] + 'a');
    }
    else
    {
        printf("%c player has no valid move.\n", botPlayer);
    }
}

int positionWeight(int n, int row, int col)
{
    /////CORE!!!!we need a combination of bools to determine the status of place.
    bool isTopEdge = (row == 0);
    bool isBottomEdge = (row == n - 1);
    bool isLeftEdge = (col == 0);
    bool isRightEdge = (col == n - 1);

    // corners!
    bool isCorner = (isTopEdge || isBottomEdge) && (isLeftEdge || isRightEdge);
    if (isCorner)
    {
        return 100;
    }

    // x-squares
    bool isXSquare = (row == 1 || row == n - 2) && (col == 1 || col == n - 2);
    if (isXSquare)
    {
        return -20;
    }

    // c squares
    bool isCSquare = ((isTopEdge || isBottomEdge) && (col == 1 || col == n - 2)) ||
                     ((isLeftEdge || isRightEdge) && (row == 1 || row == n - 2));
    if (isCSquare)
    {
        return -10;
    }

    // edge
    if (isTopEdge || isBottomEdge || isLeftEdge || isRightEdge)
    {
        return 10;
    }

    // normal place
    return 1;
}