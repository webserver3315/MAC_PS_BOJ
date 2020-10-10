//
// Created by KYEONGTAE PARK on 2020/08/08.
//

#include <bits/stdc++.h>

#define IOU_THRESHOLD 0
#define endl '\n'
#define pii pair<int, int>
#define BMAX 30
#define OMAX 30
#define ff first
#define ss second
#define mp(a, b) make_pair(a, b)
using namespace std;

int B, O;
vector<deque<pii>> vct;
pii hist[OMAX];
bool done[BMAX];

void print_ans() {
    for (int o = 0; o < O; o++) {
        // cout << hist[o].ss << " " << o << " " << hist[o].ff << endl;
        if (hist[o].ss == -1) {
            cout << "신규탐지객체 " << o << " 는 일치하는 이전탐지객체가 없어서 신규 트래킹 객체가 됩니다" << endl;
        } else {
            cout << "신규탐지객체 " << o << " 는 이전탐지객체 " << hist[o].ss << " 에 " << hist[o].ff << " 의 확신도로 append 됩니다." << endl;
        }
    }
    for (int b = 0; b < B; b++) {
        if (done[b] == false) {
            cout << "이전탐지객체 " << b << " 는 일치하는 현재탐지객체가 없어서 트래킹 영구중단합니다" << endl;
        }
    }
}

bool isAllBlueAssigned() {
    for (int b = 0; b < B; b++) {
        //undone 이면서 dq에 아직 쓸 것이 남아있다면
        if (!done[b] && !vct[b].empty()) return false;
    }
    return true;
}

void sort_each_dq() {
    for (auto& a : vct) {
        sort(a.begin(), a.end(), greater<pii>());
    }
}

void print_done() {
    // for (auto& a : done) {
    cout << "[";
    for (int b = 0; b < B; b++) {
        cout << done[b] << ", ";
    }
    cout << "]" << endl;
}

void print_vct() {
    for (auto& dq : vct) {
        for (auto& i : dq) {
            cout << i.ss << "," << i.ff << " ";
        }
        cout << endl;
    }
}

void solve() {
    while (!isAllBlueAssigned()) {
        for (int b = 0; b < B; b++) {
            if (done[b]) continue;
            if (vct[b].empty()) continue;
            deque<pii>& dq = vct[b];
            pii front = dq.front();
            dq.pop_front();
            int o = front.ss;
            int p = front.ff;
            // print_done();
            if (hist[o].ff < p) {  //NTR
                if (hist[o].ss == -1) // 결함발견
                    cout << "WARNING" << endl;
                done[hist[o].ss] = false;
                hist[o].ss = b;
                done[hist[o].ss] = true;
                hist[o].ff = p;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> B >> O;

    for (int o = 0; o < O; o++) {
        hist[o] = mp(-1, -1);
    }

    for (int b = 0; b < B; b++) {
        deque<pii> dq;
        for (int o = 0; o < O; o++) {
            int tmp;
            cin >> tmp;
            dq.push_back(mp(tmp, o));
        }
        vct.push_back(dq);
    }
    // print_vct();
    // cout << endl;
    sort_each_dq();
    // cout << endl;
    // print_vct();
    solve();
    print_ans();

    return 0;
}