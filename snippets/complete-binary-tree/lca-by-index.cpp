#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 頂点 i の親を i / k（切り捨て）とする k 分木（k >= 2、頂点は 1 以上）で、
// x と y の距離（辺の数）を求める。最後に x == y となった値が LCA
long long dist_by_index(long long x, long long y, long long k) {
    long long d = 0;
    while (x != y) {
        if (x < y) swap(x, y);  // 大きい方は小さい方の祖先ではない
        x /= k;                 // だから大きい方を親へ上げてよい
        d++;
    }
    return d;
}
// --8<-- [end:core]

// 深さ（根 1 の深さを 0 とする。k = 2 なら 2 進表記の桁数 - 1）
int depth2(long long v) { return 63 - __builtin_clzll(v); }

int main() {
    // 祖先の集合を作る素朴な方法と照合する
    for (long long k = 2; k <= 5; k++) {
        for (long long x = 1; x <= 200; x++) {
            for (long long y = 1; y <= 200; y++) {
                map<long long, int> up;  // x の祖先 → x からの距離
                long long a = x;
                for (int d = 0;; d++) {
                    up[a] = d;
                    if (a == 0) break;
                    a /= k;
                }
                long long b = y;
                int e = 0;
                while (!up.count(b)) { b /= k; e++; }
                assert(dist_by_index(x, y, k) == up[b] + e);
            }
        }
    }
    // k = 2 では距離 = dep(x) + dep(y) - 2 dep(lca)
    for (long long x = 1; x <= 300; x++) {
        for (long long y = 1; y <= 300; y++) {
            long long a = x, b = y;
            while (a != b) { if (a < b) swap(a, b); a /= 2; }
            assert(dist_by_index(x, y, 2) == depth2(x) + depth2(y) - 2 * depth2(a));
        }
    }
    long long x, y, k;
    cin >> x >> y >> k;
    cout << dist_by_index(x, y, k) << '\n';
}
