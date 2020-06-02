#include "forum.h"

//remove first element from the list
static void deleteFirst(node_t ** head);
//remove last element from the list
static void deleteEnd(node_t * head);
//searches for the index of the item in the list
static unsigned searchIndexInList(node_t * head, const unsigned id, const char * section);
//delete the row we want to delete from file
static void deleteFromFile(char * fname, const unsigned id);
//search the row we want to delete in file
static unsigned searchRowInFile(const char * fname, const unsigned id);




void deleteAdver(node_t ** head, const unsigned id, const char * section)
{
    node_t * current = * head;
    node_t * temp_node = NULL;

    //search a specific element
    while (current->payload.id != id && strcmp(current->payload.section, section) != 0)
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

        unsigned index = searchIndexInList(*head, id, section)-1;

        //check in which file the data to be deleted is saved
        if (strcmp(section, "request") == 0)
        {
            deleteFromFile("requests.dat", id);
        }

        else if (strcmp(section, "sell") == 0)
        {
            deleteFromFile("sell.dat", id);
        }

        for (unsigned i = 0; i < index; i++)
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

static unsigned searchIndexInList(node_t * head, const unsigned id, const char * section)
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

static void deleteFromFile(char * fname, const unsigned id)
{
    unsigned delete_line = searchRowInFile(fname, id);

    if (delete_line != 0)
    {
        FILE * fp = fopen(fname, "r");

        char  temp[50][400];
        unsigned row = 0;

        if (fp != NULL)
        {
            //read and save the information in string array
            while (fgets(temp[row], 400, fp))
            {
                temp[row][strlen(temp[row]) - 1] = '\0';
                row++;
            }

            fclose(fp);
            fp = fopen(fname, "w");

            for (unsigned i = 0; i<row; i++)
            {
                if (i != delete_line-1)
                {
                    fprintf(fp, "%s\n", temp[i]);
                }
            }
        }

        else
        {
            printf("File not fount.\n");
        }

        fclose(fp);
    }

    else
    {
        return;
    }
}

static unsigned searchRowInFile(const char * fname, const unsigned id)
{
    FILE * fp = fopen(fname, "r");

    unsigned count = 1;

    advert_t tmp;

    tmp.title = (char *) malloc(200);
    tmp.user.username = (char *) malloc (20);

    if (fp != NULL)
    {
        //count which line want to delete
        while (fscanf(fp,"%[^;]%*c%u;%u;%[^;]%*c%f\n",tmp.user.username, &tmp.product_type, &tmp.id, tmp.title, &tmp.price) != EOF)
        {
            if (tmp.id == id)
            {
                return count;
            }
            count++;
        }
    }

    else
    {
        printf("File not fount.\n");
    }

    fclose(fp);
    free(tmp.title);
    free(tmp.user.username);

    return 0;
}
