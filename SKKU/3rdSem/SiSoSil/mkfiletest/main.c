#include <time.h>

#include "list.h"
#define NUMBER_OF_DECK 4

int N;             //플레이어 수. 딜러있으니 총 N+1명 참전.
int deck[4 * 13];  //0은 에이스, 1은 2, ..., 9는 10, 10은 잭, 11는 퀸, 12은 킹, 몫은 스페이드 하트 다이아 클로버순
int nokoriCardCnt = 208;
int Round;
Human player[7];  //0번은 딜러, 1번은 플레이어

void printScore() {  //각 플레이어들이 소유하고 있는 현금을 출력. 초기값은 500
    printf("--------------------SCORE---------------------\n");
    for (int i = 1; i <= N; i++) {
        printf("Player %d : %d\n", i, player[i].Score);
    }
    printf("--------------------SCORE---------------------\n");
}

int getCard() {                         //카드를 뽑는 함수.
    if (nokoriCardCnt == 0) return -1;  //남은 카드가 0장이라면 못뽑으니까 -1 리턴
    int card;
    while (1) {  //플레이어 수 관계상, 절대 모든 덱이 고갈날 일은 없다.
        card = rand();
        card %= 4 * 13;  //문양이 4개에 숫자가 13개 있으므로
        if (deck[card])
            break;
        else if (nokoriCardCnt == 0)
            break;
        else
            break;
    }
    nokoriCardCnt--;  //한 장 감소
    return card;
}

void PunPai() {                     //카드 초기 2장 분배
    for (int i = 0; i <= N; i++) {  //각자에게 카드배분
        if (nokoriCardCnt) {
            int c1 = getCard();
            // player[i].hold.push_back(c1);
            holdAppend(player[i].hold, c1);
            player[i].motteruCard++;
        }
        if (nokoriCardCnt) {
            int c2 = getCard();
            // player[i].hold.push_back(c2);
            holdAppend(player[i].hold, c2);
            player[i].motteruCard++;
        }
    }
}

int getCardPoint(const Human h) {  //사람 구조체를 넣으면, 그 사람의 패에 든 카드의 수의 합을 traverse하여 반환
    int ret = 0;
    int aceNum = 0;
    for (int i = 0; i < h.hold->size; i++) {
        int cur = holdIndexAccess(h.hold, i);
        int pict = cur / 4;
        int num = cur % 13;
        if (num == 0) {  //에이스면, 일단 1취급
            aceNum++;
            ret++;
        } else if (num >= 10) {  //그림이면
            ret += 10;
        } else {
            ret += num + 1;
        }
    }
    while (aceNum) {          //10 a a a 일 때, 그리디하게 10 10 a a 했다가는 오버뜬다. 차라리 1씩 다 더하고 추후에 9 더하자.
        if (ret + 9 <= 21) {  //9더해도 버티면 a 하나를 10으로 뻥튀기.
            ret += 9;
            aceNum--;
        } else
            break;
    }
    return ret;
}

char* translate(int i) {  //int 로 카드를 받으면 그것을 스트링으로 바꿔주는 함수. 메모리해제는 함수 바깥에서 해야함.
    //char* ret = (char*)malloc(30);
    char ret[30];
    if (i / 13 == 0) {
        strcpy(ret, "Spade ");
    } else if (i / 13 == 1) {
        strcpy(ret, "Heart ");
    } else if (i / 13 == 2) {
        strcpy(ret, "Diamond ");
    } else if (i / 13 == 3) {
        strcpy(ret, "Clover ");
    }

    int num = (i % 13) + 1;
    if (num == 1) {
        strcat(ret, "A");
    } else if (num == 11) {
        strcat(ret, "j");
    } else if (num == 12) {
        strcat(ret, "Q");
    } else if (num == 13) {
        strcat(ret, "K");
    } else {
        char tmp[10];
        sprintf(tmp, "%d", num);
        strcat(ret, tmp);
    }
    char* realret = (char*)malloc(30);
    strcpy(realret, ret);
    return realret;
}

