typedef struct node
{
    int data;
    struct node *next;
} Node;

/*Node *buildJoinedList(Node *firstList, Node *secondList)

{
    if (secondList == NULL) // 又tm忘了double equal！！！
    {
        secondList = firstList;
        return secondList;
    }

    Node *cur = secondList;
    for (; cur->next != NULL; cur = cur->next)
    {
        continue;
    }
    cur->next = firstList;
    return secondList;
}
    */