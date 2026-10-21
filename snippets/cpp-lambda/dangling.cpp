#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:bad]
// 呼ぶと壊れる：k はこの関数を出ると消えるのに、返すラムダは k を参照したまま
auto make_adder_bad(int k) {
    return [&](int x) { return x + k; };
}
// --8<-- [end:bad]

// --8<-- [start:good]
// 安全：k をコピーで持つので、関数を出た後も使える
auto make_adder(int k) {
    return [=](int x) { return x + k; };
}
// --8<-- [end:good]

int main() {
    auto f = make_adder(5);
    cout << f(1) << '\n';
    (void)&make_adder_bad;
}
