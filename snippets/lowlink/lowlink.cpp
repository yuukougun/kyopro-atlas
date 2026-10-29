// 橋と関節点：ord と low を DFS 1 回で求め、橋の辺の番号と関節点を出力する。
// 頂点 v を除いたときに v の連結成分がいくつに分かれるか（pieces[v]）も求め、
// 辺・頂点を 1 つずつ除いて連結成分を数える素朴な方法と assert で比べる。
// 入力は N M と辺 (a, b)（1-indexed、無向。多重辺・自己ループ・非連結を許す）。
// 出力の辺の番号（入力の順）と頂点も 1-indexed にする。
#include <bits/stdc++.h>
using namespace std;

// 辺 skip_e と頂点 skip_v を除いたグラフの連結成分の数（素朴な方法）
int count_components(int n, const vector<pair<int, int>>& es, int skip_e, int skip_v) {
    vector<vector<int>> h(n);
    for (int i = 0; i < (int)es.size(); i++) {
        auto [a, b] = es[i];
        if (i == skip_e || a == skip_v || b == skip_v) continue;
        h[a].push_back(b);
        h[b].push_back(a);
    }
    vector<bool> seen(n, false);
    int cnt = 0;
    for (int s = 0; s < n; s++) {
        if (s == skip_v || seen[s]) continue;
        cnt++;
        vector<int> st = {s};
        seen[s] = true;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (int to : h[v]) {
                if (!seen[to]) seen[to] = true, st.push_back(to);
            }
        }
    }
    return cnt;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> es(m);
    // --8<-- [start:core]
    vector<vector<pair<int, int>>> g(n);  // g[v] = (行き先, 辺の番号)
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;  // 1-indexed → 0-indexed
        es[i] = {a, b};
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    vector<int> ord(n, -1), low(n), pieces(n, 0);
    vector<bool> is_bridge(m, false), is_cut(n, false);
    int k = 0;  // 次に振る行きがけ番号
    auto dfs = [&](auto&& self, int v, int pe) -> void {  // pe：v に下りてきた辺の番号
        ord[v] = low[v] = k++;
        int sep = 0;  // low[c] >= ord[v] となる子 c の数（v を除くと切り離される部分木）
        for (auto [to, id] : g[v]) {
            if (id == pe) continue;  // 来た辺だけを除く（頂点で除くと多重辺で誤る）
            if (ord[to] == -1) {     // 木の辺
                self(self, to, id);
                low[v] = min(low[v], low[to]);
                if (low[to] > ord[v]) is_bridge[id] = true;
                if (low[to] >= ord[v]) sep++;
            } else {                 // 後退辺（無向グラフの DFS では横断辺はない）
                low[v] = min(low[v], ord[to]);
            }
        }
        // 根（pe == -1）は「上側」がないので、切り離される部分木の数だけに分かれる
        pieces[v] = (pe == -1 ? sep : sep + 1);
        is_cut[v] = (pieces[v] >= 2);
    };
    for (int s = 0; s < n; s++) {
        if (ord[s] == -1) dfs(dfs, s, -1);  // 非連結でもすべての頂点から始める
    }
    // --8<-- [end:core]

    int base = count_components(n, es, -1, -1);
    for (int i = 0; i < m; i++) {
        assert(is_bridge[i] == (count_components(n, es, i, -1) > base));
    }
    for (int v = 0; v < n; v++) {
        // v を除くと、v の成分（1 つ）が pieces[v] 個に置き換わる
        assert(count_components(n, es, -1, v) == base - 1 + pieces[v]);
    }

    vector<int> bridges, cuts;
    for (int i = 0; i < m; i++) {
        if (is_bridge[i]) bridges.push_back(i);
    }
    for (int v = 0; v < n; v++) {
        if (is_cut[v]) cuts.push_back(v);
    }
    cout << bridges.size();
    for (int i : bridges) cout << ' ' << i + 1;
    cout << '\n' << cuts.size();
    for (int v : cuts) cout << ' ' << v + 1;
    cout << '\n';
}
