#include <bits/stdc++.h>
using namespace std;

// 実行はしない（同じ値が 10^5 個のとき、手元の g++-13・g++-15 の -O2 で Segmentation fault）。
// 本文の「比較関数に <= を書くと sort が壊れる」の再現用で、コンパイルが通ること（警告も出ないこと）だけを確かめる
int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    vector<int> a(n, 1);  // 同じ値が n 個
    sort(a.begin(), a.end(), [](int x, int y) { return x <= y; });
    // --8<-- [end:core]
    cout << a.size() << '\n';
}
