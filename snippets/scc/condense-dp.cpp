#include <bits/stdc++.h>
#include <atcoder/scc>
using namespace std;

// 頂点 1 から辺をたどって好きなだけ動く（どこで止めてもよい）。各頂点の非負の価値 w は初めて訪れたときに 1 回だけ得る。
// 得られる価値の和の最大を求める（価値が非負なので、成分に入ったら全部回っても損をしない）
int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        assert(w[i] >= 0);  // 非負が前提
    }
    vector<pair<int, int>> edges(m);
    // --8<-- [start:core]
    atcoder::scc_graph g(n);
    for (auto& [u, v] : edges) {
        cin >> u >> v;
        u--, v--;  // 1-indexed → 0-indexed
        g.add_edge(u, v);
    }
    vector<vector<int>> groups = g.scc();  // トポロジカル順の成分のリスト
    int k = groups.size();
    vector<int> comp(n);  // comp[v] ＝ v が入る成分の番号（トポロジカル順）
    vector<long long> val(k, 0);  // 成分の価値の和
    for (int c = 0; c < k; c++) {
        for (int v : groups[c]) {
            comp[v] = c;
            val[c] += w[v];
        }
    }
    // 縮約した DAG：成分をまたぐ辺だけを残す。辺は必ず番号の小さい成分から大きい成分へ向く
    vector<vector<int>> dag(k);
    for (auto [u, v] : edges) {
        if (comp[u] != comp[v]) dag[comp[u]].push_back(comp[v]);
    }
    for (int c = 0; c < k; c++) {
        for (int d : dag[c]) assert(c < d);  // scc() の順はトポロジカル順
    }
    // dp[c] ＝ 成分 c に入ってから得られる価値の和の最大。後ろの成分から順に決まる
    vector<long long> dp(k, 0);
    for (int c = k - 1; c >= 0; c--) {
        long long best = 0;
        for (int d : dag[c]) best = max(best, dp[d]);
        dp[c] = val[c] + best;
    }
    cout << dp[comp[0]] << '\n';
    // --8<-- [end:core]
}
