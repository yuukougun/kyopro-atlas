#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    // 先頭に 'a' + i % 26 を足していった文字列を作る
    string s;
    for (int i = 0; i < n; i++) {
        s += char('a' + i % 26);     // 後ろに足す（ならし O(1)）。s = c + s は毎回 O(|s|)
    }
    reverse(s.begin(), s.end());     // 最後に 1 回だけ反転する。O(|s|)
    // --8<-- [end:core]
    cout << s << '\n';
}
