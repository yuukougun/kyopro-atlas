// double の切り捨てで 1 ずれる例と、最も近い整数に丸めれば正しくなること。
#include <bits/stdc++.h>
using namespace std;

int main() {
    double b;
    cin >> b;  // 小数第 2 位までの数
    // --8<-- [start:core]
    long long ng = (long long)(b * 100);  // 2.51 * 100 = 250.99999999999997… を切り捨てて 250
    long long ok = llround(b * 100);      // 最も近い整数に丸めて 251
    // --8<-- [end:core]
    cout << ng << ' ' << ok << '\n';
}
