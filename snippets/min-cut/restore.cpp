#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

// 有向グラフの s-t 最小カットの容量と、カットに入る辺（0-indexed の番号）を出力する。
int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<int> eu(m), ev(m);
    vector<long long> ec(m);
    for (int i = 0; i < m; i++) cin >> eu[i] >> ev[i] >> ec[i];
    // --8<-- [start:core]
    atcoder::mf_graph<long long> g(n);
    for (int i = 0; i < m; i++) g.add_edge(eu[i], ev[i], ec[i]);  // i 番目の辺の番号は i
    long long cut = g.flow(s, t);           // flow_limit なしで 1 回だけ呼ぶ
    vector<bool> side = g.min_cut(s);       // 残余グラフで s から届くか ＝ s 側か
    vector<int> cut_edges;
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        if (side[eu[i]] && !side[ev[i]]) {  // s 側から t 側へ向かう辺だけがカットに入る
            cut_edges.push_back(i);
            sum += ec[i];
        }
    }
    assert(sum == cut);                     // 最大流最小カット定理
    // --8<-- [end:core]
    cout << cut << '\n' << cut_edges.size() << '\n';
    for (int i : cut_edges) cout << i << '\n';
}
