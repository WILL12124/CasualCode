//
// Note: ai is used in combining part1 and part2 code
//
#define N 26
#define INF 999999
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stddef.h>
#include "liblab8part2.h"

// time record
static struct timeval searchStartTime;
static double timeLimit = 0.94; // criteria seconds
static bool searchEnd;          // set to true when time runs out

// 获取距离 start 时间点过了多少秒的辅助函数
double getTimeElapsed(struct timeval start)
{
    struct timeval current; // not a new data type, included in lib
    gettimeofday(&current, NULL);
    return (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0;
}

// Forward declarations for functions already in your minimax file
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(const char board[][N], int n, int row, int col, char colour, int deltaRow, int deltaCol);
bool isValid(const char board[][N], int n, int row, int col, char player);
bool hasValidMove(const char board[][N], int n, char player);
void copyBoard(const char src[][N], char dest[][N], int n);
void placeDotSimulation(char board[][N], int n, int row, int col, char player);
int makeMove(const char board[][26], int n, char turn, int *row, int *col);
int minLevel(char board[][N], int n, char currentPlayer, char botPlayer, int depth, int alpha, int beta);
int maxLevel(char board[][N], int n, char currentPlayer, char botPlayer, int depth, int alpha, int beta);

// ---------- Helper functions matching the reference code ----------

void boardInit(char board[][N], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 'U';
    int mid = n / 2;
    board[mid - 1][mid - 1] = 'W';
    board[mid - 1][mid] = 'B';
    board[mid][mid - 1] = 'B';
    board[mid][mid] = 'W';
}

void printBoard(char board[][N], int n)
{
    printf("  ");
    for (int i = 0; i < n; i++)
        printf("%c", 'a' + i);
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%c ", 'a' + i);
        for (int j = 0; j < n; j++)
            printf("%c", board[i][j]);
        printf("\n");
    }
}

// Same as placeDotSimulation but used for the "real" board (identical logic)
void placeDot(char board[][N], int n, int row, int col, char player)
{
    placeDotSimulation(board, n, row, col, player);
}

// Returns a dynamically allocated string of available moves (row-col pairs as chars)
char *availableMove(char board[][N], int n, char player)
{
    char *p = calloc(2 * n * n + 1, sizeof(char));
    int num = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (isValid(board, n, i, j, player))
            {
                p[num] = 'a' + i;
                p[num + 1] = 'a' + j;
                num += 2;
            }
    p[num] = '\0';
    return p;
}

// ---------- Bot wrapper: calls makeMove then places the piece ----------

void botMakeMove(char board[][N], int n, char botPlayer)
{
    int row = -1, col = -1;
    makeMove(board, n, botPlayer, &row, &col);
    if (row != -1 && col != -1)
    {
        placeDot(board, n, row, col, botPlayer);
        printf("Computer places %c at %c%c.\n", botPlayer, row + 'a', col + 'a');
    }
    else
    {
        printf("%c player has no valid move.\n", botPlayer);
    }
}

// ---------- Main ----------

