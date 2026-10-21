// −2 進法：N = Σ d_i (−2)^i（d_i は 0 か 1）と表す。N は負でもよい。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
string to_negabinary(long long n) {
    if (n == 0) return "0";
    string s;
    while (n != 0) {           // n が負のこともあるので「n > 0」ではない
        long long r = n % 2;   // C++ では n < 0 のとき −1 になりうる
        if (r < 0) r += 2;     // 余りを 0 か 1 に直す
        s += char('0' + r);
        n = (n - r) / (-2);    // n − r は −2 で割り切れる
    }
    reverse(s.begin(), s.end());
    return s;
}
// --8<-- [end:core]

int main() {
    long long n;
    cin >> n;
    string s = to_negabinary(n);
    long long v = 0;  // 確かめ：Horner 法で −2 進から戻す
    for (char c : s) v = v * (-2) + (c - '0');
    assert(v == n);
    cout << s << '\n';
}
