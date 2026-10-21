// 再帰を使わずに、値のスタックと演算子のスタックで式を評価する（入力：空白を含まない式 1 つ）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long eval_with_stacks(const string& s) {
    vector<long long> val;                     // 値のスタック
    vector<char> ops;                          // 演算子と '(' のスタック
    auto prec = [](char c) { return c == '*' ? 2 : 1; };
    auto reduce = [&]() {                      // 一番上の演算子を、上の 2 つの値に施す
        char op = ops.back(); ops.pop_back();
        long long b = val.back(); val.pop_back();
        long long a = val.back(); val.pop_back();
        val.push_back(op == '+' ? a + b : op == '-' ? a - b : a * b);
    };
    for (int i = 0; i < (int)s.size();) {
        char c = s[i];
        if (isdigit(c)) {
            long long v = 0;
            while (i < (int)s.size() && isdigit(s[i])) v = v * 10 + (s[i++] - '0');
            val.push_back(v);
            continue;
        }
        if (c == '(') {
            ops.push_back(c);
        } else if (c == ')') {
            while (ops.back() != '(') reduce();
            ops.pop_back();                    // '(' を捨てる
        } else {
            // 優先順位が同じか高い演算子を先に施す（同じものも先に施すので左結合）
            while (!ops.empty() && ops.back() != '(' && prec(ops.back()) >= prec(c)) reduce();
            ops.push_back(c);
        }
        i++;
    }
    while (!ops.empty()) reduce();
    return val.back();
}
// --8<-- [end:core]

// 照合用の再帰下降構文解析（本文の eval.cpp と同じ文法）
long long expr_r(const string& s, int& i);
long long factor_r(const string& s, int& i) {
    if (s[i] == '(') { i++; long long v = expr_r(s, i); i++; return v; }
    long long v = 0;
    while (i < (int)s.size() && isdigit(s[i])) v = v * 10 + (s[i++] - '0');
    return v;
}
long long term_r(const string& s, int& i) {
    long long v = factor_r(s, i);
    while (i < (int)s.size() && s[i] == '*') { i++; v *= factor_r(s, i); }
    return v;
}
long long expr_r(const string& s, int& i) {
    long long v = term_r(s, i);
    while (i < (int)s.size() && (s[i] == '+' || s[i] == '-')) {
        char op = s[i++];
        long long w = term_r(s, i);
        v = (op == '+') ? v + w : v - w;
    }
    return v;
}

mt19937 rng(12345);
string gen(int depth) {                        // 小さな式をランダムに作る
    int k = rng() % 3 + 1;
    string res;
    for (int t = 0; t < k; t++) {
        if (t > 0) res += "+-*"[rng() % 3];
        if (depth > 0 && rng() % 3 == 0) res += "(" + gen(depth - 1) + ")";
        else res += to_string(rng() % 20);
    }
    return res;
}

int main() {
    for (int t = 0; t < 20000; t++) {          // 再帰下降と同じ値になるかを確かめる
        string s = gen(4);
        int i = 0;
        assert(eval_with_stacks(s) == expr_r(s, i));
    }
    string deep = string(100000, '(') + "1" + string(100000, ')');
    assert(eval_with_stacks(deep) == 1);        // 入れ子が 10^5 段でも再帰しない
    string s;
    cin >> s;
    cout << eval_with_stacks(s) << '\n';
}
