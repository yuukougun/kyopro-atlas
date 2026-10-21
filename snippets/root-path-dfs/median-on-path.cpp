// 根から各頂点へのパス上の値の中央値（個数 m のとき小さい方から ceil(m / 2) 番目）を求める。
// 値を座標圧縮した BIT に「入るとき +1、出るとき −1」で出し入れし、K 番目に小さい値を BIT の上から降りて求める。
// 確かめのため、パスの値をソートする素朴な DFS と答えが一致することを assert する。
// 入力は N、値 a_1 … a_N、辺 N − 1 本（1-indexed）。根は頂点 1。出力は各頂点の答え。
#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<int> t;
    BIT(int n) : n(n), t(n + 1, 0) {}
    void add(int i, int x) {  // 位置 i（0-indexed）に x を足す
        for (i++; i <= n; i += i & -i) t[i] += x;
    }
    int kth(int k) {  // 小さい方から k 番目（1 ≤ k ≤ 総数）の位置を返す
        int pos = 0, step = 1;
        while (step * 2 <= n) step *= 2;
        for (; step > 0; step /= 2) {
            if (pos + step <= n && t[pos + step] < k) {
                pos += step;
                k -= t[pos];
            }
        }
        return pos;  // 位置 pos（0-indexed）までの累計で初めて k 以上になる
    }
};

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // --8<-- [start:core]
    vector<long long> xs = a;  // 座標圧縮
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    vector<int> id(n);
    for (int v = 0; v < n; v++) id[v] = lower_bound(xs.begin(), xs.end(), a[v]) - xs.begin();

    BIT bit(xs.size());  // 根から今の頂点までの値の個数を、圧縮した値ごとに持つ
    vector<long long> ans(n);
    auto dfs = [&](auto&& self, int v, int p, int len) -> void {
        bit.add(id[v], +1);                    // 入る
        ans[v] = xs[bit.kth((len + 1) / 2)];   // len はパスの頂点数（v を含む）
        for (int to : g[v]) {
            if (to != p) self(self, to, v, len + 1);
        }
        bit.add(id[v], -1);                    // 出る：足した分を引く
    };
    dfs(dfs, 0, -1, 1);
    // --8<-- [end:core]

    vector<long long> path;
    auto check = [&](auto&& self, int v, int p) -> void {
        path.push_back(a[v]);
        vector<long long> s = path;
        sort(s.begin(), s.end());
        assert(ans[v] == s[(s.size() + 1) / 2 - 1]);
        for (int to : g[v]) {
            if (to != p) self(self, to, v);
        }
        path.pop_back();
    };
    check(check, 0, -1);

    for (int v = 0; v < n; v++) cout << ans[v] << '\n';
}
