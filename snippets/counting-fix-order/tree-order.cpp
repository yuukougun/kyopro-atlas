// 根付き木の頂点に、親が子より先になるように 1, 2, …, n の番号を振る方法の数（mod 998244353）。
// 根を r としたときの答えは n! / Π sz[v]。根を隣へ移すと sz が変わるのは 2 頂点だけなので、
// すべての根についての答えを O(n) で求められる（逆元の計算を除く）。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// 全通り試す（確かめ用）：根 r からの順番で、親が子より先になる順列の数
long long brute(int n, int r, const vector<vector<int>>& g) {
    vector<int> par(n, -1), order(1, r);
    for (int i = 0; i < (int)order.size(); i++)
        for (int to : g[order[i]]) if (to != par[order[i]] && to != r) par[to] = order[i], order.push_back(to);
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    long long cnt = 0;
    do {
        vector<int> pos(n);
        for (int i = 0; i < n; i++) pos[p[i]] = i;
        bool good = true;
        for (int v = 0; v < n; v++) if (par[v] != -1 && pos[par[v]] > pos[v]) good = false;
        if (good) cnt++;
    } while (next_permutation(p.begin(), p.end()));
    return cnt;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // --8<-- [start:core]
    // 根 0 での部分木の大きさ sz を、BFS 順の逆から集める
    vector<int> par(n, -1), order(1, 0), sz(n, 1);
    for (int i = 0; i < (int)order.size(); i++)
        for (int to : g[order[i]])
            // 根 0 の親は -1 なので、根へ戻る辺は to != 0 で除く
            if (to != par[order[i]] && to != 0) {
                par[to] = order[i];
                order.push_back(to);
            }
    for (int i = n - 1; i >= 1; i--) sz[par[order[i]]] += sz[order[i]];

    mint fact = 1, prod = 1;
    for (int i = 1; i <= n; i++) fact *= i;
    for (int v = 0; v < n; v++) prod *= sz[v];
    vector<mint> ans(n);
    ans[0] = fact / prod;  // 根 0 の答え n! / Π sz[v]

    // 根を親 u から子 v へ移すと、sz[u] が n から n - sz[v] に、sz[v] が sz[v] から n に変わる
    for (int i = 1; i < n; i++) {
        int v = order[i], u = par[v];
        ans[v] = ans[u] * sz[v] / (n - sz[v]);
    }
    // --8<-- [end:core]

    for (int v = 0; v < n; v++) {
        if (n <= 8) assert(ans[v].val() == brute(n, v, g) % mint::mod());
        cout << ans[v].val() << (v + 1 == n ? '\n' : ' ');
    }
}
