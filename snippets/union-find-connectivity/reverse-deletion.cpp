#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// 辺を del[0], del[1], ... の順に削除していく。
// ans[i] ＝ 最初の i + 1 本を削除した直後の連結成分の数
vector<int> components_after_deletions(int n, const vector<pair<int, int>>& edges,
                                       const vector<int>& del) {
    // --8<-- [start:core]
    int m = edges.size(), q = del.size();
    vector<bool> deleted(m, false);
    for (int e : del) deleted[e] = true;

    atcoder::dsu d(n);
    int comps = n;
    auto add = [&](int e) {
        auto [u, v] = edges[e];
        if (!d.same(u, v)) {      // 別の成分どうしをつないだときだけ 1 減る
            d.merge(u, v);
            comps--;
        }
    };
    for (int e = 0; e < m; e++) {
        if (!deleted[e]) add(e);  // 最後まで残る辺だけの状態から始める
    }

    vector<int> ans(q);
    for (int i = q - 1; i >= 0; i--) {
        ans[i] = comps;           // 今の状態 ＝ del[0..i] を削除した直後
        add(del[i]);              // 時間を戻すと、i 番目の削除は追加になる
    }
    // --8<-- [end:core]
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges) { cin >> u >> v; u--; v--; }
    int q;
    cin >> q;
    vector<int> del(q);
    for (int& e : del) { cin >> e; e--; }
    vector<int> ans = components_after_deletions(n, edges, del);
    // 素朴な方法（時点ごとに Union-Find を作り直す）と照らし合わせる
    for (int i = 0; i < q; i++) {
        vector<bool> gone(m, false);
        for (int j = 0; j <= i; j++) gone[del[j]] = true;
        atcoder::dsu d(n);
        int comps = n;
        for (int e = 0; e < m; e++) {
            if (gone[e] || d.same(edges[e].first, edges[e].second)) continue;
            d.merge(edges[e].first, edges[e].second);
            comps--;
        }
        assert(ans[i] == comps);
    }
    for (int x : ans) cout << x << '\n';
}
