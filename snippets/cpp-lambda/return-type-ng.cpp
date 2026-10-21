#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    auto fact = [&](auto&& self, int n) {  // -> long long がない
        return n == 0 ? 1LL : n * self(self, n - 1);  // 型が決まる前に self を呼ぶのでエラー
    };
    // --8<-- [end:core]
    cout << fact(fact, 5) << '\n';
}
