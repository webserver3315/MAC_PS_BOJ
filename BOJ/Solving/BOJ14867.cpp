#include <bits/stdc++.h>
#define endl '\n'
#define pii pair<int, int>
#define ppiii pair<pair<int, int>, int>  // key, value
#define ff first
#define ss second
#define mp(a, b) make_pair(a, b)
using namespace std;

int AS, BS;  //Asize, Bsize
int AF, BF;  //Afinal, Bfinal
deque<pii> dq;
map<pii, int> visited;  //key, value
int sec;

pii fill(const pii& state, bool isA) {
    pii ret = state;
    if (isA) {
        ret.ff = AS;
    } else {
        ret.ss = BS;
    }
    return ret;
}

pii flush(const pii& state, bool isA) {
    pii ret = state;
    if (isA) {
        ret.ff = 0;
    } else {
        ret.ss = 0;
    }
    return ret;
}

pii B2A(const pii& state, bool isA) {  //B에서 A로 가는게 맞는지, 역방향인지
    pii ret = state;
    if (isA) {
        ret.ff += ret.ss;
        ret.ss = 0;
        if (ret.ff > AS) {
            ret.ss = ret.ff - AS;
            ret.ff = AS;
        }
    } else {
        ret.ss += ret.ff;
        ret.ff = 0;
        if (ret.ss > BS) {
            ret.ff = ret.ss - BS;
            ret.ss = BS;
        }
    }
    return ret;
}

pii AllinOne(const pii& state, int mode) {  //1,2,3,4,5,6 각각 fi,fi,fl,fl,b2,b2 t f순
    switch (mode) {
        case 1:
            return fill(state, true);
        case 2:
            return fill(state, false);
        case 3:
            return flush(state, true);
        case 4:
            return flush(state, false);
        case 5:
            return B2A(state, true);
        case 6:
            return B2A(state, false);
        default:
            cout << "Error in AllinOne Function" << endl;
            return mp(-1, -1);
    }
}

int BFS() {  //sec 반환
    //
    /*
    선택지는 총 6가지. 이 때, 각 상태라고 해봤자 A와 B의 물양이므로 pair로 간단히 visit 구현가능.
    아, 아니다. visit array가 아니라, set 으로 해야겠다. 물 크기가 정수긴 하지만 1e5*1e5면 에바다.
    1. A 전부 채우기
    2. B 전부 채우기
    3. A 전부 버리기
    4. B 전부 버리기
    5. A 전부 버리기
    6. A에 따르기
    7. B에 따르기
    */
    pii state = mp(0, 0);  //처음에는 0으로 시작
    dq.push_back(state);
    visited[state] = 0;
    sec++;
    while (!dq.empty()) {
        int kuri = dq.size();
        while (kuri--) {
            pii cur = dq.front();
            dq.pop_front();
            if (cur.ff == AF && cur.ss == BF) {
                return sec - 1;
            }
            for (int i = 1; i <= 6; i++) {
                pii next = AllinOne(cur, i);
                auto iter = visited.find(next);
                if (iter != visited.end()) {  //visited라면 거른다.
                    // cout << iter->ff.ff << " " << iter->ff.ss << " 은 방문했으므로 걸렀다. 그 비용은 " << iter->ss << "였다." << endl;
                    continue;
                } else {  //unvisited라면
                    dq.push_back(next);
                    visited[next] = sec;
                    // cout << next.ff << " " << next.ss << " 을 최초방문했다. 그 비용은 " << sec << "였다." << endl;
                }
            }
        }
        sec++;
    }
    return -1;  //불가
}

void solve() {
    int ans = BFS();
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> AS >> BS >> AF >> BF;
    // AS = 3;
    // BS = 7;
    // AF = 3;
    // BF = 2;
    solve();

    return 0;
}