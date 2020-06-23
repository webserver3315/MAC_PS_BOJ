#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
/*
Carry
not cleared
*/
int i1, i2;
string s1, s2;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // cin >> s1 >> s2;
    // while (s1 == "0" && s2 == "0") {

    // }
    //10 digit 이니까 int 범위 내다.
    while (1) {
        cin >> i1 >> i2;
        int ret = 0;
        if (i1 == 0 && i2 == 0)
            break;
        while (i1 != 0 || i2 != 0) {
            int ld1 = i1 % 10;
            int ld2 = i2 % 10;
            i1 /= 10;
            i2 /= 10;
            // cout << "ld1 and ld2 is " << ld1 << " " << ld2 << " " << endl;
            // cout << "i1 and i2 is " << i1 << " " << i2 << endl;
            if (ld1 + ld2 > 9) {
                ret++;
                i1 += 1;
            }
        }
        cout << ret << endl;
    }
    return 0;
}