#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *link;
} Node;

Node *search(Node *head, int key)
{
    Node *current = head;
    // insert your code in the line below between the parentheses
    while (current != NULL && current->data != key)
    {
        current = current->link;
    }
    return current;
}

// 11:50

bool inPrevious(int data, int arr[])
{
    for (int i = 0; i < 100; i++)
    {
        if (arr[i] == data)
        {
            return true;
        }
    }
    return false;
}

void printDuplicates(Node *head)
{
    Node *cur = head;
    int arr[100] = {0};
    int i = 0;
    while (cur != NULL)
    {
        if (search(cur->link, cur->data))
        {
            if (!inPrevious(cur->data, arr)) // bool 返回注意正反
            {
                arr[i] = cur->data;
                printf("%d\n", cur->data);
                i++;
            }
        }
        cur = cur->link;
    }
}
