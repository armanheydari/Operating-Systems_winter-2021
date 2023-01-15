#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct Node
{
    char *value;
    int key;
    struct Node *next;
};

void Add(struct Node **head ,char value[], int key)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    new_node->key = key;
    new_node->value = (char *)malloc(sizeof(char *));
    new_node->next = *head;
    strcpy(new_node->value, value);
    *head = new_node;
}

void PrintList(struct Node **head)
{
    struct Node *ptr = *head;
    printf("\n[ ");
    while (ptr != NULL)
    {
        printf(" (%d,%s) ", ptr->key, ptr->value);
        ptr = ptr->next;
    }
    printf(" ]");
}

void Bubble_sort(struct Node **head)
{
    struct Node *ptr_i = *head, *ptr_j = *head, *ptr_j_n= *head;
    int temp[3];
    while (ptr_i != NULL)
    {
        while (ptr_j->next != NULL)
        {
            ptr_j_n = ptr_j->next;
            if((ptr_j_n->value) < (ptr_j->value)){
                temp[1]=ptr_j_n->value;
                temp[2]=ptr_j_n->key;
                ptr_j_n->value = ptr_j->value;
                ptr_j_n->key = ptr_j->key;
                ptr_j->value = temp[1];
                ptr_j->key = temp[2];
            }
            ptr_j=ptr_j_n;
        }
        ptr_j = *head;
        ptr_i = ptr_i->next;
    }
}

void Remove(struct Node **head, char value[])
{
    struct Node *ptr = *head;
    struct Node *last_ptr = *head;
    while (ptr != NULL)
    {
        if(strcmp(value, ptr->value)==0)
        {
            last_ptr->next = ptr->next;
            if(ptr->key==(*head)->key){
                *head = ptr->next;
            }
        }
        last_ptr = ptr;
        ptr = ptr->next;
    }
}

int main()
{
    struct Node *head = NULL;
    for (int i = 0; i < 13; i++)
    {
        Add(&head,"Arman_Heydari"+i,i*405,i*99);
    }
    PrintList(&head);
    printf("\n after sort:");
    Bubble_sort(&head);
    PrintList(&head);

    printf("\nwhich node do you like to remove?\nname: ");
    char value[100];
    long value;
    scanf("%s", value);
    printf("value: ");
    Remove(&head,value);
    PrintList(&head);
    return 0;
}
