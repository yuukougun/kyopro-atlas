#include <bits/stdc++.h>
using namespace std;

int c[4];
long long l[2];
int grid[3][5];

int main() {
    int n, m;
    cin >> n >> m;
    // --8<-- [start:memset]
    memset(c, 0, sizeof c);     // 0
    memset(c, -1, sizeof c);    // -1（全ビットが 1）
    memset(c, 0x3f, sizeof c);  // 0x3f3f3f3f = 1061109567
    memset(l, 0x3f, sizeof l);  // 0x3f3f3f3f3f3f3f3f = 4557430888798830399
    // --8<-- [end:memset]
    cout << c[0] << ' ' << l[0] << '\n';
    // --8<-- [start:memset-ng]
    memset(c, 1, sizeof c);     // 1 ではなく 0x01010101 = 16843009
    // --8<-- [end:memset-ng]
    cout << c[0] << '\n';
    // --8<-- [start:fill]
    fill(begin(c), end(c), 1);                    // 1 次元の C 配列
    for (auto& row : grid) ranges::fill(row, 7);  // 2 次元の C 配列は行ごとに
    vector<vector<long long>> dp(n, vector<long long>(m));
    for (auto& row : dp) ranges::fill(row, -1);   // 大きさを変えずに埋める
    dp.assign(n + 1, vector<long long>(m + 1, 0)); // 大きさごと作り直す
    // --8<-- [end:fill]
    cout << c[3] << ' ' << grid[2][4] << ' ' << dp.size() << ' ' << dp[n][m] << '\n';
}
