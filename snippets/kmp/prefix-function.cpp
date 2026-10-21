// 失敗関数 π と、最小の周期・繰り返しで書けるか
// 入力：S（空でない）。出力：1 行目に π、2 行目に最小の周期 p と、p が N を割り切るなら yes、割り切らないなら no
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// pi[i] = S[0, i+1) の最長の真の border の長さ（pi[0] = 0）
vector<int> prefix_function(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];                       // 伸ばしたい border の長さ
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];  // 伸ばせなければ次に長い border へ
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
// --8<-- [end:core]

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> pi = prefix_function(s);
    // 定義どおりに確かめる（小さい入力だけ）
    if (n <= 300) {
        for (int i = 0; i < n; i++) {
            int best = 0;
            for (int k = 1; k <= i; k++) {
                if (s.compare(0, k, s, i + 1 - k, k) == 0) best = k;
            }
            assert(pi[i] == best);
        }
    }
    for (int i = 0; i < n; i++) cout << pi[i] << (i + 1 < n ? ' ' : '\n');
    // --8<-- [start:period]
    int p = n - pi[n - 1];                       // 最小の周期
    bool repeat = (n % p == 0);                  // 長さ p の文字列の N/p 回の繰り返しか
    // --8<-- [end:period]
    cout << p << ' ' << (repeat ? "yes" : "no") << '\n';
}
