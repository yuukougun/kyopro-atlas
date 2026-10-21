// N 個の整数から 2 つ（i < j）を選んだ積 a[i] * a[j] を小さい順に並べたときの K 番目（1-indexed）。
// 「x 以下の積が K 個以上ある」となる最小の x を二分探索する。|a[i]| ≤ 10^9 なので積は long long に収まる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(n >= 2 && 1 <= k && k <= 1LL * n * (n - 1) / 2);
    for (int i = 0; i < n; i++) assert(-1000000000 <= a[i] && a[i] <= 1000000000);
    sort(a.begin(), a.end());

    // --8<-- [start:core]
    // count(x)：i < j で a[i] * a[j] ≤ x となる組の個数（x について単調に増える）
    auto count = [&](long long x) -> long long {
        long long total = 0;  // 順序付きの組 (i, j)（i = j も含む）で数える
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) {
                // a[i] * a[j] は j について増える：条件を満たすのは先頭の部分
                total += partition_point(a.begin(), a.end(),
                                         [&](long long v) { return a[i] * v <= x; }) - a.begin();
            } else if (a[i] < 0) {
                // a[i] * a[j] は j について減る：条件を満たすのは末尾の部分
                total += a.end() - partition_point(a.begin(), a.end(),
                                                   [&](long long v) { return a[i] * v > x; });
            } else if (x >= 0) {
                total += n;  // 0 との積はすべて 0
            }
            if (a[i] * a[i] <= x) total--;  // 自分自身との組を除く
        }
        return total / 2;  // (i, j) と (j, i) を 2 回数えている
    };

    long long ng = -1000000000000000001LL;  // 積はすべて -10^18 以上なので count(ng) = 0（不可）
    long long ok = 1000000000000000000LL;   // 積はすべて 10^18 以下なので count(ok) は全部（可）
    while (ok - ng > 1) {
        long long mid = ng + (ok - ng) / 2;
        if (count(mid) >= k) ok = mid;
        else ng = mid;
    }
    cout << ok << '\n';  // count(x) ≥ k となる最小の x
    // --8<-- [end:core]
}
