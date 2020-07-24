#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int t, n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;
    while (t--) {
        cin >> n;
        int cnt = 0;
        while (1) {
            if (n == 1) {
                cout << cnt << endl;
                break;
            }
            if (n % 6 == 0) {
                n /= 6;
                cnt++;
                continue;
            } else {
                n *= 2;
                cnt++;
                if (n % 6 == 0) {
                    n /= 6;
                    cnt++;
                    continue;
                } else {
                    break;
                }
            }
        }
        if (n != 1) {
            cout << -1 << endl;
        }
    }

    return 0;
}