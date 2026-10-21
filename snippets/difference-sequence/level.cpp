#include <bits/stdc++.h>
using namespace std;

long long floor_div(long long x, long long y) {  // y > 0
    return x / y - (x % y < 0 ? 1 : 0);
}

// --8<-- [start:core]
// 隣り合う a[i] を 1 減らし a[i+1] を 1 増やす操作で、a を狭義単調増加にする最小回数
long long min_ops_strict(vector<long long> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) a[i] -= i;  // 狭義 → 広義：b[i] = a[i] - i
    vector<pair<long long, long long>> st;  // ブロック（長さ, 和）。値はできるだけ均す
    for (int i = 0; i < n; i++) {
        long long len = 1, sum = a[i];
        // 左のブロックの最大（右端の値）が、今のブロックの最小（左端の値）より大きい間は併合する
        while (!st.empty()) {
            auto [pl, ps] = st.back();
            long long left_max = floor_div(ps + pl - 1, pl);
            long long right_min = floor_div(sum, len);
            if (left_max <= right_min) break;
            len += pl;
            sum += ps;
            st.pop_back();
        }
        st.push_back({len, sum});
    }
    // 操作の回数は、累積和 S_k が減った量の和 = sum i * (b'[i] - b[i])
    long long res = 0;
    int i = 0;
    for (auto [len, sum] : st) {
        for (long long j = 0; j < len; j++, i++) {
            long long b = floor_div(sum + j, len);  // 余りは右に寄せる
            res += i * (b - a[i]);
        }
    }
    return res;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long ans = min_ops_strict(a);
    assert(ans >= 0);
    cout << ans << '\n';
}
