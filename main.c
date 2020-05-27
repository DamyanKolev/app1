#include "forum.h"

int main(int argc, char * argv[])
{
    system("chcp 1251");

    node_t * head = NULL;

    if (argc > 1)
    {
        printf("\n\n\n��������� �����.\n\n");
        matchSearch(argv[1],argv[2]);

        makeList(argv[1],argv[2],&head);
        printf("\n\n������� � ������ ��������.");
        displayList(head);

        deleteAdver(&head,(unsigned) argv[3],argv[4]);
        printf("\n\n������� � ��������� �������.");
        displayList(head);

        advert_t info = insertAdvert(head);
        insertEnd(head, info);

        freeList(head);
    }

    else
    {
        printf("No argument found!\n");
    }

    return 0;
}
