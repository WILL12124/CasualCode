#include <stdbool.h>
#include <string.h>

bool isStringRotation(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL || *s1 == '\0' || *s2 == '\0')
    {
        return false;
    }
    // check if equal!!!
    if (strlen(s1) != strlen(s2))
    {
        return false;
    }

    int sumlen = strlen(s1) + strlen(s2) + 5;
    char merge[sumlen];
    strcpy(merge, s2);
    strcat(merge, s2);
    if (strstr(merge, s1) != NULL)
    {
        return true;
    }
    else
        return false;
}