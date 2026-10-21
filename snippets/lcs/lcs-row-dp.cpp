// DP の DP：英小文字からなる長さ m の文字列 T のうち、短い文字列 s との LCS の長さが
// ちょうど k になるものの個数を、k = 0, …, n について 998244353 で割った余りで求める。
// 内側の LCS の表の 1 行（s の各接頭辞との LCS の長さ）を、隣との差の bit 列にして外側の状態にする。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    string s;
    int m;
    cin >> s >> m;
    int n = s.size();
    assert(1 <= n && n <= 10);

    // --8<-- [start:core]
    // 状態 mask の bit j は row[j + 1] - row[j]（0 か 1）。row[0] = 0 なので mask から row が決まる
    auto decode = [&](int mask) {
        vector<int> row(n + 1, 0);
        for (int j = 0; j < n; j++) row[j + 1] = row[j] + (mask >> j & 1);
        return row;
    };
    // 前計算：行 mask の T に文字 c を足したときの新しい行（内側の LCS の遷移を 1 行分行う）
    vector<array<int, 26>> nxt(1 << n);
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> row = decode(mask);
        for (int c = 0; c < 26; c++) {
            vector<int> nr(n + 1, 0);
            for (int j = 1; j <= n; j++) {
                if (s[j - 1] - 'a' == c) nr[j] = row[j - 1] + 1;
                else nr[j] = max(row[j], nr[j - 1]);
            }
            int nmask = 0;
            for (int j = 0; j < n; j++) nmask |= (nr[j + 1] - nr[j]) << j;
            nxt[mask][c] = nmask;
        }
    }
    // 外側の DP：f[mask] = これまでに作った T のうち、内側の行が mask になるものの数
    vector<mint> f(1 << n, 0);
    f[0] = 1;  // 空の T の行はすべて 0
    for (int step = 0; step < m; step++) {
        vector<mint> g(1 << n, 0);
        for (int mask = 0; mask < (1 << n); mask++) {
            if (f[mask] == 0) continue;
            for (int c = 0; c < 26; c++) g[nxt[mask][c]] += f[mask];
        }
        f = move(g);
    }
    // 答え：行の右端 row[n] = popcount(mask) が s 全体との LCS の長さ
    vector<mint> ans(n + 1, 0);
    for (int mask = 0; mask < (1 << n); mask++) ans[popcount((unsigned)mask)] += f[mask];
    // --8<-- [end:core]

    for (int k = 0; k <= n; k++) cout << ans[k].val() << (k == n ? '\n' : ' ');
}
