#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:func]
// 昇順の a の中で x 以上の最小の値。なければ nullopt
optional<int> ceil_value(const vector<int>& a, int x) {
    auto it = lower_bound(a.begin(), a.end(), x);
    if (it == a.end()) return nullopt;
    return *it;
}
// --8<-- [end:func]

int main() {
    vector<int> a{2, 5, 8};
    // --8<-- [start:core]
    if (auto r = ceil_value(a, 4)) cout << *r << '\n';  // 値があるときだけ入る：5
    auto s = ceil_value(a, 9);
    cout << s.has_value() << ' ' << s.value_or(-1) << '\n';  // 0 -1
    // --8<-- [end:core]
    assert(!ceil_value({}, 0));
}
