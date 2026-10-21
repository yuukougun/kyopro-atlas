// 10^18 規模の積の差を double で計算すると、正しい値 -1 が 0 になる例。
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    // --8<-- [start:core]
    double ng = (double)y1 * x2 - (double)x1 * y2;  // 積が 10^18 規模だと、隣の double との間隔は 128
    long long ok = y1 * x2 - x1 * y2;               // 各積は 10^18 以下なので long long で正確
    // --8<-- [end:core]
    cout << (long long)ng << ' ' << ok << '\n';
}
