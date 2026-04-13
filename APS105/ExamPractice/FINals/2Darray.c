#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char str[] = "apple";
    printf("%c", *str);
    return 0;
}

int **create2D(int rows, int cols)
{
    int **arr = calloc(rows, sizeof(int *));
    arr[0] = calloc(rows * cols, sizeof(int)); // arr 不等于arr[0]

    for (int i = 0; i < rows; i++)
    {
        arr[i] = arr[0] + cols * i;
    }
    return arr;
}
