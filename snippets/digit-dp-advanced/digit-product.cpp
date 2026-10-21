// 1 以上 N 以下の整数のうち、各桁の積が K 以下のものの個数
// 入力：N K（1 <= N <= 10^18、1 <= K <= 10^18）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long count_product(long long n, long long k) {
    string s = to_string(n);
    // 積が K を超えたら K + 1 にまとめる（0 を掛ければ 0 に戻るので捨てられない）
    auto mul = [&](long long p, int x) -> long long {
        if (x == 0) return 0;
        return (p > k / x) ? k + 1 : p * x;
    };
    map<long long, long long> freeq;  // 始まっていて N より小さいことが確定した数：積 → 個数
    long long tight = 1;              // N と一致している数（1 本だけ）の積
    long long not_started = 0;        // まだ先頭の 0 しか置いていない数の個数（0 か 1）
    for (int i = 0; i < (int)s.size(); i++) {
        int lim = s[i] - '0';
        map<long long, long long> nf;  // 次の桁の表は別に作る（同じ map を書き換えながら回さない）
        for (auto [p, c] : freeq) {
            for (int x = 0; x <= 9; x++) nf[mul(p, x)] += c;
        }
        if (not_started) {
            for (int x = 1; x <= 9; x++) nf[x] += not_started;  // ここで数が始まる
        }
        // 一致の道から、N の桁より小さい数字を置いて未満へ移る
        for (int x = 0; x < lim; x++) {
            if (i == 0 && x == 0) {
                not_started = 1;  // 最上位に 0 を置いた数は、まだ始まっていない
            } else {
                nf[mul(tight, x)] += 1;
            }
        }
        tight = mul(tight, lim);
        freeq = move(nf);
    }
    long long res = (tight <= k) ? 1 : 0;  // N 自身
    for (auto [p, c] : freeq) {
        if (p <= k) res += c;
    }
    return res;
}
// --8<-- [end:core]

long long brute(long long n, long long k) {
    long long res = 0;
    for (long long x = 1; x <= n; x++) {
        long long p = 1;
        for (long long y = x; y > 0; y /= 10) p *= y % 10;
        if (p <= k) res++;
    }
    return res;
}

int main() {
    for (long long n = 1; n <= 1200; n += 7) {
        for (long long k = 1; k <= 100; k += 3) assert(count_product(n, k) == brute(n, k));
    }
    assert(count_product(99999, 1000000) == brute(99999, 1000000));
    long long n, k;
    cin >> n >> k;
    cout << count_product(n, k) << '\n';
}
