#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:bostan-mori]
// [x^n] P(x)/Q(x) を求める（deg P < deg Q、Q[0] != 0）
mint bostan_mori(vector<mint> p, vector<mint> q, long long n) {
    while (n > 0) {
        vector<mint> qm = q;  // Q(-x)：奇数次の係数の符号を反転する
        for (int i = 1; i < (int)qm.size(); i += 2) qm[i] = -qm[i];
        vector<mint> u = atcoder::convolution(p, qm);  // P(x)Q(-x)
        vector<mint> v = atcoder::convolution(q, qm);  // Q(x)Q(-x)：偶数次だけが残る
        vector<mint> np, nq;
        for (int i = n % 2; i < (int)u.size(); i += 2) np.push_back(u[i]);  // n の偶奇の側だけ残す
        for (int i = 0; i < (int)v.size(); i += 2) nq.push_back(v[i]);
        p = np;
        q = nq;
        n /= 2;
    }
    if (p.empty()) return 0;
    return p[0] / q[0];
}

// a_i = c_1 a_{i-1} + ... + c_d a_{i-d}（i >= d）の a_n。a は最初の d 項、c は c_1..c_d
mint kth_term(const vector<mint>& a, const vector<mint>& c, long long n) {
    int d = c.size();
    vector<mint> q(d + 1);
    q[0] = 1;
    for (int j = 1; j <= d; j++) q[j] = -c[j - 1];  // Q(x) = 1 - c_1 x - ... - c_d x^d
    vector<mint> p = atcoder::convolution(vector<mint>(a.begin(), a.begin() + d), q);
    p.resize(d);  // P(x) = (A(x) Q(x)) mod x^d
    return bostan_mori(p, q, n);
}
// --8<-- [end:bostan-mori]

// --8<-- [start:berlekamp-massey]
// 列 s を満たす最短の漸化式の係数 c_1..c_L を返す（O(N^2)。法は素数）
vector<mint> berlekamp_massey(const vector<mint>& s) {
    vector<mint> cur, prev;  // cur：今の漸化式、prev：最後に長さが伸びる直前の漸化式
    int shift = -1;          // prev が失敗した位置
    mint prev_delta = 1;
    for (int i = 0; i < (int)s.size(); i++) {
        mint delta = s[i];  // 今の漸化式で s[i] を予測したときのずれ
        for (int j = 0; j < (int)cur.size(); j++) delta -= cur[j] * s[i - 1 - j];
        if (delta == 0) continue;
        if (shift == -1) {  // 初めての 0 でない項：長さ i + 1 の漸化式にする
            cur.assign(i + 1, 0);
            shift = i;
            prev_delta = delta;
            continue;
        }
        // cur から (delta / prev_delta) × (prev で s[shift] を予測したときの式) を引いて、ずれを消す
        mint coef = delta / prev_delta;
        vector<mint> next = cur;
        int need = i - shift + (int)prev.size();
        if ((int)next.size() < need) next.resize(need, 0);
        next[i - shift - 1] += coef;
        for (int j = 0; j < (int)prev.size(); j++) next[i - shift + j] -= coef * prev[j];
        if (i - (int)cur.size() > shift - (int)prev.size()) {  // 長さが伸びるときだけ prev を更新する
            prev = cur;
            shift = i;
            prev_delta = delta;
        }
        cur = next;
    }
    return cur;
}
// --8<-- [end:berlekamp-massey]

// きたまさ法の素朴な形：x^n mod Φ(x) を O(d^2 log n) で求め、a_n = Σ r_i a_i
mint kitamasa(const vector<mint>& a, const vector<mint>& c, long long n) {
    int d = c.size();
    auto mulmod = [&](const vector<mint>& f, const vector<mint>& g) {
        vector<mint> h(2 * d - 1, 0);
        for (int i = 0; i < d; i++)
            for (int j = 0; j < d; j++) h[i + j] += f[i] * g[j];
        for (int k = 2 * d - 2; k >= d; k--) {  // x^k = Σ c_j x^{k-j} で次数を下げる
            for (int j = 1; j <= d; j++) h[k - j] += h[k] * c[j - 1];
            h[k] = 0;
        }
        h.resize(d);
        return h;
    };
    vector<mint> r(d, 0), x(d, 0);
    r[0] = 1;
    if (d == 1) x[0] = c[0];  // x mod (x - c_1) = c_1
    else x[1] = 1;
    while (n > 0) {
        if (n & 1) r = mulmod(r, x);
        x = mulmod(x, x);
        n >>= 1;
    }
    mint res = 0;
    for (int i = 0; i < d; i++) res += r[i] * a[i];
    return res;
}

int main() {
    int d;
    long long n;
    cin >> d >> n;
    vector<mint> a(d), c(d);
    for (int i = 0; i < d; i++) {
        int x;
        cin >> x;
        a[i] = x;
    }
    for (int i = 0; i < d; i++) {
        int x;
        cin >> x;
        c[i] = x;
    }
    // 最初の 2d 項を素朴に作る
    vector<mint> s = a;
    for (int i = d; i < 2 * d + 50; i++) {
        mint v = 0;
        for (int j = 1; j <= d; j++) v += c[j - 1] * s[i - j];
        s.push_back(v);
    }
    mint ans = kth_term(a, c, n);
    assert(ans == kitamasa(a, c, n));
    if (n < (long long)s.size()) assert(ans == s[n]);
    // 最初の 2d 項から漸化式を見つけ直し、同じ a_n が出ることを確かめる
    vector<mint> found = berlekamp_massey(vector<mint>(s.begin(), s.begin() + 2 * d));
    assert((int)found.size() <= d);
    for (int i = (int)found.size(); i < (int)s.size(); i++) {
        mint v = 0;
        for (int j = 0; j < (int)found.size(); j++) v += found[j] * s[i - 1 - j];
        assert(v == s[i]);
    }
    if (!found.empty()) {
        int l = found.size();
        assert(kth_term(vector<mint>(s.begin(), s.begin() + l), found, n) == ans);
    }
    cout << ans.val() << ' ' << found.size() << '\n';
}
