#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

typedef struct employee
{
    int ID;
    char *name;
} Employee;

int main(void)
{
    Employee *employees = malloc(sizeof(Employee) * SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        scanf("%s", &employees[i].name);
        scanf("%d", &employees[i].ID);
    }
    for (int i = 0; i < SIZE; i++)
    {
        printf("Employee %d\n Name: %s\n ID: %d\n", i + 1, employees[i].name, employees[i].ID);
    }
    // Assume freeData function is called here to free any dynamically allocated space
    return 0;
}