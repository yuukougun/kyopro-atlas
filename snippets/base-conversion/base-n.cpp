// 基数の二分探索：数字列 x を n 進数（n は x の最大の数字 + 1 以上）とみた値のうち、
// m 以下になるものが何種類あるかを数える。値は n について単調増加なので二分探索する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    string x;
    long long m;
    cin >> x >> m;
    assert(!x.empty() && m >= 1);
    int d = 0;  // 最大の数字
    for (char c : x) d = max(d, c - '0');

    // --8<-- [start:core]
    if (x.size() == 1) {  // 1 桁なら値は n によらず x そのもの（1 種類か 0 種類）
        cout << (d <= m ? 1 : 0) << '\n';
        return 0;
    }
    // x を n 進数とみた値が m 以下か。掛ける前に割り算で比べ、あふれさせない
    auto fits = [&](long long n) -> bool {
        long long v = 0;
        for (char c : x) {
            int dig = c - '0';
            // v * n + dig <= m  ⇔  v <= (m - dig) / n（m - dig >= 0 のとき）
            if (dig > m || v > (m - dig) / n) return false;
            v = v * n + dig;
        }
        return true;
    };
    long long ok = d;                 // 番兵：n = d は数えない（d + 1 から有効）
    long long ng = max(m, (long long)d) + 1;  // 2 桁以上なら値は n 以上なので m を超える
    while (ng - ok > 1) {
        long long mid = ok + (ng - ok) / 2;
        if (fits(mid)) ok = mid;
        else ng = mid;
    }
    cout << ok - d << '\n';  // 有効な n は d + 1, …, ok
    // --8<-- [end:core]
}
