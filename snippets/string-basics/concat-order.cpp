// 文字列 s[0], …, s[n-1] を好きな順に並べて連結し、結果を辞書順で最小にする。
// 長さが違うことがあるので、2 つの順序を a + b と b + a で比べてソートする。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    // --8<-- [start:core]
    // a を b より前に置くのは、a + b が b + a より小さいとき（比較 1 回は O(|a| + |b|)）
    sort(s.begin(), s.end(), [](const string& a, const string& b) {
        return a + b < b + a;
    });
    string ans;
    for (const string& t : s) ans += t;  // += は足した長さぶんだけ。ans = ans + t は毎回全体をコピーする
    // --8<-- [end:core]

    // 小さいときは全順列と照らし合わせる
    if (n <= 7) {
        vector<string> p = s;
        sort(p.begin(), p.end());
        string best;
        bool first = true;
        do {
            string cur;
            for (const string& t : p) cur += t;
            if (first || cur < best) best = cur;
            first = false;
        } while (next_permutation(p.begin(), p.end()));
        assert(best == ans);
    }
    cout << ans << '\n';
}
