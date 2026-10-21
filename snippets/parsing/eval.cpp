// +・-・*・括弧を含む式の値を、再帰下降構文解析で求める（入力：式の個数 q と、空白を含まない式 q 個）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 式 ＝ 項 { (+ | -) 項 }、項 ＝ 因子 { * 因子 }、因子 ＝ 数 | ( 式 )
// i は次に読む文字の位置。どの関数も参照で受け取り、読んだぶんだけ進める
long long expr(const string& s, int& i);

long long factor(const string& s, int& i) {
    if (i < (int)s.size() && s[i] == '(') {
        i++;                                   // '(' を読む
        long long v = expr(s, i);
        assert(i < (int)s.size() && s[i] == ')');
        i++;                                   // ')' を読む
        return v;
    }
    assert(i < (int)s.size() && isdigit(s[i]));
    long long v = 0;
    while (i < (int)s.size() && isdigit(s[i])) v = v * 10 + (s[i++] - '0');
    return v;
}

long long term(const string& s, int& i) {
    long long v = factor(s, i);
    while (i < (int)s.size() && s[i] == '*') {
        i++;
        v *= factor(s, i);
    }
    return v;
}

long long expr(const string& s, int& i) {
    long long v = term(s, i);
    while (i < (int)s.size() && (s[i] == '+' || s[i] == '-')) {
        char op = s[i++];
        long long w = term(s, i);
        v = (op == '+') ? v + w : v - w;       // ループで左から順に結ぶ（左結合）
    }
    return v;
}
// --8<-- [end:core]

int main() {
    int q;
    cin >> q;
    for (int k = 0; k < q; k++) {
        string s;
        cin >> s;
        int i = 0;
        long long v = expr(s, i);
        assert(i == (int)s.size());            // 式の後ろに読み残しがない
        cout << v << '\n';
    }
}
