// DAG 上の DP：N 頂点 M 辺の有向グラフ（辺 u → v、入力は 1-indexed）で、
// Kahn 法でトポロジカル順を作り、その順に (1) 最長路の辺数 (2) 頂点 1 から N への経路の数 を求める。
// 閉路があってトポロジカル順が作れなければ -1 を出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    assert(n >= 1 && m >= 0);
    vector<vector<int>> g(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;  // 0-indexed に直す
        assert(0 <= u && u < n && 0 <= v && v < n);
        g[u].push_back(v);
        indeg[v]++;
    }

    // --8<-- [start:core]
    // Kahn 法：入次数 0 の頂点から取り出し、出る辺を消していく
    vector<int> order;
    queue<int> q;
    for (int v = 0; v < n; v++) if (indeg[v] == 0) q.push(v);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    if ((int)order.size() < n) {  // 取り出せない頂点が残った＝閉路がある
        cout << -1 << '\n';
        return 0;
    }

    const long long MOD = 998244353;
    vector<int> len(n, 0);         // len[v]：v で終わる経路の辺数の最大（どこから始めてもよいので全頂点 0）
    vector<long long> cnt(n, 0);   // cnt[v]：頂点 0 から v への経路の数
    cnt[0] = 1;                    // 長さ 0 の経路が 1 本
    for (int u : order) {          // u の値は、u に入る辺をすべて配り終えて確定している
        for (int v : g[u]) {       // 配る DP
            len[v] = max(len[v], len[u] + 1);
            cnt[v] = (cnt[v] + cnt[u]) % MOD;
        }
    }
    cout << *max_element(len.begin(), len.end()) << ' ' << cnt[n - 1] << '\n';
    // --8<-- [end:core]
}
