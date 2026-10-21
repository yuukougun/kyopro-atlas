// BFS で 2 色に塗り、二部グラフなら成分ごとの色の数 (a, b) を出力する
// 入力：N M、続く M 行は辺「u v」（0-indexed、自己ループ・多重辺があってもよい）
// 出力：二部グラフでなければ No。二部グラフなら Yes と、成分ごとに「a b」（成分の最小の頂点の順）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 二部グラフなら各頂点の色（0 か 1）を、そうでなければ空の配列を返す
vector<int> bipartite_coloring(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> color(n, -1);  // −1 は未訪問
    for (int s = 0; s < n; s++) {
        if (color[s] != -1) continue;  // 非連結なら、未訪問の頂点ごとに塗り始める
        color[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;  // 隣は反対の色
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return {};  // 同じ色どうしの辺（自己ループも含む）
                }
            }
        }
    }
    return color;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> color = bipartite_coloring(g);
    if (color.empty()) {
        cout << "No\n";
        return 0;
    }
    // すべての辺の両端が違う色になっていることを確かめる
    for (int u = 0; u < n; u++) {
        for (int v : g[u]) assert(color[u] != color[v]);
    }
    // 成分ごとに色の数を数える（BFS をもう一度回す）
    cout << "Yes\n";
    vector<bool> seen(n, false);
    for (int s = 0; s < n; s++) {
        if (seen[s]) continue;
        array<int, 2> cnt = {0, 0};
        queue<int> q;
        q.push(s);
        seen[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cnt[color[u]]++;
            for (int v : g[u]) {
                if (!seen[v]) {
                    seen[v] = true;
                    q.push(v);
                }
            }
        }
        cout << cnt[0] << ' ' << cnt[1] << '\n';
    }
}
