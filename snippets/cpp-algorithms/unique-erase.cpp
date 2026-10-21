#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    // --8<-- [start:core]
    sort(v.begin(), v.end());                 // 等しい値を隣り合わせる
    auto it = unique(v.begin(), v.end());     // 重複を前に詰め、新しい終端を返す
    cout << v.size() << ' ' << (it - v.begin()) << '\n';  // 大きさはまだ n のまま
    v.erase(it, v.end());                     // 後ろの不要部分を消す
    // --8<-- [end:core]
    assert(is_sorted(v.begin(), v.end()) && adjacent_find(v.begin(), v.end()) == v.end());  // 重複が残っていない
    cout << v.size() << '\n';
    for (int x : v) cout << x << ' ';
    cout << '\n';
}
