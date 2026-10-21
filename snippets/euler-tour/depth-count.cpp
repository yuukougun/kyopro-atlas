// オイラーツアー：u の部分木に含まれる深さ d の頂点の数を、深さごとの in の列と二分探索で数える
// 入力：N Q、p_1 … p_{N-1}（頂点 i の親。根は頂点 0、深さ 0）、続く Q 行は「u d」
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    vector<int> par(n, -1);
    for (int i = 1; i < n; i++) {
        cin >> par[i];
        g[par[i]].push_back(i);
    }
    // --8<-- [start:core]
    vector<int> in(n), out(n), dep(n);
    vector<vector<int>> at_depth(n);   // at_depth[d]：深さ d の頂点の in を小さい順に
    int timer = 0;
    auto dfs = [&](auto&& self, int v, int d) -> void {
        dep[v] = d;
        in[v] = timer++;
        at_depth[d].push_back(in[v]);  // DFS の順に積むので自然に昇順になる
        for (int c : g[v]) self(self, c, d + 1);
        out[v] = timer;
    };
    dfs(dfs, 0, 0);

    auto count = [&](int u, int d) -> int {
        if (d < dep[u] || d >= n) return 0;  // u より浅い深さには子孫がいない
        const vector<int>& s = at_depth[d];
        return lower_bound(s.begin(), s.end(), out[u]) - lower_bound(s.begin(), s.end(), in[u]);
    };
    // --8<-- [end:core]

    for (int i = 0; i < q; i++) {
        int u, d;
        cin >> u >> d;
        int res = count(u, d);
        int check = 0;  // 確かめ：親をたどって u に着き、深さが d の頂点を数える
        for (int v = 0; v < n; v++) {
            if (dep[v] != d) continue;
            for (int w = v; w != -1; w = par[w])
                if (w == u) { check++; break; }
        }
        assert(res == check);
        cout << res << '\n';
    }
}
