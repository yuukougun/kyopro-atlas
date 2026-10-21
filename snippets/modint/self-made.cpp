#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;

// --8<-- [start:core]
template <unsigned int M>  // 法をテンプレート引数で固定すると % が速くなる。M < 2^31 を仮定
struct ModInt {
    unsigned int v = 0;  // 不変条件：0 ≤ v < M
    ModInt() = default;
    ModInt(long long x) {
        x %= (long long)M;
        if (x < 0) x += M;  // 負の数を 0 以上に直す
        v = (unsigned int)x;
    }
    ModInt& operator+=(ModInt r) {
        v += r.v;  // v + r.v < 2M < 2^32 なのであふれない
        if (v >= M) v -= M;
        return *this;
    }
    ModInt& operator-=(ModInt r) {
        v += M - r.v;
        if (v >= M) v -= M;
        return *this;
    }
    ModInt& operator*=(ModInt r) {
        v = (unsigned int)((unsigned long long)v * r.v % M);  // 積は 64bit で取る
        return *this;
    }
    ModInt pow(long long n) const {  // n ≥ 0
        ModInt r = 1, x = *this;
        for (; n > 0; n >>= 1, x *= x)
            if (n & 1) r *= x;
        return r;
    }
    ModInt inv() const { return pow(M - 2); }  // M が素数で v ≠ 0 のときだけ正しい
    ModInt& operator/=(ModInt r) { return *this *= r.inv(); }
    friend ModInt operator+(ModInt a, ModInt b) { return a += b; }
    friend ModInt operator-(ModInt a, ModInt b) { return a -= b; }
    friend ModInt operator*(ModInt a, ModInt b) { return a *= b; }
    friend ModInt operator/(ModInt a, ModInt b) { return a /= b; }
    friend bool operator==(ModInt a, ModInt b) { return a.v == b.v; }
    friend ostream& operator<<(ostream& os, ModInt a) { return os << a.v; }
    friend istream& operator>>(istream& is, ModInt& a) {
        long long x;
        is >> x;
        a = ModInt(x);
        return is;
    }
};
// --8<-- [end:core]

using mint = ModInt<998244353>;
using amint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    mint s = 0, p = 1;
    amint as = 0, ap = 1;
    for (int i = 0; i < n; i++) {
        mint x;
        cin >> x;
        amint ax = x.v;
        s += x, p *= x, s -= p;
        as += ax, ap *= ax, as -= ap;
        assert(s.v == (unsigned int)as.val() && p.v == (unsigned int)ap.val());
        if (x.v != 0) {
            assert((x / x).v == 1);
            assert((x.inv()).v == (unsigned int)ax.inv().val());
        }
    }
    assert(mint(-1).v == 998244352u);
    cout << s << ' ' << p << '\n';
}
