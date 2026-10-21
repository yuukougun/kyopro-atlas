// 元のグラフ G（N 頂点 M 辺、1-indexed の入力）の補グラフで、頂点 1 からの距離（届かなければ -1）と、
// 最短路の本数（mod 998244353、届かなければ 0）を頂点ごとに出力する。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// g は元のグラフの隣接リスト（g で隣接する組は、補グラフでは隣接しない）
vector<int> complement_bfs(const vector<vector<int>>& g, int s) {
    int n = g.size();
    vector<int> dist(n, -1);
    vector<char> mark(n, 0);  // いま取り出した頂点 u と、元のグラフで隣接するか
    vector<int> rest;         // 未訪問の頂点
    for (int v = 0; v < n; v++) {
        if (v != s) rest.push_back(v);
    }
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int w : g[u]) mark[w] = 1;
        vector<int> keep;  // u からは補グラフの辺がないので、未訪問に残す頂点
        for (int w : rest) {
            if (mark[w]) {
                keep.push_back(w);
            } else {
                dist[w] = dist[u] + 1;  // 補グラフで u と隣接する。ここで取り出す
                q.push(w);
            }
        }
        rest.swap(keep);
        for (int w : g[u]) mark[w] = 0;  // 印を消しておく
    }
    return dist;
}
// --8<-- [end:core]

// --8<-- [start:count]
// 補グラフで s から各頂点への最短路の本数。1 つ前の層の合計から、元のグラフで隣接する頂点の分を引く
vector<mint> count_paths(const vector<vector<int>>& g, const vector<int>& dist, int s) {
    int n = g.size();
    int maxd = *max_element(dist.begin(), dist.end());
    vector<vector<int>> layer(maxd + 1);
    for (int v = 0; v < n; v++) {
        if (dist[v] >= 0) layer[dist[v]].push_back(v);
    }
    vector<mint> cnt(n, 0);
    cnt[s] = 1;
    for (int d = 1; d <= maxd; d++) {
        mint total = 0;  // 距離 d - 1 の頂点の本数の合計
        for (int u : layer[d - 1]) total += cnt[u];
        for (int v : layer[d]) {
            cnt[v] = total;
            for (int u : g[v]) {
                if (dist[u] == d - 1) cnt[v] -= cnt[u];  // u から v へは補グラフの辺がない
            }
        }
    }
    return cnt;
}
// --8<-- [end:count]

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        assert(a != b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> dist = complement_bfs(g, 0);
    assert(dist[0] == 0);
    vector<mint> cnt = count_paths(g, dist, 0);
    for (int v = 0; v < n; v++) cout << dist[v] << (v + 1 < n ? ' ' : '\n');
    for (int v = 0; v < n; v++) cout << cnt[v].val() << (v + 1 < n ? ' ' : '\n');
}
