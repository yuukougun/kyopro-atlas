// 行きがけ順から木を数える：頂点の番号の列 P（長さ n、P[0] が根）が与えられる。
// 根から、子を番号の小さい順にたどる DFS の行きがけ順が P になる根付き木の数を 998244353 で割った余りを求める。
// f[l][r] = 半開区間 [l, r) が P[l] を根とする 1 本の部分木になる方法の数
// g[l][r] = [l, r) が「根の番号が増える順に並んだ部分木の列（森）」になる方法の数
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
mint count_trees(const vector<int>& p) {
    int n = p.size();
    vector<vector<mint>> f(n + 1, vector<mint>(n + 1, 0)), g(n + 1, vector<mint>(n + 1, 0));
    for (int l = 0; l <= n; l++) g[l][l] = 1;  // 空の森は 1 通り
    for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            f[l][r] = g[l + 1][r];  // 根 P[l] の下に、残り [l+1, r) を子の部分木の列として付ける
            // 先頭の部分木を [l, m) とし、残りの森 [m, r) の先頭の根 P[m] が P[l] より大きいときだけ足す
            for (int m = l + 1; m <= r; m++) {
                if (m < r && p[l] > p[m]) continue;
                g[l][r] += f[l][m] * g[m][r];
            }
        }
    }
    return f[0][n];
}
// --8<-- [end:core]

// 確かめ用：P[i] の親を P[0..i-1] から全通り選び、DFS の行きがけ順が P になるものを数える
long long brute(const vector<int>& p) {
    int n = p.size();
    vector<int> par(n, -1);  // 位置 i の親の位置
    long long cnt = 0;
    auto rec = [&](auto&& self, int i) -> void {
        if (i == n) {
            vector<vector<int>> ch(n);
            for (int v = 1; v < n; v++) ch[par[v]].push_back(v);
            for (auto& c : ch) sort(c.begin(), c.end(), [&](int a, int b) { return p[a] < p[b]; });
            vector<int> order;
            auto dfs = [&](auto&& self2, int v) -> void {
                order.push_back(v);
                for (int c : ch[v]) self2(self2, c);
            };
            dfs(dfs, 0);
            bool same = true;
            for (int k = 0; k < n; k++) same = same && order[k] == k;
            if (same) cnt++;
            return;
        }
        for (int j = 0; j < i; j++) {
            par[i] = j;
            self(self, i + 1);
        }
    };
    rec(rec, 1);
    return cnt;
}

int main() {
    // 小さい n のすべての順列（P[0] = 0 を根に固定）で全探索と比べる
    for (int n = 1; n <= 6; n++) {
        vector<int> rest(n - 1);
        iota(rest.begin(), rest.end(), 1);
        do {
            vector<int> p = {0};
            p.insert(p.end(), rest.begin(), rest.end());
            assert(count_trees(p).val() == brute(p));
        } while (next_permutation(rest.begin(), rest.end()));
    }
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x;
    cout << count_trees(p).val() << '\n';
}
