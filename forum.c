#include "forum.h"

//display match adverts from files
static void displayMatch(advert_t advert, unsigned index);
//add information from file to the list
static void fill_list(FILE * fp, node_t ** head, char * section);
//checks if a user exists
static unsigned checkUser(const char * username, const char * password);
//make a profile
static void makeProfile(char * username, char * password);
//save the information for advert in file
static void writeAdvertInFile(advert_t adver, const char * fname);

//the type of products to buy or sell
const char * p_type[6] = {"smartphone", "laptop", "video card", "tablet", "PC", "processor"};



void matchSearch(const char * fsell, const char * fbuy)
{
    FILE * fp_buy = fopen(fbuy,"r");
    FILE * fp_sell = fopen(fsell,"r");;

    advert_t buy;
    advert_t sell;

    buy.title = (char *) malloc(200);
    sell.title = (char *) malloc(200);
    buy.user.username = (char *) malloc (20);
    sell.user.username = (char *) malloc (20);

    if (fp_buy != NULL && fp_sell != NULL)
    {
        //first loop for read file for buy advert
        while (fscanf(fp_buy,"%[^;]%*c%u;%u;%[^;]%*c%f\n",buy.user.username, &buy.product_type, &buy.id, buy.title, &buy.price) != EOF)
        {
            //opens the file which will read how many lines the first file has
            fseek(fp_sell, 0, SEEK_SET);

            //second loop for read file for sell advert
            while (fscanf(fp_sell,"%[^;]%*c%u;%u;%[^;]%*c%f\n",sell.user.username, &sell.product_type, &sell.id, sell.title, &sell.price) != EOF)
            {
                //checks that the types are the same and that the difference is equal to 10% of buy price
                if (buy.product_type == sell.product_type)
                {
                    //store the difference between the two price
                    unsigned int price_dif = abs(buy.price - sell.price);

                    //check which price is bigger than other
                    if (buy.price >= sell.price && price_dif <= 0.1*buy.price)
                    {
                        //displaying the adverts
                        displayMatch(sell,1);
                        displayMatch(buy,2);

                        printf("\n\n\n");
                    }

                    else if (buy.price < sell.price && price_dif <= 0.1*sell.price)
                    {
                        //displaying the adverts
                        displayMatch(sell,1);
                        displayMatch(buy,2);

                        printf("\n\n\n");
                    }
                }
            }
        }
        //deallocation
        free(buy.title);
        free(sell.title);
        free(buy.user.username);
        free(sell.user.username);
    }

    else
    {
        printf("File not open.\n");
    }
}

static void displayMatch(advert_t advert, unsigned index)
{
    char * title[2] = {"sell", "request"};

    //Displaying the information for advert
    printf("Потребител: %s\n",advert.user.username);
    printf("Обява %s\n",title[index-1]);
    printf("Тип: %s\n",p_type[advert.product_type]);
    printf("ID: %u\n",advert.id);
    printf("Заглавие: %s\n",advert.title);
    printf("Цена: %.2f\n",advert.price);
}

void makeList(const char * fsell, const char * fbuy, node_t ** head)
{
    FILE * fp_sell = fopen(fsell, "r");
    FILE * fp_buy = fopen(fbuy,"r");

    if(fp_sell != NULL && fp_buy != NULL)
    {
        //add items to list from sell file
        fill_list(fp_sell,&(*head),"sell");
        fill_list(fp_buy,&(*head),"request");
    }

    else
    {
        printf("File not open.\n");
    }

    //closing the files
    fclose(fp_sell);
    fclose(fp_buy);
}

static void fill_list(FILE * fp, node_t ** head, char * section)
{
    advert_t temp;
    unsigned i = 2;

    temp.title = (char *) malloc(200);
    temp.section = (char *) malloc(10);
    temp.user.username = (char *) malloc(20);

    if (fp != NULL)
    {
        //fill the list
        while (fscanf(fp,"%[^;]%*c%u;%u;%[^;]%*c%f\n",temp.user.username, &temp.product_type, &temp.id, temp.title, &temp.price) != EOF)
        {
            //type of a advert
            temp.section = section;

            //checks if the list is empty
            if(*head == NULL)
            {
                //add first element
                insertFirst(&(*head),temp);
            }

            else
            {
                insertEnd(*head, temp);
            }

            //allocation the memory
            temp.title = (char *) malloc(200 * i);
            temp.section =(char *) malloc(10 * i);
            temp.user.username = (char *) malloc(20 * i);

            i++;
        }
    }

    else
    {
        printf("File not open.\n");
    }
}

void displayList(node_t * head)
{
    node_t * current = head;
    printf("\nDisplaying list\n\n");

    while (current != NULL)
    {
        //Displaying the information for list item
        printf("Потребител: %s\n",current->payload.user.username);
        printf("Обява: %s\n",current->payload.section);
        printf("Тип: %s\n",p_type[current->payload.product_type-1]);
        printf("ID: %u\n",current->payload.id);
        printf("Заглавие: %s\n",current->payload.title);
        printf("Цена: %.2f\n\n",current->payload.price);

        current = current->next;
    }
}

