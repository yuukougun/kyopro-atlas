// 次数を配る最適化：木の各頂点の次数 d_i に対するコスト Σ A_i d_i^2 の最小値。
// 各 d_i >= 1 で和が 2n - 2 なら木が作れるので、全員に 1 を配り、残り n - 2 を
// 「1 増やしたときの増分 A_i (2 d_i + 1)」の小さい頂点へ 1 つずつ配る。
// n <= 7 なら、すべての Prüfer 列（＝ すべての木）を調べた最小値と一致することを確かめる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(n >= 2);

    // --8<-- [start:core]
    vector<long long> d(n, 1);  // まず全員に次数 1
    using P = pair<long long, int>;  // （次に 1 増やしたときの増分, 頂点）
    priority_queue<P, vector<P>, greater<P>> pq;
    for (int i = 0; i < n; i++) pq.push({a[i] * (2 * d[i] + 1), i});
    for (int t = 0; t < n - 2; t++) {  // 残りの n - 2 を配る
        auto [inc, i] = pq.top();
        pq.pop();
        d[i]++;
        pq.push({a[i] * (2 * d[i] + 1), i});
    }
    long long cost = 0;
    for (int i = 0; i < n; i++) cost += a[i] * d[i] * d[i];
    // --8<-- [end:core]

    if (n <= 7) {  // 長さ n - 2 の列をすべて調べる。頂点 v の次数は（列での出現回数）+ 1
        long long best = LLONG_MAX;
        int total = 1;
        for (int i = 0; i < n - 2; i++) total *= n;
        for (int code = 0; code < total; code++) {
            vector<long long> deg(n, 1);
            for (int i = 0, c = code; i < n - 2; i++, c /= n) deg[c % n]++;
            long long s = 0;
            for (int v = 0; v < n; v++) s += a[v] * deg[v] * deg[v];
            best = min(best, s);
        }
        assert(best == cost);
    }
    cout << cost << '\n';
}
