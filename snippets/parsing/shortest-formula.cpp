// 1・+・*・括弧だけで N を表す最短の式を、文法（式・項・因子）に沿った DP で求める（入力：N）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// E[v]・T[v]・F[v]：値が v の最短の式・項・因子（空は「まだない」）
vector<string> shortest_formulas(int n) {
    vector<string> E(n + 1), T(n + 1), F(n + 1);
    auto upd = [](string& a, const string& b) {
        if (!b.empty() && (a.empty() || b.size() < a.size())) a = b;
    };
    for (int v = 1; v <= n; v++) {
        string ones = to_string(v);
        if (ranges::all_of(ones, [](char c) { return c == '1'; })) upd(F[v], ones);
        // 項 ＝ 因子 | 項 * 因子（v = a * b、a, b < v）
        upd(T[v], F[v]);
        for (int a = 2; a * a <= v; a++) {
            if (v % a != 0) continue;
            int b = v / a;                     // 掛け算は順を入れ替えてよいので両方を試す
            upd(T[v], T[a] + "*" + F[b]);
            upd(T[v], T[b] + "*" + F[a]);
        }
        // 式 ＝ 項 | 式 + 項（v = a + b、a, b < v）
        upd(E[v], T[v]);
        for (int a = 1; a < v; a++) {
            int b = v - a;
            if (E[v].empty() || E[a].size() + 1 + T[b].size() < E[v].size()) upd(E[v], E[a] + "+" + T[b]);
        }
        // 因子 ＝ ( 式 )。括弧で囲んだものは項にも使える
        upd(F[v], "(" + E[v] + ")");
        upd(T[v], F[v]);
    }
    return E;
}
// --8<-- [end:core]

// 照合用：文字列が文法どおりの式なら値を返す（大きい値は LIM で頭打ち）
const long long LIM = 100000;
struct Checker {
    const string& s;
    int i = 0;
    bool ok = true;
    long long expr() {
        long long v = term();
        while (ok && i < (int)s.size() && s[i] == '+') { i++; v = min(LIM, v + term()); }
        return v;
    }
    long long term() {
        long long v = factor();
        while (ok && i < (int)s.size() && s[i] == '*') { i++; v = min(LIM, v * factor()); }
        return v;
    }
    long long factor() {
        if (i < (int)s.size() && s[i] == '(') {
            i++;
            long long v = expr();
            if (i < (int)s.size() && s[i] == ')') i++; else ok = false;
            return v;
        }
        if (i >= (int)s.size() || s[i] != '1') { ok = false; return 0; }
        long long v = 0;
        while (i < (int)s.size() && s[i] == '1') { i++; v = min(LIM, v * 10 + 1); }
        return v;
    }
};
long long value_of(const string& s) {          // 式でなければ -1
    Checker c{s};
    long long v = c.expr();
    return (c.ok && c.i == (int)s.size()) ? v : -1;
}

int main() {
    const int MAXN = 2000;
    vector<string> E = shortest_formulas(MAXN);
    for (int v = 1; v <= MAXN; v++) assert(value_of(E[v]) == v);
    // 長さ 9 以下の文字列を全部試し、最短の長さが DP と一致するかを確かめる
    vector<int> best(MAXN + 1, INT_MAX);
    const string alpha = "1+*()";
    for (int len = 1; len <= 9; len++) {
        string s(len, '1');
        vector<int> d(len, 0);
        while (true) {
            for (int k = 0; k < len; k++) s[k] = alpha[d[k]];
            long long v = value_of(s);
            if (1 <= v && v <= MAXN) best[v] = min(best[v], len);
            int k = 0;
            while (k < len && d[k] == 4) d[k++] = 0;
            if (k == len) break;
            d[k]++;
        }
    }
    for (int v = 1; v <= MAXN; v++) {
        if (best[v] <= 9) assert((int)E[v].size() == best[v]);
        else assert((int)E[v].size() > 9);
    }
    int n;
    cin >> n;
    cout << E[n].size() << '\n';
}
