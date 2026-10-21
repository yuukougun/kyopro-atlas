// 行列の積と繰り返し二乗法（mod 998244353）
// 入力：n K、続いて n × n の行列 A。出力：A^K（n 行）
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
vector<vector<mint>> unit_matrix(int n) {
    vector<vector<mint>> e(n, vector<mint>(n, 0));
    for (int i = 0; i < n; i++) e[i][i] = 1;
    return e;
}

// C = A B。i-k-j の順に回すと B を行の向きに読むので速い
vector<vector<mint>> mul(const vector<vector<mint>>& a, const vector<vector<mint>>& b) {
    int n = a.size(), m = b.size(), l = b[0].size();
    vector<vector<mint>> c(n, vector<mint>(l, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < m; k++)
            for (int j = 0; j < l; j++) c[i][j] += a[i][k] * b[k][j];
    return c;
}

// A^K。K = 0 なら単位行列
vector<vector<mint>> matpow(vector<vector<mint>> a, long long k) {
    vector<vector<mint>> r = unit_matrix(a.size());
    while (k > 0) {
        if (k & 1) r = mul(r, a);
        a = mul(a, a);
        k >>= 1;
    }
    return r;
}
// --8<-- [end:core]

// 素朴に K 回掛けた結果と比べる（K が小さいときだけ）
vector<vector<mint>> naive(const vector<vector<mint>>& a, long long k) {
    vector<vector<mint>> r = unit_matrix(a.size());
    for (long long t = 0; t < k; t++) r = mul(r, a);
    return r;
}

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<vector<mint>> a(n, vector<mint>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            long long x;
            cin >> x;
            a[i][j] = x;
        }
    vector<vector<mint>> r = matpow(a, k);
    if (k <= 50) assert(r == naive(a, k));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << r[i][j].val() << (j + 1 < n ? ' ' : '\n');
    }
}
