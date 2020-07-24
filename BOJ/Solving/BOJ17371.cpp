#include <bits/stdc++.h>
#define pib pair<int, bool>
#define ff first
#define ss second
#define mp(a, b) make_pair(a, b)
#define endl '\n'
#define myMAX 500001
using namespace std;

int cnt;  //sum of all depth to LeafNode
int N;
vector<int> adj[myMAX];
bool visit[myMAX];

void DFS(int cur, int depth) {   //만약 인접리스트 크기가 1이라면 잎노드
    if (adj[cur].size() == 1) {  //잎노드라면
        cnt += depth;
        return;
    }
    for (auto a : adj[cur]) {
        if (visit[a] == true)
            continue;
        visit[a] = true;
        DFS(a, depth + 1);
        visit[a] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        // adj[a].push_back(mp(b,false);
        // adj[b].push_back(mp(a,false);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    DFS();

    return 0;
}