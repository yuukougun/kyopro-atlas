#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    map<string, int> cnt{{"a", 1}, {"b", 2}};
    for (auto [k, v] : cnt) v *= 10;   // コピーを書き換えるだけ
    cout << cnt["a"] << ' ' << cnt["b"] << '\n';  // 1 2
    for (auto& [k, v] : cnt) v *= 10;  // map の値が変わる
    cout << cnt["a"] << ' ' << cnt["b"] << '\n';  // 10 20
    // --8<-- [end:core]
    for (auto [k, v] : cnt) static_assert(is_const_v<remove_reference_t<decltype(k)>>);
}
