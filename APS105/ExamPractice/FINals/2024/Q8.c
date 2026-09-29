#include <stdbool.h>

bool isMagicSquare(int n, int square[][n])
{
    int sum = 0;
    int tempSum = 0;
    // check if suqre?
    for (int i = 0; i < n; i++)
    {
        sum += square[0][i];
    }

    for (int i = 0; i < n; i++)
    {
        tempSum = 0;
        for (int j = 0; j < n; j++)
        {
            tempSum += square[i][j];
        }
        if (tempSum != sum)
            return false;
    }

    for (int i = 0; i < n; i++)
    {
        tempSum = 0;
        for (int j = 0; j < n; j++)
        {
            tempSum += square[j][i];
        }
        if (tempSum != sum)
            return false;
    }

    tempSum = 0;
    for (int i = 0; i < n; i++)
    {
        tempSum += square[i][i];
    }
    if (tempSum != sum)
        return false;

    tempSum = 0;
    for (int i = 0; i < n; i++)
    {
        tempSum += square[i][n - 1 - i]; // NOTE! INDEX 和size本身就差一
    }
    if (tempSum != sum)
        return false;

    return true;
}