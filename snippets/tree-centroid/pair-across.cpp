// 頂点を ⌊N/2⌋ 組のペアにして、ペアの距離（辺の数）の和を最大にする。
// 重心 c から見て別の枝の頂点どうしを組むと、すべてのペアが c を通り、和は各辺の上限 min(s, N - s) の合計に達する。
// 入力：N、続く N-1 行に辺 u v（1-indexed）。出力：1 行目に距離の和、続いてペア（1-indexed）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    assert(n >= 1);
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // 重心を 1 つ求める（centroid.cpp と同じ）
    vector<int> par(n, -1), order = {0};
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int c : g[v]) {
            if (c == par[v]) continue;
            par[c] = v;
            order.push_back(c);
        }
    }
    vector<int> sz(n, 1);
    for (int i = n - 1; i >= 1; i--) sz[par[order[i]]] += sz[order[i]];
    int c = -1;
    for (int v = 0; v < n && c < 0; v++) {
        int mx = n - sz[v];
        for (int to : g[v])
            if (to != par[v]) mx = max(mx, sz[to]);
        if (2 * mx <= n) c = v;
    }

    // --8<-- [start:core]
    // 重心 c の枝ごとに頂点を集めて 1 列に並べる（同じ枝の頂点は列の中で連続する）
    // N が偶数なら c も列に入れ、奇数なら c を外す（外した c がペアにならない 1 頂点）
    vector<int> seq, branch(n, -1), dep(n, 0);
    if (n % 2 == 0) seq.push_back(c);
    for (int b : g[c]) {
        vector<int> st = {b};
        branch[b] = b, dep[b] = 1;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            seq.push_back(v);
            for (int to : g[v]) {
                if (to == c || branch[to] != -1) continue;
                branch[to] = b, dep[to] = dep[v] + 1;
                st.push_back(to);
            }
        }
    }
    // 列を半分に切り、i 番目と i + k 番目を組む。どの枝も k 頂点以下なので、
    // k 離れた 2 つの位置が同じ枝に入ることはなく、すべてのペアが c を通る
    int k = (int)seq.size() / 2;
    vector<pair<int, int>> pairs;
    long long total = 0;
    for (int i = 0; i < k; i++) {
        int u = seq[i], v = seq[i + k];
        assert(u == c || branch[u] != branch[v]);
        pairs.push_back({u, v});
        total += dep[u] + dep[v];  // c を通るので距離は c からの深さの和
    }
    // --8<-- [end:core]

    // 上限との一致：辺の片側が s 頂点なら、その辺を通るペアは min(s, n - s) 組以下
    long long bound = 0;
    for (int v = 1; v < n; v++) bound += min(sz[order[v]], n - sz[order[v]]);
    assert(total == bound);

    cout << total << '\n';
    for (auto [u, v] : pairs) cout << u + 1 << ' ' << v + 1 << '\n';
}
