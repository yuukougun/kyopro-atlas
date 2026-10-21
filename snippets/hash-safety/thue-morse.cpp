// Thue-Morse 列 t_k と、その a・b を入れ替えた列を、多項式ハッシュで比べる。
// 入力：k と T。長さ 2^k の 2 つの列を、奇数の基数 T 個（mod 2^64）と乱択した基数 T 個（mod 2^61 - 1）で比べ、
// 衝突した基数の個数を出力する。種を固定しているので、出力は毎回同じになる。
#include <bits/stdc++.h>
using namespace std;

const unsigned long long MOD61 = (1ULL << 61) - 1;

unsigned long long mul61(unsigned long long a, unsigned long long b) {
    unsigned __int128 t = (unsigned __int128)a * b;
    unsigned long long r = (unsigned long long)(t >> 61) + (unsigned long long)(t & MOD61);
    if (r >= MOD61) r -= MOD61;
    return r;
}

// --8<-- [start:core]
// t_0 = "a"、t_{k+1} = t_k + (t_k の a と b を入れ替えたもの)
string thue_morse(int k) {
    string t = "a";
    for (int i = 0; i < k; i++) {
        string u = t;
        for (char& c : u) c = (c == 'a' ? 'b' : 'a');
        t += u;
    }
    return t;
}

// mod 2^64 の多項式ハッシュ：unsigned long long のあふれに任せる（使ってはいけない例）
unsigned long long hash64(const string& s, unsigned long long b) {
    unsigned long long h = 0;
    for (char c : s) h = h * b + (c - 'a' + 1);  // 文字は 1 以上
    return h;
}
// --8<-- [end:core]

unsigned long long hash61(const string& s, unsigned long long b) {
    unsigned long long h = 0;
    for (char c : s) {
        h = mul61(h, b) + (c - 'a' + 1);
        if (h >= MOD61) h -= MOD61;
    }
    return h;
}

int main() {
    int k, cnt;
    cin >> k >> cnt;
    assert(0 <= k && k <= 20 && cnt >= 1);
    string s = thue_morse(k), t = s;
    for (char& c : t) c = (c == 'a' ? 'b' : 'a');
    assert((int)s.size() == (1 << k) && s != t);
    mt19937_64 rng(12345);  // 実験を再現するために種を固定する（本番では固定しない）
    int bad64 = 0, bad61 = 0;
    for (int i = 0; i < cnt; i++) {
        unsigned long long b = rng() | 1;  // 奇数の基数
        if (hash64(s, b) == hash64(t, b)) bad64++;
        unsigned long long b61 = 2 + rng() % (MOD61 - 3);  // [2, MOD61 - 2]
        if (hash61(s, b61) == hash61(t, b61)) bad61++;
    }
    cout << bad64 << ' ' << bad61 << '\n';
}
