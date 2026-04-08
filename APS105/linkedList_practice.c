#include <stdio.h>
#include <stdlib.h>

typedef struct linkedList_practice
{
    float GPA;
    char grade;
    char name[20];
    struct linkedList_practice *next;
} Node;

typedef struct
{
    Node *head;
} list;

Node *createNode(int); // 如果需要传不同的数据类型，可以直接传node
void insertHead(list *, int);
void printList(list *);
void insertTail(list *, int);

int main(int argc, char const *argv[])
{
    Node student1 = {3.88, 'A', "William", NULL}; // LInk 为变量名称！！，还未declare
    student1.GPA = 3.92;
    printf("%.2f", student1.GPA);

    return 0;
}

Node *createNode(int val)
{
    Node *ptr = calloc(1, sizeof(Node)); // calloc必须两个东西都有
    if (ptr == NULL)
    {
        exit(1);
    }
    (*ptr).GPA = val;
    return ptr;
}

void insertHead(list *list, int val) // list不会自动塌缩为指针
{
    Node *temp = createNode(val);
    (*temp).next = (*list).head;
    (*list).head = temp;
}

void printList(list *list)
{
    Node *cur = (*list).head;
    while (cur != NULL) // special!!! 需要到cur指向null的时候才停止打印
    {
        printf("%.2f", (*cur).GPA);
        cur = cur->next;
    }
}