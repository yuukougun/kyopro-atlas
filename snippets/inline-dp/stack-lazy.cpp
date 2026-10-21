// 単調スタックと遅延セグメント木：区間の最大 − 最小をコストにする分割の DP
// 入力：N C、A_0 … A_{N-1}
// 出力：列を 1 つ以上の連続する区間に分けるとき、各区間の（C + 最大 − 最小）の和の最小
#include <bits/stdc++.h>
#include <atcoder/lazysegtree>
using namespace std;

const long long INF = 1LL << 60;
long long op(long long a, long long b) { return min(a, b); }
long long e() { return INF; }
long long mapping(long long f, long long x) { return x + f; }
long long composition(long long f, long long g) { return f + g; }
long long id() { return 0; }

// 遷移元をすべて試す素朴な方法（確かめ用。O(N^2)）
long long naive(int n, long long c, const vector<long long>& a) {
    vector<long long> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        long long mx = LLONG_MIN, mn = LLONG_MAX;
        for (int j = i - 1; j >= 0; j--) {
            mx = max(mx, a[j]), mn = min(mn, a[j]);
            dp[i] = min(dp[i], dp[j] + c + mx - mn);
        }
    }
    return dp[n];
}

int main() {
    int n;
    long long c;
    cin >> n >> c;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // --8<-- [start:core]
    // i 本目の処理の後、添字 j（j < i）に dp[j] + max(A[j, i)) − min(A[j, i)) を持つ
    vector<long long> dp(n + 1);
    dp[0] = 0;
    atcoder::lazy_segtree<long long, op, e, long long, mapping, composition, id> seg(n + 1);
    vector<int> smax, smin;  // 値が狭義に減る・増える添字のスタック
    for (int i = 1; i <= n; i++) {
        int x = i - 1;  // 新しく加わる要素 A[x]
        seg.set(x, dp[x]);  // 始点 x の区間 [x, i) は最大 − 最小 = 0
        while (!smax.empty() && a[smax.back()] <= a[x]) {
            int p = smax.back();
            smax.pop_back();
            int q = smax.empty() ? -1 : smax.back();
            seg.apply(q + 1, p + 1, a[x] - a[p]);  // 始点 (q, p] の最大が A[p] から A[x] に上がる
        }
        smax.push_back(x);
        while (!smin.empty() && a[smin.back()] >= a[x]) {
            int p = smin.back();
            smin.pop_back();
            int q = smin.empty() ? -1 : smin.back();
            seg.apply(q + 1, p + 1, a[p] - a[x]);  // 始点 (q, p] の最小が A[p] から A[x] に下がる
        }
        smin.push_back(x);
        dp[i] = seg.prod(0, i) + c;
    }
    // --8<-- [end:core]
    assert(dp[n] == naive(n, c, a));
    cout << dp[n] << '\n';
}
