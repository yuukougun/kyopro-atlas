#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    // --8<-- [start:core]
    // 2 次元：(n + 1) 行 × (m + 1) 列、すべて -1
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, -1));
    // 3 次元：n × m × k、すべて 0。外側の括弧から順に 1 次元目・2 次元目・3 次元目の大きさ
    vector<vector<vector<int>>> cnt(n, vector<vector<int>>(m, vector<int>(k, 0)));
    // --8<-- [end:core]
    cout << dp.size() << ' ' << dp[0].size() << ' ' << dp[n][m] << '\n';
    cout << cnt.size();
    if (n > 0) cout << ' ' << cnt[0].size();
    if (n > 0 && m > 0) cout << ' ' << cnt[0][0].size();
    cout << '\n';
}
