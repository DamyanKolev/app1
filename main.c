#include "forum.h"

int main(int argc, char * argv[])
{
    system("chcp 1251");

    node_t * head = NULL;

    if (argc > 1)
    {
        printf("\n\n\nСъвпадащи обяви.\n\n");
        matchSearch(argv[1], argv[2]);

        makeList(argv[1], argv[2],&head);
        printf("\n\nСписъка с всички елементи.");
        displayList(head);

        unsigned a = strtol(argv[3], NULL, 10);

        deleteAdver(&head, a, argv[4]);
        printf("\n\nСписъка с премахнат елемент.");
        displayList(head);

        advert_t info = insertAdvert(head);
        insertEnd(head, info);

        freeList(head);
    }

    else
    {
        printf("No argument found!\n");
    }

    /*printf("\n\n\nСъвпадащи обяви.\n\n");
    matchSearch("sell.dat", "requests.dat");

    makeList("sell.dat", "requests.dat",&head);
    printf("\n\nСписъка с всички елементи.");
    displayList(head);

    deleteAdver(&head,(unsigned) 4363, "request");
    printf("\n\nСписъка с премахнат елемент.");
    displayList(head);

    advert_t info = insertAdvert(head);
    insertEnd(head, info);*/

    return 0;
}
