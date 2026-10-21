// セグメント木に（ハッシュ, B^長さ）の組を載せ、1 文字の更新と「S[l, r) は回文か」に答える。
// 入力：N Q、S、続く Q 行は「1 x c」（S[x] を c にする）か「2 l r」（S[l, r) は回文か）。0-indexed・半開区間。
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

const unsigned long long MOD = (1ULL << 61) - 1;

unsigned long long mul(unsigned long long a, unsigned long long b) {
    unsigned __int128 t = (unsigned __int128)a * b;
    unsigned long long r = (unsigned long long)(t >> 61) + (unsigned long long)(t & MOD);
    if (r >= MOD) r -= MOD;
    return r;
}

unsigned long long random_base() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<unsigned long long>(2, MOD - 2)(rng);
}
const unsigned long long B = random_base();

// --8<-- [start:core]
struct S {
    unsigned long long h, q;  // 区間のハッシュと B^(区間の長さ)
};
// 左のハッシュを右の長さぶんずらして足す：(h1, q1)·(h2, q2) = (h1·q2 + h2, q1·q2)
S op(S a, S b) {
    unsigned long long h = mul(a.h, b.q) + b.h;
    if (h >= MOD) h -= MOD;
    return {h, mul(a.q, b.q)};
}
S e() { return {0, 1}; }  // 空の文字列：ハッシュ 0、長さ 0（B^0 = 1）
S leaf(char c) { return {(unsigned char)c, B}; }  // 1 文字：ハッシュは文字コード、長さ 1
// --8<-- [end:core]

int main() {
    int n, q;
    string s;
    cin >> n >> q >> s;
    assert((int)s.size() == n);
    // --8<-- [start:usage]
    vector<S> vf(n), vr(n);
    for (int i = 0; i < n; i++) {
        vf[i] = leaf(s[i]);
        vr[n - 1 - i] = leaf(s[i]);  // 後ろ向きのセグ木は添字を n - 1 - i に置く
    }
    atcoder::segtree<S, op, e> fw(vf), bw(vr);
    auto update = [&](int x, char c) {
        fw.set(x, leaf(c));
        bw.set(n - 1 - x, leaf(c));
    };
    // S[l, r) を反転すると、後ろ向きの [n - r, n - l) になる
    auto is_palindrome = [&](int l, int r) { return fw.prod(l, r).h == bw.prod(n - r, n - l).h; };
    // --8<-- [end:usage]
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            char c;
            cin >> x >> c;
            assert(0 <= x && x < n);
            update(x, c);
            s[x] = c;
        } else {
            int l, r;
            cin >> l >> r;
            assert(0 <= l && l <= r && r <= n);
            bool ans = is_palindrome(l, r);
            string u = s.substr(l, r - l);
            assert(ans == equal(u.begin(), u.end(), u.rbegin()));  // 素朴な判定と照らす
            cout << (ans ? "Yes" : "No") << '\n';
        }
    }
}
