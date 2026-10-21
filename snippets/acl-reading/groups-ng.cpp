#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;
using namespace atcoder;

int main() {
    dsu d(4);
    d.merge(0, 2);
    // --8<-- [start:core]
    for (int v : d.groups()[0]) cout << v << ' ';  // C++23（GCC 15〜）より前では壊れた vector を読む
    // --8<-- [end:core]
    cout << '\n';
}
