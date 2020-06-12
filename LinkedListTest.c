#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUMBER_OF_DECK 4

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

int N;             //플레이어 수. 딜러있으니 총 N+1명 참전.
int deck[4 * 13];  //0은 에이스, 1은 2, ..., 9는 10, 10은 잭, 11는 퀸, 12은 킹, 몫은 스페이드 하트 다이아 클로버순
int nokoriCardCnt = 208;
int Round;
Human player[7];  //0번은 딜러, 1번은 플레이어

Card* create_node(Card* from, int val) {
    Card* new_node = (Card*)malloc(sizeof(Card));
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

int holdIndexAccess(Hold* h, int idx) {
    Card* cur = h->first;
    for (int i = 0; i < idx; i++) {
        cur = cur->next;
    }
    int ret = cur->val;
    return ret;
}

void holdReset(Hold* h) {  //h.hold 전부 할당해제 및 크기0으로
    Card* cur = h->first;
    while (cur->next != NULL) {
        Card* before = cur;
        cur = cur->next;
        free(before);
        h->size -= 1;
    }
    free(cur);
    h->first = NULL;
    h->last = NULL;
    h->size = 0;
}

void holdAppend(Hold* head, int val) {
    Card* newCard;
    newCard = (Card*)malloc(sizeof(Card));
    if (newCard == NULL) exit(1);
    newCard->val = val;
    newCard->next = NULL;
    if (head->first == NULL && head->last == NULL) {
        // head->first = create_node(NULL, val);
        head->first = head->last = newCard;
    } else {
        head->last->next = newCard;
        head->last = newCard;
    }
    head->size += 1;
}

int main() {
    srand((unsigned int)time(NULL));
    Human gamer;
    gamer.hold = malloc(sizeof(Hold));
    gamer.hold->first = NULL;
    gamer.hold->last = NULL;
    gamer.hold->size = 0;
    holdAppend(gamer.hold, 1);
    holdAppend(gamer.hold, 2);
    holdAppend(gamer.hold, 3);
    printf("%d\n", holdIndexAccess(gamer.hold, 0));
    printf("%d\n", holdIndexAccess(gamer.hold, 1));
    printf("%d\n", holdIndexAccess(gamer.hold, 2));
    holdReset(gamer.hold);
    holdAppend(gamer.hold, 4);
    printf("%d\n", holdIndexAccess(gamer.hold, 0));
    holdAppend(gamer.hold, 5);
    printf("%d\n", holdIndexAccess(gamer.hold, 0));
    printf("%d\n", holdIndexAccess(gamer.hold, 1));
    return 0;
}