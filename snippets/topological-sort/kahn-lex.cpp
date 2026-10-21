// Kahn 法：N 頂点 M 辺の有向グラフ（辺 a → b は「a は b より前」、入力は 1-indexed）で、
// 辞書順最小のトポロジカル順と、トポロジカル順が一意かを求める。
// 閉路があって並べられなければ -1 を出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    assert(n >= 1 && m >= 0);
    vector<vector<int>> g(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;  // 0-indexed に直す
        assert(0 <= a && a < n && 0 <= b && b < n);
        g[a].push_back(b);
        indeg[b]++;  // 多重辺も 1 本ずつ数える（消すときも 1 本ずつ減らすので合う）
    }

    // --8<-- [start:core]
    // 入次数 0 の頂点を、番号の小さい順に取り出せる優先度付きキューに入れる
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int v = 0; v < n; v++) if (indeg[v] == 0) pq.push(v);
    vector<int> order;
    bool unique = true;
    while (!pq.empty()) {
        if (pq.size() >= 2) unique = false;  // 次に置ける頂点が 2 つ以上ある
        int u = pq.top();
        pq.pop();
        order.push_back(u);
        for (int v : g[u]) {
            if (--indeg[v] == 0) pq.push(v);  // u を置いたので、u → v の辺を消す
        }
    }
    if ((int)order.size() < n) {  // 取り出せない頂点が残った＝閉路がある
        cout << -1 << '\n';
        return 0;
    }
    // --8<-- [end:core]

    for (int i = 0; i < n; i++) cout << order[i] + 1 << (i + 1 < n ? ' ' : '\n');
    cout << (unique ? "unique" : "not unique") << '\n';
}
