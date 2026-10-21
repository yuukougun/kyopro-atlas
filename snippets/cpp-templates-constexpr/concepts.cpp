#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <integral T>  // T は整数型に限る
T floor_div(T a, T b) {  // a / b の切り捨て（b > 0）。負の a でも下に丸める
    return a / b - (a % b != 0 && a < 0);
}

template <class T>
    requires integral<T>  // 上と同じ制限を requires 節で書く
T ceil_div(T a, T b) {  // a / b の切り上げ（b > 0）
    return a / b + (a % b != 0 && a > 0);
}

auto half(integral auto x) { return x / 2; }  // auto 引数にも付けられる
// --8<-- [end:core]

int main() {
    long long a, b;
    cin >> a >> b;
    cout << floor_div(a, b) << ' ' << ceil_div(a, b) << ' ' << half(a) << '\n';
}
