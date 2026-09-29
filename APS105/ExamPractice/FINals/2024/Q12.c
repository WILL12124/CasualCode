typedef struct Q11
{
    int data;
    struct Q11 *next;
} Node;

typedef struct LS
{
    Node *head;
    Node *tail;
} LinkedList;

void remove(LinkedList *list, int value)
{
    if (list->head == NULL)
    {
        return;
    }

    Node *cur = list->head;
    Node *prev = NULL;

    while (cur->data != value && cur != NULL) // while 又错了，永远要先检查NULL
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL)
    {
        return;
    }

    if (prev == NULL)
    {
        list->head = cur->next;
        free(cur);
        // 特殊处理：如果删掉后链表空了，tail 也要置空
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        return;
    }
    prev->next = cur->next;
    free(cur);

    if (prev->next == NULL)
    {
        list->tail = prev;
    }
}