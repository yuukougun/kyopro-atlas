#include <bits/stdc++.h>
using namespace std;

string make(int n) { return string(n, 'a') + "xyz"; }

// --8<-- [start:bad]
// 呼ぶと壊れる：make(n) が返した一時的な string は文の終わりで消え、sv は消えた文字列を指す
void bad(int n) {
    string_view sv = make(n);
    cout << sv << '\n';  // AddressSanitizer で止まる（警告は出ない）
}
// --8<-- [end:bad]

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    string s = make(n);  // 文字列そのものは string の変数に持つ
    string_view sv = s;  // string_view は、s が生きている間だけ使う
    cout << sv.substr(n) << '\n';
    // --8<-- [end:core]
    (void)&bad;
}
