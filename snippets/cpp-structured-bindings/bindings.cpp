#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:edge]
struct Edge {
    int to;
    long long cost;
};
// --8<-- [end:edge]

int main() {
    // --8<-- [start:core]
    pair<int, int> p{1, 2};
    auto [a, b] = p;               // a = 1, b = 2

    vector<Edge> es{{3, 10}, {4, 20}};
    for (auto [to, cost] : es) cout << to << ':' << cost << ' ';
    cout << '\n';                  // 3:10 4:20

    array<int, 3> arr{7, 8, 9};
    auto [x, y, z] = arr;          // array も C の配列 int c[3] も分けられる

    map<string, int> mp{{"a", 1}, {"b", 2}};
    for (const auto& [k, v] : mp) cout << k << '=' << v << ' ';
    cout << '\n';                  // a=1 b=2
    // --8<-- [end:core]
    int c[2] = {5, 6};
    auto [c0, c1] = c;
    assert(a + b == 3 && x + y + z == 24 && c0 + c1 == 11);
}
