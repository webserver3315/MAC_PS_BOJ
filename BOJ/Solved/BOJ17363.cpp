#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int R, C;
vector<string> vct;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> R >> C;
    for (int r = 0; r < R; r++) {
        string tmp;
        cin >> tmp;
        vct.push_back(tmp);
    }

    for (int c = C - 1; c >= 0; c--) {
        for (int r = 0; r < R; r++) {
            if (vct[r][c] == '-')
                cout << '|';
            else if (vct[r][c] == '|')
                cout << '-';
            else if (vct[r][c] == '\\')
                cout << '/';
            else if (vct[r][c] == '/')
                cout << '\\';
            else if (vct[r][c] == '^')
                cout << '<';
            else if (vct[r][c] == '<')
                cout << 'v';
            else if (vct[r][c] == 'v')
                cout << '>';
            else if (vct[r][c] == '>')
                cout << '^';
            else {
                cout << vct[r][c];
            }
        }
        cout << endl;
    }

    return 0;
}