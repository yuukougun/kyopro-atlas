// 重みが非負の木の直径を 2 回の最遠点探索で求め、直径の頂点列と各頂点の離心数（最も遠い点までの距離）も出す。
// 入力：N、続く N-1 行に辺 u v w（1-indexed、0 <= w）。
// 出力：1 行目に直径の長さと直径上の頂点数、2 行目に直径の頂点列（1-indexed）、3 行目に各頂点の離心数。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    assert(n >= 1);
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--, v--;
        assert(0 <= u && u < n && 0 <= v && v < n && w >= 0);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    // --8<-- [start:core]
    // s からの距離 dist と、s を根にしたときの親 par を求める（木なので訪れる順は何でもよい）
    // 再帰をやめて明示的なスタックで回す（パス状の木で深さが N になっても落ちない）
    auto far = [&](int s, vector<long long>& dist, vector<int>& par) -> int {
        dist.assign(n, -1);
        par.assign(n, -1);
        dist[s] = 0;
        vector<int> st = {s};
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (auto [to, w] : g[v]) {
                if (dist[to] != -1) continue;  // 親（訪問済み）へは戻らない
                dist[to] = dist[v] + w;
                par[to] = v;
                st.push_back(to);
            }
        }
        return int(max_element(dist.begin(), dist.end()) - dist.begin());  // 最も遠い点（同点ならどれでもよい）
    };

    vector<long long> da, db;
    vector<int> pa, pb;
    int a = far(0, da, pa);  // 1 回目：適当な点 0 から最も遠い点 a（直径の端点になる）
    int b = far(a, da, pa);  // 2 回目：a から最も遠い点 b。a–b が直径
    far(b, db, pb);          // 3 回目：離心数のために b からの距離も求める
    long long diameter = da[b];

    vector<int> path;  // 直径の頂点列は、a を根にしたときの親を b からたどる
    for (int v = b; v != -1; v = pa[v]) path.push_back(v);

    vector<long long> ecc(n);  // 各頂点から最も遠い点までの距離は、直径の両端への距離の大きい方
    for (int v = 0; v < n; v++) ecc[v] = max(da[v], db[v]);
    // --8<-- [end:core]

    cout << diameter << ' ' << path.size() << '\n';
    for (int i = 0; i < int(path.size()); i++) cout << path[i] + 1 << (i + 1 < int(path.size()) ? ' ' : '\n');
    for (int v = 0; v < n; v++) cout << ecc[v] << (v + 1 < n ? ' ' : '\n');
}
