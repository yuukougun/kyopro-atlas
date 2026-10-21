#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long cost;
};

int main() {
    int m;
    cin >> m;
    // --8<-- [start:core]
    vector<vector<Edge>> g(m + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        g[u].emplace_back(v, c);   // C++20：コンストラクタがなくても丸括弧で作れる
        g[u].push_back({v, c});    // C++17 まではこう書く
    }
    // --8<-- [end:core]
    // --8<-- [start:narrow]
    vector<Edge> es;
    es.emplace_back(1.9, 2);       // 1.9 が黙って int の 1 になる（警告も出ない）
    // Edge e{1.9, 2};             // 波括弧ならコンパイルエラー（縮小変換）
    // --8<-- [end:narrow]
    long long total = 0;
    for (auto& row : g)
        for (auto& e : row) total += e.cost;
    cout << total << ' ' << es[0].to << '\n';
}
