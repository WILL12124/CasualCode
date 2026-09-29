#include <stdio.h>

void recurCount(int num)
{
    // base case
    num = num / 2;
    if (num == 0)
    {
        printf("Count Down: %d\n", num + 1);
        return;
    }

    // recursive case
    printf("Count Down: %d\n", num * 2 + 1);
    printf("Count Down: %d\n", num * 2);
    recurCount(num * 2 - 1);
    printf("Count Up: %d\n", num);
}

// OFFICIAL SOLUTION, SIMPLER
void ecurCount(int num)
{
    if (num == 0)
    {
        return;
    }
    else
    {
        printf("Count Down: %d\n", num);
        ecurCount(num - 1);
        if (num % 2 == 0)
            printf("Count Up: %d\n", num / 2); // it only folds when going back up
    }
}

int main(int argc, char const *argv[])
{
    recurCount(5);
    printf("%d", 5 % 5);
    return 0;
}
