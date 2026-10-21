#include <bits/stdc++.h>
using namespace std;

// オイラー路を Hierholzer 法で作る（非再帰）。頂点は 0-indexed、辺 i は edges[i]。
// あれば {頂点の列（M+1 個）, 辺の番号の列（M 個）} を、なければ nullopt を返す。
struct Trail {
    vector<int> vs, es;
};

// --8<-- [start:core]
// 無向グラフ。多重辺・自己ループがあってもよい
optional<Trail> euler_undirected(int n, const vector<pair<int, int>>& edges) {
    int m = edges.size();
    vector<vector<pair<int, int>>> g(n);  // (行き先, 辺の番号)
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        g[u].push_back({v, i});
        g[v].push_back({u, i});  // 自己ループは g[u] に 2 回入り、次数に 2 数える
    }
    int s = -1, odd = 0;
    for (int v = 0; v < n; v++) {
        if (g[v].size() % 2 == 1) {
            odd++;
            s = v;  // 奇数次数の頂点があれば、そこから始める
        }
    }
    if (odd != 0 && odd != 2) return nullopt;
    if (s == -1) {
        s = 0;
        for (int v = 0; v < n; v++) {
            if (!g[v].empty()) { s = v; break; }  // 辺のある頂点から始める
        }
    }
    vector<char> used(m, 0);
    vector<int> ptr(n, 0);  // g[v] のどこまで調べたか（戻らない）
    vector<pair<int, int>> st = {{s, -1}};  // (頂点, そこへ来た辺)
    Trail t;
    while (!st.empty()) {
        int v = st.back().first;
        while (ptr[v] < (int)g[v].size() && used[g[v][ptr[v]].second]) ptr[v]++;
        if (ptr[v] == (int)g[v].size()) {  // 行き止まり：路に確定させる
            t.vs.push_back(v);
            if (st.back().second != -1) t.es.push_back(st.back().second);
            st.pop_back();
        } else {
            auto [to, id] = g[v][ptr[v]];
            used[id] = 1;
            st.push_back({to, id});
        }
    }
    if ((int)t.es.size() != m) return nullopt;  // 辺のある頂点が連結でない
    reverse(t.vs.begin(), t.vs.end());
    reverse(t.es.begin(), t.es.end());
    return t;
}
// --8<-- [end:core]

// --8<-- [start:directed]
// 有向グラフ。辺 i は edges[i].first から edges[i].second へ向かう
optional<Trail> euler_directed(int n, const vector<pair<int, int>>& edges) {
    int m = edges.size();
    vector<vector<pair<int, int>>> g(n);
    vector<int> diff(n, 0);  // 出次数 − 入次数
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        g[u].push_back({v, i});
        diff[u]++;
        diff[v]--;
    }
    int s = -1, plus = 0, minus = 0;
    for (int v = 0; v < n; v++) {
        if (diff[v] == 1) { plus++; s = v; }  // 出次数が 1 多い頂点が始点
        else if (diff[v] == -1) minus++;
        else if (diff[v] != 0) return nullopt;
    }
    if (plus > 1 || minus > 1) return nullopt;
    if (s == -1) {
        s = 0;
        for (int v = 0; v < n; v++) {
            if (!g[v].empty()) { s = v; break; }
        }
    }
    vector<int> ptr(n, 0);  // 有向では各辺が g に 1 回しか入らないので used は要らない
    vector<pair<int, int>> st = {{s, -1}};
    Trail t;
    while (!st.empty()) {
        int v = st.back().first;
        if (ptr[v] == (int)g[v].size()) {
            t.vs.push_back(v);
            if (st.back().second != -1) t.es.push_back(st.back().second);
            st.pop_back();
        } else {
            auto [to, id] = g[v][ptr[v]++];
            st.push_back({to, id});
        }
    }
    if ((int)t.es.size() != m) return nullopt;  // 弱連結でない
    reverse(t.vs.begin(), t.vs.end());  // 帰りがけに積んだので逆順になっている
    reverse(t.es.begin(), t.es.end());
    return t;
}
// --8<-- [end:directed]

// 返した路が正しいかを確かめる
bool valid(int n, const vector<pair<int, int>>& edges, const Trail& t, bool directed) {
    int m = edges.size();
    if ((int)t.vs.size() != m + 1 || (int)t.es.size() != m) return false;
    vector<char> seen(m, 0);
    for (int i = 0; i < m; i++) {
        int id = t.es[i];
        if (id < 0 || id >= m || seen[id]) return false;
        seen[id] = 1;
        auto [u, v] = edges[id];
        bool fwd = (u == t.vs[i] && v == t.vs[i + 1]);
        bool bwd = (v == t.vs[i] && u == t.vs[i + 1]);
        if (!(fwd || (!directed && bwd))) return false;
    }
    for (int v : t.vs) if (v < 0 || v >= n) return false;
    return true;
}

// 辺の順をすべて試す素朴な判定（M ≤ 6）
bool brute(int n, const vector<pair<int, int>>& edges, bool directed) {
    int m = edges.size();
    if (m == 0) return true;
    vector<char> used(m, 0);
    auto dfs = [&](auto&& self, int v, int cnt) -> bool {
        if (cnt == m) return true;
        for (int i = 0; i < m; i++) {
            if (used[i]) continue;
            auto [a, b] = edges[i];
            int to = -1;
            if (a == v) to = b;
            else if (!directed && b == v) to = a;
            if (to == -1) continue;
            used[i] = 1;
            bool ok = self(self, to, cnt + 1);
            used[i] = 0;
            if (ok) return true;
        }
        return false;
    };
    for (int s = 0; s < n; s++) {
        if (dfs(dfs, s, 0)) return true;
    }
    return false;
}

void self_test() {
    mt19937 rng(12345);
    for (int iter = 0; iter < 3000; iter++) {
        int n = rng() % 5 + 1, m = rng() % 7;
        vector<pair<int, int>> edges(m);
        for (auto& [u, v] : edges) { u = rng() % n; v = rng() % n; }
        for (bool directed : {false, true}) {
            auto r = directed ? euler_directed(n, edges) : euler_undirected(n, edges);
            assert(r.has_value() == brute(n, edges, directed));
            if (r) assert(valid(n, edges, *r, directed));
        }
    }
}

int main() {
    self_test();
    // 入力：D（0 なら無向、1 なら有向）、T、各ケースの N M と辺。出力：Yes と頂点の列・辺の列、または No
    int d, T;
    cin >> d >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> edges(m);
        for (auto& [u, v] : edges) cin >> u >> v;
        auto r = d ? euler_directed(n, edges) : euler_undirected(n, edges);
        if (!r) {
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";
        for (int i = 0; i <= m; i++) cout << r->vs[i] << (i == m ? '\n' : ' ');
        for (int i = 0; i < m; i++) cout << r->es[i] << (i + 1 == m ? "" : " ");
        cout << '\n';
    }
}
