#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class T>
void print(const T& x) {
    if (is_integral_v<T>) {  // constexpr のない if
        cout << x << '\n';
    } else {
        for (const auto& e : x) cout << e << ' ';  // T = int でもこの行がコンパイルされてエラー
        cout << '\n';
    }
}
// --8<-- [end:core]

int main() { print(3); }
