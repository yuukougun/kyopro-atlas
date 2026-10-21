// 平均の扱い：数列の空でない部分集合のうち、要素の平均が整数になるものの数を 998244353 で割った余りで求める。
// 選ぶ個数 k を外側で固定し、「k 個選んで和が k の倍数」を数えて足し合わせる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(1 <= n);

    // --8<-- [start:core]
    mint ans = 0;
    for (int k = 1; k <= n; k++) {  // 選ぶ個数 k を固定すると、法 k が決まる
        // dp[p][m] ＝ ここまでの要素から p 個を選び、和を k で割った余りが m になる選び方の数
        vector dp(k + 1, vector<mint>(k, 0));
        dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            int ai = a[i] % k;
            for (int p = min(i, k - 1); p >= 0; p--) {  // p を大きい方から回して a[i] を 1 回だけ使う
                for (int m = 0; m < k; m++) {
                    dp[p + 1][(m + ai) % k] += dp[p][m];
                }
            }
        }
        ans += dp[k][0];  // ちょうど k 個で和が k の倍数 ⇔ 平均が整数
    }
    cout << ans.val() << '\n';
    // --8<-- [end:core]
}
