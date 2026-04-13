#include <stdio.h>
#include <stdbool.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

typedef struct list
{
    node *head;
} list;

// CREATE NODE: FINAL VER
node *createNode(int val)
{
    node *newNode = calloc(1, sizeof(node));
    if (newNode == NULL)
        exit(1);
    newNode->number = val;
    return newNode;
}

// INSERT FRONT: FINAL VER
void InsertFront(list *plist, int val)
{
    node *pNewNode = calloc(1, sizeof(node));
    pNewNode->next = plist->head;
    plist->head = pNewNode;
    return;
}

// PRINT LIST: FINAL VER
void PrintList(list *plist)
{
    node *cur = plist->head;
    while (cur != NULL)
    {
        printf("%d ->- ", cur->number);
        cur = cur->next;
    }
}

// INSERT BACK: FINAL VER
void InsertBack(list *plist, int val)
{
    node *pNewNode = createNode(val);

    if (plist->head == NULL) // segmentation fault!!!
    {
        plist->head = pNewNode;
        return;
    }

    node *cur = plist->head;
    while (cur->next != NULL) // stop at last element
    {
        cur = cur->next;
    }
    cur->next = pNewNode;
}

node *FindNode(list *plist, int val)
{
    if (plist->head == NULL)
        return NULL;
    node *cur = plist->head;
    while (cur != NULL) // this is a do loop, not a traverse loop
    {
        if (cur->number == val)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void DeleteFront(list *plist)
{
    if (plist->head == NULL)
    {
        return;
    }
    node *temp = plist->head->next;
    free(plist->head);
    plist->head = temp;
    return;
}

void DeleteBack(list *plist)
{
    if (plist->head == NULL)
    {
        return;
    }

    node *cur = plist->head;
    node *past = NULL; // set to null to avoid unintialized!
    while (cur->next != NULL)
    {
        past = cur;
        cur = cur->next;
    }

    if (past == NULL)
        plist->head = NULL; // only one node in list
    else
        past->next = NULL;
    free(cur);
}

bool InsertOrderedList(list *plist, int val) // eg increasing order
{
    node *pNewNode = createNode(val);

    // insert at front (empty list or smallest value)
    if (plist->head == NULL || plist->head->number > val) // lazy evaluation
    {
        pNewNode->next = plist->head;
        plist->head = pNewNode;
        return true;
    }

    node *cur = plist->head;
    while (cur->next != NULL && cur->next->number < val) // 小于
    {
        cur = cur->next;
    }
    pNewNode->next = cur->next;
    cur->next = pNewNode;
    return true;
}

bool DeleteVal(list *plist, int val)
{
    if (plist->head == NULL)
        return false;

    node *cur = plist->head;
    node *past = NULL;
    while (cur->next != NULL && cur->next->number != val) ////!!!!IF LAST ONE ISN'T DON'T DELETE
    {
        past = cur;
        cur = cur->next;
    }

    if (cur == NULL) // value not found
        return false;

    if (past == NULL)
        plist->head = cur->next; // don't bridge list off
    else
        past->next = cur->next;
    free(cur);
    return true;
}