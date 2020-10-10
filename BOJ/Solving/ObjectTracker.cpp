//
// Created by KYEONGTAE PARK on 2020/08/08.
//

#include <bits/stdc++.h>

#define IOU_THRESHOLD 60
#define endl '\n'
#define pii pair<int, int>
#define TMAX 10
#define DMAX 10
#define ff first
#define ss second
#define mp(a, b) make_pair(a, b)
using namespace std;

int T, D;
vector<deque<pii>> tracked_detected;  // [0]번 추적객체에 append되는 detected obj, [1]번 추적객체에 ...,
bool done[TMAX];
pii assigned[DMAX];  // assigned[i] = i번 Detected Object 가 append될 예정인 IoU 및 Tracked Object의 인덱스

void sort_tracked_detected() {
    for (int t = 0; t < T; t++) {
        sort(tracked_detected[t].begin(), tracked_detected[t].end(), greater<pii>());
    }
}

void link_tracked_and_detected() {
    for (int i = 0; i < D; i++) {
        for (int t = 0; t < T; t++) {
            if (tracked_detected[t][i].ff < IOU_THRESHOLD) continue;  //역치미만이면 무시
            if (assigned[i].ff < tracked_detected[t][i].ff) {         //NTR
                int& d = assigned[i].ss;
                assigned[i].ff = tracked_detected[t][i].ff;
                done[d] = false;
                d = tracked_detected[t][i].ss;
                done[d] = true;
            }
        }
    }
}

void printTD() {
    for (int t = 0; t < T; t++) {
        for (int d = 0; d < D; d++) {
            cout << tracked_detected[t][d].ss << "," << tracked_detected[t][d].ff << " ";
        }
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T >> D;

    for (int t = 0; t < T; t++) {
        deque<pii> dq;
        for (int i = 0; i < D; i++) {
            int tmp;
            cin >> tmp;
            dq.push_back(mp(tmp, i));
        }
        tracked_detected.push_back(dq);
    }

    for (int i = 0; i < TMAX; i++) {
        assigned[i] = mp(-1, -1);
    }

    sort_tracked_detected();

    printTD();

    link_tracked_and_detected();
    for (int i = 0; i < D; i++) {
        cout << i << " " << assigned[i].ss << " " << assigned[i].ff << endl;
        // cout << assigned[i].ss << " " << i << " " << assigned[i].ff << endl;
    }

    return 0;
}