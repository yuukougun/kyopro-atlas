#include <bits/stdc++.h>
using namespace std;

// 入力：n k、続けて構築した出力（辺の数 m と m 本の辺。1-indexed）または -1
// 出力：条件を満たせば OK、満たさなければ理由
// --8<-- [start:core]
// 「連結な単純グラフで、距離がちょうど 2 の頂点の組が k 個」を満たすかを確かめる
string check(int n, long long k, const vector<pair<int, int>>& edges) {
    vector<vector<int>> g(n);
    set<pair<int, int>> seen;
    for (auto [u, v] : edges) {
        if (u < 0 || u >= n || v < 0 || v >= n) return "vertex out of range";
        if (u == v) return "self loop";
        if (!seen.insert(minmax(u, v)).second) return "multiple edge";
        g[u].push_back(v);
        g[v].push_back(u);
    }
    long long cnt = 0;
    for (int s = 0; s < n; s++) {  // 各頂点から BFS して距離 2 の頂点を数える
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : g[v]) {
                if (dist[w] == -1) {
                    dist[w] = dist[v] + 1;
                    q.push(w);
                }
            }
        }
        for (int t = 0; t < n; t++) {
            if (dist[t] == -1) return "not connected";
            if (dist[t] == 2) cnt++;
        }
    }
    cnt /= 2;  // (s, t) と (t, s) を 2 回数えている
    if (cnt != k) return "distance-2 pairs = " + to_string(cnt);
    return "OK";
}
// --8<-- [end:core]

int main() {
    int n;
    long long k, m;
    cin >> n >> k >> m;
    if (m == -1) {  // 「存在しない」の判定は、小さい n の全探索と突き合わせて確かめる
        cout << "claimed impossible\n";
        return 0;
    }
    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges) {
        cin >> u >> v;
        u--, v--;
    }
    cout << check(n, k, edges) << '\n';
}
