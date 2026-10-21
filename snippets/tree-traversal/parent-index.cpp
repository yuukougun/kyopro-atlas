// 親の番号が自分より小さい（p_i < i）形の木：番号の順がそのまま「親が子より前」の順になる
// 入力：N、続いて p_2 … p_N（1-indexed、p_i < i）。頂点 1 が根
// 出力：各頂点の「深さ 部分木サイズ」
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> p(n, -1);
    for (int v = 1; v < n; v++) {
        cin >> p[v];
        p[v]--;
        assert(0 <= p[v] && p[v] < v);
    }
    // --8<-- [start:core]
    vector<int> dep(n, 0), sz(n, 1);
    for (int v = 1; v < n; v++) dep[v] = dep[p[v]] + 1;  // 番号の順：親が先に確定している
    for (int v = n - 1; v >= 1; v--) sz[p[v]] += sz[v];  // 番号の逆順：子が先に確定している
    // --8<-- [end:core]
    assert(sz[0] == n);
    for (int v = 0; v < n; v++) cout << dep[v] << ' ' << sz[v] << '\n';
}
