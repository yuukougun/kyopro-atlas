// 1〜n の順列のうち、p_i < p_{i+1} となる i がちょうど k 個あるものの数を、
// k = 0, 1, …, n-1 について 998244353 で割った余りで求める。値の小さい順に挿入する。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    assert(n >= 1);

    // --8<-- [start:core]
    // dp[j] = 1〜i を並べて、増える所がちょうど j 個ある並べ方の数
    vector<mint> dp(n, 0);
    dp[0] = 1;  // i = 1
    for (int i = 1; i < n; i++) {  // 値 i+1（いちばん大きい）を i+1 か所の隙間のどれかに入れる
        vector<mint> ndp(n, 0);
        for (int j = 0; j < i; j++) {
            if (dp[j] == 0) continue;
            ndp[j] += dp[j] * (j + 1);           // 先頭か、増える所の間：数は変わらない
            ndp[j + 1] += dp[j] * (i - j);        // 末尾か、減る所の間：1 つ増える
        }
        dp = ndp;
    }
    for (int j = 0; j < n; j++) cout << dp[j].val() << (j + 1 < n ? ' ' : '\n');
    // --8<-- [end:core]
}
