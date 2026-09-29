#include <stdio.h>
#include <string.h>

void mergeLInes(char *merged, char *lineOne, char *lineTwo)
{
    // base case
    if (*lineOne == '\0') // double equal!!!
    {
        strcpy(merged, lineTwo);
        return;
    }
    if (*lineTwo == '\0')
    {
        strcpy(merged, lineOne);
        return;
    }

    // recursive case
    if (*lineOne <= *lineTwo)
    {
        *merged = *lineOne;
        mergeLInes(merged + 1, lineOne + 1, lineTwo);
    }
    else
    {
        *merged = *lineTwo;
        mergeLInes(merged + 1, lineOne, lineTwo + 1);
    }
}