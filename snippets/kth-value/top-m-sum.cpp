// 長さ N の列 a・b から作る N^2 個の値 a[i] + b[j] のうち、大きい方から M 個の和。
// M 番目に大きい値 t を二分探索で求め、t より大きい値の和に、足りない分だけ t を足す。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long m;
    cin >> n >> m;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    assert(n >= 1 && 1 <= m && m <= 1LL * n * n);
    sort(b.begin(), b.end());
    vector<long long> suf(n + 1, 0);  // suf[p] = b[p] + … + b[n-1]
    for (int p = n - 1; p >= 0; p--) suf[p] = suf[p + 1] + b[p];

    // --8<-- [start:core]
    // x 以上の値 a[i] + b[j] の個数と和。各 i で b[j] ≥ x - a[i] となる j は b の末尾の部分
    auto count_ge = [&](long long x) -> long long {
        long long cnt = 0;
        for (int i = 0; i < n; i++) cnt += b.end() - lower_bound(b.begin(), b.end(), x - a[i]);
        return cnt;
    };
    auto sum_ge = [&](long long x) -> long long {
        long long s = 0;
        for (int i = 0; i < n; i++) {
            int p = lower_bound(b.begin(), b.end(), x - a[i]) - b.begin();
            s += a[i] * (n - p) + suf[p];
        }
        return s;
    };

    // t = M 番目に大きい値 = count_ge(x) ≥ m となる最大の x
    long long ok = *min_element(a.begin(), a.end()) + b[0];          // すべての値が ok 以上（可）
    long long ng = *max_element(a.begin(), a.end()) + b[n - 1] + 1;  // ng 以上の値はない（不可）
    while (ng - ok > 1) {
        long long mid = ok + (ng - ok) / 2;
        if (count_ge(mid) >= m) ok = mid;
        else ng = mid;
    }
    long long t = ok;
    // t より大きい値はすべて上位 M 個に入る。残りの枠は値 t で埋める
    long long c = count_ge(t + 1);  // t より大きい値の個数（m 未満）
    cout << sum_ge(t + 1) + (m - c) * t << '\n';
    // --8<-- [end:core]
}
