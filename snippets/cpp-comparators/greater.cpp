#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<long long> a = {3, 1, 2};
    // --8<-- [start:core]
    sort(a.begin(), a.end(), greater<long long>());  // 型を書く版
    sort(a.begin(), a.end(), greater<>());           // 型を省く版（greater<void>）
    sort(a.begin(), a.end(), greater{});             // CTAD で greater<void> になる
    static_assert(is_same_v<decltype(greater{}), greater<void>>);
    ranges::sort(a, greater{});                      // ranges::sort でも同じ
    // --8<-- [end:core]
    assert((a == vector<long long>{3, 2, 1}));

    // --8<-- [start:pitfall]
    vector<long long> b = {3000000000LL, 1, 2};
    sort(b.begin(), b.end(), greater<int>());  // 比べる前に int に変換される
    assert((b == vector<long long>{2, 1, 3000000000LL}));  // 3000000000 が負の int として比べられた
    sort(b.begin(), b.end(), greater<>());     // 元の型のまま比べる
    assert((b == vector<long long>{3000000000LL, 2, 1}));
    // --8<-- [end:pitfall]
    cout << "ok\n";
}
