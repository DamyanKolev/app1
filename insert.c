#include "forum.h"

void insertEnd(node_t * head, advert_t advert)
{
    node_t * current = head;

    //search  the last item
    while (current->next != NULL)
    {
        current = current->next;
    }

    //adding an element
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->payload = advert;
    current->next->next = NULL;
}

void insertFirst(node_t ** head, advert_t advert)
{
    node_t * new_node;
    new_node = (node_t *) malloc(sizeof(node_t));

    //Adding an item to the beginning of the list
    new_node->payload = advert;
    new_node->next = *head;
    *head = new_node;
}
