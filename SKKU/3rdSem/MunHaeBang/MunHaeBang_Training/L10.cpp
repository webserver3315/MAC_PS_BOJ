#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int V, E;
vector<int> adj[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back(b);
        adj[b].push_back(a);
        int* a;
    }

    return 0;
}