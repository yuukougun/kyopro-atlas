#include <bits/stdc++.h>
#include <atcoder/convolution>
using namespace std;

// 入力：英小文字と ?（どの文字とも一致する）からなる文字列 S, T（|T| <= |S|）。
// 出力：各位置 p（p = 0, ..., |S|-|T|）について、T を S の位置 p に重ねて一致すれば 1、しなければ 0。

// --8<-- [start:core]
string wildcard_match(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    // ? を 0、a〜z を 1〜26 にした値の e 乗
    auto val = [](char ch, int e) -> long long {
        long long x = (ch == '?' ? 0 : ch - 'a' + 1), r = 1;
        for (int k = 0; k < e; k++) r *= x;
        return r;
    };
    // x^e の列を作る（S はそのまま、T は反転）
    auto power_s = [&](int e) {
        vector<long long> f(n);
        for (int i = 0; i < n; i++) f[i] = val(s[i], e);
        return f;
    };
    auto power_t = [&](int e) {
        vector<long long> g(m);
        for (int j = 0; j < m; j++) g[m - 1 - j] = val(t[j], e);
        return g;
    };
    // Σ_j x y (x - y)^2 = Σ x^3 y - 2 x^2 y^2 + x y^3（x = S[p+j] の値、y = T[j] の値）
    auto c31 = atcoder::convolution_ll(power_s(3), power_t(1));
    auto c22 = atcoder::convolution_ll(power_s(2), power_t(2));
    auto c13 = atcoder::convolution_ll(power_s(1), power_t(3));
    string res(n - m + 1, '0');
    for (int p = 0; p + m <= n; p++) {
        int k = p + m - 1;
        // 各項は 0 以上で、0 になるのは「どちらかが ?」か「同じ文字」のときだけ
        if (c31[k] - 2 * c22[k] + c13[k] == 0) res[p] = '1';
    }
    return res;
}
// --8<-- [end:core]

int main() {
    string s, t;
    cin >> s >> t;
    string res = wildcard_match(s, t);
    // 全探索と一致することを確かめる
    for (int p = 0; p + (int)t.size() <= (int)s.size(); p++) {
        bool ok = true;
        for (int j = 0; j < (int)t.size(); j++)
            if (s[p + j] != '?' && t[j] != '?' && s[p + j] != t[j]) ok = false;
        assert((res[p] == '1') == ok);
    }
    cout << res << '\n';
}
