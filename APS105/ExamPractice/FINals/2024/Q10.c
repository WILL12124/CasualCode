#include <stdbool.h>
#include <stdlib.h>

typedef struct Q10
{
    int *arr;
    int lenth;
    int size;
} Databse;

// realloc

void addElement(Databse *x, int num)
{
    if (x->lenth == x->size)
    {
        int *newDatabase = realloc(x->arr, 2 * (x->size) * sizeof(int)); // 没有乘以sizeof int
        if (newDatabase == NULL)
            exit(1);
        x->arr = newDatabase;    // 扩容的是指针！
        x->size = (x->size) * 2; // don't forget this.
    }

    *((x->arr) + (x->lenth)) = num;
    x->lenth = (x->lenth) + 1;
}