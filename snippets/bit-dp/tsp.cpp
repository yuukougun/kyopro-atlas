// 巡回セールスマン：頂点 0 から出て全頂点をちょうど 1 回ずつ訪れ、頂点 0 に戻る最小コスト
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;

// --8<-- [start:core]
long long tsp(const vector<vector<long long>>& cost) {
    int n = cost.size();
    // dp[S][v]：訪れた頂点の集合が S（頂点 0 を含む）で、いま v にいるときの最小コスト
    vector<vector<long long>> dp(1 << n, vector<long long>(n, INF));
    dp[1 << 0][0] = 0;                        // 始点 0 は最初から集合に入れる
    for (int S = 0; S < (1 << n); S++) {      // 整数の昇順＝部分集合が先
        for (int v = 0; v < n; v++) {
            if (dp[S][v] == INF) continue;    // 到達できない状態を飛ばす
            for (int u = 0; u < n; u++) {
                if ((S >> u) & 1) continue;   // u は訪問済み
                int T = S | (1 << u);
                dp[T][u] = min(dp[T][u], dp[S][v] + cost[v][u]);
            }
        }
    }
    long long ans = INF;
    int full = (1 << n) - 1;
    for (int v = 0; v < n; v++) {
        if (dp[full][v] == INF) continue;
        ans = min(ans, dp[full][v] + cost[v][0]);  // 最後に始点へ戻る分
    }
    return ans;
}
// --8<-- [end:core]

// 確かめ用：頂点 1..n-1 の順列をすべて試す
long long brute(const vector<vector<long long>>& cost) {
    int n = cost.size();
    vector<int> p;
    for (int i = 1; i < n; i++) p.push_back(i);
    long long best = INF;
    do {
        long long s = 0;
        int cur = 0;
        for (int x : p) {
            s += cost[cur][x];
            cur = x;
        }
        s += cost[cur][0];
        best = min(best, s);
    } while (next_permutation(p.begin(), p.end()));
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> cost(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> cost[i][j];
    }
    long long ans = tsp(cost);
    if (n <= 8) assert(ans == brute(cost));
    cout << ans << '\n';
}
