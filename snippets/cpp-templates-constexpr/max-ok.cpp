#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a;
    int b;
    cin >> a >> b;
    // --8<-- [start:core]
    cout << max<long long>(a, b) << '\n';  // T を long long と明示する。b は long long に直される
    cout << max(a, (long long)b) << '\n';  // 型をそろえてから渡しても同じ
    cout << min({a, 3LL, (long long)b}) << '\n';  // 3 個以上は {} で渡す。中身の型もそろえる
    // --8<-- [end:core]
}
