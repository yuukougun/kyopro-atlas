// bit ごとの寄与：すべてのペアの XOR の和と、長さ 2 以上のすべての区間の XOR の和。
// 入力：n と a[0..n-1]（0 <= a[i] < 2^60）。出力：1 行目にペアの和を 10^9+7 で割った余り、
// 2 行目に区間の和（a[i] < 2^30・n <= 2×10^5 程度なら long long に収まる範囲で使う）。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

// --8<-- [start:core]
// すべてのペア i < j について a[i] xor a[j] を足した値を MOD で割った余り
long long pair_xor_sum(const vector<long long>& a) {
    long long n = a.size(), res = 0;
    for (int k = 0; k < 60; k++) {
        long long ones = 0;
        for (long long x : a) ones += (x >> k) & 1;
        long long zeros = n - ones;
        // bit k が 1 になるのは、0 と 1 を 1 つずつ選んだペアだけ
        long long pairs = ones % MOD * (zeros % MOD) % MOD;
        long long pw = (1LL << k) % MOD;  // 1 << k は int であふれるので 1LL
        res = (res + pairs * pw) % MOD;
    }
    return res;
}
// --8<-- [end:core]

// --8<-- [start:range]
// 長さ 2 以上のすべての区間 [l, r) について、区間の XOR を足した値
long long range_xor_sum(const vector<long long>& a) {
    int n = a.size();
    long long res = 0;
    for (int k = 0; k < 30; k++) {
        long long cnt[2] = {1, 0};  // s_0 = 0 の bit k は 0
        long long s = 0, odd = 0;   // s：s_r の bit k、odd：bit k が 1 の区間の数
        for (int r = 1; r <= n; r++) {
            s ^= (a[r - 1] >> k) & 1;
            odd += cnt[s ^ 1];  // s_l と s_r の bit k が異なる l < r の数
            cnt[s]++;
        }
        res += odd << k;
    }
    for (long long x : a) res -= x;  // 長さ 1 の区間（a[i] そのもの）を除く
    return res;
}
// --8<-- [end:range]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // 小さい入力では素朴な計算と照らし合わせる
    if (n <= 300) {
        long long naive_pair = 0, naive_range = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) naive_pair = (naive_pair + (a[i] ^ a[j]) % MOD) % MOD;
        for (int l = 0; l < n; l++) {
            long long x = a[l];
            for (int r = l + 1; r < n; r++) {
                x ^= a[r];
                naive_range += x;
            }
        }
        assert(pair_xor_sum(a) == naive_pair);
        bool small = true;
        for (long long x : a) small = small && x < (1LL << 30);
        if (small) assert(range_xor_sum(a) == naive_range);
    }
    cout << pair_xor_sum(a) << '\n';
    bool small = true;
    for (long long x : a) small = small && x < (1LL << 30);
    cout << (small ? range_xor_sum(a) : -1) << '\n';
}
