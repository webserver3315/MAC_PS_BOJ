#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    n--;
    n %= 8;
    if (n < 5) {
        cout << n + 1 << endl;
    } else {
        cout << 8 - n + 1 << endl;
    }
    return 0;
}