int main(void)
{
    int n = 0;
    do
    {
        printf("Enter the board dimension: ");
        scanf(" %3d", &n);
    } while (n > 26 || n < 2);

    char board[N][N];
    boardInit(board, n);

    char botPlay = '\0', userPlay = '\0';
    printf("Computer plays (B/W): ");
    do
    {
        scanf(" %c", &botPlay);
    } while (botPlay != 'B' && botPlay != 'W');

    printBoard(board, n);

    // If bot is Black, it moves first
    if (botPlay == 'B')
    {
        botMakeMove(board, n, botPlay);
        printBoard(board, n);
    }

    userPlay = (botPlay == 'B') ? 'W' : 'B';
    char userRow, userCol;

    while (1)
    {
        // Check if either player can move
        char *botMoves = availableMove(board, n, botPlay);
        char *userMoves = availableMove(board, n, userPlay);

        if (botMoves[0] == '\0' && userMoves[0] == '\0')
        {
            free(botMoves);
            free(userMoves);
            break;
        }

        // --- User's turn ---
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

        // Recalculate available moves after user's turn
        free(botMoves);
        botMoves = availableMove(board, n, botPlay);

        free(userMoves);
        userMoves = availableMove(board, n, userPlay);

        if (botMoves[0] == '\0' && userMoves[0] == '\0')
        {
            free(botMoves);
            free(userMoves);
            break;
        }

        // --- Bot's turn ---
        if (botMoves[0] != '\0')
        {
            botMakeMove(board, n, botPlay);
            printBoard(board, n);
        }
        else
        {
            printf("%c player has no valid move.\n", botPlay);
        }

        free(botMoves);
        free(userMoves);
    }

    // --- Final score ---
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
        printf("B player wins.\n");
    else if (wCount > bCount)
        printf("W player wins.\n");
    else
        printf("Draw!\n");

    return 0;
}

int minLevel(char board[][N], int n, char currentPlayer, char botPlayer, int depth, int alpha, int beta);

bool positionInBounds(int n, int row, int col)
{
    return (row >= 0 && row < n && col >= 0 && col < n);
}

bool checkLegalInDirection(const char board[][N], int n, int row, int col, char colour, int deltaRow, int deltaCol)
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

bool isValid(const char board[][N], int n, int row, int col, char player)
{
    int deltaRows[] = {0, 1, 1, 1, 0, -1, -1, -1}; // star from 0 rad, counterclockwise
    int deltaCols[] = {1, 1, 0, -1, -1, -1, 0, 1};
    if ((!positionInBounds(n, row, col)) || (board[row][col] != 'U')) //////note! must check before accessing
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
bool hasValidMove(const char board[][N], int n, char player)
{
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (isValid(board, n, r, c, player))
                return true;
        }
    }
    return false;
}

// --- 2. Board Simulation Tools ---

void copyBoard(const char src[][N], char dest[][N], int n)
{
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            dest[r][c] = src[r][c];
        }
    }
}

