// 最小の周期と、S がその長さの繰り返しか
// 入力：S（空でない）。出力：最小の周期 p と、p が N を割り切るなら yes、割り切らないなら no
#include <bits/stdc++.h>
#include <atcoder/string>
using namespace std;

// --8<-- [start:core]
int min_period(const string& s) {
    int n = s.size();
    vector<int> z = atcoder::z_algorithm(s);
    for (int p = 1; p < n; p++) {
        if (z[p] == n - p) return p;  // S[p, N) が S の接頭辞と一致 ⇔ p は周期
    }
    return n;  // 長さ N 自身はいつでも周期
}
// --8<-- [end:core]

int main() {
    string s;
    cin >> s;
    int n = s.size();
    int p = min_period(s);
    // 定義どおりに確かめる
    for (int i = 0; i + p < n; i++) assert(s[i] == s[i + p]);
    for (int q = 1; q < p; q++) {
        bool ok = true;
        for (int i = 0; i + q < n; i++) if (s[i] != s[i + q]) ok = false;
        assert(!ok);
    }
    cout << p << ' ' << (n % p == 0 ? "yes" : "no") << '\n';
}
