#include <bits/stdc++.h>
using namespace std;

// 検算用：要素 i を「今ある組に入れる／新しい組を作る」で全列挙する
long long brute(int n, const vector<vector<long long>>& a) {
    vector<int> g(n);
    long long best = LLONG_MIN;
    auto dfs = [&](auto&& self, int i, int groups) -> void {
        if (i == n) {
            long long s = 0;
            for (int x = 0; x < n; x++)
                for (int y = x + 1; y < n; y++)
                    if (g[x] == g[y]) s += a[x][y];
            best = max(best, s);
            return;
        }
        for (int c = 0; c <= groups; c++) {
            g[i] = c;
            self(self, i + 1, max(groups, c + 1));
        }
    };
    dfs(dfs, 0, 0);
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> a(n, vector<long long>(n));
    for (auto& row : a)
        for (auto& x : row) cin >> x;
    int full = (1 << n) - 1;

    // --8<-- [start:precompute]
    // f[s] ＝ 集合 s を 1 つのグループにしたときの得点。最小の要素 v を外した集合から O(N) で求める
    vector<long long> f(1 << n, 0);
    for (int s = 1; s <= full; s++) {
        int v = __builtin_ctz(s);
        int rest = s ^ (1 << v);
        f[s] = f[rest];
        for (int j = 0; j < n; j++)
            if (rest >> j & 1) f[s] += a[v][j];
    }
    // --8<-- [end:precompute]

    // --8<-- [start:core]
    // dp[s] ＝ 集合 s をいくつかのグループに分けたときの得点の最大。全体で O(3^N)
    vector<long long> dp(1 << n, LLONG_MIN);
    dp[0] = 0;  // 空の集合は 0 個のグループに分ける
    for (int s = 1; s <= full; s++) {
        int low = s & -s;   // s の最小の要素。これを含むグループ g を選ぶ
        int rest = s ^ low;
        for (int t = rest;; t = (t - 1) & rest) {  // t は rest の部分集合（0 も含む）
            int g = t | low;
            dp[s] = max(dp[s], f[g] + dp[s ^ g]);  // s ^ g は s より小さい
            if (t == 0) break;
        }
    }
    // --8<-- [end:core]

    if (n <= 8) assert(dp[full] == brute(n, a));
    cout << dp[full] << '\n';
}
