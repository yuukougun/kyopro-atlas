// 次数列 d から木を作る。各 d[v] >= 1 かつ和が 2n - 2 なら必ず作れる（n >= 2）。
// 次数 2 以上の頂点を 1 本のパスに並べ、残りの次数の分だけ葉をぶら下げる（毛虫の形）。
// 入力：n と d_1, ..., d_n（1-indexed）。出力：作れれば Yes と辺（1-indexed）、作れなければ No。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 次数列 d（各 d[v] >= 1、和が 2n - 2、n >= 2）の木の辺を返す（毛虫の形）
vector<pair<int, int>> build_tree(const vector<int>& d) {
    int n = d.size();
    vector<int> inner, leaves;  // 次数 2 以上の頂点と、次数 1 の頂点
    for (int v = 0; v < n; v++) (d[v] >= 2 ? inner : leaves).push_back(v);
    vector<pair<int, int>> edges;
    if (inner.empty()) {  // n = 2：葉どうしを結ぶ
        edges.push_back({leaves[0], leaves[1]});
        return edges;
    }
    int k = inner.size();
    for (int i = 0; i + 1 < k; i++) edges.push_back({inner[i], inner[i + 1]});  // 背骨のパス
    int li = 0;
    for (int i = 0; i < k; i++) {
        int used = (k == 1) ? 0 : (i == 0 || i == k - 1) ? 1 : 2;  // パスで使った次数
        for (int t = 0; t < d[inner[i]] - used; t++) edges.push_back({inner[i], leaves[li++]});
    }
    assert(li == (int)leaves.size());  // 葉はちょうど使い切る
    return edges;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<int> d(n);
    for (int v = 0; v < n; v++) cin >> d[v];

    // 作れる条件：n = 1 なら d = (0)。n >= 2 なら、すべて 1 以上で和が 2n - 2
    if (n == 1) {
        cout << (d[0] == 0 ? "Yes\n" : "No\n");
        return 0;
    }
    long long sum = 0;
    bool ok = true;
    for (int v = 0; v < n; v++) {
        if (d[v] < 1) ok = false;
        sum += d[v];
    }
    if (!ok || sum != 2LL * n - 2) {
        cout << "No\n";
        return 0;
    }

    vector<pair<int, int>> edges = build_tree(d);
    // 確かめ：辺は n - 1 本、次数が一致し、閉路がない（Union-Find で連結を確かめる）
    assert((int)edges.size() == n - 1);
    vector<int> deg(n), root(n);
    iota(root.begin(), root.end(), 0);
    auto find = [&](auto&& self, int x) -> int { return root[x] == x ? x : root[x] = self(self, root[x]); };
    for (auto [u, v] : edges) {
        deg[u]++;
        deg[v]++;
        int ru = find(find, u), rv = find(find, v);
        assert(ru != rv);
        root[ru] = rv;
    }
    assert(deg == d);
    cout << "Yes\n";
    for (auto [u, v] : edges) cout << u + 1 << ' ' << v + 1 << '\n';
}
