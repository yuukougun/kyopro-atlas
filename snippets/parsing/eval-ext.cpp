// 空白と単項マイナスを許す版（入力：1 行に 1 つの式）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 因子 ＝ - 因子 | 数 | ( 式 )。空白は記号を読む前に読み飛ばす
struct Parser {
    string s;
    int i = 0;
    char peek() {                              // 空白を飛ばし、次の文字を返す（末尾なら '\0'）
        while (i < (int)s.size() && s[i] == ' ') i++;
        return i < (int)s.size() ? s[i] : '\0';
    }
    long long expr() {
        long long v = term();
        while (peek() == '+' || peek() == '-') {
            char op = s[i++];
            long long w = term();
            v = (op == '+') ? v + w : v - w;
        }
        return v;
    }
    long long term() {
        long long v = factor();
        while (peek() == '*') {
            i++;
            v *= factor();
        }
        return v;
    }
    long long factor() {
        char c = peek();
        if (c == '-') { i++; return -factor(); }   // 単項マイナス：因子の頭でだけ読む
        if (c == '(') {
            i++;
            long long v = expr();
            assert(peek() == ')');
            i++;
            return v;
        }
        assert(isdigit(c));
        long long v = 0;
        while (i < (int)s.size() && isdigit(s[i])) v = v * 10 + (s[i++] - '0');
        return v;
    }
};
// --8<-- [end:core]

int main() {
    string line;
    while (getline(cin, line)) {
        Parser p{line};
        long long v = p.expr();
        assert(p.peek() == '\0');              // 末尾の空白のほかに読み残しがない
        cout << v << '\n';
    }
}
