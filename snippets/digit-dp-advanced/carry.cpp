// 額面 a[0] = 1 < a[1] < ... < a[n-1]（a[i+1] は a[i] の倍数）の硬貨で X 円を払い、
// お釣りを受け取るとき、やり取りする硬貨の枚数の最小
// 入力：n X、続けて a[0] ... a[n-1]
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long min_coins(const vector<long long>& a, long long x) {
    int n = a.size();
    // X を混合進数に直す：d[i] は額面 a[i] の桁（i < n-1 なら 0 <= d[i] < a[i+1]/a[i]）
    vector<long long> d(n);
    for (int i = n - 1; i >= 0; i--) {
        d[i] = x / a[i];
        x %= a[i];
    }
    const long long INF = LLONG_MAX / 4;
    // dp[c]：下の桁から額面 a[i] の手前まで決めたとき、
    //   桁 i へ繰り上がりが c（0 か 1）ある状態での、それまでの枚数の最小
    long long dp[2] = {0, INF};
    for (int i = 0; i < n - 1; i++) {
        long long r = a[i + 1] / a[i];  // この桁の 1 つ上は r 枚ぶん
        long long nd[2] = {INF, INF};
        for (int c = 0; c < 2; c++) {
            if (dp[c] == INF) continue;
            long long v = d[i] + c;                      // この桁で払う枚数（0 <= v <= r）
            nd[0] = min(nd[0], dp[c] + v);               // ちょうど v 枚払う
            nd[1] = min(nd[1], dp[c] + (r - v));         // 上の硬貨で払い、r - v 枚のお釣りをもらう
        }
        dp[0] = nd[0];
        dp[1] = nd[1];
    }
    // いちばん上の額面には繰り上げる先がないので、繰り上がりを含めて払う
    return min(dp[0] + d[n - 1], dp[1] + d[n - 1] + 1);
}
// --8<-- [end:core]

// 小さい場合の確かめ：金額の範囲 [-M, M] で、0 から x まで ±a[i] の移動の最短路
long long brute(const vector<long long>& a, long long x) {
    const int M = 2000;
    vector<int> dist(2 * M + 1, -1);
    deque<int> q;
    dist[M] = 0;
    q.push_back(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (long long c : a) {
            for (int s : {-1, 1}) {
                long long w = v + s * c;
                if (w < -M || w > M || dist[w + M] != -1) continue;
                dist[w + M] = dist[v + M] + 1;
                q.push_back(w);
            }
        }
    }
    return dist[x + M];
}

int main() {
    vector<vector<long long>> coin_sets = {{1}, {1, 10}, {1, 10, 100}, {1, 2, 4, 8, 16}, {1, 3, 9, 27, 81}, {1, 5, 10, 50, 100}, {1, 6, 36}, {1, 4, 12, 60}};
    for (auto& a : coin_sets) {
        for (long long x = 1; x <= 400; x++) assert(min_coins(a, x) == brute(a, x));
    }
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    cout << min_coins(a, x) << '\n';
}
