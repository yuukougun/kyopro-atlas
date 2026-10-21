#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// すべての区間 [L, R) と、その中から選んだ和が s（≥ 1）の選び方の組の数
// 段階 0：区間の前、1：区間の中、2：区間の後
mint count_pairs(const vector<int>& a, int s) {
    int n = a.size();
    // dp[p][j]：見終えた最後の位置が段階 p にあり、選んだ和が j の組の数
    vector<vector<mint>> dp(3, vector<mint>(s + 1));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        vector<vector<mint>> nd(3, vector<mint>(s + 1));
        for (int j = 0; j <= s; j++) {
            mint in = dp[0][j] + dp[1][j];             // 位置 i を区間の中にする
            nd[0][j] += dp[0][j];                      // 位置 i も区間の前
            nd[1][j] += in;                            // 区間の中で a[i] を選ばない
            if (j + a[i] <= s) nd[1][j + a[i]] += in;  // 区間の中で a[i] を選ぶ
            nd[2][j] += dp[1][j] + dp[2][j];           // 位置 i は区間の後
        }
        dp = move(nd);
    }
    return dp[1][s] + dp[2][s];  // 区間に 1 回は入った状態
}
// --8<-- [end:core]

long long brute(const vector<int>& a, int s) {
    int n = a.size();
    long long cnt = 0;
    for (int l = 0; l < n; l++) {
        for (int r = l + 1; r <= n; r++) {
            int len = r - l;
            for (int mask = 0; mask < (1 << len); mask++) {
                int sum = 0;
                for (int k = 0; k < len; k++) {
                    if (mask >> k & 1) sum += a[l + k];
                }
                if (sum == s) cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    mint ans = count_pairs(a, s);
    if (n <= 12) assert(ans.val() == brute(a, s) % 998244353);
    cout << ans.val() << '\n';
}