void ShowCard(int hide) {  //각자 가지고 있는 카드를 공개하는 함수. hide가 1이면 딜러의 첫카드는 숨기고, 0이면 전부 공개한다.
    printf("--------------------SHOW CARD--------------------\n");
    for (int i = 0; i <= N; i++) {
        if (i == 0)
            printf("Dealer's Cards : ");
        else
            printf("Player %d's Cards : ", i);
        if (player[i].isDealer) {
            if (hide)
                printf("(안보임), ");
            else {
                char* name = translate(holdIndexAccess(player[i].hold, 0));
                printf("%s, ", name);
                free(name);
            }
            for (int j = 1; j < player[i].hold->size; j++) {
                char* name = translate(holdIndexAccess(player[i].hold, j));
                printf("%s, ", name);
                free(name);
            }
        } else {
            for (int j = 0; j < player[i].hold->size; j++) {
                char* name = translate(holdIndexAccess(player[i].hold, j));
                printf("%s, ", name);
                free(name);
            }
        }
        printf("\n");
    }
    printf("--------------------SHOW CARD--------------------\n");
    printf("\n");
}

void DrawEveryone() {  //모두 stand 또는 bust 할때까지 카드를 뽑게하는 함수
    int hit = 1;
    int i = 1;
    while (1) {  //1번 플레이어는 플레이어 본인이다.
        ShowCard(1);
        printf("hit 하려면 1을, stand 하려면 0을 입력하세요\n");
        scanf("%d", &hit);
        if (!hit) break;
        int cur = getCard();
        if (cur == -1) {
            printf("덱 고갈!!!\n");
            break;
        } else {
            // player[i].hold.push_back(cur);
            holdAppend(player[i].hold, cur);
            player[i].motteruCard++;
            char* name = translate(cur);
            printf("You Drawed %s\n", name);
            free(name);
            if (getCardPoint(player[i]) == 21) {
                printf("BlackJack!!!\n");
                break;
            } else if (getCardPoint(player[i]) > 21) {
                printf("Bust!!!!!!!!!!\n");
                break;
            }
        }
    }
    for (i = 2; i <= N; i++) {                  //인공지능_히트? 스탠드?
        while (getCardPoint(player[i]) < 14) {  //14미만은 무조건 hit
            int cur = getCard();
            if (cur == -1) {
                printf("덱 고갈!!!\n");
                break;
            } else {
                // player[i].hold.push_back(cur);
                holdAppend(player[i].hold, cur);
                player[i].motteruCard++;
                if (getCardPoint(player[i]) == 21) {
                    printf("Player %d BlackJack!!!\n", i);
                    break;
                } else if (getCardPoint(player[i]) > 21) {
                    printf("Player %d Bust!!!!!!!!!!\n", i);
                    break;
                } else {
                    char* tmp = translate(cur);
                    printf("Player %d Drawed %s\n", i, tmp);
                    free(tmp);
                }
            }
        }
        if (getCardPoint(player[i]) <= 17) {  //14~17이면 절반확률 히트
            hit = rand() % 2;
            if (hit) {
                int cur = getCard();
                if (cur == -1) {
                    printf("덱 고갈!!!\n");
                } else {
                    // player[i].hold.push_back(cur);
                    holdAppend(player[i].hold, cur);
                    player[i].motteruCard++;
                    if (getCardPoint(player[i]) == 21) {
                        printf("Player %d BlackJack!!!\n", i);
                    } else if (getCardPoint(player[i]) > 21) {
                        printf("Player %d Bust!!!!!!!!!!\n", i);
                    } else {
                        char* tmp = translate(cur);
                        printf("Player %d Drawed %s\n", i, tmp);
                        free(tmp);
                    }
                }
            }
        } else
            continue;  //17 초과는 무조건 스탠드
    }
    i = 0;                                  //딜러
    while (getCardPoint(player[i]) < 17) {  //16 이하는 무조건 hit
        int cur = getCard();
        if (cur == -1) {
            printf("덱 고갈!!!\n");
            break;
        } else {
            // player[i].hold.push_back(cur);
            holdAppend(player[i].hold, cur);
            player[i].motteruCard++;
            if (getCardPoint(player[i]) == 21) {
                printf("BlackJack!!!\n");
                break;
            } else if (getCardPoint(player[i]) > 21) {
                printf("Bust!!!!!!!!!!\n");
                break;
            } else {
                char* tmp = translate(cur);
                printf("Drawed %s\n", tmp);
                free(tmp);
            }
        }
    }
    printf("-------이번 라운드 카드패 최종결과--------\n");
    ShowCard(0);
}

