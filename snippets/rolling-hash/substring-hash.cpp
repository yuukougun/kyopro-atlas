// ローリングハッシュ（mod 2^61 - 1、基数は実行時に乱択）で、部分文字列の一致と回文を判定する。
// 入力：S、Q、続く Q 行は「1 a b c d」（S[a, b) と S[c, d) は等しいか）か「2 l r」（S[l, r) は回文か）。0-indexed・半開区間。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const unsigned long long MOD = (1ULL << 61) - 1;  // 素数

// a·b mod (2^61 - 1)。2^61 ≡ 1 なので、上位と下位の 61 ビットを足せば剰余になる
unsigned long long mul(unsigned long long a, unsigned long long b) {
    unsigned __int128 t = (unsigned __int128)a * b;
    unsigned long long r = (unsigned long long)(t >> 61) + (unsigned long long)(t & MOD);
    if (r >= MOD) r -= MOD;
    return r;
}

// 基数は実行時に [2, MOD - 2] から乱択し、すべてのハッシュで共有する（前向きと後ろ向きを比べるため）
unsigned long long random_base() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<unsigned long long>(2, MOD - 2)(rng);
}
const unsigned long long B = random_base();

struct RollingHash {
    vector<unsigned long long> h, pw;  // h[i] = S[0, i) のハッシュ、pw[i] = B^i
    RollingHash(const string& s) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        for (int i = 0; i < (int)s.size(); i++) {
            h[i + 1] = mul(h[i], B) + (unsigned char)s[i];  // 文字コード（'a' = 97）は 1 以上
            if (h[i + 1] >= MOD) h[i + 1] -= MOD;
            pw[i + 1] = mul(pw[i], B);
        }
    }
    // S[l, r) のハッシュ = h[r] - h[l]·B^(r-l)。MOD を足してから引き、負にしない
    unsigned long long get(int l, int r) const {
        unsigned long long x = h[r] + MOD - mul(h[l], pw[r - l]);
        if (x >= MOD) x -= MOD;
        return x;
    }
};
// --8<-- [end:core]

int main() {
    string s;
    int q;
    cin >> s >> q;
    int n = s.size();
    // --8<-- [start:usage]
    RollingHash fw(s);
    string t(s.rbegin(), s.rend());  // 反転した文字列：S[l, r) は T[n - r, n - l) に対応する
    RollingHash bw(t);
    auto same = [&](int a, int b, int c, int d) {  // 長さが違えば比べるまでもなく別の文字列
        return b - a == d - c && fw.get(a, b) == fw.get(c, d);
    };
    auto is_palindrome = [&](int l, int r) { return fw.get(l, r) == bw.get(n - r, n - l); };
    // --8<-- [end:usage]
    while (q--) {
        int type;
        cin >> type;
        bool ans;
        if (type == 1) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            assert(0 <= a && a <= b && b <= n && 0 <= c && c <= d && d <= n);
            ans = same(a, b, c, d);
            assert(ans == (s.substr(a, b - a) == s.substr(c, d - c)));  // 素朴な比較と照らす
        } else {
            int l, r;
            cin >> l >> r;
            assert(0 <= l && l <= r && r <= n);
            ans = is_palindrome(l, r);
            string u = s.substr(l, r - l);
            assert(ans == equal(u.begin(), u.end(), u.rbegin()));
        }
        cout << (ans ? "Yes" : "No") << '\n';
    }
}
