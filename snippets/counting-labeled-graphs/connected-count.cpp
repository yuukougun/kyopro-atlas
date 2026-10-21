#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// c[n] ＝ 頂点に番号の付いた n 頂点の連結な単純無向グラフの数（n = 1..N）
// g[n] ＝ 2^(n(n-1)/2)（連結とは限らないグラフの数）。O(N^2)
vector<mint> count_connected(int N) {
    vector<vector<mint>> C(N + 1, vector<mint>(N + 1, 0));  // パスカルの三角形
    for (int i = 0; i <= N; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    vector<mint> g(N + 1), c(N + 1, 0);
    for (int n = 0; n <= N; n++) g[n] = mint(2).pow((long long)n * (n - 1) / 2);
    for (int n = 1; n <= N; n++) {
        c[n] = g[n];
        // 頂点 1 を含む成分の大きさ k（k < n）で非連結なものを分類して引く
        for (int k = 1; k < n; k++) {
            c[n] -= C[n - 1][k - 1] * c[k] * g[n - k];
        }
    }
    return c;
}
// --8<-- [end:core]

// 検算用：辺の部分集合をすべて試し、Union-Find で連結かを調べる
long long brute(int n) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) edges.push_back({i, j});
    int m = edges.size();
    long long cnt = 0;
    vector<int> par(n);
    for (int bits = 0; bits < (1 << m); bits++) {
        iota(par.begin(), par.end(), 0);
        auto find = [&](auto&& self, int x) -> int {
            return par[x] == x ? x : par[x] = self(self, par[x]);
        };
        int comp = n;
        for (int e = 0; e < m; e++) {
            if (!(bits >> e & 1)) continue;
            int a = find(find, edges[e].first), b = find(find, edges[e].second);
            if (a != b) { par[a] = b; comp--; }
        }
        if (comp == 1) cnt++;
    }
    return cnt;
}

int main() {
    int N;
    cin >> N;
    vector<mint> c = count_connected(max(N, 5));
    for (int n = 1; n <= 5; n++) assert(c[n].val() == brute(n));
    for (int n = 1; n <= N; n++) cout << c[n].val() << (n == N ? '\n' : ' ');
}
