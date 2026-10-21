#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:print]
// __int128 を 10 進の文字列にする（cout << x はコンパイルエラーになるため）
string to_str(__int128 x) {
    if (x == 0) return "0";
    bool neg = x < 0;
    string s;
    while (x != 0) {
        int d = (int)(x % 10);  // x < 0 なら d は 0 以下
        s += char('0' + (neg ? -d : d));
        x /= 10;
    }
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    return s;
}
// --8<-- [end:print]

// --8<-- [start:read]
// 文字列で読んだ 10 進の整数を __int128 にする
__int128 parse(const string& s) {
    __int128 x = 0;
    size_t i = (s[0] == '-') ? 1 : 0;
    for (; i < s.size(); i++) x = x * 10 + (s[i] - '0');
    return s[0] == '-' ? -x : x;
}
// --8<-- [end:read]

int main() {
    long long a, b;
    string t;
    cin >> a >> b >> t;
    // --8<-- [start:core]
    __int128 p = (__int128)a * b;          // a, b ≤ 10^18 でも正確（10^36 < 1.7×10^38）
    bool ok = p <= 1'000'000'000'000'000'000LL;  // 積が 10^18 以下か
    __int128 big = (__int128)1 << 100;     // リテラルはないので、広げてからシフトする
    // --8<-- [end:core]
    cout << to_str(p) << ' ' << ok << ' ' << to_str(big) << '\n';
    cout << to_str(parse(t) + 1) << '\n';
}
