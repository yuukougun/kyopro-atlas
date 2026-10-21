// 全方位木 DP の枠組み：各頂点 v について、v を含む連結な頂点集合の数を M で割った余り
// （M は素数とは限らないので、逆元を使わず左右からの累積で「自分以外」を作る）
// 入力：N M、続く N - 1 行に辺 u v（1-indexed）。出力：頂点 1, …, N の値
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// e：合成の単位元、merge：子の側の値どうしの合成（結合法則を満たす）
// add_root(x, c, v)：c の子の合成が x のとき、c を根に付けて辺 (c, v) を通し、v へ渡す値
// 戻り値の ans[v] は、v のすべての隣の側の値を合成したもの
template <class T, class Merge, class AddRoot>
vector<T> rerooting(const vector<vector<int>>& g, T e, Merge merge, AddRoot add_root) {
    int n = g.size();
    vector<int> par(n, -1), order = {0};
    for (int i = 0; i < (int)order.size(); i++) {  // BFS 順（親が子より前）
        int v = order[i];
        for (int c : g[v])
            if (c != par[v]) par[c] = v, order.push_back(c);
    }
    // 1 回目（下から上）：dp[v] = v の子の側の値の合成
    vector<T> dp(n, e), up(n, e), ans(n, e);
    for (int i = n - 1; i >= 1; i--) {
        int v = order[i];
        dp[par[v]] = merge(dp[par[v]], add_root(dp[v], v, par[v]));
    }
    // 2 回目（上から下）：up[c] = 根を c にしたときの、親 v の子の側の値の合成
    for (int v : order) {
        int k = g[v].size();
        vector<T> val(k), L(k + 1, e), R(k + 1, e);
        for (int i = 0; i < k; i++) {
            int u = g[v][i];
            val[i] = (u == par[v]) ? add_root(up[v], u, v) : add_root(dp[u], u, v);
        }
        for (int i = 0; i < k; i++) L[i + 1] = merge(L[i], val[i]);
        for (int i = k - 1; i >= 0; i--) R[i] = merge(val[i], R[i + 1]);
        ans[v] = L[k];
        for (int i = 0; i < k; i++)
            if (g[v][i] != par[v]) up[g[v][i]] = merge(L[i], R[i + 1]);  // i 番目だけを除く
    }
    return ans;
}
// --8<-- [end:core]

int main() {
    int n;
    long long m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // --8<-- [start:usage]
    // 子 c の側は「使わない（1 通り）」か「c を含む連結な集合（x 通り）」なので x + 1 を掛ける
    auto merge = [&](long long a, long long b) { return a * b % m; };
    auto add_root = [&](long long x, int, int) { return (x + 1) % m; };
    vector<long long> ans = rerooting<long long>(g, 1 % m, merge, add_root);
    // --8<-- [end:usage]
    // 素朴に各頂点を根にして木 DP をやり直して確かめる
    if (n <= 300) {
        for (int r = 0; r < n; r++) {
            auto dfs = [&](auto&& self, int v, int p) -> long long {
                long long res = 1 % m;
                for (int c : g[v])
                    if (c != p) res = res * ((self(self, c, v) + 1) % m) % m;
                return res;
            };
            assert(dfs(dfs, r, -1) == ans[r]);
        }
    }
    for (int v = 0; v < n; v++) cout << ans[v] << '\n';
}
