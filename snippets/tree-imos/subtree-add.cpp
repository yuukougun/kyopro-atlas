// 木の上のいもす法（部分木への加算をまとめて処理する）
// 入力：N、続く N - 1 行に辺 u v（1-indexed）、Q、続く Q 行にクエリ
//   1 p x   ：頂点 p の部分木の全頂点に x を足す（頂点 1 が根）
//   2 a b x ：辺 (a, b) を切ったとき a の側に残る頂点すべてに x を足す
// 出力：すべてのクエリの後の各頂点の値（1-indexed の順）
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> par(n, -1), order = {0};  // 根 0 からの BFS 順（親が子より前）
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int c : g[v]) {
            if (c == par[v]) continue;
            par[c] = v;
            order.push_back(c);
        }
    }
    int q;
    cin >> q;
    // --8<-- [start:core]
    vector<long long> mark(n, 0);  // mark[v]：v の部分木全体に足す量
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int p;
            long long x;
            cin >> p >> x;
            mark[p - 1] += x;
        } else {
            int a, b;
            long long x;
            cin >> a >> b >> x;
            a--, b--;
            if (par[a] == b) {
                mark[a] += x;  // a が子：a の側は a の部分木
            } else {
                mark[0] += x;  // b が子：全体に足してから
                mark[b] -= x;  // b の部分木から引く
            }
        }
    }
    for (int i = 1; i < n; i++) {  // BFS 順に、親の値を子へ累積する
        int v = order[i];
        mark[v] += mark[par[v]];
    }
    // --8<-- [end:core]
    for (int v = 0; v < n; v++) cout << mark[v] << '\n';
}
