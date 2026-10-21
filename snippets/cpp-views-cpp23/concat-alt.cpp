#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a{1, 2}, b{3};
    // --8<-- [start:core]
    // C++23 でつなげて回すなら：範囲の範囲を作って join する
    for (int x : array{views::all(a), views::all(b)} | views::join) cout << x;
    // --8<-- [end:core]
    cout << '\n';
}
