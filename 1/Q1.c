#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct Node
{
    char *name;
    long value;
    int index;
    struct Node *next;
};

void Add(struct Node **head ,char name[], long value, int index)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    new_node->index = index;
    new_node->value = value;
    new_node->name = (char *)malloc(sizeof(char *));
    new_node->next = *head;
    strcpy(new_node->name, name);
    *head = new_node;
}

void PrintList(struct Node **head)
{
    struct Node *ptr = *head;
    printf("\n[ ");
    while (ptr != NULL)
    {
        printf(" (%ld,%d,%s) ", ptr->value, ptr->index, ptr->name);
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
                temp[0]=ptr_j_n->name;
                temp[1]=ptr_j_n->value;
                temp[2]=ptr_j_n->index;
                ptr_j_n->name = ptr_j->name;
                ptr_j_n->value = ptr_j->value;
                ptr_j_n->index = ptr_j->index;
                ptr_j->name = temp[0];
                ptr_j->value = temp[1];
                ptr_j->index = temp[2];
            }
            ptr_j=ptr_j_n;
        }
        ptr_j = *head;
        ptr_i = ptr_i->next;
    }
}

void Remove(struct Node **head, char name[], long value)
{
    struct Node *ptr = *head;
    struct Node *last_ptr = *head;
    while (ptr != NULL)
    {
        if(strcmp(name, ptr->name)==0 && value==ptr->value)
        {
            last_ptr->next = ptr->next;
            if(ptr->index==(*head)->index){
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
    char name[100];
    long value;
    scanf("%s", name);
    printf("value: ");
    scanf("%ld", &value);
    Remove(&head,name,value);
    PrintList(&head);
    return 0;
}
