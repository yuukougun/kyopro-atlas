#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

const int MAX = 2000000;
vector<mint> fact(MAX + 1), ifact(MAX + 1);

void init() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) fact[i] = fact[i - 1] * i;
    ifact[MAX] = fact[MAX].inv();
    for (int i = MAX; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
}

mint comb(int n, int r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return fact[n] * ifact[r] * ifact[n - r];
}

// --8<-- [start:core]
// 和が 2n-2 の正の整数列 d すべてについての (n - 葉の数 + 1) の和（n >= 2）
// 列の個数は C(2n-3, n-1)。葉の数の和は「頂点 v が葉になる列の数」の n 倍で、
// d[v] = 1 を除いた n-1 個の正の整数の和が 2n-3 になる列の数 C(2n-4, n-2) を使う
mint sum_max_diameter(int n) {
    mint sequences = comb(2 * n - 3, n - 1);
    mint leaves = mint(n) * comb(2 * n - 4, n - 2);
    return mint(n + 1) * sequences - leaves;
}
// --8<-- [end:core]

// 小さい n で、木をすべて作って次数列ごとの直径の最大値を足したものと比べる
long long brute(int n) {
    vector<pair<int, int>> cand;
    for (int u = 0; u < n; u++)
        for (int v = u + 1; v < n; v++) cand.push_back({u, v});
    int m = cand.size();
    map<vector<int>, int> best;
    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount(mask) != n - 1) continue;
        vector<vector<int>> g(n);
        vector<int> d(n);
        for (int e = 0; e < m; e++)
            if (mask >> e & 1) {
                auto [u, v] = cand[e];
                g[u].push_back(v), g[v].push_back(u);
                d[u]++, d[v]++;
            }
        auto bfs = [&](int s) {
            vector<int> dist(n, -1);
            queue<int> q;
            dist[s] = 0;
            q.push(s);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int w : g[v])
                    if (dist[w] < 0) dist[w] = dist[v] + 1, q.push(w);
            }
            return dist;
        };
        vector<int> d0 = bfs(0);
        if (*min_element(d0.begin(), d0.end()) < 0) continue;  // 連結でない
        int far = max_element(d0.begin(), d0.end()) - d0.begin();
        vector<int> d1 = bfs(far);
        int diam = *max_element(d1.begin(), d1.end());
        best[d] = max(best[d], diam);
    }
    long long sum = 0;
    for (auto& [d, x] : best) sum += x;
    return sum;
}

int main() {
    init();
    for (int n = 2; n <= 7; n++) assert(mint(brute(n)) == sum_max_diameter(n));
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << sum_max_diameter(n).val() << '\n';
    }
}
