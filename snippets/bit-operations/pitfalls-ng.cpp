#include <bits/stdc++.h>
using namespace std;

// 落とし穴の実例（C++20 以降は、どの行も値が決まっている）
int main() {
    long long b = 1 << 31;        // int で計算してから広げるので負になる
    long long c = 1LL << 31;      // 正しい
    long long y = (1LL << 40) | 1;
    int p = __builtin_popcount(y);   // unsigned int に切り詰められ、bit 40 が消える
    int q = __builtin_popcountll(y); // 正しい
    cout << b << ' ' << c << '\n';
    cout << p << ' ' << q << '\n';
    cout << (-7 >> 1) << ' ' << (-7 / 2) << '\n';  // 右シフトは下へ丸め、割り算は 0 へ丸める
}
