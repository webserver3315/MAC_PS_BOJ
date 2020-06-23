#ifndef __GAME
#define __GAME
#include <time.h>

#include "list.h"
#define NUMBER_OF_DECK 4

int N;             //플레이어 수. 딜러있으니 총 N+1명 참전.
int deck[4 * 13];  //0은 에이스, 1은 2, ..., 9는 10, 10은 잭, 11는 퀸, 12은 킹, 몫은 스페이드 하트 다이아 클로버순
int nokoriCardCnt = 208;
int Round;
Human player[7];  //0번은 딜러, 1번은 플레이어

void printScore();

int getCard();

void PunPai();

int getCardPoint(const Human h);

char* translate(int i);

void ShowCard(int hide);

void DrawEveryone();

void Kaikei();
void endRound();

void startRound();

#endif