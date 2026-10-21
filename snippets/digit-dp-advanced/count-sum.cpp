// 1 以上 N 以下（N は 10 進の文字列）の整数のうち、各桁の和が D の倍数のものの総和を 998244353 で割った余り
// 入力：N D
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
mint sum_digit_sum(const string& n, int d) {
    // cnt[t][r]・sum[t][r]：上から i 桁を決めた数のうち、フラグが t、桁和の余りが r のものの個数と、
    //   それらの数（決めた i 桁を 1 つの整数として読んだ値）の総和
    vector cnt(2, vector<mint>(d)), sum(2, vector<mint>(d));
    cnt[1][0] = 1;
    for (char c : n) {
        int lim = c - '0';
        vector ncnt(2, vector<mint>(d)), nsum(2, vector<mint>(d));
        for (int t = 0; t < 2; t++) {
            for (int r = 0; r < d; r++) {
                if (cnt[t][r] == 0) continue;
                for (int x = 0; x <= (t ? lim : 9); x++) {
                    int nt = (t && x == lim) ? 1 : 0;
                    int nr = (r + x) % d;
                    ncnt[nt][nr] += cnt[t][r];
                    // 各数は 10 倍して x を足したものになる：総和は 10 × 総和 + x × 個数
                    nsum[nt][nr] += sum[t][r] * 10 + cnt[t][r] * x;
                }
            }
        }
        cnt = ncnt;
        sum = nsum;
    }
    return sum[0][0] + sum[1][0];  // 0 も数えているが、総和には 0 しか足さない
}
// --8<-- [end:core]

long long brute(long long n, int d) {
    long long res = 0;
    for (long long x = 1; x <= n; x++) {
        int s = 0;
        for (long long y = x; y > 0; y /= 10) s += y % 10;
        if (s % d == 0) res += x;
    }
    return res % 998244353;
}

int main() {
    for (long long n = 1; n <= 600; n++) {
        for (int d = 1; d <= 12; d++) assert(sum_digit_sum(to_string(n), d).val() == brute(n, d));
    }
    string n;
    int d;
    cin >> n >> d;
    cout << sum_digit_sum(n, d).val() << '\n';
}
