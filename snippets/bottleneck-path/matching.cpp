#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// --8<-- [start:core]
// A と B を 1 対 1 に組にして、ボトルネックの和を最小にする（すべて組にできると仮定）
long long min_sum(int n, vector<array<long long, 3>> edges,
                  const vector<int>& A, const vector<int>& B) {
    vector<long long> ca(n, 0), cb(n, 0);  // 代表元ごとの、まだ組にしていない A と B の数
    for (int x : A) ca[x]++;
    for (int y : B) cb[y]++;
    for (int v = 0; v < n; v++) {  // 同じ頂点の A と B は重み 0 で組にする
        long long k = min(ca[v], cb[v]);
        ca[v] -= k, cb[v] -= k;
    }
    sort(edges.begin(), edges.end(),
         [](const auto& a, const auto& b) { return a[2] < b[2]; });
    atcoder::dsu d(n);
    long long sum = 0;
    for (auto [u, v, w] : edges) {
        int a = d.leader(u), b = d.leader(v);
        if (a == b) continue;
        int r = d.merge(a, b);
        long long x = ca[a] + ca[b], y = cb[a] + cb[b];
        long long k = min(x, y);  // 新しくつながった組は、ちょうど重み w で組にできる
        sum += k * w;
        ca[a] = ca[b] = cb[a] = cb[b] = 0;
        ca[r] = x - k, cb[r] = y - k;
    }
    return sum;
}
// --8<-- [end:core]

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<array<long long, 3>> edges(m);
    for (auto& [u, v, w] : edges) cin >> u >> v >> w;
    vector<int> A(k), B(k);
    for (int& x : A) cin >> x;
    for (int& y : B) cin >> y;
    long long ans = min_sum(n, edges, A, B);

    // 確かめ：f をすべて求め、B の並べ方を全部試す（k が小さいとき）
    if (k <= 7) {
        vector f(n, vector<long long>(n, LLONG_MAX));
        for (int s = 0; s < n; s++) {
            f[s][s] = 0;
            for (int t = 0; t < n; t++) {
                for (auto [a, b, x] : edges) {
                    atcoder::dsu d(n);
                    for (auto [c, e, w] : edges)
                        if (w <= x) d.merge(c, e);
                    if (d.same(s, t)) f[s][t] = min(f[s][t], x);
                }
            }
        }
        vector<int> p(k);
        iota(p.begin(), p.end(), 0);
        long long best = LLONG_MAX;
        do {
            long long s = 0;
            for (int i = 0; i < k; i++) s += f[A[i]][B[p[i]]];
            best = min(best, s);
        } while (next_permutation(p.begin(), p.end()));
        assert(ans == best);
    }
    cout << ans << '\n';
}
