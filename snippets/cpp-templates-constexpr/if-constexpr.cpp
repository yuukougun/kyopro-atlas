#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class T>
void print(const T& x) {
    if constexpr (is_integral_v<T> || is_floating_point_v<T>) {
        cout << x << '\n';  // 数なら 1 つ出す
    } else {
        for (const auto& e : x) cout << e << ' ';  // それ以外は範囲として要素を並べる
        cout << '\n';
    }
}
// --8<-- [end:core]

int main() {
    // --8<-- [start:assert]
    static_assert(sizeof(long long) == 8, "long long は 64 bit のはず");
    static_assert(numeric_limits<int>::max() == 2147483647);  // メッセージは省ける（C++17）
    // --8<-- [end:assert]
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    print(n);
    print(v);
}
