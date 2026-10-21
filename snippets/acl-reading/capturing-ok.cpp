#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;

// --8<-- [start:core]
int m;  // 実行時に決まる値はグローバル変数に置く
int op(int x, int y) { return (x + y) % m; }
int e() { return 0; }

int main() {
    int n;
    cin >> n >> m;  // 入力を読んでから segtree を作る
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    segtree<int, op, e> seg(a);
    // --8<-- [end:core]
    cout << seg.all_prod() << '\n';
}
