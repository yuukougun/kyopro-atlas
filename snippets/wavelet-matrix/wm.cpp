#include <bits/stdc++.h>
using namespace std;

// 値は 0 以上 2^lg 未満（座標圧縮しておくと lg が小さくなる）
struct WaveletMatrix {
    int n, lg;
    vector<vector<int>> zero;       // zero[d][i]：段 d の先頭 i 個のうち bit が 0 の個数
    vector<int> nz;                 // nz[d]：段 d で bit が 0 の個数
    vector<vector<long long>> sum;  // sum[d][i]：段 d の並びの先頭 i 個の値の和

    WaveletMatrix(vector<int> a, int lg) : n(a.size()), lg(lg) {
        zero.assign(lg, vector<int>(n + 1, 0));
        nz.assign(lg, 0);
        sum.assign(lg + 1, vector<long long>(n + 1, 0));
        for (int d = 0; d < lg; d++) {
            int b = lg - 1 - d;  // 段 d は上から d 番目の bit を見る
            for (int i = 0; i < n; i++) {
                zero[d][i + 1] = zero[d][i] + ((a[i] >> b & 1) == 0);
                sum[d][i + 1] = sum[d][i] + a[i];
            }
            nz[d] = zero[d][n];
            stable_partition(a.begin(), a.end(), [&](int v) { return (v >> b & 1) == 0; });
        }
        for (int i = 0; i < n; i++) sum[lg][i + 1] = sum[lg][i] + a[i];
    }

    // --8<-- [start:core]
    // [l, r) の k 番目（0 始まり）に小さい値
    int kth_smallest(int l, int r, int k) const {
        int res = 0;
        for (int d = 0; d < lg; d++) {
            int zl = zero[d][l], zr = zero[d][r];
            if (k < zr - zl) {
                l = zl, r = zr;                    // 0 の側へ
            } else {
                k -= zr - zl;
                res |= 1 << (lg - 1 - d);
                l = nz[d] + (l - zl), r = nz[d] + (r - zr);  // 1 の側へ
            }
        }
        return res;
    }

    // [l, r) のうち x 未満の値の（個数, 和）
    pair<int, long long> count_sum_less(int l, int r, long long x) const {
        if (x <= 0) return {0, 0};
        if (x >= (1LL << lg)) return {r - l, sum[0][r] - sum[0][l]};
        int cnt = 0;
        long long s = 0;
        for (int d = 0; d < lg; d++) {
            int zl = zero[d][l], zr = zero[d][r];
            if (x >> (lg - 1 - d) & 1) {
                // x の bit が 1：0 の側はすべて x 未満。段 d + 1 での位置は [zl, zr)
                cnt += zr - zl;
                s += sum[d + 1][zr] - sum[d + 1][zl];
                l = nz[d] + (l - zl), r = nz[d] + (r - zr);
            } else {
                l = zl, r = zr;
            }
        }
        return {cnt, s};  // 残った [l, r) は x と等しい値なので数えない
    }
    // --8<-- [end:core]
};

int main() {
    // 小さな乱択で素朴な方法と比べる
    mt19937 rng(1);
    for (int t = 0; t < 200; t++) {
        int n = rng() % 9, lg = 1 + rng() % 4;
        vector<int> a(n);
        for (auto& v : a) v = rng() % (1 << lg);
        WaveletMatrix wm(a, lg);
        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                vector<int> b(a.begin() + l, a.begin() + r);
                sort(b.begin(), b.end());
                for (int k = 0; k < r - l; k++) assert(wm.kth_smallest(l, r, k) == b[k]);
                for (long long x = -1; x <= (1 << lg) + 1; x++) {
                    int c = 0;
                    long long s = 0;
                    for (int v : b) if (v < x) c++, s += v;
                    assert(wm.count_sum_less(l, r, x) == make_pair(c, s));
                }
            }
        }
    }
    // 入力：n q、列、クエリ「0 l r k」は k 番目、「1 l r x」は x 未満の個数と和
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& v : a) cin >> v;
    WaveletMatrix wm(a, 30);
    while (q--) {
        int type, l, r;
        long long y;
        cin >> type >> l >> r >> y;
        if (type == 0) {
            cout << wm.kth_smallest(l, r, y) << '\n';
        } else {
            auto [c, s] = wm.count_sum_less(l, r, y);
            cout << c << ' ' << s << '\n';
        }
    }
}
