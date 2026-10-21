#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    int k = 10;
    auto by_ref = [&] { return k + 1; };   // k への参照を持つ
    auto by_copy = [=] { return k + 1; };  // 作った時点の k（10）のコピーを持つ
    k = 20;
    cout << by_ref() << ' ' << by_copy() << '\n';  // 21 11
    // --8<-- [end:core]
    assert(by_ref() == 21 && by_copy() == 11);

    // --8<-- [start:init]
    vector<int> v = {3, 1, 4};
    auto owner = [w = std::move(v)] { return w.size(); };  // v の中身をラムダの中へ移す（コピーしない）
    int cnt = 0;
    auto counter = [cnt]() mutable { return ++cnt; };  // コピーした cnt を中で書き換える
    counter();
    counter();
    cout << owner() << ' ' << counter() << ' ' << cnt << '\n';  // 3 3 0（外の cnt は 0 のまま）
    // --8<-- [end:init]
}
