#include <bits/stdc++.h>
#define endl '\n'
#define myMAX 32001
using namespace std;

int N, M;
vector<int> adj[myMAX];
int indegree[myMAX];
deque<int> buf;
deque<int> ans;

void solve() {  //사이클이 없는 경우만 주어진다. 즉, 위상정렬이 가능한 경우만 주어진다.
    /*
우선 큐를 이용해서 구현해보자.
일단 진입차수를 유지하고, 0인 것들만 착착 뽑아내야한다.
이를 위해서는, priority queue를 써야할까?
아, 나동빈 블로그 따르면 굳이 그럴 필요 없이 배열만 써도 된다. 그래도 충분히 빠르다.
*/
    for (int i = 1; i <= N; i++) {  //최초의 진입차수 0 노드들 죄다 넣기
        if (indegree[i] == 0) {
            buf.push_back(i);
        }
    }
    for (int i = 1; i <= N; i++) {  //정확히 n개의 노드를 방문해야 위상정렬이 종료되므로
        if (buf.empty()) break;
        int cur = buf.front();
        buf.pop_front();
        ans.push_back(cur);  //buf 탈출한 순으로 답큐에 넣기
        for (auto i : adj[cur]) {
            indegree[i]--;
            if (indegree[i] == 0) {  //빼서 0이 되면 buf에 넣기
                buf.push_back(i);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indegree[b]++;
    }

    solve();
    for (auto a : ans) {
        cout << a << " ";
    }
    cout << endl;

    return 0;
}