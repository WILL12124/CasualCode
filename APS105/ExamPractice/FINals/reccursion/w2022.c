#include <stdio.h>
#include <stdbool.h>

bool compareLines(const char *lineOne, const char *lineTwo)
{
    // recursive case
    if (lineOne[0] == '.' || lineOne[0] == ' ')
    {
        return compareLines(lineOne + 1, lineTwo);
    }

    if (lineTwo[0] == '.' || lineTwo[0] == ' ')
    {
        return compareLines(lineOne, lineTwo + 1);
    }

    // base case (顺序错误)
    if (lineOne[0] == '\0' && lineTwo[0] == '\0')
    {
        return true;
    }

    if (lineOne[0] == '\0' || lineTwo[0] == '\0')
    {
        return false;
    }

    // recusive case
    if (lineOne[0] == lineTwo[0])
    {
        return compareLines(lineOne + 1, lineTwo + 1);
    }

    return false; // characters differ
}