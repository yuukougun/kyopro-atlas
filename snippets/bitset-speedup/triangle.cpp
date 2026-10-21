#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3000;        // 頂点数の上限（コンパイル時の定数）
bitset<MAXN> adj[MAXN];       // 隣接行列の各行。約 1.1 MB なのでグローバルに置く

int main() {
    int n, m;
    cin >> n >> m;
    for (int e = 0; e < m; e++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u][v] = adj[v][u] = 1;
    }
    // --8<-- [start:core]
    long long total = 0;  // 各三角形を 3 本の辺から 1 回ずつ、合わせて 3 回数える
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!adj[i][j]) continue;
            total += (adj[i] & adj[j]).count();  // i と j の共通の隣接頂点の数
        }
    }
    long long triangles = total / 3;
    // --8<-- [end:core]
    // 確かめ：素朴な O(N^3)
    long long naive = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                if (adj[i][j] && adj[j][k] && adj[i][k]) naive++;
    assert(naive == triangles);
    cout << triangles << '\n';
}
