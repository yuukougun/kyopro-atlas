// (min,+) の行列の累乗：辺をちょうど K 本使う最短の歩道
// 入力：N M K、続く M 行は有向辺「u v w」（0-indexed、重み w ≥ 0）
// 出力：頂点 0 から各頂点への、辺をちょうど K 本使う歩道の重みの最小（なければ -1）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long INF = 1LL << 60;  // 「足し算」min の単位元（零元）。辺がないことを表す

// 単位行列：対角が 0（「掛け算」+ の単位元）、ほかは INF
vector<vector<long long>> unit_matrix(int n) {
    vector<vector<long long>> e(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) e[i][i] = 0;
    return e;
}

// C[i][j] = min_k (A[i][k] + B[k][j])。INF どうしを足してあふれさせない
vector<vector<long long>> mul(const vector<vector<long long>>& a,
                              const vector<vector<long long>>& b) {
    int n = a.size();
    vector<vector<long long>> c(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) {
            if (a[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (b[k][j] == INF) continue;
                c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
            }
        }
    return c;
}

vector<vector<long long>> matpow(vector<vector<long long>> a, long long k) {
    vector<vector<long long>> r = unit_matrix(a.size());
    while (k > 0) {
        if (k & 1) r = mul(r, a);
        a = mul(a, a);
        k >>= 1;
    }
    return r;
}
// --8<-- [end:core]

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<vector<long long>> a(n, vector<long long>(n, INF));
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        a[u][v] = min(a[u][v], w);  // 多重辺は軽い方だけでよい
    }
    vector<vector<long long>> r = matpow(a, k);
    for (int j = 0; j < n; j++) {
        cout << (r[0][j] == INF ? -1 : r[0][j]) << (j + 1 < n ? ' ' : '\n');
    }
}
