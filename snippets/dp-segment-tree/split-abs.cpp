// 移動費 C × |x − y| のある DP：町 0 から出発し、順に開かれる市場（町 t_i、利益 p_i）に参加するかを選ぶ。
// 移動費を引いた利益の最大を求める。|x − y| を左右に分け、dp[y] + C·y と dp[y] − C·y を 2 本のセグメント木に持つ。
// 入力：N C M、続く M 行に t_i p_i（町は 0-indexed）。出力：利益の最大（1 つも参加しなければ 0）
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

const long long NEG = -(1LL << 62);  // 届かない状態（−∞）。足し引きしても溢れないよう 2^62 にとどめる
long long op(long long x, long long y) { return max(x, y); }
long long e() { return NEG; }

// --8<-- [start:core]
long long solve(int n, long long c, const vector<int>& t, const vector<long long>& p) {
    // lft[y] = dp[y] + c·y（y が今の町より左のとき使う）、rgt[y] = dp[y] − c·y（右のとき使う）
    atcoder::segtree<long long, op, e> lft(n), rgt(n);
    lft.set(0, 0);  // 町 0 にいて利益 0
    rgt.set(0, 0);
    for (int i = 0; i < (int)t.size(); i++) {
        int x = t[i];
        long long from_left = lft.prod(0, x + 1);   // y ≤ x：dp[y] − c(x − y) = (dp[y] + c·y) − c·x
        long long from_right = rgt.prod(x, n);      // y ≥ x：dp[y] − c(y − x) = (dp[y] − c·y) + c·x
        long long best = NEG;
        if (from_left != NEG) best = max(best, from_left - c * x);
        if (from_right != NEG) best = max(best, from_right + c * x);
        long long cur = best + p[i];                // 取得を全部終えてから更新する
        if (cur + c * x > lft.get(x)) lft.set(x, cur + c * x);
        if (cur - c * x > rgt.get(x)) rgt.set(x, cur - c * x);
    }
    long long ans = 0;  // どこにも参加しない
    for (int y = 0; y < n; y++) {
        long long v = lft.get(y);
        if (v != NEG) ans = max(ans, v - c * y);
    }
    return ans;
}
// --8<-- [end:core]

// 素朴な O(MN) の DP で確かめる
long long naive(int n, long long c, const vector<int>& t, const vector<long long>& p) {
    vector<long long> dp(n, NEG);
    dp[0] = 0;
    for (int i = 0; i < (int)t.size(); i++) {
        long long best = NEG;
        for (int y = 0; y < n; y++)
            if (dp[y] != NEG) best = max(best, dp[y] - c * abs(t[i] - y));
        dp[t[i]] = max(dp[t[i]], best + p[i]);
    }
    return max(0LL, *max_element(dp.begin(), dp.end()));
}

int main() {
    int n, m;
    long long c;
    cin >> n >> c >> m;
    vector<int> t(m);
    vector<long long> p(m);
    for (int i = 0; i < m; i++) cin >> t[i] >> p[i];
    long long ans = solve(n, c, t, p);
    assert(ans == naive(n, c, t, p));
    cout << ans << '\n';
}
