#include <curses.h>
#include <unistd.h>

#include "bits/stdc++.h"
using namespace std;

#define EMPTY ' '
#define POOP '.'
#define WALL1 '8'
#define PLAYER '*'
#define MONSTER 'M'
#define MONSTER_NUM 10
#define R 23
#define C 74
#define pii pair<int, int>
#define ff first
#define ss second
#define mp(a, b) make_pair(a, b)

// deque<pii> fireDQ;

int mr[MONSTER_NUM];
int mc[MONSTER_NUM];

bool can_go_monster(int r, int c) {
    int testch;
    testch = mvinch(r, c);
    return ((testch == EMPTY));
}

bool can_go_player(int r, int c) {
    int testch;
    testch = mvinch(r, c);
    return (testch == EMPTY);
}

bool monster_move(int& mr, int& mc, int doko) {  //상 하 좌 우로 이동
    if (doko == 0) {                             //상
        if ((mr > 0) && can_go_monster(mr - 1, mc)) {
            mvaddch(mr, mc, EMPTY);
            mr--;
            return true;
        }
    } else if (doko == 1) {  //하
        if ((mr < LINES - 1) && can_go_monster(mr + 1, mc)) {
            mvaddch(mr, mc, EMPTY);
            mr++;
            return true;
        }
    } else if (doko == 2) {  //좌
        if ((mc > 0) && can_go_monster(mr, mc - 1)) {
            mvaddch(mr, mc, EMPTY);
            mc--;
            return true;
        }
    } else if (doko == 3) {  //우
        if ((mc < COLS - 1) && can_go_monster(mr, mc + 1)) {
            mvaddch(mr, mc, EMPTY);
            mc++;
            return true;
        }
    }
    return false;
}

/*void BFS() {
    int cnt = fireDQ.size();
    while (cnt--) {
        int rr = fireDQ.front().ff;
        int cc = fireDQ.front().ss;
        fireDQ.pop_front();
        for (int i = 0; i < 4; i++) {
            int rrr = rr;
            int ccc = cc;
            if (monster_move(rrr, ccc, i)) {
                fireDQ.push_back(mp(rrr, ccc));
            }
        }
    }
}*/

bool is_player_okay(int r, int c, int mr, int mc) {
    if (abs(r - mr) > 1 && abs(c - mc) > 2)  //r, c 모두 1, 2 이상 이격되어있어야 생존가능
        return true;
    else
        return false;
}

void player_move(int& r, int& c, char ch) {
    switch (ch) {  //플레이어 이동
        case 'w':
        case 'W':
            if ((r > 0) && can_go_player(r - 1, c)) {
                mvaddch(r, c, POOP);
                r = r - 1;
            }
            break;
        case 's':
        case 'S':
            if ((r < LINES - 1) && can_go_player(r + 1, c)) {
                mvaddch(r, c, POOP);
                r = r + 1;
            }
            break;
        case 'a':
        case 'A':
            if ((c > 0) && can_go_player(r, c - 1)) {
                mvaddch(r, c, POOP);
                c = c - 1;
            }
            break;
        case 'd':
        case 'D':
            if ((c < COLS - 1) && can_go_player(r, c + 1)) {
                mvaddch(r, c, POOP);
                c = c + 1;
            }
            break;
    }
}

