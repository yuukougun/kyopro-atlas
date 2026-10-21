// 数字だけからなる n 個の文字列をすべて好きな順に連結し、整数として読んだ値が最大になる連結を出力する。
// 「a + b > b + a なら a が先」で並べる。小さい n では全順列と比べる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    // --8<-- [start:core]
    // a + b と b + a は同じ長さなので、文字列の大小がそのまま整数の大小になる
    sort(s.begin(), s.end(), [](const string& a, const string& b) {
        return a + b > b + a;
    });
    string ans;
    for (const string& x : s) ans += x;
    // --8<-- [end:core]

    if (n <= 7) {  // 全順列と比べて確かめる（長さはすべて同じなので文字列で比べてよい）
        vector<string> p = s;
        sort(p.begin(), p.end());
        string best;
        do {
            string cur;
            for (const string& x : p) cur += x;
            best = max(best, cur);
        } while (next_permutation(p.begin(), p.end()));
        assert(ans == best);
    }
    cout << ans << '\n';
}
