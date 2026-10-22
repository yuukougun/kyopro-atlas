#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

// 入力：頂点数 n、辺数 m、DAG の辺 u v（0-indexed、u→v）
// 出力：頂点を共有しないパスでの最小被覆の本数、
//       頂点を共有してよい鎖での最小被覆の本数、最大反鎖の頂点

// --8<-- [start:core]
// DAG の最小パス被覆の本数。頂点 v を「出る側 v」と「入る側 n + v」に分ける
int min_path_cover(int n, const vector<pair<int, int>>& edges) {
    int s = 2 * n, t = s + 1;
    atcoder::mf_graph<int> g(2 * n + 2);
    for (int v = 0; v < n; v++) {
        g.add_edge(s, v, 1);      // 出る側：後ろにつなぐ相手は 1 つまで
        g.add_edge(n + v, t, 1);  // 入る側：前につなぐ相手は 1 つまで
    }
    for (auto [u, v] : edges) g.add_edge(u, n + v, 1);
    return n - g.flow(s, t);  // つないだ辺 1 本ごとにパスが 1 本減る
}
// --8<-- [end:core]

// --8<-- [start:antichain]
// 推移閉包を取ってから同じ二部グラフを作り、最大反鎖を取り出す
vector<int> max_antichain(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n);
    for (auto [u, v] : edges) adj[u].push_back(v);
    int s = 2 * n, t = s + 1;
    atcoder::mf_graph<int> g(2 * n + 2);
    for (int v = 0; v < n; v++) {
        g.add_edge(s, v, 1);
        g.add_edge(n + v, t, 1);
    }
    for (int u = 0; u < n; u++) {  // u から届く頂点 w すべてに辺 u→w を張る
        vector<bool> seen(n, false);
        vector<int> st = adj[u];
        while (!st.empty()) {
            int w = st.back();
            st.pop_back();
            if (seen[w]) continue;
            seen[w] = true;
            g.add_edge(u, n + w, 1);
            for (int x : adj[w]) st.push_back(x);
        }
    }
    int matching = g.flow(s, t);
    vector<bool> reach = g.min_cut(s);  // 残余グラフで s から届くか
    vector<int> res;                    // どちらの側も最小頂点被覆に入らない頂点
    for (int v = 0; v < n; v++) {
        if (reach[v] && !reach[n + v]) res.push_back(v);
    }
    assert((int)res.size() == n - matching);  // 最大反鎖 ＝ 最小の鎖の本数
    return res;
}
// --8<-- [end:antichain]

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges) cin >> u >> v;

    int paths = min_path_cover(n, edges);
    vector<int> anti = max_antichain(n, edges);
    int chains = anti.size();
    assert(chains <= paths);  // 頂点を共有してよい分だけ少なくて済む

    // 小さいグラフでは、到達可能性を全部求めて反鎖を全探索で確かめる
    if (n <= 12) {
        vector<vector<bool>> reach(n, vector<bool>(n, false));
        for (auto [u, v] : edges) reach[u][v] = true;
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (reach[i][k] && reach[k][j]) reach[i][j] = true;
        auto is_antichain = [&](int mask) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if ((mask >> i & 1) && (mask >> j & 1) && reach[i][j]) return false;
            return true;
        };
        int best = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (is_antichain(mask)) best = max(best, __builtin_popcount(mask));
        }
        assert(best == chains);
        int got = 0;
        for (int v : anti) got |= 1 << v;
        assert(is_antichain(got));
    }

    cout << "paths " << paths << '\n';
    cout << "chains " << chains << '\n';
    cout << "antichain:";
    for (int v : anti) cout << ' ' << v;
    cout << '\n';
}
