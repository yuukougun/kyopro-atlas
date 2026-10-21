#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class T, class U>
bool chmin(T& a, const U& b) {  // 型引数を 2 つにすると、a と b の型が違っても通る
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}
// --8<-- [end:core]

// --8<-- [start:identity]
template <class T>
bool chmin2(T& a, const type_identity_t<T>& b) {  // b からは T を推論しない（C++20）
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}
// --8<-- [end:identity]

int main() {
    long long a;
    cin >> a;
    // --8<-- [start:call]
    bool changed = chmin(a, 3);  // T = long long、U = int。3 は long long に直して比べる
    cout << changed << ' ' << a << '\n';
    // --8<-- [end:call]
    long long c = a + 5;
    chmin2(c, 0);  // T = long long に決まり、0 は long long に直される
    cout << c << '\n';
}
