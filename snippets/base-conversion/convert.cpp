// b 進表記への変換（下の桁から余りを積む）と、Horner 法による復元。
// 入力：N（0 以上）と基数 b（2 ≤ b ≤ 36）。出力：N の b 進表記。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 0 以上の n を b 進表記の文字列にする（10 以上の数字は 'A', 'B', … で表す）
string to_base(long long n, int b) {
    if (n == 0) return "0";  // ループが 1 回も回らず空文字列になるのを防ぐ
    string s;
    while (n > 0) {
        int d = n % b;  // いちばん下の桁
        s += (d < 10 ? char('0' + d) : char('A' + d - 10));
        n /= b;         // 残りの桁を 1 つ右へずらす
    }
    reverse(s.begin(), s.end());  // 下の桁から積んだので逆順に直す
    return s;
}

// b 進表記の文字列を数に戻す（Horner 法：上の桁から v = v * b + d）
long long from_base(const string& s, int b) {
    long long v = 0;
    for (char c : s) {
        int d = isdigit(c) ? c - '0' : c - 'A' + 10;
        v = v * b + d;
    }
    return v;
}
// --8<-- [end:core]

int main() {
    long long n;
    int b;
    cin >> n >> b;
    assert(n >= 0 && 2 <= b && b <= 36);
    string s = to_base(n, b);
    assert(from_base(s, b) == n);  // 往復で元に戻る
    cout << s << '\n';
}
