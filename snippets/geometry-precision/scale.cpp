// 小数第 k 位までの数を文字列で読み、10^k 倍した整数に直す。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// s は "-12.5"・"3"・"0.05" のような 10 進の小数。小数点以下は k 桁以下とする。
long long to_scaled(const string& s, int k) {
    int i = 0;
    bool neg = false;
    if (s[i] == '-') neg = true, i++;
    long long v = 0;
    int frac = -1;  // 小数点の後に読んだ桁数（小数点がまだなら -1）
    for (; i < (int)s.size(); i++) {
        if (s[i] == '.') { frac = 0; continue; }
        v = v * 10 + (s[i] - '0');
        if (frac >= 0) frac++;
    }
    if (frac < 0) frac = 0;
    assert(frac <= k);
    for (int j = frac; j < k; j++) v *= 10;  // 足りない桁を 0 で埋める
    return neg ? -v : v;                     // 符号は最後に全体へ付ける
}
// --8<-- [end:core]

int main() {
    assert(to_scaled("2.51", 2) == 251);
    assert(to_scaled("-0.05", 2) == -5);
    assert(to_scaled("3", 4) == 30000);
    assert(to_scaled("-12.5", 4) == -125000);
    assert(to_scaled("100000.0000", 4) == 1000000000);
    int k;
    string s;
    cin >> k >> s;
    cout << to_scaled(s, k) << '\n';
}
