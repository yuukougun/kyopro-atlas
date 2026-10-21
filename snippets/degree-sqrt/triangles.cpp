#include <bits/stdc++.h>
using namespace std;

// 単純無向グラフの三角形をすべて列挙する。f(a, b, c) を三角形ごとに 1 回呼ぶ。
// --8<-- [start:core]
template <class F>
void enumerate_triangles(int n, const vector<pair<int, int>>& edges, F f) {
    vector<int> deg(n, 0);
    for (auto [a, b] : edges) deg[a]++, deg[b]++;
    // (次数, 番号) の小さい方から大きい方へ向き付ける
    auto less_rank = [&](int a, int b) {
        return deg[a] != deg[b] ? deg[a] < deg[b] : a < b;
    };
    vector<vector<int>> out(n);       // 出次数はどれも √(2M) 以下
    for (auto [a, b] : edges) {
        if (less_rank(a, b)) out[a].push_back(b);
        else out[b].push_back(a);
    }
    vector<char> mark(n, 0);
    for (int u = 0; u < n; u++) {
        for (int w : out[u]) mark[w] = 1;
        for (int v : out[u])
            for (int w : out[v])
                if (mark[w]) f(u, v, w);     // u → v → w かつ u → w
        for (int w : out[u]) mark[w] = 0;
    }
}
// --8<-- [end:core]

long long naive(int n, const vector<pair<int, int>>& edges) {
    vector<vector<char>> adj(n, vector<char>(n, 0));
    for (auto [a, b] : edges) adj[a][b] = adj[b][a] = 1;
    long long c = 0;
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++)
            for (int d = b + 1; d < n; d++)
                if (adj[a][b] && adj[b][d] && adj[a][d]) c++;
    return c;
}

void self_test() {
    mt19937 rng(2026);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 10 + 1;
        vector<pair<int, int>> edges;
        for (int a = 0; a < n; a++)
            for (int b = a + 1; b < n; b++)
                if (rng() % 3 != 0 || iter % 5 == 0) edges.push_back({a, b});
        long long c = 0;
        set<array<int, 3>> seen;
        enumerate_triangles(n, edges, [&](int a, int b, int d) {
            array<int, 3> t = {a, b, d};
            sort(t.begin(), t.end());
            assert(!seen.count(t));   // 同じ三角形を 2 回数えない
            seen.insert(t);
            c++;
        });
        assert(c == naive(n, edges));
    }
}

int main() {
    self_test();
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& [a, b] : edges) {
        cin >> a >> b;
        a--, b--;
    }
    long long c = 0;
    enumerate_triangles(n, edges, [&](int, int, int) { c++; });
    cout << c << '\n';
}
