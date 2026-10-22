#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// n の約数 d と φ(d) の組をすべて作る（素因数分解は試し割りで O(√n)）
vector<pair<long long, long long>> divisors_with_phi(long long n) {
    vector<pair<long long, int>> fac;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p != 0) continue;
        int e = 0;
        while (n % p == 0) { n /= p; e++; }
        fac.push_back({p, e});
    }
    if (n > 1) fac.push_back({n, 1});
    vector<pair<long long, long long>> res = {{1, 1}};  // (d, φ(d))
    for (auto [p, e] : fac) {
        int sz = res.size();
        for (int i = 0; i < sz; i++) {
            long long d = res[i].first, ph = res[i].second;
            long long pk = 1;
            for (int j = 1; j <= e; j++) {
                // φ(p^j) = p^(j-1) (p - 1)
                res.push_back({d * pk * p, ph * pk * (p - 1)});
                pk *= p;
            }
        }
    }
    return res;
}

// n 個の玉の輪を k 色で塗る方法（回転で一致するものは同じ）
// (1/n) Σ_{d|n} φ(d) k^(n/d)。n は法 998244353 の倍数でないこと
mint necklace(long long n, long long k) {
    mint sum = 0;
    for (auto [d, ph] : divisors_with_phi(n)) {
        sum += mint(ph) * mint(k).pow(n / d);
    }
    return sum / mint(n);
}
// --8<-- [end:core]

// --8<-- [start:bracelet]
// 裏返しも同じとみなす（2n 個の操作の平均）
mint bracelet(long long n, long long k) {
    mint rot = necklace(n, k) * mint(n);  // 回転 n 個の Fix の和
    mint ref;                             // 裏返し n 個の Fix の和
    if (n % 2 == 1) {
        ref = mint(n) * mint(k).pow((n + 1) / 2);  // 軸が玉 1 個を通る
    } else {
        ref = mint(n / 2) * mint(k).pow(n / 2 + 1)  // 軸が玉 2 個を通る
            + mint(n / 2) * mint(k).pow(n / 2);     // 軸が玉を通らない
    }
    return (rot + ref) / mint(2 * n);
}
// --8<-- [end:bracelet]

// --8<-- [start:by-period]
// 最短周期で分類する方法：f(d) = 最短周期がちょうど d の列の数
// 答え = Σ_{d|n} f(d) / d（周期 d の列は d 個ずつ同じ輪になる）
mint necklace_by_period(long long n, long long k) {
    vector<long long> ds;
    for (auto [d, ph] : divisors_with_phi(n)) ds.push_back(d);
    sort(ds.begin(), ds.end());
    map<long long, mint> f;
    mint ans = 0;
    for (long long d : ds) {
        mint v = mint(k).pow(d);  // 周期 d を持つ列の数
        for (long long e : ds) {
            if (e < d && d % e == 0) v -= f[e];
        }
        f[d] = v;
        ans += v / mint(d);
    }
    return ans;
}
// --8<-- [end:by-period]

// 全列挙：回転させた n 通りのうち辞書順で最小のものだけを数える
long long brute(int n, int k, bool flip) {
    long long total = 1;
    for (int i = 0; i < n; i++) total *= k;
    long long cnt = 0;
    for (long long code = 0; code < total; code++) {
        vector<int> a(n);
        long long c = code;
        for (int i = 0; i < n; i++) { a[i] = c % k; c /= k; }
        bool canonical = true;
        for (int r = 0; r < 2 && canonical; r++) {
            if (r == 1 && !flip) break;
            vector<int> b = a;
            if (r == 1) reverse(b.begin(), b.end());
            for (int s = 0; s < n; s++) {
                vector<int> t(n);
                for (int i = 0; i < n; i++) t[i] = b[(i + s) % n];
                if (t < a) { canonical = false; break; }
            }
        }
        if (canonical) cnt++;
    }
    return cnt;
}

int main() {
    for (int n = 1; n <= 8; n++) {
        for (int k = 1; k <= 3; k++) {
            assert(necklace(n, k).val() == brute(n, k, false));
            assert(necklace_by_period(n, k).val() == brute(n, k, false));
            assert(bracelet(n, k).val() == brute(n, k, true));
        }
    }
    long long n, k;
    cin >> n >> k;
    cout << necklace(n, k).val() << ' ' << bracelet(n, k).val() << '\n';
}
