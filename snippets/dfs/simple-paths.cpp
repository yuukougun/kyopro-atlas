// バックトラック型の DFS：無向グラフで頂点 0 から始まる単純パス（長さ 0 の 1 頂点だけのものも含む）の数を、
// 上限 limit で打ち切って数える。入力は N M limit と辺 (u, v)（1-indexed）。
// 呼び出し 1 回で 1 本のパスを数えるので、呼び出しは limit 回以下、全体で O(limit × 最大次数)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    long long limit;
    cin >> n >> m >> limit;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // --8<-- [start:core]
    vector<bool> onpath(n, false);  // いまのパスに載っている頂点（訪問済みではない）
    long long count = 0;
    auto dfs = [&](auto&& self, int v) -> void {
        if (count >= limit) return;  // 上限に達したら打ち切る
        count++;                     // 0 から v までのパスを 1 本数える
        onpath[v] = true;            // 行きがけで印を付ける
        for (int to : g[v]) {
            if (!onpath[to]) self(self, to);
        }
        onpath[v] = false;  // 帰りがけで印を外す（別のパスでは v を通ってよい）
    };
    dfs(dfs, 0);
    // --8<-- [end:core]
    cout << count << '\n';
}
