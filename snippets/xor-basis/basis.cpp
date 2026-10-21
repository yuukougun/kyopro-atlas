// XOR 基底：n 個の整数（0 以上 2^60 未満）から XOR で作れる値の個数・最大値・K 番目に小さい値。
// 入力：n、a[0..n-1]、q、k[0..q-1]（k は 0 から数えた番号）。
// 出力：基底の大きさ r、作れる値の最大値、各 k について k 番目に小さい値（なければ -1）。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const int B = 60;  // 値は 0 以上 2^B 未満

struct XorBasis {
    // b[i] は最上位 bit が i の基底の要素（なければ 0）
    long long b[B] = {};
    int r = 0;  // 基底の大きさ

    // x を基底に入れる。今の基底で作れる値なら false（何も変えない）
    bool insert(long long x) {
        for (int i = B - 1; i >= 0; i--) {
            if ((x >> i & 1) == 0) continue;
            if (b[i] == 0) {  // 最上位 bit が i の要素がまだない
                b[i] = x;
                r++;
                return true;
            }
            x ^= b[i];  // bit i を消す（上の bit は変わらない）
        }
        return false;  // 0 になった：作れる値だった
    }

    // x に基底の要素を XOR して作れる値のうち最小のもの（x が作れる値なら 0）
    long long reduce(long long x) const {
        for (int i = B - 1; i >= 0; i--) x = min(x, x ^ b[i]);
        return x;
    }

    // 作れる値の最大値（上の bit から貪欲）
    long long max_value() const {
        long long x = 0;
        for (int i = B - 1; i >= 0; i--) x = max(x, x ^ b[i]);
        return x;
    }
};
// --8<-- [end:core]

// --8<-- [start:kth]
// 簡約した基底（各要素の最上位 bit が、ほかの要素では 0）を小さい順に返す
vector<long long> reduced(const XorBasis& xb) {
    long long b[B];
    for (int i = 0; i < B; i++) b[i] = xb.b[i];
    for (int i = 0; i < B; i++) {  // 下の bit から：b[i] はもう下の pivot が 0
        if (b[i] == 0) continue;
        for (int j = i + 1; j < B; j++) {
            if (b[j] >> i & 1) b[j] ^= b[i];
        }
    }
    vector<long long> res;
    for (int i = 0; i < B; i++) {
        if (b[i] != 0) res.push_back(b[i]);
    }
    return res;  // 最上位 bit の小さい順＝値の小さい順
}

// 作れる値（0 を含む）の k 番目に小さい値（k は 0 から数える）。なければ -1
long long kth(const vector<long long>& rb, long long k) {
    int r = rb.size();
    if (k >= (1LL << r)) return -1;
    long long x = 0;
    for (int i = 0; i < r; i++) {
        if (k >> i & 1) x ^= rb[i];  // k の bit i が 1 なら i 番目に小さい基底を使う
    }
    return x;
}
// --8<-- [end:kth]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    XorBasis xb;
    for (int i = 0; i < n; i++) xb.insert(a[i]);
    vector<long long> rb = reduced(xb);

    // 小さい n では全部の部分集合と比べる
    if (n <= 16) {
        set<long long> all;
        map<long long, long long> ways;
        for (int s = 0; s < (1 << n); s++) {
            long long x = 0;
            for (int i = 0; i < n; i++) {
                if (s >> i & 1) x ^= a[i];
            }
            all.insert(x);
            ways[x]++;
        }
        assert((long long)all.size() == (1LL << xb.r));
        for (auto [x, c] : ways) assert(c == (1LL << (n - xb.r)));  // 作り方は 2^(n-r) 通りずつ
        assert(*all.rbegin() == xb.max_value());
        long long k = 0;
        for (long long x : all) {
            assert(kth(rb, k) == x);
            assert(xb.reduce(x) == 0);
            k++;
        }
    }

    cout << xb.r << '\n' << xb.max_value() << '\n';
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long k;
        cin >> k;
        cout << kth(rb, k) << '\n';
    }
}
