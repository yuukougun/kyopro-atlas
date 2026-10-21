#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// ok[s] ＝ 集合 s を 1 つのグループにしてよいか。全体 (1 << n) - 1 を
// 名前のないグループに分ける方法の数を数える。O(3^n)
long long count_partitions(int n, const vector<bool>& ok) {
    int full = (1 << n) - 1;
    vector<long long> dp(1 << n, 0);
    dp[0] = 1;
    for (int mask = 1; mask <= full; mask++) {
        int low = mask & -mask;                  // まだグループのない最小番号
        for (int s = mask; s > 0; s = (s - 1) & mask) {
            if (!(s & low) || !ok[s]) continue;  // 最小番号を含むグループだけを選ぶ
            dp[mask] += dp[mask ^ s];
        }
    }
    return dp[full];
}
// --8<-- [end:core]

// ベル数を三角形で求める（検算用）
long long bell(int n) {
    vector<long long> row = {1};
    for (int i = 0; i < n; i++) {
        vector<long long> next = {row.back()};
        for (long long x : row) next.push_back(next.back() + x);
        row = next;
    }
    return row.front();
}

int main() {
    int n;
    cin >> n;
    vector<bool> all(1 << n, true);
    long long b = count_partitions(n, all);
    assert(b == bell(n));
    // 各グループを 2 人以下に限ると、マッチング（相手がいてもいなくてもよい）の数になる
    vector<bool> small(1 << n);
    for (int s = 0; s < (1 << n); s++) small[s] = __builtin_popcount(s) <= 2;
    vector<long long> inv(n + 2, 1);  // 対合の数 a(i) = a(i-1) + (i-1) a(i-2)
    for (int i = 2; i <= n; i++) inv[i] = inv[i - 1] + (i - 1) * inv[i - 2];
    assert(count_partitions(n, small) == inv[n]);
    cout << b << '\n';
}
