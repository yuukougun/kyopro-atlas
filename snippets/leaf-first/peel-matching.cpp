// 木の最大マッチングの大きさを、次数 1 の頂点をキューで削りながら求める。
// 入力：n、続いて辺 n - 1 本（1-indexed）。出力：最大マッチングの辺の数。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// g は木（頂点 0..n-1）の隣接リスト
int max_matching_by_peeling(int n, const vector<vector<int>>& g) {
    vector<int> deg(n);
    for (int v = 0; v < n; v++) deg[v] = g[v].size();  // 削られていない隣の数
    vector<bool> removed(n, false), matched(n, false);
    queue<int> q;
    for (int v = 0; v < n; v++) {
        if (deg[v] <= 1) q.push(v);  // 最初の葉（n = 1 なら次数 0 の頂点）
    }
    int res = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        removed[u] = true;
        for (int p : g[u]) {
            if (removed[p]) continue;  // 残っている隣はたかだか 1 つ
            if (!matched[u] && !matched[p]) {  // 葉 u とその隣 p を組む
                matched[u] = matched[p] = true;
                res++;
            }
            deg[p]--;
            if (deg[p] == 1) q.push(p);  // 新しく葉になった頂点を足す
        }
    }
    return res;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    assert(n >= 1);
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int res = max_matching_by_peeling(n, g);
    assert(0 <= res && 2 * res <= n);
    cout << res << '\n';
}
