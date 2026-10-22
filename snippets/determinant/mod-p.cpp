#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// 行列式 mod 998244353。上三角にしながら対角成分を掛けていく
mint det(vector<vector<mint>> a) {
    int n = a.size();
    mint res = 1;
    for (int c = 0; c < n; c++) {
        int p = c;
        while (p < n && a[p][c] == 0) p++;
        if (p == n) return 0;  // この列に 0 でない値がない
        if (p != c) {
            swap(a[p], a[c]);
            res = -res;  // 行の交換で符号が反転する
        }
        res *= a[c][c];
        mint inv = a[c][c].inv();
        for (int r = c + 1; r < n; r++) {
            mint f = a[r][c] * inv;
            if (f == 0) continue;
            for (int j = c; j < n; j++) a[r][j] -= f * a[c][j];
        }
    }
    return res;
}
// --8<-- [end:core]

// 定義（置換の和）どおりに求める。小さい行列で det と比べる
mint det_brute(const vector<vector<mint>>& a) {
    int n = a.size();
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    mint sum = 0;
    do {
        int inv = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (perm[i] > perm[j]) inv++;
        mint prod = 1;
        for (int i = 0; i < n; i++) prod *= a[i][perm[i]];
        sum += (inv % 2 == 0) ? prod : -prod;
    } while (next_permutation(perm.begin(), perm.end()));
    return sum;
}

int main() {
    mt19937 rng(1);
    for (int t = 0; t < 300; t++) {
        int n = rng() % 6 + 1;
        vector<vector<mint>> a(n, vector<mint>(n));
        for (auto& row : a)
            for (auto& x : row) x = rng() % 3;  // 0 を多くして行の交換を起こす
        assert(det(a) == det_brute(a));
    }
    int n;
    cin >> n;
    vector<vector<mint>> a(n, vector<mint>(n));
    for (auto& row : a)
        for (auto& x : row) {
            long long v;
            cin >> v;
            x = v;
        }
    cout << det(a).val() << '\n';
}
