// 区間の右端で、区間の左端以降の dp にまとめて加算する（区間加算・区間最大の遅延セグメント木）
// 入力：N M、続く M 行に「l r a」（閉区間 [l, r]、1-indexed。a は負でもよい）
// 出力：長さ N の 0/1 列で、1 を 1 つ以上含む区間の a の和の最大
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

const long long INF = 1LL << 60;
long long op(long long a, long long b) { return max(a, b); }
long long e() { return -INF; }
long long mapping(long long f, long long x) { return x + f; }
long long composition(long long f, long long g) { return f + g; }
long long id() { return 0; }

// 0/1 列をすべて試す素朴な方法（確かめ用。N が小さいときだけ）
long long naive(int n, const vector<int>& l, const vector<int>& r, const vector<long long>& a) {
    long long best = -INF;
    for (int s = 0; s < (1 << n); s++) {
        long long sc = 0;
        for (int j = 0; j < (int)l.size(); j++) {
            bool has = false;
            for (int p = l[j]; p <= r[j]; p++) has |= (s >> (p - 1)) & 1;
            if (has) sc += a[j];
        }
        best = max(best, sc);
    }
    return best;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> l(m), r(m);
    vector<long long> a(m);
    for (int j = 0; j < m; j++) cin >> l[j] >> r[j] >> a[j];
    // --8<-- [start:core]
    // 添字 j（0 ≤ j ≤ N）＝ 最後に 1 を置いた位置（1-indexed。0 はまだ置いていない）
    vector<vector<pair<int, long long>>> ending(n + 1);  // ending[i] = 右端が i の区間（左端, 得点）
    for (int j = 0; j < m; j++) ending[r[j]].push_back({l[j], a[j]});
    vector<long long> init(n + 1, -INF);
    init[0] = 0;
    atcoder::lazy_segtree<long long, op, e, long long, mapping, composition, id> seg(init);
    for (int i = 1; i <= n; i++) {
        seg.set(i, seg.prod(0, i));  // 位置 i に 1 を置く：前の行の最大から移る
        for (auto [lj, aj] : ending[i]) seg.apply(lj, i + 1, aj);  // 最後の 1 が [l, i] にあれば得点
    }
    long long ans = seg.all_prod();
    // --8<-- [end:core]
    if (n <= 12) assert(ans == naive(n, l, r, a));
    cout << ans << '\n';
}
