// 復元の基本：各 i で a[i]（表 H）か b[i]（裏 T）のどちらかを選び、和をちょうど s にする。
// 前からの可否 DP の表を残し、終端 (n, s) から逆にたどって選び方を 1 つ作る。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    assert(n >= 1 && s >= 0);

    // --8<-- [start:core]
    // dp[i][j]：最初の i 個の選び方で和を j にできるか（表は捨てずに全部残す）
    vector dp(n + 1, vector<char>(s + 1, false));
    dp[0][0] = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= s; j++) {
            if (!dp[i][j]) continue;
            if (j + a[i] <= s) dp[i + 1][j + a[i]] = true;
            if (j + b[i] <= s) dp[i + 1][j + b[i]] = true;
        }
    }
    if (!dp[n][s]) {
        cout << "No\n";
        return 0;
    }
    // 終端から逆にたどる：今いる (i + 1, j) へ来られた遷移元を 1 つ選ぶ
    string ans;
    int j = s;
    for (int i = n - 1; i >= 0; i--) {
        if (j - a[i] >= 0 && dp[i][j - a[i]]) {
            ans += 'H';
            j -= a[i];
        } else {  // dp[i + 1][j] が true なので、こちらは必ず成り立つ
            assert(j - b[i] >= 0 && dp[i][j - b[i]]);
            ans += 'T';
            j -= b[i];
        }
    }
    reverse(ans.begin(), ans.end());  // 後ろから決めたので、最後に向きを直す
    cout << "Yes\n" << ans << '\n';
    // --8<-- [end:core]
}
