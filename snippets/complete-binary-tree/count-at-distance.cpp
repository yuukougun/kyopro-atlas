#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 頂点 1..n（i の親は i / 2）の木で、v の子孫のうち v から深さ d 下にある頂点の数
long long count_below(long long n, long long v, long long d) {
    if (v > n) return 0;
    long long l = v, r = v;  // 深さ 0 下の範囲は [v, v]
    for (long long i = 0; i < d; i++) {
        l = 2 * l;           // l <= n <= 10^18 なので 2 倍してもあふれない
        r = 2 * r + 1;       // r <= n に切ってあるのであふれない
        if (l > n) return 0;  // この深さに頂点がない（d が巨大でも 60 回ほどで抜ける）
        r = min(r, n);        // 範囲を n で切る
    }
    return r - l + 1;
}

// 頂点 x から距離がちょうど k の頂点の数
long long count_at_distance(long long n, long long x, long long k) {
    long long ans = count_below(n, x, k);  // x の部分木の中
    long long c = x;                       // 今いる頂点（祖先へ上がっていく）
    for (long long j = 1; j <= k && c > 1; j++) {
        long long p = c / 2;  // x から距離 j の祖先
        if (j == k) {
            ans += 1;         // 祖先 p そのもの
        } else {
            ans += count_below(n, c ^ 1, k - j - 1);  // c の兄弟の部分木
        }
        c = p;
    }
    return ans;
}
// --8<-- [end:core]

int main() {
    // 小さい木で BFS と照合する
    for (int n = 1; n <= 70; n++) {
        vector<vector<int>> g(n + 1);
        for (int i = 2; i <= n; i++) { g[i].push_back(i / 2); g[i / 2].push_back(i); }
        for (int x = 1; x <= n; x++) {
            vector<int> dist(n + 1, -1);
            queue<int> q;
            dist[x] = 0;
            q.push(x);
            while (!q.empty()) {
                int v = q.front(); q.pop();
                for (int w : g[v]) if (dist[w] < 0) { dist[w] = dist[v] + 1; q.push(w); }
            }
            for (int k = 0; k <= n + 2; k++) {
                long long cnt = count(dist.begin() + 1, dist.end(), k);
                assert(count_at_distance(n, x, k) == cnt);
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        long long n, x, k;
        cin >> n >> x >> k;
        cout << count_at_distance(n, x, k) << '\n';
    }
}
