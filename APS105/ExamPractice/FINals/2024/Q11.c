typedef struct Q11
{
    int data;
    struct Q11 *next;
} Node;

typedef struct LS
{
    Node *head;
} LinkedList;

bool isCycle(LinkedList *list)
{
    if (list->head == NULL || list->head->next == NULL)
    {
        return false;
    }

    Node *cur = list->head->next;
    while (cur != list->head && cur != NULL) // 逻辑错误！应该用&&
    {
        cur = cur->next;
    }

    if (cur == NULL)
        return false;
    else
        return true;
}