// Places a piece and flips opponent pieces on a simulated board
void placeDotSimulation(char board[][N], int n, int row, int col, char player)
{
    int deltaRows[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int deltaCols[] = {1, 1, 0, -1, -1, -1, 0, 1};
    char other = (player == 'W') ? 'B' : 'W';

    board[row][col] = player;

    for (int i = 0; i < 8; i++)
    {
        if (checkLegalInDirection((const char (*)[N])board, n, row, col, player, deltaRows[i], deltaCols[i]))
        {
            for (int num = 1; num < n; num++)
            {
                int nr = row + num * deltaRows[i];
                int nc = col + num * deltaCols[i];
                if (board[nr][nc] == other)
                {
                    board[nr][nc] = player; // Flip
                }
                else
                {
                    break;
                }
            }
        }
    }
}

// weight matrix (classic)
int getPositionWeight(int n, int row, int col, const char board[][N], char botPlayer)
{
    // classic weight matrix (from google)
    int weights[4][4] = {
        {100, -20, 10, 5},
        {-20, -50, -2, -2},
        {10, -2, 5, 1},
        {5, -2, 1, 1}};

    // mirror to the top-left quadrant
    int r = (row < n / 2) ? row : (n - 1 - row);
    int c = (col < n / 2) ? col : (n - 1 - col);

    if (r > 3) ////如果在整个内部，直接是1
    {
        r = 3;
    }
    if (c > 3)
    {
        c = 3;
    }

    int weight = weights[r][c]; // 先拿到基础权重（比如原本是 -20 或 -50）

    // 一旦角是我的，旁边的格子就是香饽饽
    if (board[0][0] == botPlayer) // 检查左上角
    {
        if (row == 0 && col == 1)
            return 30; // 紧挨左上角的水平边缘
        if (row == 1 && col == 0)
            return 30;
        if (row == 1 && col == 1)
            return 30;
    }

    if (board[0][n - 1] == botPlayer)
    {
        if (row == 0 && col == n - 2)
            return 30;
        if (row == 1 && col == n - 1)
            return 30;
        if (row == 1 && col == n - 2)
            return 30;
    }

    if (board[n - 1][0] == botPlayer)
    {
        if (row == n - 1 && col == 1)
            return 30;
        if (row == n - 2 && col == 0)
            return 30;
        if (row == n - 2 && col == 1)
            return 30;
    }

    if (board[n - 1][n - 1] == botPlayer)
    {
        if (row == n - 1 && col == n - 2)
            return 30;
        if (row == n - 2 && col == n - 1)
            return 30;
        if (row == n - 2 && col == n - 2)
            return 30;
    }

    return weight;
}

// evaluate the board using weighted score and see which has a better hand
int evaluateBoard(const char board[][N], int n, char botPlayer)
{
    char userPlayer = (botPlayer == 'W') ? 'B' : 'W';

    int myPieces = 0, oppPieces = 0, emptyCount = 0;
    int positionalScore = 0;

    // static weight
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (board[r][c] == botPlayer)
            {
                myPieces++;
                positionalScore += getPositionWeight(n, r, c, board, botPlayer);
            }
            else if (board[r][c] == userPlayer)
            {
                oppPieces++;
                positionalScore -= getPositionWeight(n, r, c, board, botPlayer); // also need to minimise opponent
            }
            else
            {
                emptyCount++;
            }
        }
    }

    // calculate mobility
    int myValidMoves = 0, oppValidMoves = 0;
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (isValid(board, n, r, c, botPlayer))
                myValidMoves++;
            if (isValid(board, n, r, c, userPlayer))
                oppValidMoves++;
        }
    }

    // phased strategy
    int finalScore = 0;

    if (emptyCount > (n * n * 2 / 3)) // 开局阶段 (前 1/3)
    {
        // 开局极其看重行动力，且不鼓励多吃子
        finalScore = 50 * (myValidMoves - oppValidMoves) + 10 * positionalScore - 15 * (myPieces - oppPieces);
    }
    else if (emptyCount > (n * n / 4)) // 中局阶段
    {
        // 中局平衡行动力与阵地战（静态权重）
        finalScore = 40 * (myValidMoves - oppValidMoves) + 30 * positionalScore + 0 * (myPieces - oppPieces);
    }
    else // 残局阶段 (最后 1/4)
    {
        // 残局什么都不管了，哪怕送角落，只要最终子多就行
        finalScore = 100 * (myPieces - oppPieces) + 10 * positionalScore + 10 * (myValidMoves - oppValidMoves);
    }

    return finalScore;
}

// Alpha-Beta Minimax!!!!

int maxLevel(char board[][N], int n, char currentPlayer, char botPlayer, int depth, int alpha, int beta)
{
    //
    // TIME CHECK
    //
    if (getTimeElapsed(searchStartTime) >= timeLimit)
    {
        searchEnd = true;
        return evaluateBoard(board, n, botPlayer);
    }

    char nextPlayer = (currentPlayer == 'W') ? 'B' : 'W';
    int best = -INF;

    // base case
    if (depth == 0)
    {
        return evaluateBoard(board, n, botPlayer); // always from bot's perspective
    }

    // Check if the current player (Max) has valid moves
    if (!hasValidMove(board, n, currentPlayer))
    {
        // Max has no moves. Min moves?
        if (!hasValidMove(board, n, nextPlayer))
        {
            // Game over
            return evaluateBoard(board, n, botPlayer);
        }
        else
        {
            // Max skips their turn. Pass control to Min without decreasing depth.
            return minLevel(board, n, nextPlayer, botPlayer, depth, alpha, beta);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!isValid(board, n, i, j, currentPlayer)) // check legality
                continue;
            char nextBoard[N][N];
            copyBoard(board, nextBoard, n); // correct argument order
            placeDotSimulation(nextBoard, n, i, j, currentPlayer);
            int score = minLevel(nextBoard, n, nextPlayer, botPlayer, depth - 1, alpha, beta);
            if (searchEnd)
                return best;
            if (score > best)
                best = score;
            if (best > alpha)
                alpha = best;
            if (alpha >= beta)
                return best; // prune
        }
    }
    return best; // don't forget this!
}

