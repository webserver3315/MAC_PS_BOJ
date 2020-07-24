#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int t, x, y, n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;
    while (t--) {
        cin >> x >> y >> n;
        n -= y;
        int r = n - (n / x) * x;
        cout << n + y - r << endl;
    }

    return 0;
}