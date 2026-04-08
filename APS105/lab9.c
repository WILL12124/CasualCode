#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int id;
    char name[100];
    int severity;
    struct node *next; // 要用struct！！！
} patient;

// THIS IS USELESS!!!! ALREADY HAVE NEXT IN patient
/*typedef struct node
{
    patient patient;
    struct node *next;
} node;*/

bool insertPatient(patient **, patient);
bool deleteFront(patient **);
bool removePatient(patient **, int);
void printList(patient **);
bool freeList(patient **);

int main(int argc, char const *argv[])
{
    patient *= calloc(1, sizeof(patient)); // 一开始就要dynamic allocate
    patient **pHead = &patient_new;

    while (1)
    {
        char cmd = 0;
        char buffer[200] = {0}; // 不能设成NULL

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, " %c", &cmd); // 剩下的留在buffer当中
        if (cmd == 'A')              // 需要根据第一个字符决定做什么操作——这是个典型的命令解析模式
        {
            // scan 100-1 个 char； A不要双引号; fgets buffer里面的不会消失
            //; ！！！！！string no '&'！！！！！
            sscanf(buffer, " %*c %d %99s %d", &patient_new.id, patient_new.name, &patient_new.severity); //%*c to skip
            if (insertPatient(pHead, patient_new))
                printf("Patient <ID> Added.\n");
            else
                printf("Error: Patient <ID> already exists.\n");
        }

        else if (cmd == 'T')
        {
            if (deleteFront(pHead))
                printf("Patient <ID> Treated.\n");
            else
                printf("Queue is empty.\n");
        }
        else if (cmd == 'R')
        {
            sscanf(buffer, " %*c %d", &patient_new.id);
            if (removePatient(pHead, patient_new.id))
                printf("Patient <ID> Removed.\n");
            else
                printf("Error: Patient <ID> not found.\n");
        }
        else if (cmd == 'D')
        {
            printList(pHead);
        }
        else if (cmd == 'Q')
        {
            freeList(pHead);
            return 0;
        }
        else
        {
            printf("ERROR: Invalid Command\n");
            exit(1);
        }
    }

    return 0;
}

// 哥们你拷贝数据的环节呢？？？？
bool insertPatient(patient **head, patient patient_new)
{
    //  find if existing，别忘了检测头节点！！！（直接cur->next会跳过头）
    for (patient *cur = *head; cur != NULL; cur = cur->next)
    {
        // firts enter
        if (cur == NULL)
            break;
        if (cur->id == patient_new.id)
            return false;
    }

    // special case:
    if (*head == NULL || patient_new.severity > (*head)->severity)
    {
        patient *newPatient = calloc(1, sizeof(patient)); // at back
        newPatient->id = patient_new.id;
        newPatient->severity = patient_new.severity;
        memcpy(newPatient->name, patient_new.name, sizeof(patient_new.name));
        newPatient->next = *head;
        *head = newPatient;

        return true;
    }
    for (patient *cur = *(head);; cur = cur->next)
    {
        if (cur->next == NULL)
        {
            patient *newPatient = calloc(1, sizeof(patient)); // at back
            newPatient->id = patient_new.id;
            newPatient->severity = patient_new.severity;
            memcpy(newPatient->name, patient_new.name, sizeof(patient_new.name));
            newPatient->next = cur;
            cur = newPatient;
            break;
        }

        if ((*cur).severity >= patient_new.severity && (*cur->next).severity < patient_new.severity) // check
        {
            patient *newPatient = calloc(1, sizeof(patient));
            newPatient->id = patient_new.id;
            newPatient->severity = patient_new.severity;
            memcpy(newPatient->name, patient_new.name, sizeof(patient_new.name));
            newPatient->next = cur;
            cur = newPatient;
            break;
        }
    }

    return true;
}

bool deleteFront(patient **head)
{
    if (*head == NULL)
    {
        return false;
    }
    if ((*head)->next == NULL)
    {
        free(*head);
        *head = NULL;
        return true;
    }

    patient *temp = (*head)->next;
    free(*head);
    *head = temp;
    return true;
}

bool removePatient(patient **head, int ID)
{
    if (*head == NULL)
        return false;
    if ((*head)->id == ID)
    {
        patient *temp = (*head)->next;
        free(*head);
        *head = temp;
        return true;
    }
    for (patient *cur = *head; cur->next != NULL; cur = cur->next)
    {
        if ((*(cur->next)).id == ID) // dereference 优先级这里面最低的
        {
            patient *temp = cur->next->next;
            free(cur->next);
            cur->next = temp;
            return true;
        }
    }
    return false;
}

void printList(patient **head)
{
    if (*head == NULL)
        return;
    for (patient *cur = *head; cur != NULL; cur = cur->next)
    {
        printf("%s", (*cur).name);
        printf(" %d\n", (*cur).severity);
    }
    return;
}

bool freeList(patient **head)
{
    if (*head == NULL)
        return true;
    for (patient *cur = *head; cur != NULL;) // current is a pointer
    {
        patient *temp = cur->next;
        free(cur);
        cur = temp;
    }
    return true;
}