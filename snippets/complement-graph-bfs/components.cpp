// 元のグラフ G（N 頂点 M 辺、0-indexed の入力）の補グラフを連結成分に分け、
// 成分の数と、各成分の頂点（昇順）を、最小の頂点の小さい順に出力する。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
vector<vector<int>> complement_components(const vector<vector<int>>& g) {
    int n = g.size();
    vector<char> mark(n, 0);
    vector<int> rest(n);  // 未訪問の頂点。すべての BFS で共有する
    iota(rest.begin(), rest.end(), 0);
    vector<vector<int>> comps;
    while (!rest.empty()) {
        int s = rest.back();  // 残っている頂点から新しい成分を始める
        rest.pop_back();
        vector<int> comp = {s};
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int w : g[u]) mark[w] = 1;
            vector<int> keep;
            for (int w : rest) {
                if (mark[w]) {
                    keep.push_back(w);
                } else {
                    comp.push_back(w);
                    q.push(w);
                }
            }
            rest.swap(keep);
            for (int w : g[u]) mark[w] = 0;
        }
        comps.push_back(comp);
    }
    return comps;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        assert(a != b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<vector<int>> comps = complement_components(g);
    for (auto& c : comps) sort(c.begin(), c.end());
    sort(comps.begin(), comps.end());
    int total = 0;
    for (auto& c : comps) total += c.size();
    assert(total == n);
    cout << comps.size() << '\n';
    for (auto& c : comps) {
        cout << c.size();
        for (int v : c) cout << ' ' << v;
        cout << '\n';
    }
}
