#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    // 再帰より前の return 1LL で戻り値の型が long long に決まるので通る
    auto fact1 = [&](auto&& self, int n) {
        if (n == 0) return 1LL;
        return n * self(self, n - 1);
    };
    // 戻り値の型を書けば、三項演算子の中で再帰しても通る
    auto fact2 = [&](auto&& self, int n) -> long long {
        return n == 0 ? 1 : n * self(self, n - 1);
    };
    // --8<-- [end:core]
    cout << fact1(fact1, n) << ' ' << fact2(fact2, n) << '\n';
}