void draw_maze() {  //empty로의 초기화작업이 필요한가?
    int r, c;
    string maze[23];
    //73*23
    maze[0] = "8888888888888888888888888888888888888888888888888888888888888888888888 88";
    maze[1] = "8   8               8                           8                   8   8";
    maze[2] = "8   8   888888888   8   88888   888888888   88888   88888   88888   8   8";
    maze[3] = "8                                   8               8   8   8       8   8";
    maze[4] = "888888888   8   888888888   888888888   88888   8   8   8   888888888   8";
    maze[5] = "8       8   8               8           8   8   8   8   8           8   8";
    maze[6] = "8   8   8888888888888   8   8   888888888   88888   8   888888888   8   8";
    maze[7] = "8   8               8   8   8       8           8           8       8   8";
    maze[8] = "8   8888888888888   88888   88888   8   88888   888888888   8   88888   8";
    maze[9] = "8                   8   8       8   8       8           8   8           8";
    maze[10] = "8   88888   88888   8   88888   8   888888888   8   8   8   8888888888888";
    maze[11] = "8       8       8   8   8       8       8       8   8   8       8       8";
    maze[12] = "8888888888888   8   8   8   888888888   8   88888   8   88888   88888   8";
    maze[13] = "8           8   8           8       8   8       8   8       8           8";
    maze[14] = "8   88888   8   888888888   88888   8   88888   88888   8888888888888   8";
    maze[15] = "8   8       8           8           8       8   8   8               8   8";
    maze[16] = "8   8   888888888   8   88888   888888888   8   8   8888888888888   8   8";
    maze[17] = "8   8           8   8   8   8   8           8               8   8       8";
    maze[18] = "8   888888888   8   8   8   88888   888888888   888888888   8   888888888";
    maze[19] = "8   8       8   8   8           8           8   8       8               8";
    maze[20] = "8   8   88888   88888   88888   888888888   88888   8   888888888   8   8";
    maze[21] = "8   8                   8                           8               8   8";
    maze[22] = "8   888888888888888888888888888888888888888888888888888888888888888888888";
    for (int r = 0; r < 23; r++) {
        mvaddstr(r, 1, maze[r].c_str());
    }
}

int main(void) {
    int r, c;                              //플레이어 위치. 커서의 위치이기도 함.
    int mr[MONSTER_NUM], mc[MONSTER_NUM];  //몬스터 위치
    int ch;
    srand((unsigned int)time(NULL));

    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    clear();

    draw_maze();

    for (int i = 0; i < MONSTER_NUM; i++) {
        mr[i] = (i + 1) * 2;
        mc[i] = (i + 1) * 6;
    }
    mr[2] -= 1;
    mr[3] += 1;
    mr[5] += 1;
    mr[6] += 1;
    mr[8] += 1;
    mr[9] -= 1;
    // fireDQ.push_back(mp(mr[0], mc[0]));
    r = R - 1;
    c = 3;
    // r = 3;
    // c = 70;
    int second = 0;
    bool isClear = false;
    do {
        if (r == 0) {
            isClear = true;
            break;
        }
        second++;
        mvaddch(r, c, PLAYER);
        for (int i = 0; i < MONSTER_NUM; i++) {
            mvaddch(mr[i], mc[i], MONSTER);
        }
        move(r, c);
        refresh();
        ch = getch();
        player_move(r, c, ch);
        for (int i = 0; i < MONSTER_NUM; i++) {
            for (int cnt = 0; cnt < 10; cnt++) {
                int doko = rand() % 4;
                if (monster_move(mr[i], mc[i], doko))
                    break;
                else
                    continue;
            }
        }
        for (int i = 0; i < MONSTER_NUM; i++) {
            if (r == mr[i] && c == mc[i]) {
                clear();
                mvprintw(LINES / 2 - 2, COLS / 2 - 20, "MONSTER MONSTER HUMAN DINNER!!!");
                mvprintw(LINES / 2, COLS / 2 - 8, "GAME OVER");
                mvprintw(LINES / 2 + 2, COLS / 2 - 18, "Your Lifetime is %d Second", second);
                refresh();
                sleep(3);
                endwin();
                exit(1);
            }
        }
    } while ((ch != 'q') && (ch != 'Q') && second < 600);

    if (isClear) {
        clear();
        mvprintw(LINES / 2 - 2, COLS / 2 - 20, "You Escaped by yourself!!! Congratulations!!!");
        mvprintw(LINES / 2, COLS / 2 - 8, "GAME CLEAR");
        mvprintw(LINES / 2 + 2, COLS / 2 - 18, "Your Score is %d Second", second);
        refresh();
        sleep(3);
        endwin();
        exit(1);
    } else {
        clear();
        if (second < 600)
            mvprintw(LINES / 2 - 2, COLS / 2 - 20, "You Just Ran Away By the Helicopter");
        else
            mvprintw(LINES / 2 - 2, COLS / 2 - 20, "TimeOver!!!");
        mvprintw(LINES / 2, COLS / 2 - 8, "GAME OVER");
        mvprintw(LINES / 2 + 2, COLS / 2 - 18, "Your Lifetime is %d Second", second);
        refresh();
        sleep(3);
        endwin();
        exit(1);
    }
    endwin();
    exit(0);
}
//g++ newgame.cpp -lncurses -o gm00