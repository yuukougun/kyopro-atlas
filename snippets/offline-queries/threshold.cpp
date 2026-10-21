#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

struct Edge { int u, v; long long w; };
struct Query { int u, v; long long w; };

// 各クエリ (u, v, w) に「重み w 以下の辺だけで u と v が連結か」を答える
vector<bool> threshold_connected(int n, vector<Edge> edges, const vector<Query>& qs) {
    // --8<-- [start:core]
    int q = qs.size();
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    vector<int> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return qs[i].w < qs[j].w; });

    atcoder::dsu d(n);
    vector<bool> ans(q);
    int e = 0;                                    // edges[0, e) を併合済み
    for (int k : ord) {
        // 「w 以下」なので、重みがちょうど w の辺も先に足す
        while (e < (int)edges.size() && edges[e].w <= qs[k].w) {
            d.merge(edges[e].u, edges[e].v);
            e++;
        }
        ans[k] = d.same(qs[k].u, qs[k].v);
    }
    // --8<-- [end:core]
    return ans;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<Edge> edges(m);
    for (auto& [u, v, w] : edges) { cin >> u >> v >> w; u--; v--; }
    vector<Query> qs(q);
    for (auto& [u, v, w] : qs) { cin >> u >> v >> w; u--; v--; }
    vector<bool> ans = threshold_connected(n, edges, qs);
    // 素朴な方法（クエリごとに Union-Find を作り直す）と照らし合わせる
    for (int k = 0; k < q; k++) {
        atcoder::dsu d(n);
        for (auto& [u, v, w] : edges) if (w <= qs[k].w) d.merge(u, v);
        assert(ans[k] == d.same(qs[k].u, qs[k].v));
    }
    for (bool b : ans) cout << (b ? "Yes" : "No") << '\n';
}
