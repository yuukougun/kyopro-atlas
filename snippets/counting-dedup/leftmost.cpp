#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;

// --8<-- [start:core]
// 文字の種類が sigma 個のとき、長さ n の決まった文字列 S を部分列として含む
// 長さ n + k の文字列の数（S の中身によらない。n >= 1）
mint count_containing(int n, int k, int sigma) {
    // 階乗・逆階乗と、sigma - 1 と sigma の累乗を前計算して O(n + k)
    vector<mint> fact(n + k + 1, 1), ifact(n + k + 1), p1(k + 1, 1), p2(k + 1, 1);
    for (int i = 1; i <= n + k; i++) fact[i] = fact[i - 1] * i;
    ifact[n + k] = fact[n + k].inv();
    for (int i = n + k; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
    for (int i = 1; i <= k; i++) p1[i] = p1[i - 1] * (sigma - 1), p2[i] = p2[i - 1] * sigma;
    auto binom = [&](int a, int b) { return fact[a] * ifact[b] * ifact[a - b]; };
    mint ans = 0;
    // j ＝ 最も左の埋め込みで S の最後の文字を置いた位置より後ろの文字数
    for (int j = 0; j <= k; j++) {
        // 前の n + k - j - 1 文字に S の残り n - 1 文字の位置を選び、
        // 埋め込みに使わない k - j 文字は「次に合わせたい文字」以外の sigma - 1 通り
        ans += binom(n + k - j - 1, n - 1) * p1[k - j] * p2[j];
    }
    return ans;
}
// --8<-- [end:core]

// 素朴な数え方：sigma 種の文字の長さ n + k の文字列を全部作り、S を含むか貪欲に判定する
long long brute(const string& s, int k, int sigma) {
    int len = (int)s.size() + k;
    long long total = 1, cnt = 0;
    for (int i = 0; i < len; i++) total *= sigma;
    for (long long code = 0; code < total; code++) {
        long long c = code;
        size_t p = 0;
        for (int i = 0; i < len; i++) {
            char ch = (char)('a' + c % sigma);
            c /= sigma;
            if (p < s.size() && s[p] == ch) p++;
        }
        if (p == s.size()) cnt++;
    }
    return cnt;
}

int main() {
    // 小さい場合に全列挙と一致し、S の中身によらないことを確かめる
    for (string s : {"a", "ab", "aa", "aba", "abc", "cab"}) {
        for (int k = 0; k <= 3; k++) {
            int sigma = 3;
            assert(count_containing((int)s.size(), k, sigma).val() == brute(s, k, sigma));
        }
    }
    int n, k;
    cin >> n >> k;
    cout << count_containing(n, k, 26).val() << '\n';
}
