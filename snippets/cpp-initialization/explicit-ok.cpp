#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    atcoder::dsu d(n);                 // 丸括弧で作る
    atcoder::dsu e = atcoder::dsu(n);  // 型を書けば = でもよい
    atcoder::dsu f;                    // 大きさ 0 で作っておき、
    f = atcoder::dsu(n);               // 大きさが分かってから作り直す
    // --8<-- [end:core]
    if (n >= 2) d.merge(0, 1);
    cout << (n >= 2 ? d.size(0) : 0) << ' ' << (n >= 1 ? e.size(0) + f.size(0) : 0) << '\n';
}
