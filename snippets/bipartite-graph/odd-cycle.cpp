// BFS 木を使って、長さが奇数の閉路を 1 つ取り出す
// 入力：N M、続く M 行は辺「u v」（0-indexed）
// 出力：奇閉路がなければ -1。あれば閉路の長さ L と、閉路を順にたどる L 個の頂点
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 奇閉路の頂点を順に並べて返す。なければ空の配列
vector<int> find_odd_cycle(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> dep(n, -1), par(n, -1);
    for (int s = 0; s < n; s++) {
        if (dep[s] != -1) continue;
        dep[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    par[v] = u;
                    q.push(v);
                } else if (dep[v] % 2 == dep[u] % 2) {
                    // BFS では隣の深さの差は 1 以下なので、偶奇が同じなら dep[u] == dep[v]
                    // u と v から同時に親へ上り、出会った頂点 w で 2 本の道をつなぐ
                    vector<int> left, right;
                    int a = u, b = v;
                    while (a != b) {
                        left.push_back(a);
                        right.push_back(b);
                        a = par[a];
                        b = par[b];
                    }
                    left.push_back(a);  // w
                    reverse(right.begin(), right.end());
                    left.insert(left.end(), right.begin(), right.end());
                    return left;  // u → … → w → … → v（v と u は辺で結ばれている）
                }
            }
        }
    }
    return {};
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        edges.insert({min(u, v), max(u, v)});
    }
    vector<int> cyc = find_odd_cycle(g);
    if (cyc.empty()) {
        cout << -1 << '\n';
        return 0;
    }
    // 長さが奇数で、頂点が重複せず、隣り合う頂点（最後と最初も）が辺で結ばれていることを確かめる
    int len = cyc.size();
    assert(len % 2 == 1);
    assert((int)set<int>(cyc.begin(), cyc.end()).size() == len);
    for (int i = 0; i < len; i++) {
        int a = cyc[i], b = cyc[(i + 1) % len];
        assert(edges.count({min(a, b), max(a, b)}));
    }
    cout << len << '\n';
    for (int i = 0; i < len; i++) cout << cyc[i] << (i + 1 < len ? ' ' : '\n');
}
