// 二重辺連結成分：橋を求めた後、橋を渡らずに行ける頂点を同じ成分にし、橋で成分を結んで木（森）を作る。
// 「2 頂点が同じ成分 ⇔ どの辺を 1 本除いても 2 頂点は連結のまま」を素朴な方法と assert で比べる。
// 入力は N M と辺 (a, b)（0-indexed、無向。多重辺・自己ループ・非連結を許す）。
// 出力は成分の数と、各頂点の成分の番号。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> es(m);
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        es[i] = {a, b};
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    // lowlink.cpp と同じ DFS で橋を求める
    vector<int> ord(n, -1), low(n);
    vector<bool> is_bridge(m, false);
    int k = 0;
    auto dfs = [&](auto&& self, int v, int pe) -> void {
        ord[v] = low[v] = k++;
        for (auto [to, id] : g[v]) {
            if (id == pe) continue;
            if (ord[to] == -1) {
                self(self, to, id);
                low[v] = min(low[v], low[to]);
                if (low[to] > ord[v]) is_bridge[id] = true;
            } else {
                low[v] = min(low[v], ord[to]);
            }
        }
    };
    for (int s = 0; s < n; s++) {
        if (ord[s] == -1) dfs(dfs, s, -1);
    }

    // --8<-- [start:core]
    vector<int> comp(n, -1);  // comp[v] = v の二重辺連結成分の番号
    int c = 0;
    for (int s = 0; s < n; s++) {
        if (comp[s] != -1) continue;
        comp[s] = c;
        vector<int> st = {s};
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (auto [to, id] : g[v]) {
                if (is_bridge[id] || comp[to] != -1) continue;  // 橋は渡らない
                comp[to] = c;
                st.push_back(to);
            }
        }
        c++;
    }
    vector<vector<int>> tree(c);  // 成分を頂点、橋を辺にした木（非連結なら森）
    for (int i = 0; i < m; i++) {
        if (!is_bridge[i]) continue;
        auto [a, b] = es[i];
        tree[comp[a]].push_back(comp[b]);
        tree[comp[b]].push_back(comp[a]);
    }
    // --8<-- [end:core]

    // 確かめ：辺を 1 本除くごとに連結成分を求め、どの場合も同じ成分に残る組が同じ二重辺連結成分
    auto label = [&](int skip) {
        vector<int> lab(n, -1);
        int cnt = 0;
        for (int s = 0; s < n; s++) {
            if (lab[s] != -1) continue;
            lab[s] = cnt;
            vector<int> st = {s};
            while (!st.empty()) {
                int v = st.back();
                st.pop_back();
                for (auto [to, id] : g[v]) {
                    if (id == skip || lab[to] != -1) continue;
                    lab[to] = cnt;
                    st.push_back(to);
                }
            }
            cnt++;
        }
        return lab;
    };
    vector<vector<int>> labs;
    labs.push_back(label(-1));
    for (int i = 0; i < m; i++) labs.push_back(label(i));
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            bool together = true;
            for (const auto& lab : labs) together = together && (lab[u] == lab[v]);
            assert(together == (comp[u] == comp[v]));
        }
    }
    // 縮約したグラフは森：辺の数 = 成分の数 − 元のグラフの連結成分の数
    int bridges = 0;
    for (int i = 0; i < m; i++) bridges += is_bridge[i];
    int cc = *max_element(labs[0].begin(), labs[0].end()) + 1;
    assert(bridges == c - cc);

    cout << c << '\n';
    for (int v = 0; v < n; v++) cout << comp[v] << (v + 1 < n ? ' ' : '\n');
}
