#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 頂点 0 からの距離で、頂点 n-1 だけが最も遠い n 頂点（n >= 2）の
// 連結な単純無向グラフの数を mod で割った余り。mod は素数でなくてよい。O(n^3)
long long count_farthest(int n, long long mod) {
    int mid = n - 2;                             // 頂点 0 と n-1 以外の頂点の数
    vector<vector<long long>> C(mid + 1, vector<long long>(mid + 1, 0));
    for (int i = 0; i <= mid; i++) {             // 割り算を使わないパスカルの三角形
        C[i][0] = 1 % mod;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    vector<long long> pw2(n * (n - 1) / 2 + 1);
    pw2[0] = 1 % mod;
    for (int i = 1; i < (int)pw2.size(); i++) pw2[i] = pw2[i - 1] * 2 % mod;
    // to[j][k] ＝ (2^j - 1)^k：前の層 j 頂点へ、新しい層の k 頂点がそれぞれ 1 本以上つなぐ
    vector<vector<long long>> to(n, vector<long long>(n, 0));
    for (int j = 1; j < n; j++) {
        to[j][0] = 1 % mod;
        for (int k = 1; k < n; k++) to[j][k] = to[j][k - 1] * ((pw2[j] - 1 + mod) % mod) % mod;
    }
    // dp[i][j] ＝ 真ん中の頂点を i 個まで層に配り、最後の層が j 頂点のときの辺の張り方の数
    vector<vector<long long>> dp(mid + 1, vector<long long>(n, 0));
    dp[0][1] = 1 % mod;                          // 距離 0 の層は頂点 0 だけ
    for (int i = 0; i < mid; i++) {
        for (int j = 1; j <= i + 1; j++) {
            if (dp[i][j] == 0) continue;
            for (int k = 1; i + k <= mid; k++) {  // 次の層の大きさ
                long long w = C[mid - i][k] * to[j][k] % mod * pw2[k * (k - 1) / 2] % mod;
                dp[i + k][k] = (dp[i + k][k] + dp[i][j] * w) % mod;
            }
        }
    }
    long long ans = 0;                           // 頂点 n-1 は 1 頂点だけの最後の層
    for (int j = 1; j <= mid + 1; j++) ans = (ans + dp[mid][j] * to[j][1]) % mod;
    return ans;
}
// --8<-- [end:core]

// 検算用：辺の部分集合をすべて試し、BFS で距離を調べる
long long brute(int n) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) edges.push_back({i, j});
    int m = edges.size();
    long long cnt = 0;
    for (int bits = 0; bits < (1 << m); bits++) {
        vector<vector<int>> g(n);
        for (int e = 0; e < m; e++)
            if (bits >> e & 1) {
                g[edges[e].first].push_back(edges[e].second);
                g[edges[e].second].push_back(edges[e].first);
            }
        vector<int> dist(n, -1);
        queue<int> q;
        dist[0] = 0;
        q.push(0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : g[v])
                if (dist[u] < 0) { dist[u] = dist[v] + 1; q.push(u); }
        }
        bool ok = dist[n - 1] >= 0;
        for (int v = 1; v < n - 1; v++) ok = ok && dist[v] >= 0 && dist[v] < dist[n - 1];
        if (ok) cnt++;
    }
    return cnt;
}

int main() {
    int n;
    long long mod;
    cin >> n >> mod;
    for (int k = 2; k <= 6; k++) assert(count_farthest(k, 1000000007) == brute(k));
    cout << count_farthest(n, mod) << '\n';
}
