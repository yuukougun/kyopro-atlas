// 区間を覆う最小コスト：半開区間 [l_i, r_i)（費用 c_i）をいくつか選び、[0, L) 全体を覆う費用の最小を求める。
// dp[x] = [0, x) を覆う最小の費用。区間を右端の小さい順に見て、dp[r] ← min(dp[l..r)) + c とする。
// 入力：N L、続く N 行に l_i r_i c_i（0 ≤ l_i < r_i ≤ L）。出力：費用の最小（覆えなければ -1）
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

const long long INF = 1LL << 62;  // 届かない状態（+∞）
long long op(long long x, long long y) { return min(x, y); }
long long e() { return INF; }

// --8<-- [start:core]
long long min_cover(int len, vector<array<long long, 3>> iv) {  // iv[i] = {r, l, c}
    sort(iv.begin(), iv.end());            // 右端の小さい順に処理する
    atcoder::segtree<long long, op, e> dp(len + 1);  // dp[x]：[0, x) を覆う最小の費用
    dp.set(0, 0);                          // 空の区間 [0, 0) は費用 0 で覆えている
    for (auto [r, l, c] : iv) {
        long long best = dp.prod(l, r);    // 覆い終えた位置 x が [l, r) にあれば、この区間でつなげる
        if (best == INF) continue;         // INF に c を足さない
        if (best + c < dp.get(r)) dp.set(r, best + c);
    }
    long long ans = dp.get(len);
    return ans == INF ? -1 : ans;
}
// --8<-- [end:core]

// 素朴な O(N L) の DP で確かめる
long long naive(int len, vector<array<long long, 3>> iv) {
    sort(iv.begin(), iv.end());
    vector<long long> dp(len + 1, INF);
    dp[0] = 0;
    for (auto [r, l, c] : iv)
        for (long long x = l; x < r; x++)
            if (dp[x] != INF) dp[r] = min(dp[r], dp[x] + c);
    return dp[len] == INF ? -1 : dp[len];
}

int main() {
    int n, len;
    cin >> n >> len;
    vector<array<long long, 3>> iv(n);
    for (auto& [r, l, c] : iv) {
        cin >> l >> r >> c;
        assert(0 <= l && l < r && r <= len);
    }
    long long ans = min_cover(len, iv);
    assert(ans == naive(len, iv));
    cout << ans << '\n';
}
