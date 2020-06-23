#include <bits/stdc++.h>
#define endl '\n'
#define pii pair<int, int>
#define ff first
#define ss second
#define mp(a, b) make_pair(a, b)
#define myMAX (int)1e5 + 1
using namespace std;

int N, M;
int BackSmallCnt[myMAX];
int FrontSmallCnt[myMAX];
int motteru[myMAX];
bool visited[myMAX];

/*
참조: https://emotionofengineering.tistory.com/28
이름과 번호가 따로 논다는 것이 익숙하지 않아 자꾸 헷갈렸다. 하나도 빠짐없으며 이름과 번호가 따로 논다는 점을 교묘하게 캐치하여,
자신 앞의 작은 카드, 자기 뒤의 큰카드 개수까지 자연스럽게 얻을 수 있다는 점을 깨달아야만 했다.
*/

bool solve() {
    /*
    mm으로부터 k번 학생 앞에 있는 작은 카드소지자의 머릿수를 get 가능
    rmm으로부터 k번 학생 뒤에 있는 작은카드소시자의 머릿수를 get 가능
    */
    for (int i = 1; i <= M; i++) {
        int maeChisaMochi = i - 1 - FrontSmallCnt[i];
        // cout << mm.count(i) << endl;
        int UsiroChisaMochi = BackSmallCnt[i];
        int val = maeChisaMochi + UsiroChisaMochi + 1;
        if (visited[val]) {
            return false;
        }
        // cout << i << " student is " << maeChisaMochi << " + " << UsiroChisaMochi << " = " << val << endl;
        motteru[i] = val;
        visited[val] = true;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> M >> N;  //변수 잘못 바꿔썼다;;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        BackSmallCnt[a]++;   //a 뒤에 b가 있음을 찾기위함
        FrontSmallCnt[b]++;  //b 앞에 a가 있음을 찾기위함
    }
    if (solve()) {
        for (int i = 1; i <= M; i++) {
            cout << motteru[i] << " ";
        }
        cout << endl;
        return 0;
    } else {
        cout << -1 << endl;
        return 0;
    }

    return 0;
}