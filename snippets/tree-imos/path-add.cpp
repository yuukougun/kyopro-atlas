// パスへの加算をまとめて処理する（木の上のいもす法・葉から上へ累積する）
// 入力：N、続く N - 1 行に辺 u v（1-indexed）、Q、続く Q 行に u v x
//   u と v を結ぶパス上の全頂点（両端を含む）に x を足す
// 出力：各頂点の値、続いて各辺 (par[c], c) を通ったパスの本数（c = 2..N の順。頂点 1 が根）
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
    // 根 0 からの BFS 順・親・深さと、LCA のためのダブリングの表
    vector<int> par(n, -1), dep(n, 0), order = {0};
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int c : g[v]) {
            if (c == par[v]) continue;
            par[c] = v;
            dep[c] = dep[v] + 1;
            order.push_back(c);
        }
    }
    const int LOG = 18;
    vector<vector<int>> up(LOG, vector<int>(n));
    for (int v = 0; v < n; v++) up[0][v] = (par[v] == -1 ? v : par[v]);
    for (int k = 0; k + 1 < LOG; k++)
        for (int v = 0; v < n; v++) up[k + 1][v] = up[k][up[k][v]];
    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int k = LOG - 1; k >= 0; k--)
            if (dep[u] - (1 << k) >= dep[v]) u = up[k][u];
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--)
            if (up[k][u] != up[k][v]) u = up[k][u], v = up[k][v];
        return up[0][u];
    };
    int q;
    cin >> q;
    // --8<-- [start:core]
    vector<long long> val(n, 0), cnt(n, 0);  // 頂点の値の印と、辺を通る本数の印
    for (int i = 0; i < q; i++) {
        int u, v;
        long long x;
        cin >> u >> v >> x;
        u--, v--;
        int l = lca(u, v);
        val[u] += x, val[v] += x;  // 頂点版：両端に +x
        val[l] -= x;               // lca で 1 回打ち消し
        if (par[l] != -1) val[par[l]] -= x;  // lca の親でもう 1 回打ち消す
        cnt[u] += 1, cnt[v] += 1;  // 辺版：両端に +1
        cnt[l] -= 2;               // lca で 2 回打ち消す
    }
    for (int i = n - 1; i >= 1; i--) {  // BFS 順の逆に、子の値を親へ累積する
        int v = order[i];
        val[par[v]] += val[v];
        cnt[par[v]] += cnt[v];
    }
    // ここで val[v] は v の値、cnt[c] は辺 (par[c], c) を通ったパスの本数
    // --8<-- [end:core]
    for (int v = 0; v < n; v++) cout << val[v] << '\n';
    for (int c = 1; c < n; c++) cout << cnt[c] << (c + 1 < n ? ' ' : '\n');
}
