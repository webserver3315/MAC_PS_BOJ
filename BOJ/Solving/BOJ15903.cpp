#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

priority_queue<int, vector<int>, greater<int>> minh;
int N, M;

int solve() {
    while (M--) {
        int a, b;
        a = minh.top();
        minh.pop();
        int cnt = 0;
        do {
            b = minh.top();
            minh.pop();
            cnt++;
        } while (a != b);

        int c = a + b;
        minh.push(c);
        minh.push(c);
        while (--cnt) {
            minh.push(b);
        }
    }
    //결산
    int ret = 0;
    while (!minh.empty()) {
        ret += minh.top();
        minh.pop();
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        minh.push(tmp);
    }

    int ans = solve();

    return 0;
}