void Kaikei() {    //라운드 결과를 결산
    int kekka[7];  //4: 블랙잭우승, 3: 우승, 2: 무승부, 1: 패배
    printf("-------------이번라운드 결과-------------\n");
    if (getCardPoint(player[0]) > 21) {  //딜러가 버스트면
        printf("Dealer has been Busted!!!\n");
        for (int i = 1; i <= N; i++) {
            printf("Player %d's CardSum is %d!!! ->　", i, getCardPoint(player[i]));
            if (getCardPoint(player[i]) > 21) {  //지면 -100
                printf("Lose(Bust)\n");
                player[i].Score -= 100;
            } else if (getCardPoint(player[i]) == 21) {  //블랙잭으로 이기면 +200
                player[i].Score += 200;
                printf("BLACKJACK Win\n");
            } else {
                player[i].Score += 100;  //그냥 이기면 +1000
                printf("Win\n");
            }
        }
    } else if (getCardPoint(player[0]) == 21) {  //딜러가 블랙잭이면
        printf("Dealer got BlackJack!!!\n");
        for (int i = 1; i <= N; i++) {
            printf("Player %d's CardSum is %d!!! -> ", i, getCardPoint(player[i]));
            if (getCardPoint(player[i]) > 21) {
                player[i].Score -= 100;
                printf("Lose(Bust)\n");
            } else if (getCardPoint(player[i]) == 21) {  //비김
                printf("Draw\n");
                continue;
            } else {
                printf("Lose\n");
                player[i].Score -= 100;
            }
        }
    } else {  //딜러가 평타면
        printf("Dealer's CardSum is %d!!!\n", getCardPoint(player[0]));
        for (int i = 1; i <= N; i++) {
            printf("Player %d's CardSum is %d!!! -> ", i, getCardPoint(player[i]));
            if (getCardPoint(player[i]) > 21) {
                printf("Lose(Bust)\n");
                player[i].Score -= 100;
            } else if (getCardPoint(player[i]) == 21) {
                printf("BLACKJACK WIN\n");
                player[i].Score += 200;
            } else {
                if (getCardPoint(player[0]) < getCardPoint(player[i])) {
                    printf("Win\n");
                    player[i].Score += 100;
                } else if (getCardPoint(player[0]) > getCardPoint(player[i])) {
                    printf("Lose\n");
                    player[i].Score -= 100;
                } else {
                    printf("Draw\n");
                }
            }
        }
    }
}

void endRound() {
    for (int i = 0; i <= N; i++) {
        // player[i].hold.clear();
        holdReset(player[i].hold);  //패 메모리 해제
        player[i].motteruCard = 0;  //카드 보유수 초기화
    }
}

void startRound() {
    Round++;
    printf("\n\n\n\n\n---------------------Round %d--------------------\n", Round);
    printScore();
    PunPai();
    DrawEveryone();
    Kaikei();
    endRound();
}

int main() {
    srand((unsigned int)time(NULL));
    printf("Number of Players: ");
    scanf("%d", &N);
    for (int i = 0; i < 4 * 13; i++) {
        deck[i] = NUMBER_OF_DECK;  //덱마다 52장인데, 이것들이 4장씩 있음.
    }
    for (int i = 0; i <= N; i++) {
        if (i == 0) {
            player[i].isDealer = 1;  //딜러에게 스코어는 무의미하지만..
        } else {
            player[i].isDealer = 0;
        }
        player[i].motteruCard = 0;
        player[i].Score = 500;  //500점 초기자본으로 주고 시작하자
        player[i].hold = (Hold*)malloc(sizeof(Hold));
        player[i].hold->size = 0;
        player[i].hold->first = NULL;
        player[i].hold->last = NULL;
    }

    while (nokoriCardCnt >= (N + 1) * 5) {
        startRound();
    }

    printf("====================경기 종료===================\n");
    printScore();

    for (int i = 0; i <= N; i++) {
        free(player[i].hold);
    }

    return 0;
}