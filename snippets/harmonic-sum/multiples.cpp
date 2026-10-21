// 調和級数と倍数の列挙：値を添字にした配列で、各 d について d の倍数をたどる処理を 4 つ並べる
// 入力：n、続いて n 個の正の整数 a（1 <= a_i <= 10^6）
// 出力：1 行目 自分以外のどの要素でも割り切れない要素の個数
//       2 行目 すべての組 i < j についての ⌊max(a_i, a_j) / min(a_i, a_j)⌋ の和
//       3 行目 gcd(a_i, a_j) = 1 となる組 i < j の個数
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:mark]
// cnt[v]：値 v の出現回数（v = 0..m）。自分以外のどの要素でも割り切れない要素の個数を返す
long long count_not_divisible(const vector<long long>& cnt) {
    int m = (int)cnt.size() - 1;
    vector<bool> bad(m + 1, false);  // bad[v]：v はほかの要素で割り切れる
    for (int d = 1; d <= m; d++) {
        if (cnt[d] == 0) continue;
        if (cnt[d] >= 2) bad[d] = true;                  // 同じ値どうしで割り切れる
        for (int k = 2 * d; k <= m; k += d) bad[k] = true;  // 自分自身は除いて 2d から
    }
    long long res = 0;
    for (int v = 1; v <= m; v++) {
        if (cnt[v] > 0 && !bad[v]) res += cnt[v];  // ここに来るのは cnt[v] = 1 のときだけ
    }
    return res;
}
// --8<-- [end:mark]

// --8<-- [start:collect]
// c[d] = Σ_{d | k} cnt[k]：d の倍数である要素の個数。合計 m/1 + m/2 + … + m/m 回
vector<long long> count_multiples(const vector<long long>& cnt) {
    int m = (int)cnt.size() - 1;
    vector<long long> c(m + 1, 0);
    for (int d = 1; d <= m; d++) {
        for (int k = d; k <= m; k += d) c[d] += cnt[k];
    }
    return c;
}
// --8<-- [end:collect]

// --8<-- [start:back]
// gcd がちょうど 1 になる組の個数。f[d] = gcd がちょうど d の組の個数を、d の大きい順に
// f[d] = (d の倍数どうしの組の個数) − Σ_{k ≥ 2} f[kd] で決める
long long count_coprime_pairs(const vector<long long>& cnt) {
    int m = (int)cnt.size() - 1;
    vector<long long> c = count_multiples(cnt);
    vector<long long> f(m + 1, 0);
    for (int d = m; d >= 1; d--) {
        f[d] = c[d] * (c[d] - 1) / 2;
        for (int k = 2 * d; k <= m; k += d) f[d] -= f[k];  // f[2d], f[3d], … は決まっている
    }
    return m >= 1 ? f[1] : 0;
}
// --8<-- [end:back]

// --8<-- [start:quotient]
// すべての組 i < j の ⌊max / min⌋ の和。小さい方の値 x を固定し、
// 大きい方の値 y を [qx, (q+1)x) の範囲ごとに数える（この範囲では ⌊y/x⌋ = q）
long long sum_floor_ratio(const vector<long long>& cnt) {
    int m = (int)cnt.size() - 1;
    vector<long long> s(m + 1, 0);  // s[v]：値が v 以下の要素の個数
    for (int v = 1; v <= m; v++) s[v] = s[v - 1] + cnt[v];
    auto count_range = [&](long long lo, long long hi) -> long long {  // 値が閉区間 [lo, hi] の個数
        hi = min<long long>(hi, m);
        return lo > hi ? 0 : s[hi] - s[lo - 1];
    };
    long long res = 0;
    for (long long x = 1; x <= m; x++) {
        if (cnt[x] == 0) continue;
        res += cnt[x] * (cnt[x] - 1) / 2;  // 同じ値どうしの組は ⌊x/x⌋ = 1
        long long larger = 0;              // 値が x より大きい要素についての ⌊y/x⌋ の和
        for (long long q = 1; q * x <= m; q++) {
            long long lo = max(q * x, x + 1), hi = (q + 1) * x - 1;
            larger += q * count_range(lo, hi);
        }
        res += cnt[x] * larger;
    }
    return res;
}
// --8<-- [end:quotient]

// 愚直に O(n^2) で求める（main の確かめに使う。本文には載せない）
array<long long, 3> brute(const vector<int>& a) {
    int n = a.size();
    long long nd = 0, sum = 0, cop = 0;
    for (int i = 0; i < n; i++) {
        bool ok = true;
        for (int j = 0; j < n; j++) {
            if (i != j && a[i] % a[j] == 0) ok = false;
        }
        if (ok) nd++;
        for (int j = i + 1; j < n; j++) {
            sum += max(a[i], a[j]) / min(a[i], a[j]);
            if (gcd(a[i], a[j]) == 1) cop++;
        }
    }
    return {nd, sum, cop};
}

array<long long, 3> solve(const vector<int>& a) {
    int m = *max_element(a.begin(), a.end());  // ループの上限は値の最大
    vector<long long> cnt(m + 1, 0);
    for (int x : a) cnt[x]++;
    return {count_not_divisible(cnt), sum_floor_ratio(cnt), count_coprime_pairs(cnt)};
}

int main() {
    // 小さい乱択で愚直と一致することを確かめる
    mt19937 rng(12345);
    for (int t = 0; t < 2000; t++) {
        int n = rng() % 8 + 1, lim = rng() % 30 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % lim + 1;
        assert(solve(a) == brute(a));
    }

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    auto [nd, sum, cop] = solve(a);
    cout << nd << '\n' << sum << '\n' << cop << '\n';
}
