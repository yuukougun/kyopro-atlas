#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 先頭の要素から作る空でない部分集合を順に調べ、和の mod m が等しい異なる 2 つを探す。
// 余りは m 種類なので、部分集合を m + 1 個調べるまでに必ず一致が起きる。
// 見つかれば 2 つの bit 列（mask）を、なければ {-1, -1} を返す。a_i ≥ 0 を前提とする。
pair<int, int> find_same_remainder(const vector<long long>& a, int m) {
    int k = 0;  // 2^k − 1 ≥ m + 1 になる最小の k（ただし要素数まで）
    while (k < (int)a.size() && (1 << k) - 1 < m + 1) k++;
    vector<int> seen(m, -1);  // seen[r]：和の余りが r になった最初の mask
    for (int mask = 1; mask < (1 << k); mask++) {
        long long r = 0;
        for (int i = 0; i < k; i++) {
            if (mask >> i & 1) r = (r + a[i]) % m;
        }
        if (seen[r] != -1) return {seen[r], mask};
        seen[r] = mask;
    }
    return {-1, -1};  // 要素が少なく、調べた部分集合が m 個以下だった
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    auto [p, q] = find_same_remainder(a, m);
    if (p == -1) {
        cout << "No\n";
        return 0;
    }
    long long sp = 0, sq = 0;
    for (int i = 0; i < n && i < 30; i++) {
        if (p >> i & 1) sp += a[i];
        if (q >> i & 1) sq += a[i];
    }
    assert(p != q && sp % m == sq % m);
    cout << "Yes " << p << ' ' << q << '\n';
}
