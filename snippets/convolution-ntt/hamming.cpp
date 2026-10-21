#include <bits/stdc++.h>
#include <atcoder/convolution>
using namespace std;

// 入力：0 と 1 からなる文字列 S, T（|T| <= |S|）。
// 出力：T を S の位置 p（p = 0, ..., |S|-|T|）に重ねたときの、食い違う文字の数。

// --8<-- [start:core]
vector<int> mismatches(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    vector<int> match(n - m + 1, 0);
    for (char ch : {'0', '1'}) {  // 文字ごとに「両方 ch の位置の数」を数える
        vector<int> f(n), g(m);
        for (int i = 0; i < n; i++) f[i] = (s[i] == ch);
        for (int j = 0; j < m; j++) g[m - 1 - j] = (t[j] == ch);  // T を反転
        // c[p + m - 1] = Σ_j [S[p + j] = ch][T[j] = ch]。値は m 以下なので mod で足りる
        auto c = atcoder::convolution(f, g);
        for (int p = 0; p + m <= n; p++) match[p] += c[p + m - 1];
    }
    vector<int> res(n - m + 1);
    for (int p = 0; p + m <= n; p++) res[p] = m - match[p];
    return res;
}
// --8<-- [end:core]

int main() {
    string s, t;
    cin >> s >> t;
    auto res = mismatches(s, t);
    // 全探索と一致することを確かめる
    for (int p = 0; p + (int)t.size() <= (int)s.size(); p++) {
        int cnt = 0;
        for (int j = 0; j < (int)t.size(); j++) cnt += (s[p + j] != t[j]);
        assert(res[p] == cnt);
    }
    for (int p = 0; p < (int)res.size(); p++) cout << res[p] << (p + 1 == (int)res.size() ? '\n' : ' ');
}
