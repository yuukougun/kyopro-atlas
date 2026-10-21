#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> seen;
    // --8<-- [start:core]
    if (auto [it, ok] = seen.insert(3)) {  // 構造化束縛そのものを条件にする（C++26）：pair は bool にならずエラー
        cout << *it << '\n';
    }
    // --8<-- [end:core]
}
