// 木の重心をすべて求める。部分木サイズを 1 回求め、各頂点で「子の部分木」と「親側の n - sz[v]」の最大を見る。
// 入力：N、続く N-1 行に辺 u v（1-indexed）。
// 出力：1 行目に重心（1-indexed、昇順）、2 行目に各頂点を取り除いたときの最大の成分の大きさ。
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

    // --8<-- [start:core]
    // 頂点 0 を根にして BFS 順 order と親 par を作る（再帰を使わないので一直線の木でも落ちない）
    vector<int> par(n, -1), order = {0};
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int c : g[v]) {
            if (c == par[v]) continue;
            par[c] = v;
            order.push_back(c);
        }
    }
    // BFS 順の逆に子から親へ足すと、部分木サイズ sz が求まる
    vector<int> sz(n, 1);
    for (int i = n - 1; i >= 1; i--) sz[par[order[i]]] += sz[order[i]];

    // v を取り除いたときの成分は「各子の部分木」と「親側（n - sz[v] 頂点）」
    vector<int> mx(n, 0), centroids;
    for (int v = 0; v < n; v++) {
        mx[v] = n - sz[v];  // 親側を忘れない（根では 0）
        for (int c : g[v]) {
            if (c != par[v]) mx[v] = max(mx[v], sz[c]);
        }
        if (2 * mx[v] <= n) centroids.push_back(v);  // どの成分も n/2 以下
    }
    // --8<-- [end:core]

    // 重心は 1 個か、隣り合う 2 個
    assert(centroids.size() == 1 || centroids.size() == 2);
    if (centroids.size() == 2) {
        int a = centroids[0], b = centroids[1];
        assert(par[a] == b || par[b] == a);
        assert(n % 2 == 0);
    }
    // 重心は「最大の成分の大きさ」を最小にする頂点と一致する
    int best = *min_element(mx.begin(), mx.end());
    for (int v = 0; v < n; v++) {
        bool is_c = find(centroids.begin(), centroids.end(), v) != centroids.end();
        assert(is_c == (mx[v] == best));
    }

    for (int i = 0; i < (int)centroids.size(); i++) {
        cout << centroids[i] + 1 << (i + 1 < (int)centroids.size() ? ' ' : '\n');
    }
    for (int v = 0; v < n; v++) cout << mx[v] << (v + 1 < n ? ' ' : '\n');
}
