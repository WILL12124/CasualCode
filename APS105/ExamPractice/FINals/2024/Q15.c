#include <stdlib.h>

typedef struct Q11
{
    int data;
    struct Q11 *next;
} Node;

typedef struct LS
{
    Node *head;
} LinkedList;

bool fixOrder(LinkedList *list)
{
    if (list->head == NULL || list->head->next == NULL)
    {
        return false;
    }

    Node *cur = list->head;
    Node *prev = NULL;
    while (cur->next != NULL && (cur->data) <= (cur->next->data)) // while 又写反了！！！
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur->next == NULL)
    {
        return false;
    }

    if (prev == NULL)
    {
        list->head = cur->next;
        cur->next = cur->next->next; // 考虑头问题的时候不能只看两个
        list->head->next = cur;
    }
    else
    {
        prev->next = cur->next;
        cur->next = cur->next->next;
        prev->next->next = cur;
    }

    return true;
}