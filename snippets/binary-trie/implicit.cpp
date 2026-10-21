#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// a は昇順。a[l, r) は bit b より上がそろっている（空でない）とする。
// x を 0 から 2^(b+1) − 1 まで動かしたときの、min_i ((a_i xor x) の下位 b+1 bit) の和
long long full_sum(const vector<long long>& a, int l, int r, int b) {
    if (b < 0) return 0;
    // bit b が 1 になる最初の位置で 2 つに分ける（ソート済みなので連続）
    int m = l;
    while (m < r && !((a[m] >> b) & 1)) m++;
    if (l < m && m < r)  // 両側にある：x の bit b に合う側へ降りれば bit b は 0
        return full_sum(a, l, m, b - 1) + full_sum(a, m, r, b - 1);
    // 片側だけ：x の半分は bit b で必ず 1 になり、2^b ずつ払う
    int nl = (l < m ? l : m), nr = (l < m ? m : r);
    long long half = 1LL << b;
    return 2 * full_sum(a, nl, nr, b - 1) + half * half;
}
// --8<-- [end:core]

int main() {
    mt19937 rng(3);
    for (int t = 0; t < 300; t++) {
        int B = 1 + rng() % 6;
        int n = 1 + rng() % 8;
        vector<long long> a(n);
        for (auto& e : a) e = rng() % (1 << B);
        sort(a.begin(), a.end());
        long long want = 0;
        for (long long x = 0; x < (1 << B); x++) {
            long long mn = LLONG_MAX;
            for (long long e : a) mn = min(mn, e ^ x);
            want += mn;
        }
        assert(full_sum(a, 0, n, B - 1) == want);
    }
    // 入力：N B と a（2^B 未満）
    int n, B;
    cin >> n >> B;
    vector<long long> a(n);
    for (auto& e : a) cin >> e;
    sort(a.begin(), a.end());
    cout << full_sum(a, 0, n, B - 1) << '\n';
}
