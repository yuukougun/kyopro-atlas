#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    long long s = 0;
    int cnt = 0;
    int x;
    while (cin >> x) {  // 読めなくなる（入力が終わる）と cin が偽になって抜ける
        s += x;
        cnt++;
    }
    cout << cnt << ' ' << s << '\n';
    // --8<-- [end:core]
}
