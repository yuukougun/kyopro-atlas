#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 行列式 mod m（m は素数でなくてよい、2 ≤ m ≤ 10^9）。逆元を使わず、
// ピボットの行と下の行で互除法のように引き合い、下の行のその列を 0 にする
long long det_mod(vector<vector<long long>> a, long long m) {
    int n = a.size();
    long long res = 1;
    for (int c = 0; c < n; c++) {
        for (int r = c + 1; r < n; r++) {
            while (a[r][c] != 0) {
                long long q = a[c][c] / a[r][c];  // 整数としての商
                for (int j = c; j < n; j++) {
                    a[c][j] = (a[c][j] - q * a[r][j]) % m;
                    if (a[c][j] < 0) a[c][j] += m;
                }
                swap(a[c], a[r]);  // 余りが小さい方をピボットの行に
                res = (m - res) % m;  // 行の交換で符号が反転する
            }
        }
        if (a[c][c] == 0) return 0;
        res = res * a[c][c] % m;
    }
    return res;
}
// --8<-- [end:core]

long long det_brute(const vector<vector<long long>>& a, long long m) {
    int n = a.size();
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    long long sum = 0;
    do {
        int inv = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (perm[i] > perm[j]) inv++;
        long long prod = 1;
        for (int i = 0; i < n; i++) prod = prod * a[i][perm[i]] % m;
        sum = (inv % 2 == 0) ? (sum + prod) % m : (sum - prod + m) % m;
    } while (next_permutation(perm.begin(), perm.end()));
    return sum;
}

int main() {
    mt19937 rng(2);
    const long long mods[] = {2, 4, 6, 12, 36, 1000000000};
    for (int t = 0; t < 600; t++) {
        long long m = mods[t % 6];
        int n = rng() % 6 + 1;
        vector<vector<long long>> a(n, vector<long long>(n));
        for (auto& row : a)
            for (auto& x : row) x = (t % 2 == 0) ? rng() % m : rng() % 3;
        assert(det_mod(a, m) == det_brute(a, m));
    }
    int n;
    long long m;
    cin >> n >> m;
    vector<vector<long long>> a(n, vector<long long>(n));
    for (auto& row : a)
        for (auto& x : row) cin >> x;
    cout << det_mod(a, m) << '\n';
}
