// 反例を探す：硬貨 {1, x, y}（1 < x < y <= ymax）で金額 m を払う最小枚数について、
// 「大きい硬貨から使えるだけ使う」貪欲と DP（全探索の代わり）を比べ、最初の反例を出す。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int ymax;
    cin >> ymax;
    assert(ymax >= 1);

    // --8<-- [start:core]
    auto greedy = [](vector<int> coins, int m) {  // 大きい硬貨から使えるだけ使う
        sort(coins.rbegin(), coins.rend());
        int cnt = 0;
        for (int c : coins) {
            cnt += m / c;
            m %= c;
        }
        return cnt;
    };
    auto exact = [](const vector<int>& coins, int m) {  // 正しい答え（金額ごとの DP）
        vector<int> dp(m + 1, INT_MAX);
        dp[0] = 0;
        for (int v = 1; v <= m; v++)
            for (int c : coins)
                if (c <= v && dp[v - c] != INT_MAX) dp[v] = min(dp[v], dp[v - c] + 1);
        return dp[m];
    };
    for (int y = 3; y <= ymax; y++)
        for (int x = 2; x < y; x++)
            for (int m = 1; m <= 2 * y; m++) {  // 小さい入力から順に比べる
                vector<int> coins = {1, x, y};
                int g = greedy(coins, m), e = exact(coins, m);
                if (g != e) {
                    cout << "coins 1 " << x << ' ' << y << ", amount " << m
                         << ": greedy " << g << ", optimal " << e << '\n';
                    return 0;
                }
            }
    cout << "none\n";
    // --8<-- [end:core]
}
