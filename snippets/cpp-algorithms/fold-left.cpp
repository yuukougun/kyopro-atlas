#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> v(n);
    for (auto& e : v) cin >> e;
    // --8<-- [start:core]
    cout << ranges::fold_left(v, 0LL, plus{}) << '\n';  // 初期値 0LL の型で左から畳む
    cout << ranges::contains(v, x) << '\n';             // ranges::find(v, x) != v.end() と同じ
    auto r = ranges::find_last(v, x);                   // 最後の x から末尾までの subrange
    cout << (r.begin() == v.end() ? -1 : r.begin() - v.begin()) << '\n';  // 最後の x の添字
    // --8<-- [end:core]
}
