#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned x;
    cin >> x;
    // --8<-- [start:core]
    int pc = popcount(x);         // 1 の個数
    int tz = countr_zero(x);      // 下から続く 0 の個数（x = 0 なら 32）
    int lz = countl_zero(x);      // 上から続く 0 の個数（unsigned は 32 桁）
    int bw = bit_width(x);        // 2 進表記の桁数。x > 0 なら bw - 1 が最上位の 1 の位置
    unsigned c = bit_ceil(x);     // x 以上の最小の 2 のべき乗（x = 0 なら 1）
    unsigned f = bit_floor(x);    // x 以下の最大の 2 のべき乗（x = 0 なら 0）
    bool one = has_single_bit(x); // 2 のべき乗か（1 がちょうど 1 個か）
    // --8<-- [end:core]
    cout << pc << ' ' << tz << ' ' << lz << ' ' << bw << ' ' << c << ' ' << f << ' ' << one << '\n';
}
