#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x;
    cin >> x;
    // --8<-- [start:core]
    int a = __builtin_popcountll(x);          // long long の 1 の個数（int なら __builtin_popcount）
    int b = __builtin_popcount(x);            // 誤り：unsigned int に変換され、上位 32 桁が消える
    if (x != 0) {                             // 以下の 3 つは x = 0 だと未定義
        int tz = __builtin_ctzll(x);          // 下から続く 0 の個数
        int hi = 63 - __builtin_clzll(x);     // 最上位の 1 の位置
        int lg = __lg(x);                     // 同じく最上位の 1 の位置（⌊log2 x⌋）
        cout << tz << ' ' << hi << ' ' << lg << '\n';
    }
    // --8<-- [end:core]
    cout << a << ' ' << b << '\n';
}
