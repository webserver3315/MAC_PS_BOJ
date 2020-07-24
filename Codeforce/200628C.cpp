#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int t;
vector<char> stk;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        stk.clear();
        string tmp;
        cin >> tmp;
        for (char c : tmp) {
            stk.push_back(c);
            // cout << "푸시: " << stk.back() << endl;
            if (stk.size() == 1)
                continue;
            else {
                if (stk[stk.size() - 2] == '(' && stk.back() == ')') {
                    // cout << "팝: " << stk.back() << endl;
                    stk.pop_back();
                    // cout << "팝: " << stk.back() << endl;
                    stk.pop_back();
                }
            }
        }
        cout << (int)stk.size() / 2 << endl;
    }

    return 0;
}