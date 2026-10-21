#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {1, 1, 2};
    // --8<-- [start:core]
    int best = 0;
    best = max(best, ranges::count(v, 1));  // int と ptrdiff_t：コンパイルエラー
    // 直し方：max(best, (int)ranges::count(v, 1))
    // --8<-- [end:core]
    cout << best << '\n';
}
