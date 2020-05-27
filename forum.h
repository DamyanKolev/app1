#ifndef FORUM_H_INCLUDED
#define FORUM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <time.h>


//user data
typedef struct
{
    char * username; //max 20 symbols 20B
    char * password; //max 20 symbols 20B
}user_t;

//the structure storing the information about the advert
typedef struct
{
    user_t user;
    unsigned product_type;
    unsigned id;
    char * title; //max 200 symbols 200B
    float price;
    char * section; //max 10 symbols 10B
}advert_t;


//structure for buy and sell advert
typedef struct node
{
    advert_t payload;
    struct node * next;
}node_t;


//search for matching advert
void matchSearch(const char * fsell, const char * fbuy);
//make the lists
void makeList(const char * fsell, const char * fbuy, node_t ** head);
//insert element in the end of list
void insertEnd(node_t * head, advert_t advert);
//insert an item to the beginning of the list
void insertFirst(node_t ** head, advert_t advert);
//delete element with id and section (in payload member) id and section
void deleteAdver(node_t ** head, const unsigned id, const char * section);
//display the list
void displayList(node_t * head);
//Deallocation
void freeList(node_t * head);
//make a advert
advert_t insertAdvert(node_t * head);
#endif // FORUM_H_INCLUDED
