// 1 ≤ X_i ≤ A_i で、隣り合う項が異なる長さ N の数列 X の数を 998244353 で割った余り。
// 「等しい」と指定した隣接で区間にまとめる符号付き DP（O(N^2) の素朴な形）。
// N と A が小さいときは全探索で検算する。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;

    // --8<-- [start:core]
    // dp[i] = 先頭 i 項を区間に分けた分け方すべてについての、
    //         (−1)^(等しいと指定した隣接の数) × Π(区間の A の最小値) の和
    vector<mint> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        long long mn = LLONG_MAX;
        for (int j = i - 1; j >= 0; j--) {  // 最後の区間を [j, i) とする
            mn = min(mn, a[j]);
            mint term = dp[j] * mint(mn);   // 区間の項はすべて同じ値で、mn 通り
            if ((i - j - 1) % 2 == 0) dp[i] += term;  // 区間の中の隣接は i − j − 1 個
            else dp[i] -= term;
        }
    }
    mint ans = dp[n];
    // --8<-- [end:core]

    long long total = 1;
    for (auto v : a) total = (total > 100000 ? total : total * v);
    if (n <= 8 && total <= 100000) {
        long long brute = 0;
        vector<long long> xs(n, 1);
        auto dfs = [&](auto&& self, int i) -> void {
            if (i == n) {
                brute++;
                return;
            }
            for (long long v = 1; v <= a[i]; v++) {
                if (i > 0 && xs[i - 1] == v) continue;
                xs[i] = v;
                self(self, i + 1);
            }
        };
        dfs(dfs, 0);
        assert(ans == mint(brute));
    }
    cout << ans.val() << '\n';
}
