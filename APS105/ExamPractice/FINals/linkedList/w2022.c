typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct linkedList
{
    Node *head;
} LinkedList;

void reorder(LinkedList *list)
{
    if (list->head == NULL || list->head->next == NULL)
        return;
    int numZero = findNumZero(list);

    Node *cur = list->head;
    Node *past = NULL;

    for (bool isNum = 0; isNum;)
    {
        isNum = 0;
        for (int i = 0; i < numZero;)
        {
            if (cur->data != 0)
                isNum = 1;
            if (cur->next->data == 0)
                i++;
            past = cur;
            cur = cur->next;
        }
        // shiff position
        Node *temp1 = past->next;
        Node *temp2 = cur->next;
        Node *temp3 = cur->next->next;
        past->next = cur->next;
        temp2->next = temp1;
        temp1->next = temp3;
    }
}