void freeList(node_t * head)
{
    node_t * temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

advert_t insertAdvert(node_t * head)
{
    advert_t info;
    srand(time(NULL));
    node_t * current = head;

    //allocation the memory
    info.section = (char *)malloc(10);
    info.title = (char *)malloc(200);
    info.user.username = (char *) malloc(20);
    info.user.password = (char *) malloc(20);

    printf("\n\nLogin in\n");

    //account of the user
    printf("Username: ");
    gets(info.user.username);
    fflush(stdin);
    printf("Password: ");
    gets(info.user.password);
    fflush(stdin);

    //check user
    if (checkUser(info.user.username, info.user.password) == 0)
    {
        printf("\nНяма съществуващ профил с това име и парола.\n");

        printf("\nЗа да създадете обява ви трябва профил.\n");

        //make profile in the forum
        makeProfile(info.user.username, info.user.password);
    }


    printf("\n\nСъздаване на обява:\n");


    do
    {
        //type of advert
        printf("Тип на обявата(request/sell): ");
        gets(info.section);
        if (abs(strcmp(info.section,"sell")) != 0 && abs(strcmp(info.section,"request")) != 0)
        {
            printf("Грешно въведено поле.");
        }
    }
    while (abs(strcmp(info.section,"sell")) != 0 && abs(strcmp(info.section,"request")) != 0);

    //display type of product
    for (unsigned i=0; i<6; i++)
    {
        printf("\nИзберете %d за %s",i+1, p_type[i]);
    }

    do
    {
        //type of product
        printf("\nТип на предмета: ");
        scanf("%u",&info.product_type);

        if (info.product_type < 1 || info.product_type > 6)
        {
            printf("Грешно въведено поле.");
        }
    }
    while (info.product_type < 1 || info.product_type > 6);

    //clean the buffer
    fflush(stdin);

    //description of the advert
    printf("\nОписание на обявата до 200 символа: ");
    gets(info.title);


    //price of the product
    printf("\nЦена: ");
    scanf("%f",&info.price);

    //generate advert id
    info.id = rand() % 9000 + 1000;

    //check if id is equal to any other in the list
    while (current->next != NULL)
    {
        //check if id of a new advert is equal to any other advert
        if (current->payload.id == info.id)
        {
            //generates a new id until it becomes different from the others
            while (current->payload.id == info.id)
            {
                //generate id
                info.id = rand() % 9000 + 1000;
            }
        }
        current = current->next;
    }

    //check if section of this advert is request
    if (strcmp(info.section, "request") == 0)
    {
        //save the advert in the file for request
        writeAdvertInFile(info, "requests.dat");
    }

    //check if section of this advert is sell
    else if (strcmp(info.section, "sell") == 0)
    {
        //save the advert in the file for request
        writeAdvertInFile(info, "sell.dat");
    }

    return info;
}

static void makeProfile(char * username, char * password)
{
    FILE * fp = fopen("user.dat","r+");
    char buffer[50];

    if (fp != NULL)
    {
        printf("Създаване на профил.\n");

        //make a username
        printf("Потребителско име(max 20 символа): ");
        gets(username);

        fflush(stdin);

        //make password
        printf("Парола(max 20 символа): ");
        gets(password);

        //connect all information into string
        strcpy(buffer, username);
        strcat(buffer, ";");
        strcat(buffer, password);
        strcat(buffer, "\0");

        //write into file
        fseek(fp, 0, SEEK_END);
        fwrite("\n",1,1,fp);
        fwrite(buffer, strlen(buffer), 1, fp);

    }

    else
    {
        printf("File not open.\n");
    }
}

static unsigned checkUser(const char * username, const char * password)
{
    FILE * fp = fopen("user.dat","r");

    user_t user;

    if (fp != NULL)
    {
        user.username = (char *) malloc(20);
        user.password = (char *) malloc(20);

        //read file and search
        while (fscanf(fp,"%[^;]%*c%[^\n]%*c",user.username, user.password) != EOF)
        {
            //check the profile is ins the file
            if (strcmp(username,user.username) == 0 && strcmp(password,user.password) == 0)
            {
                free(user.username);
                free(user.password);

                return 1;
            }
        }

        free(user.username);
        free(user.password);
    }

    else
    {
        printf("File not open.\n");
    }

    return 0;
}

static void writeAdvertInFile(advert_t adver, const char * fname)
{
    FILE * fp = fopen(fname, "r+");

    if (fp != NULL)
    {
        //write in file new line
        fseek(fp,0,SEEK_END);
        fwrite("\n",1,1,fp);

        //write in file new line
        fseek(fp,0,SEEK_END);
        fwrite(adver.user.username, strlen(adver.user.username), 1, fp);

        fseek(fp,0,SEEK_END);
        fwrite(";",1,1,fp);

        fseek(fp,0,SEEK_END);
        fprintf(fp,"%u", adver.product_type);

        fseek(fp,0,SEEK_END);
        fwrite(";",1,1,fp);

        fseek(fp,0,SEEK_END);
        fprintf(fp,"%u", adver.id);

        fseek(fp,0,SEEK_END);
        fwrite(";",1,1,fp);

        fseek(fp,0,SEEK_END);
        fwrite(adver.title, strlen(adver.title), 1, fp);

        fseek(fp,0,SEEK_END);
        fwrite(";",1,1,fp);

        fseek(fp,0,SEEK_END);
        fprintf(fp,"%.2lf", adver.price);
    }

    else
    {
        printf("File not open.\n");
    }
}
