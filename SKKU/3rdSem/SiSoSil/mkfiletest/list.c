#include "list.h"

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
