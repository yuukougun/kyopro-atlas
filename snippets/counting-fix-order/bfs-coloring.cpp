// 木の各頂点を k 色で塗り、距離 2 以下の 2 頂点がすべて異なる色になる塗り方の数（mod 998244353）。
// 根から BFS 順に塗ると、各頂点で避ける色の数が前の塗り方によらず一定になり、積の法則で数えられる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// 全通り試す（確かめ用。n と k が小さいときだけ）
long long brute(int n, int k, const vector<pair<int, int>>& edges, const vector<vector<int>>& g) {
    long long cnt = 0;
    vector<int> c(n, 0);
    while (true) {
        bool good = true;
        for (auto [u, v] : edges) if (c[u] == c[v]) good = false;
        for (int v = 0; v < n; v++)  // v を挟んで隣り合う 2 頂点（距離 2）
            for (int x : g[v]) for (int y : g[v]) if (x != y && c[x] == c[y]) good = false;
        if (good) cnt++;
        int i = 0;
        while (i < n && c[i] == k - 1) c[i++] = 0;
        if (i == n) break;
        c[i]++;
    }
    return cnt;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> edges(n - 1);
    vector<vector<int>> g(n);
    for (auto& [u, v] : edges) {
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // --8<-- [start:core]
    // 根 0 から BFS 順に塗る。v を塗るとき、距離 2 以内で塗り終わっているのは
    // 親・祖父・先に塗った兄弟で、これらは互いに距離 2 以内なので色がすべて違う。
    // よって避ける色の「数」は塗り方によらず決まる。
    mint ans = k;  // 根は k 通り
    vector<int> par(n, -1);
    queue<int> que;
    que.push(0);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        int used = (v == 0 ? 1 : 2);  // 子が避ける色：v と（いれば）v の親
        for (int to : g[v]) {
            if (to == par[v]) continue;
            par[to] = v;
            // max で 0 に止める（mod を取った後では負かどうか分からない）
            ans *= max(0, k - used);
            used++;  // 次の兄弟は、いま塗った子の色も避ける
            que.push(to);
        }
    }
    // --8<-- [end:core]

    if (n <= 7 && k <= 4) assert(ans.val() == brute(n, k, edges, g) % mint::mod());
    cout << ans.val() << '\n';
}
