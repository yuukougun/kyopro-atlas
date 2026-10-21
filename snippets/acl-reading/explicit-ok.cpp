#include <bits/stdc++.h>
#include <atcoder/dsu>
#include <atcoder/modint>
using namespace std;
using namespace atcoder;
using mint = modint998244353;

int main() {
    // --8<-- [start:core]
    dsu d(5);           // 丸括弧で作る
    dsu d2 = dsu(5);    // 型名を書いて作ってから入れるのもよい
    vector<dsu> ds(3, dsu(4));
    mint x = 5;         // modint だけは = で作れる
    // --8<-- [end:core]
    d.merge(0, 1);
    d2.merge(2, 3);
    cout << d.size(0) << ' ' << d2.size(3) << ' ' << ds[2].size(0) << ' ' << x.val() << '\n';
}
