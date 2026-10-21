#include <bits/stdc++.h>
using namespace std;

int main() {
    int x, m;
    cin >> x >> m;
    // --8<-- [start:core]
    int low = x & -x;          // 最下位の 1 だけを残す（12 = 1100 → 4 = 100）
    int rest = x & (x - 1);    // 最下位の 1 を消す（12 → 8 = 1000）
    vector<int> subs;
    for (int s = m;; s = (s - 1) & m) {  // m の部分集合を大きい順に
        subs.push_back(s);
        if (s == 0) break;               // 0 を処理してから止める
    }
    // --8<-- [end:core]
    cout << low << ' ' << rest << '\n';
    for (int s : subs) cout << s << ' ';
    cout << '\n';
}
