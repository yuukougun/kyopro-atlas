#include <bits/stdc++.h>
using namespace std;
int main() {
    // --8<-- [start:core]
    // GCC 14 から：deducing this・println・ranges::to
    auto sum = [](this auto&& self, int n) -> int { return n == 0 ? 0 : n + self(n - 1); };
    vector<int> v = views::iota(1, 4) | ranges::to<vector>();
    println("{}", sum(3));
    // GCC 15 から：範囲の書式化・from_range・flat_map
    set<int> s(from_range, v);
    flat_map<int, int> m;
    m[2] = 5;
    println("{} {} {}", v, s.size(), m[2]);
    // --8<-- [end:core]
}
