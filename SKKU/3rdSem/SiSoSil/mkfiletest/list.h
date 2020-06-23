#ifndef __LIST
#define __LIST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct myCard {
    int val;
    struct myCard* next;
} Card;

typedef struct myHold {
    int size;
    Card* first;
    Card* last;
} Hold;

typedef struct myHuman {
    Hold* hold;       //패
    int motteruCard;  //현재 라운드에서 소유중인 카드수
    int Score;
    int isDealer;  //딜러여부
} Human;

Card* create_node(Card* from, int val);

int holdIndexAccess(Hold* h, int idx);

void holdReset(Hold* h);

void holdAppend(Hold* head, int val);

#endif