// Prüfer 列の生成（木 → 列）と復元（列 → 木）。どちらも O(N log N)。
// 入力：n と n - 1 本の辺（1-indexed）。出力：Prüfer 列（1-indexed、n = 2 なら空行）。
// 復元した木が元の木と同じ辺の集合になることを assert で確かめる。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:encode]
// 木 → Prüfer 列：最小番号の葉を消し、その隣を記録する（n - 2 回）
vector<int> encode(int n, const vector<vector<int>>& g) {
    vector<int> deg(n);
    vector<bool> removed(n, false);
    priority_queue<int, vector<int>, greater<int>> leaves;  // 今の葉（小さい順）
    for (int v = 0; v < n; v++) {
        deg[v] = g[v].size();
        if (deg[v] == 1) leaves.push(v);
    }
    vector<int> seq;
    for (int step = 0; step < n - 2; step++) {
        int leaf = leaves.top();
        leaves.pop();
        removed[leaf] = true;
        int nb = -1;
        for (int u : g[leaf]) if (!removed[u]) nb = u;  // 残っている隣はちょうど 1 つ
        seq.push_back(nb);
        if (--deg[nb] == 1) leaves.push(nb);  // 隣が新しく葉になったら候補に入れる
    }
    return seq;
}
// --8<-- [end:encode]

// --8<-- [start:decode]
// Prüfer 列 → 木：列にもう現れない頂点が今の葉で、その最小のものを列の先頭とつなぐ
vector<pair<int, int>> decode(int n, const vector<int>& seq) {
    vector<int> cnt(n, 0);  // 列の残りに現れる回数（＝ 今の次数 − 1）
    for (int x : seq) cnt[x]++;
    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int v = 0; v < n; v++) if (cnt[v] == 0) leaves.push(v);
    vector<pair<int, int>> edges;
    for (int x : seq) {
        int leaf = leaves.top();
        leaves.pop();
        edges.push_back({leaf, x});
        if (--cnt[x] == 0) leaves.push(x);
    }
    int u = leaves.top();  // 最後に残った 2 頂点を結ぶ
    leaves.pop();
    int v = leaves.top();
    edges.push_back({u, v});
    return edges;
}
// --8<-- [end:decode]

int main() {
    int n;
    cin >> n;
    assert(n >= 2);
    vector<vector<int>> g(n);
    set<pair<int, int>> original;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        original.insert(minmax(u, v));
    }
    vector<int> seq = encode(n, g);
    assert((int)seq.size() == n - 2);
    for (int v = 0; v < n; v++) {  // 頂点 v は列にちょうど 次数 − 1 回現れる
        assert(count(seq.begin(), seq.end(), v) == (int)g[v].size() - 1);
    }
    set<pair<int, int>> restored;
    for (auto [a, b] : decode(n, seq)) restored.insert(minmax(a, b));
    assert(restored == original);
    for (int i = 0; i < (int)seq.size(); i++) cout << seq[i] + 1 << (i + 1 < (int)seq.size() ? ' ' : '\n');
    if (seq.empty()) cout << '\n';
}
