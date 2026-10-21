#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    // --8<-- [start:core]
    long long p = 1LL * a * b;        // 1LL * a が long long なので、続く * b も long long で計算する
    long long q = (long long)a * b;   // a を先に広げる。(long long)(a * b) は掛けた後に広げるので誤り
    // --8<-- [end:core]
    assert(p == q);
    cout << p << ' ' << q << '\n';
}
