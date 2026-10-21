#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    tuple<int, int, int> t{1, 2, 3};
    auto [_, x, _] = t;  // _ を 2 回：C++26。g++-15 は警告つきで通す
    // --8<-- [end:core]
    cout << x << '\n';
}
