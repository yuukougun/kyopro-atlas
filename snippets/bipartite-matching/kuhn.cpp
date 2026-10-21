// 増加路を 1 本ずつ探す二部マッチング（Kuhn の方法）。
// 入力：左の頂点数 L、右の頂点数 R、辺の本数 M と、M 本の辺 (u, v)（左 u と右 v、どちらも 0-indexed）。
// 出力：最大マッチングの大きさと、各左の頂点の相手（いなければ -1）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int l, r, m;
    cin >> l >> r >> m;
    vector<vector<int>> g(l);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    // --8<-- [start:core]
    vector<int> match_l(l, -1), match_r(r, -1);  // 相手の番号（いなければ -1）
    vector<int> used(l, -1);  // used[u] == stamp なら、今回の探索で u を訪れた
    int stamp = 0;
    // 左の頂点 u から交互路をのばし、空いた右の頂点に着けば反転して true を返す
    auto dfs = [&](auto&& self, int u) -> bool {
        used[u] = stamp;
        for (int v : g[u]) {
            int w = match_r[v];  // v の今の相手（左の頂点）
            if (w == -1 || (used[w] != stamp && self(self, w))) {
                match_l[u] = v;  // 帰りがけに組を付け替える = 交互路の反転
                match_r[v] = u;
                return true;
            }
        }
        return false;
    };
    int size = 0;
    for (int u = 0; u < l; u++) {
        stamp++;  // 訪れた印は始点ごとに消す
        if (dfs(dfs, u)) size++;
    }
    // --8<-- [end:core]

    cout << size << '\n';
    for (int u = 0; u < l; u++) cout << match_l[u] << (u + 1 < l ? ' ' : '\n');
    if (l == 0) cout << '\n';
}
