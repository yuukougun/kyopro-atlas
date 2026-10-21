// ランレングス圧縮：文字列 s を（文字, 長さ）の組の列にする。空の行も受け付ける。
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);

    // --8<-- [start:core]
    vector<pair<char, int>> runs;
    int n = s.size();
    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;  // [i, j) が同じ文字の塊
        runs.push_back({s[i], j - i});
        i = j;  // 次の塊の先頭へ。最後の塊もループの中で追加される
    }
    // --8<-- [end:core]

    // 元に戻せることを確かめる
    string back;
    for (auto [c, len] : runs) back += string(len, c);
    assert(back == s);

    cout << runs.size() << '\n';
    for (auto [c, len] : runs) cout << c << ' ' << len << '\n';
}
