#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

int main() {
    // 入力：n m と m 本の辺（1-indexed）。
    // 出力：閉路を作る辺（両端がすでに同じグループ）の本数と、連結成分の数
    int n, m;
    cin >> n >> m;
    // --8<-- [start:core]
    atcoder::dsu d(n);
    int extra = 0;   // すでに同じグループだった辺の数
    int merged = 0;  // 併合に成功した回数
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;  // 0-indexed に直す
        if (d.same(u, v)) {
            extra++;  // 自己ループ・多重辺もここに来る
        } else {
            d.merge(u, v);
            merged++;
        }
    }
    int components = n - merged;
    // --8<-- [end:core]
    assert((int)d.groups().size() == components);
    assert(extra + merged == m);
    cout << extra << ' ' << components << '\n';
}
