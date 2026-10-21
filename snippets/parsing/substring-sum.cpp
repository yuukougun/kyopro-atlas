// 数字と + と * からなる式 S について、式として正しい部分文字列すべての値の和を mod 998244353 で求める（入力：S）
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// 終わりが今の位置の部分文字列の値を「済んだ項の和 A ＋ 今の項の済んだ因子の積 P × 今の数 x」と書き、
// 始まりごとの A・P・P×x を足し合わせたものを持つ（cnt は始まりの数）
mint substring_sum(const string& s) {
    mint cnt = 0, sumA = 0, sumP = 0, sumPx = 0, ans = 0;
    char prev = '+';
    for (char c : s) {
        if (!isdigit(c) && !isdigit(prev)) {   // 演算子が 2 つ並ぶ：前の始まりはどれも式にならない
            cnt = sumA = sumP = sumPx = 0;
        }
        prev = c;
        if (isdigit(c)) {
            int d = c - '0';
            sumPx = sumPx * 10 + sumP * d;     // 今の数 x を 10x + d にする
            cnt += 1, sumP += 1, sumPx += d;   // ここから始まる部分文字列（A = 0, P = 1, x = d）
            ans += sumA + sumPx;               // ここで終わる部分文字列の値の和
        } else if (c == '*') {
            sumP = sumPx, sumPx = 0;           // P ← P × x、x ← 0
        } else {                               // '+'
            sumA += sumPx, sumP = cnt, sumPx = 0;  // A ← A + P × x、P ← 1、x ← 0
        }
    }
    return ans;
}
// --8<-- [end:core]

// 照合用：部分文字列を 1 つずつ再帰下降構文解析で評価して足す
mint eval_mod(const string& s, int& i);
mint factor_mod(const string& s, int& i) {
    mint v = 0;
    while (i < (int)s.size() && isdigit(s[i])) v = v * 10 + (s[i++] - '0');
    return v;
}
mint term_mod(const string& s, int& i) {
    mint v = factor_mod(s, i);
    while (i < (int)s.size() && s[i] == '*') { i++; v *= factor_mod(s, i); }
    return v;
}
mint eval_mod(const string& s, int& i) {
    mint v = term_mod(s, i);
    while (i < (int)s.size() && s[i] == '+') { i++; v += term_mod(s, i); }
    return v;
}
mint brute(const string& s) {
    mint res = 0;
    int n = s.size();
    for (int l = 0; l < n; l++) {
        for (int r = l + 1; r <= n; r++) {
            // 両端が数字で、演算子が 2 つ並ばない部分文字列が式として正しい
            if (!isdigit(s[l]) || !isdigit(s[r - 1])) continue;
            string t = s.substr(l, r - l);
            bool ok = true;
            for (int j = 0; j + 1 < (int)t.size(); j++) {
                if (!isdigit(t[j]) && !isdigit(t[j + 1])) ok = false;
            }
            if (!ok) continue;
            int i = 0;
            res += eval_mod(t, i);
        }
    }
    return res;
}

int main() {
    mt19937 rng(1);
    for (int t = 0; t < 3000; t++) {
        int k = rng() % 6 + 1;
        string s;
        for (int j = 0; j < k; j++) {
            if (j > 0) s += "+*"[rng() % 2];
            if (j > 0 && rng() % 4 == 0) s += "+*"[rng() % 2];  // 演算子が並ぶ入力も試す
            int len = rng() % 3 + 1;
            for (int q = 0; q < len; q++) s += char('1' + rng() % 9);
        }
        assert(substring_sum(s) == brute(s));
    }
    string s;
    cin >> s;
    cout << substring_sum(s).val() << '\n';
}
