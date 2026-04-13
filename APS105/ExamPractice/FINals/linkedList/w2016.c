#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int value;
    struct node *link;
} Node;

Node *createList(int arr[], int size)
{
    Node *head = calloc(1, sizeof(Node));
    head->value = arr[0];

    Node *cur = head;
    for (int i = 1; i < size; i++)
    {
        Node *temp = calloc(1, sizeof(Node));
        temp->value = arr[i];
        cur->link = temp;
        cur = cur->link;
    }
    return head;
}

void deleteNextNode(Node *past)
{
    if (past->link == NULL)
        return;
    Node *temp = past->link;
    past->link = past->link->link;
    free(temp);
}

void simplify(Node *head)
{
    if (head == NULL || head->link == NULL)
        return;

    Node *cur = head->link;
    Node *past = head;
    while (cur != NULL)
    {
        if (cur->value == past->value) // double equal!!!
        {
            deleteNextNode(past);
            cur = past->link;
            continue;
        }
        past = cur; // need to advance past
        cur = cur->link;
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {-2, -2, 1, 1, 3, 3, 5, 5, 5, 8, 9};
    CreateList(arr, sizeof(arr));
    return 0;
}
