#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//: 10:24 10:30

void PrintReverse()
{
    // recursive case
    int num = 0;
    printf("Enter num: ");
    scanf(" %d", &num);

    // base case
    if (num == 0)
    {

        printf("Reversed Sequence: ");
        printf("0 ");
        return;
    }

    PrintReverse();
    printf("%d ", num);
}

int main(int argc, char const *argv[])
{
    char *i = NULL;
    *i;
    PrintReverse();
    return 0;
}
