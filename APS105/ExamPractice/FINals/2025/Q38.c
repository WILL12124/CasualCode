// 9：09
#include <stdbool.h>

int nextRowWater(int rows, int cols, int arr[rows][cols], int row, bool isWater[cols], int num)
{
    bool isWaterNew[cols];
    memset(isWaterNew, 0, cols); // VLA 用此方法清零
    int newNum = 0;
    for (int j = 0; j < cols; j++)
    {
        if (arr[row][j] == 0)
        {
            isWaterNew[j] = 1;
            if (isWater[j] != 0 || isWater[j + 1] != 0 || isWater[j - 1] != 0)
            {
                // shao le xiapailian
                newNum++;
            }
            if (arr[row][j - 1] == 0 && isWaterNew[j - 1] == 1)
            {
                newNum++;
            }
        }
        else
        {
            newNum = 0;
        }
    }
    int prevNum = nextRowWater(rows, cols, arr, row + 1, isWaterNew, num);
    return prevNum + newNum;
}

int findLargestWaterBody(int rows, int cols, int arr[rows][cols])
{
    bool isWaterNew[cols] = {0};
    return nextRowWater(rows, cols, arr, 0, isWaterNew, 0);
}