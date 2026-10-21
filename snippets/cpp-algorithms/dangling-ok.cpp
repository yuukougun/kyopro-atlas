#include <bits/stdc++.h>
using namespace std;

vector<int> make() { return {3, 1, 4}; }

int main() {
    // --8<-- [start:core]
    cout << ranges::max(make()) << '\n';  // 値を返すので一時オブジェクトでもよい
    auto v = make();                      // イテレータが欲しいなら変数に入れる
    auto it = ranges::max_element(v);
    cout << *it << ' ' << it - v.begin() << '\n';
    // --8<-- [end:core]
}
