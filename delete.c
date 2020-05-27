#include "forum.h"

//remove first element from the list
static void deleteFirst(node_t ** head);
//remove last element from the list
static void deleteEnd(node_t * head);
//searches for the index of the item in the list
static unsigned searchIndex(node_t * head, const unsigned id, const char * section);




void deleteAdver(node_t ** head, const unsigned id, const char * section)
{
    node_t * current = * head;
    node_t * temp_node = NULL;

    //search a specific element
    while (current->payload.id != id && strcmp(current->payload.section,section) != 0)
    {
        current = current->next;
    }

     //delete the first element
    if (current == *head)
    {
        deleteFirst(&(*head));

        return;
    }

    //delete the specific item
    else if (current->next != NULL)
    {
        current = *head;

        unsigned index = searchIndex(*head, id, section)-1;

        for (unsigned i = 0;i < index; i++)
        {
            current = current->next;
        }

        temp_node = current->next;
        current->next = temp_node->next;
        free(temp_node);
    }

    //delete end item
    else
    {
        deleteEnd(*head);
    }

}

static void deleteFirst(node_t ** head)
{
    node_t * next_node = NULL;

    //checks if the list is empty
    if (*head == NULL)
    {
        printf("Empty list;\n");

        return;
    }

    //delete element
    next_node = (*head)->next;
    free(*head);
    *head = next_node;
}

static void deleteEnd(node_t * head)
{
    node_t * current = head;

    //if the list have one element
    if (head->next == NULL)
    {
        free(head);

        return;
    }

    //search the last item
    while (current->next->next != NULL)
    {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
}

static unsigned searchIndex(node_t * head, const unsigned id, const char * section)
{
    node_t * current = head;
    unsigned count = 0;

    //searches for the position of the item in the list
    while (current->payload.id != id && strcmp(current->payload.section,section) != 0)
    {
        current = current->next;
        count++;
    }

    return count;
}