int minLevel(char board[][N], int n, char currentPlayer, char botPlayer, int depth, int alpha, int beta)
{
    //
    // TIME CHECK
    //
    if (getTimeElapsed(searchStartTime) >= timeLimit)
    {
        searchEnd = true;
        return evaluateBoard(board, n, botPlayer);
    }

    char nextPlayer = (currentPlayer == 'W') ? 'B' : 'W';
    int worst = INF;

    // 最小更改：同样去掉了这里的 || !hasValidMove(...)
    if (depth == 0)
    {
        return evaluateBoard(board, n, botPlayer); // always from bot's perspective
    }

    // 2. Check if the current player (Min) has valid moves
    if (!hasValidMove(board, n, currentPlayer))
    {
        // Min has no moves. Does Max have moves?
        if (!hasValidMove(board, n, nextPlayer))
        {
            // Neither player has moves. Game over. Evaluate and return.
            return evaluateBoard(board, n, botPlayer);
        }
        else
        {
            // Min skips their turn. Pass control to Max without decreasing depth.
            return maxLevel(board, n, nextPlayer, botPlayer, depth, alpha, beta);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!isValid(board, n, i, j, currentPlayer)) // check legality
                continue;
            char nextBoard[N][N];
            copyBoard(board, nextBoard, n); // correct argument order
            placeDotSimulation(nextBoard, n, i, j, currentPlayer);
            int score = maxLevel(nextBoard, n, nextPlayer, botPlayer, depth - 1, alpha, beta);
            if (searchEnd)
                return worst;
            if (score < worst)
                worst = score;
            if (worst < beta)
                beta = worst;
            if (alpha >= beta)
                return worst; // prune
        }
    }
    return worst; // return after full search
}

int makeMove(const char board[][26], int n, char current, int *row, int *col)
{
    gettimeofday(&searchStartTime, NULL);
    searchEnd = false; // global var, set to false!
    int bestScore = -INF;
    int bestRow = -1;
    int bestCol = -1;

    int maxDepth = 8;

    char opponent = (current == 'W') ? 'B' : 'W';

    for (int depth = 1; depth <= maxDepth; depth++) // depth start at 1
    {
        int currentBestRow = -1, currentBestCol = -1;
        int currentBestScore = -INF;
        searchEnd = false;
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                // Root Node (need to remember coordinates)
                if (isValid(board, n, r, c, current))
                {
                    char nextBoard[N][N];
                    copyBoard(board, nextBoard, n);
                    placeDotSimulation(nextBoard, n, r, c, current);

                    // Opponent moves next, minimize bot's score
                    int moveScore = minLevel(nextBoard, n, opponent, current,
                                             depth - 1, -INF, INF);
                    if (moveScore > currentBestScore)
                    {
                        currentBestScore = moveScore;
                        currentBestRow = r;
                        currentBestCol = c;
                    }
                }
                if (searchEnd)
                {
                    break;
                }
            }
            if (searchEnd)
            {
                break;
            }
        }
        if (!searchEnd)
        {
            // This depth completed fully, save the result
            bestScore = currentBestScore;
            bestRow = currentBestRow;
            bestCol = currentBestCol;
        }
        else
        {
            // this depth was incomplete — discard this results, keep previous
            break;
        }
        // If we're already near the time limit, don't start a deeper search
        if (getTimeElapsed(searchStartTime) >= timeLimit * 0.5)
            break;
    }
    if (bestRow != -1 && bestCol != -1)
    {
        *row = bestRow;
        *col = bestCol;
    }
    return 0;
}
