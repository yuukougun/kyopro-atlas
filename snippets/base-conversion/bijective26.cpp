// 1 始まりの 26 進：1 → a, …, 26 → z, 27 → aa, …, 702 → zz, 703 → aaa, …
// 入力：N（1 以上）。出力：N 番目の名前。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 各桁は 1〜26（a〜z）で、0 に当たる文字がない。1 を引いてから割ると桁が 0〜25 にそろう
string to_name(long long n) {
    string s;
    while (n > 0) {
        n--;                      // 桁を 1〜26 から 0〜25 に直す
        s += char('a' + n % 26);  // いちばん下の桁
        n /= 26;
    }
    reverse(s.begin(), s.end());
    return s;
}

// 名前を番号に戻す（各桁を 1〜26 として Horner 法）
long long from_name(const string& s) {
    long long v = 0;
    for (char c : s) v = v * 26 + (c - 'a' + 1);
    return v;
}
// --8<-- [end:core]

int main() {
    long long n;
    cin >> n;
    assert(n >= 1);
    string s = to_name(n);
    assert(from_name(s) == n);
    cout << s << '\n';
}
