#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    // --8<-- [start:core]
    string line(5, '-');                          // "-----"（個数が先、文字が後）
    string r = s;
    reverse(r.begin(), r.end());
    bool palindrome = (r == s);                   // 回文か。== は O(|s|)
    cout << line << ' ' << palindrome << '\n';
    cout << (string("ab") < string("abc")) << ' ';   // 1：接頭辞の方が小さい
    cout << (string("b") < string("abc")) << ' ';    // 0：最初の文字で決まる
    cout << (string("10") < string("9")) << '\n';    // 1：数の大小ではない
    // --8<-- [end:core]
}
